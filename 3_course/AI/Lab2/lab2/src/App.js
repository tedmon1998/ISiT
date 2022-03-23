import { useEffect, useState, useRef } from "react";
import { category, default_value, regulation } from "./components/data";
import './styles/css/app.css'
import data_file from "./components/data_file.json";

function App() {

  const [regulations, setRegulations] = useState("")
  const [count, setCount] = useState(0)
  const [newFact, setNewFact] = useState({})

  const inputAb = useRef()
  const inputValue = useRef()
  const inputAnswer = useRef()

  const [newAnsewerDefault, setNewAnsewerDefault] = useState([])
  const [newAnsewerUser, setNewAnsewerUser] = useState([])
  const [newAnsewerApp, setNewAnsewerApp] = useState([])

  const [newVar, setNewVar] = useState("")

  useEffect(() => {
    const arr = []
    regulation.forEach(array => {
      Object.keys(array).forEach(element => {
        arr.push(<h3 key={Math.random()}>{element} : {array[element]}</h3>)
      })
      arr.push(<h3 key={Math.random()}>--------------</h3>)
    })
    setRegulations(arr)
  }, [])


  const seatchKey = (param) => {
    /**
     * function takes a key as a parameter and
     * return index of the regulation that conains this key
     */

    const [key, value] = Object.entries(param)[0]
    for (let i = 0; i < regulation.length; i++) {
      const arrKeyRegulations = Object.keys(regulation[i])
      if (arrKeyRegulations.findIndex(e => e == key) !== -1) {
        const result = regulation[i]
        regulation.splice(i, 1)
        if (result[key] === parseInt(value)) return result
      }
    }
    return false
  }

  const getType = (ab) => {
    /**
     * function takes anabbreviation as a parameter and 
     * returns type of abbreviation
     */

    const index = category.findIndex(el => Object.values(el).toString() === ab.toString())
    return index > -1 ? Object.keys(category[index]).toString() : false
  }

  const searchRegulations = (arrKeys) => {
    /**
     * function takes an array of objects as a parameter and 
     * returns number (index) of the regulation that contains this key(s)
    */

    data_file.forEach(el => console.log(`test ${Object.keys(el)}`))
    for (let key of arrKeys) {
      const res = Object.keys(seatchKey(key)).filter(e => e !== Object.keys(key).toString())

      if (res) {
        for (const k of res) {
          const tk = k;
          const ty = getType(k)

          if (getType(k) === "user") {
            setNewVar(
              <div className="center">
                <h1>Ответьте пожалуйста на вопрос</h1>
                <h3>{k}</h3>
                <h2 className="abTitle">
                  <input placeholder={"введите ответ"} ref={inputAnswer} />
                  <button onClick={() => calculate({ user: k })} >+</button>
                </h2>
              </div>
            )
          }
          else {
            console.log(`res ${k} ${res[k]}`)
            calculate({ app: { [k]: res[k] } })
          }
          break
        }
      }
      break
    }
  }

  const calculate = (params = false) => {
    const ab = params.user ? params.user : params.app ? Object.keys(params.app) : inputAb.current.value.toUpperCase()
    const val = params.user ? inputAnswer.current.value : params.app ? Object.values(params.app) : inputValue.current.value

    console.clear()
    data_file.push({ [ab]: val })

    const typ = params.user ? "user" : params.app ? "app" : "default"

    switch (typ) {
      case "default":
        setNewAnsewerDefault([...newAnsewerDefault, <h3 key={Math.random()}>{ab}</h3>])
        break;
      case "user":
        setNewAnsewerUser([...newAnsewerUser, <h3 key={Math.random()}>{ab}</h3>])
        break;
      case "app":
        setNewAnsewerApp([...newAnsewerApp, <h3 key={Math.random()}>{ab}</h3>])
        break;
    }



    newAnsewerDefault.length >= 1 && searchRegulations(data_file)
    !params && (inputAb.current.value = "")
    params.user ? inputAnswer.current.value = "" : !params.app && (inputValue.current.value = "")
  }


  return (
    <div className="app">
      {data_file.length < 2 &&
        <div className="center">
          <h1>Аб - аббревиатура, значение - (0/1)</h1>
          <h2>{default_value[count]}</h2>
          <h2 className="abTitle">
            <input placeholder="Аб." className="ab" ref={inputAb} />
            <input placeholder={"значение"} ref={inputValue} />
            <button onClick={() => calculate()} >+</button>
          </h2>
        </div>
      }
      {data_file.length >= 2 &&
        newVar && newVar
      }
      {
        newAnsewerDefault.length > 0 && (
          <div className="center">
            <h2>Значение по умолчанию:</h2>
            {newAnsewerDefault}
          </div>
        )
      }
      {
        newAnsewerUser.length > 0 && (
          <div className="center">
            <h2>Значение выбранные пользователем:</h2>
            {newAnsewerUser}
          </div>
        )
      }
      {
        newAnsewerApp.length > 0 && (
          <div className="center">
            <h2>Значение выданные системой:</h2>
            {newAnsewerApp}
          </div>
        )
      }
    </div>
  );
}

export default App;
