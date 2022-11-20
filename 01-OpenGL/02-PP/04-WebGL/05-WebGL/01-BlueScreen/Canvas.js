//Date: 13/11/2022
//RTR2021 WebGL Blue Screen

//global variables
var canvas = null;
var gl = null;
var bFullScreen = false;
var canvas_original_width;
var canvas_original_height;

//var for double buffering emulation / to perform animation on compatible browser
var requestAnimationFrame = window.requestAnimationFrame ||
                            window.mozRequestAnimationFrame ||
                            window.webkitRequestAnimationFrame ||
                            window.oRequestAnimationFrame ||
                            window.msRequestAnimationFrame;         //similar to SwapBuffers();

//function definitions
function main() {
    //code
    //get canvas
    //document here below is an inbuilt variable in JS, representation/interface of DOM (which came from COM) in JS is done by document
    canvas = document.getElementById("AMP"); //the wndProc of this canvas (i.e window) is with browser program
    if (!canvas) {
        console.log("Obtaining canvas failed\n")
    }
    else {
        console.log("Obtaining canvas succeeded\n")
    }

    //backup canvas dimensions
    canvas_original_width = canvas.width;
    canvas_original_height = canvas.height;

    //initialize
    initialize();

    //resize
    resize();

    //display
    display();

    //adding keyboard & mouse event listener (event handlers or msg handler or event deligate)
    window.addEventListener("keydown", keyDown, false);     //"keydown" here is inbuilt keyword in js for browser's wndproc
    window.addEventListener("click", mouseDown, false);     //"click" here is inbuilt keyword in js for browser's wndproc
    window.addEventListener("resize", resize, false);
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

function initialize() {
    //code
    //webGL removed word 'gl' from all OpenGL ES functions, they are all called on context object
    //so to be in sync or in line with OpenGL ES functions while writing we reassign 'context' var to 'gl' var
    //so that it is easy to call functions

    //get webgl2 rendering context from canvas
    //var context = canvas.getContext("webgl2");
    //gl = context;
    gl = canvas.getContext("webgl2");
    if (!gl) {
        console.log("Obtaining WebGL 2.0 context failed\n")
    }
    else {
        console.log("Obtaining WebGL 2.0 context succeeded\n")
    }
    
    //set viewport width & height of context
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    //clear screen by color
    gl.clearColor(0.0, 0.0, 1.0, 1.0);      //blue
}

function resize() {
    //code
    if(bFullScreen == true) {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
    }
    else {
        canvas.width = canvas_original_width;
        canvas.height = canvas_original_height;
    }

    gl.viewport(0, 0, canvas.width, canvas.height);
}

function display() {
    //code
    gl.clear(gl.COLOR_BUFFER_BIT);

    //double buffering emulation
    requestAnimationFrame(display, canvas);                 //kinda msg loop / render loop / swapbuffers()
}

function update() {
    //code

}

//keyboard event listener
function keyDown(event) {
    //code
    switch (event.keyCode) {
        case 69:                    //default key of browser exit for fullscreen mode is ESC i.e 27 hence replacing it with E 69, you can also override browsers this default behaviour for ESC key
            uninitialize();
            if(bFullScreen == true)
                toggleFullscreen(); //removing fullscreen before closing tab
            
            window.close();         //not all browser will follow this
            break;

        case 70:
            toggleFullscreen();
            break;
    }
}

//mouse event listener
function mouseDown() {
    //code
    
}

function uninitialize() {
    //code
    
}
