//Date: 12/11/2022
//RTR2021 WebGL Event Handling in Canvas

//JavaScript source code
function main() {
    //code

    //step-1: get canvas
    //document here below is an inbuilt variable in JS, representation/interface of DOM (which came from COM) in JS is done by document
    var canvas = document.getElementById("AMP"); //the wndProc of this canvas (i.e window) is with browser program
    if (!canvas) {
        console.log("Obtaining canvas failed\n")
    }
    else {
        console.log("Obtaining canvas succeeded\n")
    }

    //step-2: get 2D context from canvas
    var context = canvas.getContext("2d");
    if (!context) {
        console.log("Obtaining context failed\n")
    }
    else {
        console.log("Obtaining context succeeded\n")
    }

    //step-3: paint bg of canvas by black color
    context.fillStyle = "black";   //color can be written in hexadecimals too "#000000"
    context.fillRect(0, 0, canvas.width, canvas.height);

    //step-4: adding keyboard & mouse event listener (event handlers or msg handler or event deligate)
    window.addEventListener("keydown", keyDown, false);     //"keydown" here is inbuilt keyword in js for browser's wndproc
    window.addEventListener("click", mouseDown, false);     //"click" here is inbuilt keyword in js for browser's wndproc
    //third parameter is capture parameter & is for event bubbling concept
}

//keyboard event listener
function keyDown(event) {
    //code
    alert("A Key is Pressed");
}

//mouse event listener
function mouseDown() {
    //code
    alert("A Mouse Button is Clicked");
}
