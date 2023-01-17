#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

//func list

//letters
void amp_A(GLfloat color_array[]);
void amp_B(GLfloat color_array[], GLfloat inner_half_circle_color_array[]);
void amp_C(GLfloat color_array[]);       //to be written
void amp_D(GLfloat color_array[]);
void amp_E(GLfloat color_array[]);       //tb written
void amp_F(GLfloat color_array[]);
//G
void amp_H(GLfloat color_array[]);
void amp_I(GLfloat color_array[]);
//J
//K
void amp_L(GLfloat color_array[]);       //tb written
void amp_M(GLfloat color_array[]);
void amp_N(GLfloat color_array[]);
void amp_O(GLfloat color_array[]);       //tb written
void amp_P(GLfloat color_array[]);
//Q
void amp_R(GLfloat color_array[]);
void amp_S(GLfloat color_array[]);
void amp_S_v2(GLfloat color_array[]);
void amp_T(GLfloat color_array[]);
void amp_U(GLfloat color_array[]);
//V
void amp_W(GLfloat color_array[]);       //tb written
//X
void amp_Y(GLfloat color_array[]);
//Z

//symbols
void amp_chevron_right(GLfloat color_array[]);
void amp_chevron_left(GLfloat color_array[]);
void amp_slash_forward(GLfloat color_array[]);
void amp_heart_half_circle(GLfloat color_array[]);

//color pallette
GLfloat gfaColor_blue1[] = {0.59f, 0.68f, 1.0f};							//blue
GLfloat gfaColor_blue2[] = {0.59f, 0.68f, 1.0f};							//blueish
GLfloat gfaColor_blue3[] = {204.0f/256.0f, 1.0f, 1.0f};						//blueish
GLfloat gfaColor_blue_aqua[] = {0.40f, 181.0f / 256.0f, 181.0f / 256.0f};	//blue aqua
GLfloat gfaColor_blue_azure[] = {0.0f, 0.5f, 0.8f}; 						//blue azure
GLfloat gfaColor_black[] = {0.0f, 0.0f, 0.0f}; 								//black
GLfloat gfaColor_blue_aqua2[] = {0.40f, 181.0f / 256.0f, 181.0f / 256.0f};	//aqua blue
GLfloat gfaColor_green[] = {0.19, 0.9, 0.08}; 								//green
GLfloat gfaColor_green2[] = {0.6f, 1.0f, 0.0f};								//green2
GLfloat gfaColor_gray[] = {0.5, 0.5, 0.5};									//gray
GLfloat gfaColor_pinkish[] = {0.90, 0.17, 0.31}; 							//pinkish - amaranth
GLfloat gfaColor_saffron[] = {1.0, 0.60, 0.20}; 							//saffron
GLfloat gfaColor_red[] = {1.0f, 0.0f, 0.0f};
GLfloat gfaColor_yellow[] = {0.9f, 1.0f, 0.1f};
GLfloat gfaColor_white[] = {1.0, 1.0, 1.0}; 								//white 
GLfloat gfaAddBackgroundColor[] = {204.0f/256.0f, 1.0f, 1.0f};

//letter function definitions
void amp_A(GLfloat color_array[])
{
//3rd quad Center line -
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.7f, -0.6f, 0.0f);
	glVertex3f(0.7f, -0.6f, 0.0f);
	glEnd();

//First quad /
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.2f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glEnd();

//2nd quad \
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.2f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(0.6f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(1.0f, -1.3f, 0.0f);
	glVertex3f(0.6f, -1.3f, 0.0f);
	glEnd();
}

void amp_B(GLfloat color_array[], GLfloat inner_half_circle_color_array[])
{
//vertical left line of B
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle top line of B
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 0.9f, 0.0f);
	glVertex3f(0.2f, 0.9f, 0.0f);
	glEnd();

//middle centre line of B
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(0.2f, -0.2f, 0.0f);
	glEnd();

//middle bottom line of B
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, -0.9f, 0.0f);
	glVertex3f(-0.6f, -0.9f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(0.2f, -1.3f, 0.0f);
	glEnd();

	glTranslatef(-0.1f, 0.0f, 0.0f);

//Upper right most quad of B half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	GLfloat radius = 0.7f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//Upper right most quad small of B inner half circle
	glPointSize(5.0f);
	glColor3fv(inner_half_circle_color_array);
	glBegin(GL_POLYGON);

	radius = 0.3f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//Lower right most quad of B half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	radius = 0.7f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate - 0.6);
		}
		
	}

	glEnd();

//Lower right most quad small of B inner half circle
	glPointSize(5.0f);
	glColor3fv(inner_half_circle_color_array);
	glBegin(GL_POLYGON);

	radius = 0.3f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate - 0.6);
		}
		
	}

	glEnd();
}

