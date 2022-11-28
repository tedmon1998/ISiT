// let LIST = []

function getCipher(text) {
    // LIST = []
    // function random() {
    //     const num = Math.floor(Math.random() * 17)
    //     LIST.push(num)
    //     return num
    // }
    // const cipher_cod = text.split('').map(ch => ch.charCodeAt(0) + random())
    const cipher_cod = text.split('').map(ch => ch.charCodeAt(0) + text.length)
    const cipher = cipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`cipher_cod ${cipher_cod}`);
    return cipher
}

function getDecipher(text) {
    // const decipher_cod = text.split('').map(ch => ch.charCodeAt(0) - LIST.shift())
    const decipher_cod = text.split('').map(ch => ch.charCodeAt(0) - text.length)
    const decipher = decipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`decipher_cod ${decipher_cod}`);
    return decipher
}

const cipher = document.getElementById('cipher')
cipher.onclick = () => {
    const text = document.getElementById("text")
    const text_cipher = getCipher(text.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

const decipher = document.getElementById('decipher')
decipher.onclick = () => {
    const text = document.getElementById("text")
    const text_cipher = getDecipher(text.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

const text_input = document.getElementById('text')
text_input.ondblclick = () => clipboard.value = null
text_input.oncontextmenu = () => navigator.clipboard.readText().then(text => text_input.value = text)


const next = document.getElementById('next')
next.onclick = () => {
    window.location.href = './lab2.html'
}
