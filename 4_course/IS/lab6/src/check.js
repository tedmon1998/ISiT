var path = require('path')
var full_path_file = path.join(path.resolve(), 'pc_info.json')
var fs = require('fs')
var cryptos = require('crypto')
var info = require('os').networkInterfaces()
var id = info[Object.keys(info)[0]][0].address

var h1 = document.getElementById('root')

var hash = cryptos.createHash('sha1').update(id).digest("utf8")
if (fs.existsSync(full_path_file) && fs.statSync(full_path_file).size > 0) {
    var info_hash = JSON.parse(fs.readFileSync('pc_info.json').toString()).ip
    if (info_hash !== hash) {
        h1.innerText = `Использование данного ПО яв-ся не законным`
        alert(`Использование данного ПО яв-ся не законным`)
    }
    h1.innerText = `Добро пожаловать: ${id}`
}
else {
    h1.innerText = `Добро пожаловать: ${id}`
    fs.writeFileSync('pc_info.json', JSON.stringify({ ip: hash }))
}