void amp_C(GLfloat color_array[])
{































}

void amp_D(GLfloat color_array[])
{
//vertical left line of D 
	//top quad
	glBegin(GL_QUADS);
	//glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);			//saffron
	glVertex3f(-0.4f, 1.0f, 0.f);
	glVertex3f(-0.8f, 1.0f, 0.f);
	//glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(-0.8f, 0.0f, 0.f);
	glVertex3f(-0.4f, 0.0f, 0.f);
	glEnd();
	

	//lower quad
	glBegin(GL_QUADS);
	//glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(-0.4f, 0.0f, 0.f);
	glVertex3f(-0.8f, 0.0f, 0.f);
	//glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(-0.8f, -1.0f, 0.f);
	glVertex3f(-0.4f, -1.0f, 0.f);
	glEnd();

//vertical right line of D 
	//top quad
	glBegin(GL_QUADS);
	//glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);				//saffron
	glVertex3f(1.0f, 1.0f, 0.f);
	glVertex3f(0.6f, 1.0f, 0.f);
	//glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white	
	glVertex3f(0.6f, 0.0f, 0.f);
	glVertex3f(1.0f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	//glColor3f(gfWhiteColor_R, gfWhiteColor_G, gfWhiteColor_B);			//white
	glVertex3f(0.6f, 0.0f, 0.f);
	glVertex3f(1.0f, 0.0f, 0.f);
	//glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(1.0f, -1.0f, 0.f);
	glVertex3f(0.6f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of D
	glBegin(GL_QUADS);
	//glColor3f(gfSaffColor_R, gfSaffColor_G, gfSaffColor_B);			//saffron
	glVertex3f(1.0f, 1.3f, 0.f);
	glVertex3f(-1.1f, 1.3, 0.f);
	glVertex3f(-1.1f, 1.0f, 0.f);
	glVertex3f(1.0f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of D
	glBegin(GL_QUADS);
	//glColor3f(gfGreenColor_R, gfGreenColor_G, gfGreenColor_B);			//india green
	glVertex3f(1.0f, -1.3f, 0.f);
	glVertex3f(-1.1f, -1.3f, 0.f);
	glVertex3f(-1.1f, -1.0f, 0.f);
	glVertex3f(1.0f, -1.0f, 0.f);
	glEnd();
}

void amp_E(GLfloat color_array[])
{
//vertical left line of E
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//upper line of E
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 0.91f, 0.0f);
	glVertex3f(0.8f, 0.91f, 0.0f);
	glEnd();

//middle line of E
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glVertex3f(-0.6f, -0.19f, 0.0f);
	glVertex3f(0.8f, -0.19f, 0.0f);
	glEnd();

//lower line of E
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, -0.91f, 0.0f);
	glVertex3f(-0.6f, -0.91f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(0.8f, -1.3f, 0.0f);
	glEnd();
}

void amp_F(GLfloat color_array[])
{
//vertical line of F 
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.5f, 1.0f, 0.f);
	glVertex3f(-0.9f, 1.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.9f, 0.0f, 0.f);
	glVertex3f(-0.5f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.5f, 0.0f, 0.f);
	glVertex3f(-0.9f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.9f, -1.0f, 0.f);
	glVertex3f(-0.5f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of F
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(.9f, 1.3f, 0.f);
	glVertex3f(-.9f, 1.3, 0.f);
	glVertex3f(-.9f, 1.0f, 0.f);
	glVertex3f(.9f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of F
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.5f, 0.4f, 0.f);
	glVertex3f(-.9f, 0.4f, 0.f);
	glVertex3f(-.9f, 0.1f, 0.f);
	glVertex3f(.5f, 0.1f, 0.f);
	
	glEnd();
}

void amp_H(GLfloat color_array[])
{
//vertical left line of H
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle line of H
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glVertex3f(-0.6f, -0.19f, 0.0f);
	glVertex3f(0.8f, -0.19f, 0.0f);
	glEnd();

//vertical right line of H
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(0.8f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();
}

void amp_I(GLfloat color_array[])
{
//vertical line of I 
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 1.0f, 0.f);
	glVertex3f(-0.2f, 1.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.f);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, -1.0f, 0.f);
	glVertex3f(0.2f, -1.0f, 0.f);
	glEnd();

//upper horizontal line of I
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(.9f, 1.3f, 0.f);
	glVertex3f(-.9f, 1.3, 0.f);
	glVertex3f(-.9f, 1.0f, 0.f);
	glVertex3f(.9f, 1.0f, 0.f);
	glEnd();

//lower horizontal line of I
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(.9f, -1.3f, 0.f);
	glVertex3f(-.9f, -1.3f, 0.f);
	glVertex3f(-.9f, -1.0f, 0.f);
	glVertex3f(.9f, -1.0f, 0.f);
	glEnd();
}

void amp_L(GLfloat color_array[])
{
//vertical left line of L
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//lower line of L
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, -0.91f, 0.0f);
	glVertex3f(-0.6f, -0.91f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(0.8f, -1.3f, 0.0f);
	glEnd();
}

void amp_M(GLfloat color_array[])
{
	//vertical left line of M
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle diagonal line of N \
	//top quad
	glBegin(GL_QUAD_STRIP);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glEnd();

//middle diagonal line of N /
	//top quad
	glBegin(GL_QUAD_STRIP);
	glColor3fv(color_array);
	glVertex3f(1.0f, 1.3f, 0.f);
	glVertex3f(0.6f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glEnd();

//vertical right line of M
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(0.8f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();
}

void amp_N(GLfloat color_array[])
{
//vertical left line of N
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle diagonal line of N
	//top quad
	glBegin(GL_QUAD_STRIP);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUAD_STRIP);
	glColor3fv(color_array);
	glVertex3f(0.3f, 0.f, 0.f);
	glVertex3f(-0.1f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();

//vertical right line of N
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(0.8f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();
}

void amp_O(GLfloat color_array[])
{





















}

void amp_P(GLfloat color_array[])
{
//vertical left line of P
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle top line of P
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 0.9f, 0.0f);
	glVertex3f(0.2f, 0.9f, 0.0f);
	glEnd();

//middle bottom line of P
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 0.3f, 0.0f);
	glVertex3f(-0.6f, 0.3f, 0.0f);
	glVertex3f(-0.6f, -0.1f, 0.0f);
	glVertex3f(0.2f, -0.1f, 0.0f);
	glEnd();

	glTranslatef(-0.1f, 0.0f, 0.0f);

//2nd right most quad of P half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	GLfloat radius = 0.7f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//3rd right most quad small of P inner half circle
	glPointSize(5.0f);
	glColor3fv(gfaAddBackgroundColor);
	glBegin(GL_POLYGON);

	radius = 0.3f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();
}

void amp_R(GLfloat color_array[])
{
//vertical left line of R
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle top line of R
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 1.3f, 0.0f);
	glVertex3f(-0.6f, 0.9f, 0.0f);
	glVertex3f(0.2f, 0.9f, 0.0f);
	glEnd();

//middle bottom line of R
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, 0.3f, 0.0f);
	glVertex3f(-0.6f, 0.3f, 0.0f);
	glVertex3f(-0.6f, -0.1f, 0.0f);
	glVertex3f(0.2f, -0.1f, 0.0f);
	glEnd();

	glTranslatef(-0.1f, 0.0f, 0.0f);

//2nd right most quad of R half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	GLfloat radius = 0.7f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//3rd right most quad small of R inner half circle
	glPointSize(5.0f);
	glColor3fv(gfaAddBackgroundColor);
	glBegin(GL_POLYGON);

	radius = 0.3f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//For quad \ in R
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glVertex3f(-0.0f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(0.6f, -1.3f, 0.0f);
	glVertex3f(1.0f, -1.3f, 0.0f);
	glEnd();
}

void amp_S(GLfloat color_array[])
{
//middle top line of S
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.6f, 1.35f, 0.0f);
	glVertex3f(0.0f, 1.35f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.6f, 1.0f, 0.0f);
	glEnd();

//middle bottom line of S
	glBegin(GL_QUADS);
	glColor3fv(color_array);	
	glVertex3f(0.2f, -1.0f, 0.0f);
	glVertex3f(-0.6f, -1.0f, 0.0f);
	glVertex3f(-0.6f, -1.35f, 0.0f);
	glVertex3f(0.2f, -1.35f, 0.0f);
	glEnd();

	glTranslatef(-0.1f, 0.0f, 0.0f);

//Upper right most quad of S half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	GLfloat radius = 0.73f;
	GLfloat incre = 1.0f;

	for (float i = 360.0f; i > 0.0f; i = i - incre)
	{
		if(i < 275 && i > 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//Upper right most quad small of S inner half circle
	glPointSize(5.0f);
	glColor3fv(gfaAddBackgroundColor);
	glBegin(GL_POLYGON);

	radius = 0.37f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i < 290 && i > 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate + 0.6);
		}
		
	}

	glEnd();

