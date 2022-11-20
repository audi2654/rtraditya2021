//Date: 19/11/2022
//RTR2021 WebGL Orthographic Projection Triangle

//global variables
var canvas = null;
var gl = null;
var bFullScreen = false;
var canvas_original_width;
var canvas_original_height;

//WebGL specific variables
//PP related global vars
var shaderProgramObject;

//macros for user defined vertex attributes
const webGlMacros = 
    {
        AMP_ATTRIBUTE_POSITION : 0,
	    AMP_ATTRIBUTE_COLOR : 1,
	    AMP_ATTRIBUTE_NORMAL : 2,
	    AMP_ATTRIBUTE_TEXTURE0 : 3,
    };

//vao & vbo variables for shader attributes
var vao;									//vertex array object
var vbo;									//vertex buffer object

//user defined uniform vars for MVP & different matrices in shaders
var mvpMatrixUniform;					    //uniform variable for MVP matrix

//user defined var for viewing matrix
var orthographicProjectionMatrix;

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
        console.log("Obtaining WebGL 2.0 context failed\n");
    }
    else {
        console.log("Obtaining WebGL 2.0 context succeeded\n");
    }
    
    //set viewport width & height of context
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;

    //vertex shader code
    var vertexShaderSourceCode = String
    (
        "#version 300 es" +
        "\n" +
        "in vec4 a_position;" +
        "uniform mat4 u_mvpMatrix;" +
        "void main(void)" +
        "{" +
        "gl_Position = u_mvpMatrix * a_position;" +
        "}"
    );

    var vertexShaderObject = gl.createShader(gl.VERTEX_SHADER);

    gl.shaderSource(vertexShaderObject, vertexShaderSourceCode);

	gl.compileShader(vertexShaderObject);	    //inline shader compiler

    //compilation error checking for vertex shader
    if(gl.getShaderParameter(vertexShaderObject, gl.COMPILE_STATUS) == false) {
        var error = gl.getShaderInfoLog(vertexShaderObject);
        if(error.length > 0) {
            var errorStr = "Vertex Shader Compilation Error : " + error;
            alert(errorStr);
            uninitialize();
        }
    }

    //fragment shader code
    var fragmentShaderSourceCode = String
    (
        "#version 300 es" +
        "\n" +
        "precision highp float;" +
        "out vec4 FragColor;" +
        "void main(void)" +
        "{" +
            "FragColor = vec4(1.0, 1.0, 1.0, 1.0);" +
        "}"
    );

    var fragmentShaderObject = gl.createShader(gl.FRAGMENT_SHADER);

    gl.shaderSource(fragmentShaderObject, fragmentShaderSourceCode);

	gl.compileShader(fragmentShaderObject);	    //inline shader compiler

    //compilation error checking for fragment shader
    if(gl.getShaderParameter(fragmentShaderObject, gl.COMPILE_STATUS) == false) {
        var error = gl.getShaderInfoLog(fragmentShaderObject);
        if(error.length > 0) {
            var errorStr = "Fragment Shader Compilation Error :" + error;
            alert(errorStr);
            uninitialize();
        }
    }

    //shader program object
    shaderProgramObject = gl.createProgram();

    //attaching all shader object with shader program object
    gl.attachShader(shaderProgramObject, vertexShaderObject);
	gl.attachShader(shaderProgramObject, fragmentShaderObject);

    //prelinking & binding of shader program object with vertex attributes 
	gl.bindAttribLocation(shaderProgramObject, webGlMacros.AMP_ATTRIBUTE_POSITION, "a_position");			//viable place for andhar

    //shader program linking
	gl.linkProgram(shaderProgramObject);			//inline shader linker

    //error checking for shader program
    if(gl.getProgramParameter(shaderProgramObject, gl.LINK_STATUS) == false) {
        var error = gl.getProgramInfoLog(shaderProgramObject);
        if(error.length > 0) {
            var errorStr = "Shader Program Compilation Error :" + error;
            alert(errorStr);
            uninitialize();
        }
    }

    //post linking retrieving uniformed locations of user defined uniform type variables from shaderProgramObject
    mvpMatrixUniform = gl.getUniformLocation(shaderProgramObject, "u_mvpMatrix");				//viable place for andhar

    //here starts OpenGL code
	//declaration of vertex data arrays
	//ORDER of position, texcoord & normals for faces of shapes is important
	//i.e if in 1st array first 3 values are for front face then all 3 arrays should have first 3 values for front face

    var triangleVertices = new Float32Array
    ([
        0.0, 50.0, 0.0,
		-50.0, -50.0, 0.0,
		50.0, -50.0, 0.0
    ])

    //vao for triangle
    vao = gl.createVertexArray();
    gl.bindVertexArray(vao);

    //vbo for triangle
    vbo = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
    gl.bufferData(gl.ARRAY_BUFFER, triangleVertices, gl.STATIC_DRAW);
    gl.vertexAttribPointer(webGlMacros.AMP_ATTRIBUTE_POSITION, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(webGlMacros.AMP_ATTRIBUTE_POSITION);
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    gl.bindVertexArray(null);					//unbinding vao
    
    //clear screen by color
    gl.clearColor(0.0, 0.0, 1.0, 1.0);      //blue

    //depth 3D related changes
	gl.clearDepth(1.0);
	gl.enable(gl.DEPTH_TEST);
	gl.depthFunc(gl.LEQUAL);

    //initializing orthographic projection matrix
    orthographicProjectionMatrix = mat4.create();

    console.log("Good initialize()\n");
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

    if (canvas.height == 0)
        canvas.height = 1;		//we keep compulsorily min val as 1 to avoid divided by 0 in future code calls

    gl.viewport(0, 0, canvas.width, canvas.height);

    if(canvas.width <= canvas.height)
    {
        mat4.ortho(orthographicProjectionMatrix, -100.0,
                                                100.0,
                                                (-100.0 * (canvas.height / canvas.width)),
                                                (100.0 * (canvas.height / canvas.width)),
                                                -100.0,
                                                100.0);
    }
    else
    {
        mat4.ortho(orthographicProjectionMatrix, (-100.0 * (canvas.width / canvas.height)),
                                                (100.0 * (canvas.width / canvas.height)),
                                                -100.0,
                                                100.0,
                                                -100.,
                                                100.0);
    }
    
    console.log("Good resize()\n");
}

