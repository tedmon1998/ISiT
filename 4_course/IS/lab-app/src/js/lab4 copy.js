var el_gamal = require('./src/js/el_gamal')

var gamal = new el_gamal.ElGamal()

function getDecipher(ctext, close_key) {
    let sum_key = 0
    close_key.split('').map(char => sum_key += char.charCodeAt(0))
    const ctext_list = ctext.split('').map(char => char.charCodeAt(0))
    const [open_key, result] = gamal.decipher(sum_key, ctext_list)
    console.log(`open_key ${open_key}`);
    console.log(`result ${result}`);
    return [open_key, result.map(item => String.fromCharCode(Number(item))).join('')];
}

function getCipher(clear, close_key) {
    let sum_key = 0
    close_key.split('').map(char => sum_key += char.charCodeAt(0))
    const clear_list = clear.split('').map(char => char.charCodeAt(0))
    console.log(`sum_key ${sum_key}`);
    console.log(`clear_list ${clear_list}`);
    const [open_key, result] = gamal.cipher(sum_key, clear_list)
    console.log(`open_key ${open_key}`);
    console.log(`result ${result}`);
    return [open_key, result.map(item => String.fromCharCode(Number(item))).join('')];
}
// Edmon Tunyan Garnikovich  g Vanadzor 1998 test cipher
// Эдмон Тунян Гарникович г Ванадзор 1998 тест шифр

var cipher = document.getElementById('cipher')
cipher.onclick = () => {
    const open_key_el = document.getElementById("open_key")
    const close_key = document.getElementById("close_key")
    const text = document.getElementById("text")
    const [open_key, text_cipher] = getCipher(text.value, close_key.value)
    open_key_el.value = open_key
    const textarea_result = document.getElementById('result')

    textarea_result.placeholder = text_cipher
    navigator.clipboard.writeText(text_cipher)
}

var decipher = document.getElementById('decipher')
decipher.onclick = () => {
    const open_key_el = document.getElementById("open_key")
    const close_key = document.getElementById("close_key")
    const ctext = document.getElementById("text")
    const [open_key, text_cipher] = getDecipher(ctext.value, close_key.value)
    const textarea_result = document.getElementById('result')
    if (parseInt(open_key_el.value) === open_key) {
        textarea_result.placeholder = text_cipher
    }
    else {
        textarea_result.placeholder = "Сообщение подделано!!!"
    }
    navigator.clipboard.writeText(text_cipher)
}

var text_input = document.getElementById('text')
text_input.ondblclick = () => text_input.value = null
text_input.oncontextmenu = () => navigator.clipboard.readText().then(text => text_input.value = text)

var open_key = document.getElementById('open_key')
open_key.ondblclick = () => open_key.value = null
open_key.oncontextmenu = () => navigator.clipboard.readText().then(text => open_key.value = text)

var close_key = document.getElementById('close_key')
close_key.ondblclick = () => close_key.value = null
close_key.oncontextmenu = () => navigator.clipboard.readText().then(text => close_key.value = text)


var next = document.getElementById('next')
next.onclick = () => change_content(4)

var previous = document.getElementById('previous')
previous.onclick = () => change_content('3_1')