//Lower right most quad of S half circle
	glPointSize(5.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	radius = 0.73f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate - 0.6);
		}
		
	}

	glEnd();

//Lower right most quad small of S inner half circle
	glPointSize(5.0f);
	glColor3fv(gfaAddBackgroundColor);
	glBegin(GL_POLYGON);

	radius = 0.37f;
	incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i > 270 || i < 90)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate + 0.2, Y_coordinate - 0.6);
		}
		
	}

	glEnd();
}

void amp_S_v2(GLfloat color_array[])
{
    //func decl.
    void amp_chevron_right(GLfloat color_array[]);
	void amp_chevron_left(GLfloat color_array[]);
	void amp_slash_forward(GLfloat color_array[]);

    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    amp_chevron_right(color_array);
    amp_chevron_left(color_array);
    amp_slash_forward(color_array);
}

void amp_T(GLfloat color_array[])
{
//vertical line of T
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 1.0f, 0.f);
	glVertex3f(-0.2f, 1.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.f);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, -1.3f, 0.f);
	glVertex3f(0.2f, -1.3f, 0.f);
	glEnd();

//upper horizontal line of T
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(-1.2f, 1.3, 0.f);
	glVertex3f(-1.2f, 0.95f, 0.f);
	glVertex3f(1.2f, 0.95f, 0.f);
	glEnd();
}

