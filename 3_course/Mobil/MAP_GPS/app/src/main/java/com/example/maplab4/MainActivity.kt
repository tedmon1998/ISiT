package com.example.maplab4

import android.Manifest
import android.annotation.SuppressLint
import android.content.SharedPreferences
import android.content.pm.PackageManager
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.os.Bundle
import android.os.PersistableBundle
import android.util.Log
import android.view.ActionMode
import android.view.animation.Animation
import android.view.animation.RotateAnimation
import android.widget.Toast
import androidx.annotation.NonNull
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.example.maplab4.constance.Constance
import com.example.maplab4.databinding.ActivityMainBinding
import com.google.android.gms.maps.*
import com.google.android.gms.maps.model.*


class MainActivity : AppCompatActivity(), OnMapReadyCallback, SensorEventListener {

    // for activity
    private lateinit var bs: ActivityMainBinding
    // for GPS
    private lateinit var locationManager: LocationManager
    // for Map
    private lateinit var MAP: GoogleMap
    private var mType: Array<Int> = arrayOf(GoogleMap.MAP_TYPE_NORMAL, GoogleMap.MAP_TYPE_SATELLITE, GoogleMap.MAP_TYPE_TERRAIN, GoogleMap.MAP_TYPE_HYBRID)
    private var countTipe = 0
    private lateinit var POSITION : MarkerOptions
    private lateinit var MARKER : Marker
    // for preferences
    private lateinit var sPref: SharedPreferences
    // for compass
    private var mGravity = FloatArray(3)
    private var mGeomagnetic = FloatArray(3)
    private var azimuth : Float = 0f
    private var currectAzimuth : Float = 0f
    private lateinit var mSensorManager : SensorManager




    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        bs = ActivityMainBinding.inflate(layoutInflater)
        setContentView(bs.root)

        val mapFragment = supportFragmentManager
            .findFragmentById(R.id.map) as SupportMapFragment
        mapFragment.getMapAsync(this)


        bs.button.setOnClickListener {
            MAP.mapType = mType[countTipe]
            if (countTipe != (mType.size)-1)
                countTipe++
            else
                countTipe = 0
            //Log.d("err ", countTipe.toString())
            //Log.d("mType.size ", mType.size.toString())
        }
        locationManager = getSystemService(LOCATION_SERVICE) as LocationManager

