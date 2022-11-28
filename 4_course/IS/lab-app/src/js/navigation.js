const $ = require("jquery");

$(document).ready(function () {
    $("#content").load("src/pages/lab1.html")
})

function change_content(N) {
    $("#content").load(`src/pages/lab${N}.html`)
    document.getElementById('title').innerHTML = `Лабораторная работа № ${N}`
}
