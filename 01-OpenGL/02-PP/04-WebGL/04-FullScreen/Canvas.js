//Date: 12/11/2022
//RTR2021 WebGL Fullscreen in Canvas

//JavaScript source code
//global variables
var canvas = null;
var context = null;
var bFullScreen = false;

//function definitions
function main() {
    //code

    //step-1: get canvas
    //document here below is an inbuilt variable in JS, representation/interface of DOM (which came from COM) in JS is done by document
    canvas = document.getElementById("AMP"); //the wndProc of this canvas (i.e window) is with browser program
    if (!canvas) {
        console.log("Obtaining canvas failed\n")
    }
    else {
        console.log("Obtaining canvas succeeded\n")
    }

    //step-2: get 2D context from canvas
    context = canvas.getContext("2d");
    if (!context) {
        console.log("Obtaining context failed\n")
    }
    else {
        console.log("Obtaining context succeeded\n")
    }

    //step-3: paint bg of canvas by black color
    context.fillStyle = "black";          //color can be written in hexadecimals too "#000000"
    context.fillRect(0, 0, canvas.width, canvas.height);

    drawText("HelloWorld!!!");

    //step-9: fullscreen

    //step-10: adding keyboard & mouse event listener (event handlers or msg handler or event deligate)
    window.addEventListener("keydown", keyDown, false);     //"keydown" here is inbuilt keyword in js for browser's wndproc
    window.addEventListener("click", mouseDown, false);     //"click" here is inbuilt keyword in js for browser's wndproc
    //third parameter is capture parameter & is for event bubbling concept
}

function drawText(text) {
    //code
    //step-4: declare the string
    var str = text;

    //step-5: decide the font
    context.font = "48px sans-serif";

    //step-6: decide text color
    context.fillStyle = "white";

    //step-7: put the text in the center of canvas
    context.textAlign = "center"        //horizontal centre DT_CENTRE in win32
    context.textBaseline = "middle"     //vertical centre DT_VCENTRE in win32

    //step-8: display the text
    context.fillText(str, canvas.width / 2, canvas.height / 2);
}

function toggleFullscreen() {
    //code
    //check whether your browser supports fullscreen element or not & check for all browser you want your app to run on
    var fullscreen_element = document.fullscreenElement ||
        document.mozFullScreenElement ||
        document.webkitFullscreenElement ||
        document.msFullscreenElement ||
        null;

    if (fullscreen_element == null) {       //if not fullscreen
        if (canvas.requestFullscreen) {     //here canvas.requestFullscreen is function pointer
            canvas.requestFullscreen();
        }
        else if (canvas.mozRequestFullScreen) {
            canvas.mozRequestFullScreen();
        }
        else if (canvas.webkitRequestFullscreen) {
            canvas.webkitRequestFullscreen();
        }
        else if (canvas.msRequestFullscreen) {
            canvas.msRequestFullscreen();
        }
        bFullScreen = true;
    }
    else {
        if (document.exitFullscreen) {     //here canvas.requestFullscreen is function pointer
            document.exitFullscreen();
        }
        else if (document.mozExitFullScreen) {
            document.mozExitFullScreen();
        }
        else if (document.webkitExitFullscreen) {
            document.webkitExitFullscreen();
        }
        else if (document.msExitFullscreen) {
            document.msExitFullscreen();
        }
        bFullScreen = false;
    }

    //then call your respective browser's fullscreen function to make fullscreen

    //if already fullscreen then call your respective browser's restoring function to restore fullscreen to normal window
}

//keyboard event listener
function keyDown(event) {
    //code
    switch (event.keyCode) {
        case 70:
            toggleFullscreen();
            //drawText("HelloWorld!!!");        //for repaint because it was not previous default behaviour
            break;
    }
}

//mouse event listener
function mouseDown() {
    //code
    
}