void amp_U(GLfloat color_array[])
{
//vertical left line of H
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.f);
	glVertex3f(-1.0f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.f);
	glVertex3f(-1.0f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.f);
	glVertex3f(-0.6f, -1.3f, 0.f);
	glEnd();

//middle line of H
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, -1.0f, 0.0f);
	glVertex3f(-0.6f, -1.0f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(0.8f, -1.3f, 0.0f);
	glEnd();

//vertical right line of H
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(1.2f, 1.3f, 0.f);
	glVertex3f(0.8f, 1.3f, 0.f);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.8f, 0.0f, 0.f);
	glVertex3f(1.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(1.2f, -1.3f, 0.f);
	glVertex3f(0.8f, -1.3f, 0.f);
	glEnd();
}

void amp_V(GLfloat color_array[])
{
//First quad \ 
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 1.3f, 0.0f);
	glVertex3f(-1.4f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(-0.2f, -1.3f, 0.0f);
	glEnd();

//2nd quad \
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.6f, 1.3f, 0.0f);
	glVertex3f(0.2f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glEnd();

	//lower quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glVertex3f(-0.2f, -1.3f, 0.0f);
	glEnd();
}

void amp_W(GLfloat color_array[])
{
	amp_V(color_array);
	glTranslatef(1.6f, 0.0f, 0.0f);
	amp_V(color_array);
}

void amp_X(GLfloat color_array[])
{
	//to be written
}

void amp_Y(GLfloat color_array[])
{
//First quad \
	//top left quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.3f, 0.0f);
	glVertex3f(-1.0f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

//2nd quad /
	//top right quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.6f, 1.3f, 0.0f);
	glVertex3f(1.0f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.f);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glEnd();

//lower vertical line of Y 
	//top quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 0.0f, 0.f);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, -1.3f, 0.f);
	glVertex3f(0.2f, -1.3f, 0.f);
	glEnd();
}

//symbol function definitions
void amp_chevron_right(GLfloat color_array[])
{
//First quad \
	//top left quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

//2nd quad /
	//top right quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
    glVertex3f(0.2f, 0.0f, 0.f);
    glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.6f, -1.0f, 0.0f);
	glColor3fv(color_array);
	glEnd();
}

void amp_chevron_left(GLfloat color_array[])
{
//First quad \
	//top left quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
    glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.6f, 1.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.f);
	glVertex3f(0.2f, 0.0f, 0.f);
	glEnd();

//2nd quad /
	//top right quad
	glBegin(GL_QUADS);
	glColor3fv(color_array);
    glVertex3f(0.2f, 0.0f, 0.f);
    glVertex3f(-0.2f, 0.0f, 0.f);
    glVertex3f(0.6f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glColor3fv(color_array);
	glEnd();
}

void amp_slash_forward(GLfloat color_array[])
{
//top quad /
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(0.2f, 1.3f, 0.0f);
	glVertex3f(-0.2f, 1.3f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glEnd();

//lower quad /
	glBegin(GL_QUADS);
	glColor3fv(color_array);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glColor3fv(color_array);
	glVertex3f(-1.0f, -1.3f, 0.0f);
	glVertex3f(-0.6f, -1.3f, 0.0f);
	glEnd();
}

void amp_heart_half_circle(GLfloat color_array[])
{
	glPointSize(8.0f);
	glColor3fv(color_array);	
	glBegin(GL_POLYGON);

	GLfloat radius = 1.2f;
	GLfloat incre = 1.0f;

	for (float i = 0; i < 360; i = i + incre)
	{
		if(i < 180)
		{
			GLfloat X_coordinate = radius * cos(i * M_PI / 180.0f);
			GLfloat Y_coordinate = radius * sin(i * M_PI / 180.0f);
			glVertex2f(X_coordinate, Y_coordinate);
		}
		
	}
	glEnd();
}
