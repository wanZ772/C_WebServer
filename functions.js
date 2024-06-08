function load_seats()   {
    alert(1);
    for (i = 0; i < 5; i++) {
        document.getElementById("seats").innerHTML = "<button>" + i + "</button>";
    }
}