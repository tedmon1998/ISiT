document.addEventListener('click', function (e) {
    // получим элемент
    const el = e.target.closest('.nav__link');
    // проверим присутствие элемента
    if (el) {
        el.classList.toggle('active');
    }
})