        // for compass
        mSensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
    }


    @SuppressLint("ServiceCast", "MissingPermission")
    override fun onResume() {
        super.onResume()
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            Toast.makeText(applicationContext, "Есть подключение", Toast.LENGTH_LONG).show()

            if(locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER))
            {
                Toast.makeText(applicationContext, "GPS ON", Toast.LENGTH_LONG).show()
                locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER,
                    1000 * 1, 0.5f, locationListener)
                locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER,
                    1000*1, 0.5f, locationListener) // type, time (coordinate update), distance, listener
                chechkEnabled()
            }
            else
            {
                Toast.makeText(applicationContext, "GPS OFF", Toast.LENGTH_LONG).show()
            }
        }
        else
        {
            Toast.makeText(applicationContext, "Нет подключение", Toast.LENGTH_LONG).show()
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), 1
            )
        }
        chechkAccess()

        // for compass
        mSensorManager.registerListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
            SensorManager.SENSOR_DELAY_GAME)
        mSensorManager.registerListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
            SensorManager.SENSOR_DELAY_GAME)
    }

    @SuppressLint("CommitPrefEdits")
    override fun onDestroy() {
        super.onDestroy()
        sPref = getSharedPreferences("MapLab4", MODE_PRIVATE)
        val ed = sPref.edit()
        ed.putFloat(Constance.LATITUDE, MARKER.position.latitude.toFloat())
        ed.putFloat(Constance.LONGITUDE, MARKER.position.longitude.toFloat())
        ed.putInt(Constance.MAPTYPE, countTipe)
        ed.apply()
    }

    @SuppressLint("MissingPermission")
    override fun onPause() {
        super.onPause()
        locationManager.removeUpdates(locationListener)
        // for compass
        mSensorManager.unregisterListener(this)
    }

    override fun onSensorChanged(p0: SensorEvent?) {
        val alpha : Float = 0.97f
        synchronized(this) {
            if (p0 != null) {
                if (p0.sensor.type == Sensor.TYPE_ACCELEROMETER) {
                    mGravity[0] = alpha*mGravity[0] + (1-alpha)*p0.values[0]
                    mGravity[1] = alpha*mGravity[1] + (1-alpha)*p0.values[1]
                    mGravity[2] = alpha*mGravity[2] + (1-alpha)*p0.values[2]
                }
                if (p0.sensor.type == Sensor.TYPE_MAGNETIC_FIELD)
                {
                    if (p0 != null) {
                        mGeomagnetic[0] = alpha*mGeomagnetic[0] + (1-alpha)*p0.values[0]
                        mGeomagnetic[1] = alpha*mGeomagnetic[1] + (1-alpha)*p0.values[1]
                        mGeomagnetic[2] = alpha*mGeomagnetic[2] + (1-alpha)*p0.values[2]
                    }
                }
            }
            var R = FloatArray(9)
            var I = FloatArray(9)
            val success : Boolean = SensorManager.getRotationMatrix(R, I, mGravity, mGeomagnetic)
            if(success)
            {
                var orientation = FloatArray(3)
                SensorManager.getOrientation(R, orientation)
                azimuth = Math.toDegrees(orientation[0].toDouble()).toFloat()
                azimuth = (azimuth+360)%360

                val anim : Animation = RotateAnimation(-currectAzimuth, -azimuth, Animation.RELATIVE_TO_SELF, 0.5f, Animation.RELATIVE_TO_SELF, 0.5f)
                currectAzimuth = azimuth

                anim.duration = 500
                anim.repeatCount = 0
                anim.fillAfter = true

                bs.compass.startAnimation(anim)
            }
        }
    }

    override fun onAccuracyChanged(p0: Sensor?, p1: Int) {
    }


    var locationListener = object: LocationListener
    {
        override fun onLocationChanged(location: Location) {
            showLocation(location)
        }

        @SuppressLint("MissingPermission")
        override fun onProviderEnabled(provider: String) {
            chechkEnabled()
            locationManager.getLastKnownLocation(provider)
        }

        @SuppressLint("SetTextI18n")
        override fun onStatusChanged(provider: String?, status: Int, extras: Bundle?) {
            if(provider.equals(LocationManager.GPS_PROVIDER))
            {
                bs.idGps.text = "Status $status.toString()"
            }
            else if(provider.equals(LocationManager.NETWORK_PROVIDER))
            {
                bs.idNetwork.text = "Status $status.toString()"
            }
        }

        override fun onProviderDisabled(provider: String) {
            Toast.makeText(applicationContext,"onProviderDisabled", Toast.LENGTH_LONG).show()

        }

    }

    @SuppressLint("SetTextI18n")
    private fun showLocation(location: Location)
    {
        if(location == null) {
            return
        }
        if(location.provider.equals(LocationManager.GPS_PROVIDER))
        {
            positionChange(location)
            bs.idData.text = "GPS"
        }
        else if(location.provider.equals(LocationManager.NETWORK_PROVIDER))
        {
            bs.idData.text = "NETWORK"
        }
    }

    @SuppressLint("SetTextI18n")
    private fun chechkEnabled() {
        bs.idGps.text = "Enabled ${locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)}"
        bs.idNetwork.text = "Enabled ${locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER)}"
    }

    override fun onMapReady(googleMap: GoogleMap) {
        MAP = googleMap

        sPref = getSharedPreferences("MapLab4", MODE_PRIVATE)
        val x = sPref.getFloat(Constance.LATITUDE, 0.0f)
        val y = sPref.getFloat(Constance.LONGITUDE, 0.0f)

        val pos = if(x != 0.0f && y != 0.0f)
            LatLng(x.toDouble(), y.toDouble())
        else
            LatLng(-34.0, 151.0)

        POSITION = MarkerOptions().position(pos)

        MARKER = MAP.addMarker(MarkerOptions().position(pos).icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN)))
        MARKER.title = "Я тут"
        MAP.moveCamera(CameraUpdateFactory.newLatLng(pos))

        zoomCam(pos)
    }

    private fun positionChange(location: Location)
    {
        bs.idLatitude.text = location.latitude.toString()
        bs.idLongitude.text = location.longitude.toString()

        MARKER.position = LatLng(location.latitude, location.longitude)
        MAP.moveCamera(CameraUpdateFactory.newLatLng(LatLng(location.latitude, location.longitude)))
    }

    private fun zoomCam(pos: LatLng){
        sPref = getSharedPreferences("MapLab4", MODE_PRIVATE)
        countTipe = sPref.getInt(Constance.MAPTYPE, 0)
        MAP.mapType = mType[countTipe]

        val cameraPosition: CameraPosition = CameraPosition.Builder()
            .target(pos).zoom(20.0F).bearing(0.0F).tilt(20.0F).build()
        val cameraUpdate: CameraUpdate = CameraUpdateFactory.newCameraPosition(cameraPosition)
        MAP.animateCamera(cameraUpdate)
    }

    private fun chechkAccess()
    {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_DENIED)
        {
            Toast.makeText(applicationContext, "Нет доступа к вашему расположению", Toast.LENGTH_LONG).show()
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_COARSE_LOCATION), 1
            )
        }
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_NETWORK_STATE) == PackageManager.PERMISSION_DENIED)
        {
            Toast.makeText(applicationContext, "Нет доступа к статусу вашего интернета", Toast.LENGTH_LONG).show()
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_NETWORK_STATE), 1
            )
        }
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.INTERNET) == PackageManager.PERMISSION_DENIED)
        {
            Toast.makeText(applicationContext, "Нет интернета", Toast.LENGTH_LONG).show()
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.INTERNET), 1
            )
        }
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED)
        {
            Toast.makeText(applicationContext, "Нет доступа к записи внешнего хранилища", Toast.LENGTH_LONG).show()
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE), 1
            )
        }
    }
}