var gost89 = require("./src/js/gost89")

var gost = gost89.init

// var ci = gost.crypt_cfb('pas', 'test')
// console.log(`crypt_cfb ${ci}`);

// console.log(`ci ${JSON.stringify(ci)}`);
// console.log(`Buffer.from('ãi¤»') ${JSON.stringify(Buffer.from(ci.toString('binary'), 'binary'))}`);


// var dci = gost.decrypt_cfb('pas', ci)
// console.log(`decrypt_cfb ${dci}`);

function getDecipher(ctext, iv) {
    Buffer.from(ctext, 'binary')
    ctext = gost.decrypt_cfb(iv.split(''), ctext).toString()
    ctext = ctext.split('|').map(ch => String.fromCharCode(ch)).join('')
    return ctext
}

function getCipher(clear, iv) {
    clear = clear.split('').map(ch => ch.charCodeAt(0)).join('|')
    var ctext = gost.crypt_cfb(iv.split(''), clear)
    return ctext.toString('binary');
}
// Edmon Tunyan Garnikovich  g Vanadzor 1998 test cipher
// Эдмон Тунян Гарникович г Ванадзор 1998 тест шифр

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
next.onclick = () => change_content(4)

var previous = document.getElementById('previous')
previous.onclick = () => change_content('3_1')