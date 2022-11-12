//Date: 12/11/2022
//RTR2021 WebGL First Browser Canvas Program

//JavaScript source code
function main() {
    //code

    //step-1: get canvas
    //document here below is an inbuilt variable in JS, representation/interface of DOM (which came from COM) in JS is done by document
    var canvas = document.getElementById("AMP");
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
}
