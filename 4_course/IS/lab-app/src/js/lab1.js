function getCipher(text) {
    // System.Console.WriteLine((int)'A'); // выдаст 65
    // System.Console.WriteLine((char)65); // Выдаст A

    const cipher_cod = text.split('').map(ch => ch.charCodeAt(0) + text.length)
    const cipher = cipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`cipher_cod ${cipher_cod}`);
    return cipher
}

function getDecipher(text) {
    const decipher_cod = text.split('').map(ch => ch.charCodeAt(0) - text.length)
    const decipher = decipher_cod.map(kod => String.fromCharCode(kod)).join('')
    console.log(`decipher_cod ${decipher_cod}`);
    return decipher
}

var cipher = document.getElementById('cipher')
cipher.onclick = () => {
    const text = document.getElementById("text")
    const text_cipher = getCipher(text.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

var decipher = document.getElementById('decipher')
decipher.onclick = () => {
    const text = document.getElementById("text")
    const text_cipher = getDecipher(text.value)
    const textarea_result = document.getElementById('result')
    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

var text_input = document.getElementById('text')
text_input.ondblclick = () => text_input.value = null
text_input.oncontextmenu = () => navigator.clipboard.readText().then(text => text_input.value = text)

var next = document.getElementById('next')
next.onclick = () => change_content(2)