function display() {
    //code
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);    //here actual clearing happens with color which was set in initialize(), framebuffer/colorbuffer in VRAM

    //use shadeProgramObject
	gl.useProgram(shaderProgramObject);

    //transformations related code
	//declaring TRS & MVP identity matrices as per requirement
	var modelViewMatrix = mat4.create();
	var modelViewProjectionMatrix = mat4.create();

    //initializing matrices with values or doing calculation
	mat4.multiply(modelViewProjectionMatrix, orthographicProjectionMatrix, modelViewMatrix);	//here order is important always put projection matric first, matrix multi is non-commutative

	//now passing/pushing above matrices with updated/calculated values to shader using uniform type variables
    gl.uniformMatrix4fv(mvpMatrixUniform, false, modelViewProjectionMatrix);

    gl.bindVertexArray(vao);                            //binding here vao means running cassette & running all lines of vbo written in initialize() between bind & unbind of vao

    //here there should be drawing code
    gl.drawArrays(gl.TRIANGLES, 0, 3);

	gl.bindVertexArray(null);				            //unbinding vao of triangle

	//unuse the shaderProgramObject
	gl.useProgram(null);

    //double buffering emulation
    requestAnimationFrame(display, canvas);             //kinda msg loop / render loop / SwapBuffers()
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
    //deletion/uninitialization of vbo
	if (vbo)
	{
		gl.deleteBuffer(vbo);
		vbo = null;
	}

	//deletion/uninitialization of vao
	if (vao)
	{
		gl.deleteVertexArray(vao);
		vao = null;
	}

    //shader uninitialization
    if (shaderProgramObject)
	{
        gl.useProgram(shaderProgramObject);

        var shaderObjects = gl.getAttachedShaders(shaderProgramObject);

        for (let i = 0; i < shaderObjects.length; i++)
		{
			gl.detachShader(shaderProgramObject, shaderObjects[i]);
			gl.deleteShader(shaderObjects[i]);	//deleting shader obj from WebGL memory
			shaderObjects[i] = 0;
		}

		gl.useProgram(null);
		gl.deleteProgram(shaderProgramObject);
		shaderProgramObject = null;
    }
}
