function sumList(lsit) {
    let sum = 0
    for (const item of lsit) {
        sum += parseInt(item)
    }
    return sum
}
function getCipher(text, token) {
    token = token.split('').map(ch => ch.charCodeAt(0))
    let count = 0
    const cipher_cod = text.split('').map(ch => {
        const _temp_token = token[count].toString().split('')
        const result = ch.charCodeAt(0) + sumList(_temp_token)
        count + 1 === token.length ? count = 0 : count += 1
        return result
    })
    const cipher = cipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`cipher_cod ${cipher_cod}`);
    return cipher
}

function getDecipher(text, token) {
    token = token.split('').map(ch => ch.charCodeAt(0))
    let count = 0
    const decipher_cod = text.split('').map(ch => {
        const _temp_token = token[count].toString().split('')
        const result = ch.charCodeAt(0) - sumList(_temp_token)
        count + 1 === token.length ? count = 0 : count += 1
        return result
    })
    const decipher = decipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`decipher_cod ${decipher_cod}`);
    return decipher
}

var cipher = document.getElementById('cipher')
cipher.onclick = () => {
    const token = document.getElementById("token")
    const text = document.getElementById("text")
    const text_cipher = getCipher(text.value, token.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

var decipher = document.getElementById('decipher')
decipher.onclick = () => {
    const token = document.getElementById("token")
    const text = document.getElementById("text")
    const text_cipher = getDecipher(text.value, token.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

var token_input = document.getElementById('token')
token_input.ondblclick = () => token_input.value = null
token_input.oncontextmenu = () => navigator.clipboard.readText().then(text => token_input.value = text)
var text_input = document.getElementById('text')
text_input.ondblclick = () => text_input.value = null
text_input.oncontextmenu = () => navigator.clipboard.readText().then(text => text_input.value = text)

var next = document.getElementById('next')
next.onclick = () => change_content('3_1')

var previous = document.getElementById('previous')
previous.onclick = () => change_content(1)