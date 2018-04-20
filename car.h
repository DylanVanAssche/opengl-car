/*
#################################################################################
#	OpenGL futuristic soapbox car					                        	#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)			                      	#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	        #
#################################################################################

INFO: the 'static' keyword is used to avoid multiple definitions across the
several files.
*/

// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

// My version of the GCC compiler doesn't support the constant M_PI by default
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// Constants
#define AXIS_LENGTH 100.0
#define AXIS_LINE_WIDTH 2.0
#define MENU_QUIT 0
#define MENU_COACHWORK_GREY 1
#define MENU_COACHWORK_WHITE 2
#define MENU_SUSPENSION_CHROME 3
#define MENU_SUSPENSION_BRONZE 4
#define MENU_FINISH_YELLOW 5
#define MENU_FINISH_LILAC 6
#define CAR_LINE_WIDTH 5.0
#define CAR_SUBDIVIONS 50 // change this if rendering performance is bad on HP Thin CLients
#define ANIMATION_SPEED 100 // Don't fry the GPU please
#define MATERIAL_SHININESS_STEP 5.0
#define SPOT_EXPONENT_DEFAULT 20.0
#define SPOT_EXPONENT_STEP 5.0
#define SPOT_ANGLE_DEFAULT 0.0
#define SPOT_HEIGHT_DEFAULT 0.0

// Colors
static const GLfloat RED[] = {1.0, 0.0, 0.0, 1.0};
static const GLfloat GREEN[] = {0.0, 1.0, 0.0, 1.0};
static const GLfloat BLUE[] = {0.0, 0.0, 1.0, 1.0};
static const GLfloat GREEN_BLUE[] = {0.0, 0.75, 0.75, 1.0};
static const GLfloat YELLOW[] = {1.0, 1.0, 0.0, 1.0};
static const GLfloat WHITE[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat BLACK[] = {0.0, 0.0, 0.0, 1.0};

// Materials
static GLfloat AMBIENT_GREY[] = {0.22, 0.22, 0.22, 1.0};
static GLfloat DIFFUSE_GREY[] = {0.33, 0.33, 0.33, 1.0};
static GLfloat SPECULAR_GREY[] = {0.11, 0.11, 0.11, 1.0};
static GLfloat AMBIENT_BLACK[] = {0.11, 0.11, 0.11, 1.0};
static GLfloat DIFFUSE_BLACK[] = {0.055, 0.055, 0.055, 1.0};
static GLfloat SPECULAR_BLACK[] = {0.0275, 0.0275, 0.0275, 1.0};
static GLfloat AMBIENT_WHITE[] = {0.66, 0.66, 0.66, 1.0};
static GLfloat DIFFUSE_WHITE[] = {0.77, 0.77, 0.77, 1.0};
static GLfloat SPECULAR_WHITE[] = {0.55, 0.55, 0.55, 1.0};
static GLfloat AMBIENT_CHROME[] = {0.46, 0.58, 0.35, 1.0};
static GLfloat DIFFUSE_CHROME[] = {0.23, 0.29, 0.17, 1.0};
static GLfloat SPECULAR_CHROME[] = {0.69, 0.87, 0.52, 1.0};
static GLfloat AMBIENT_BRONZE[] = {0.21, 0.13, 0.10, 1.0};
static GLfloat DIFFUSE_BRONZE[] = {0.39, 0.27, 0.17, 1.0};
static GLfloat SPECULAR_BRONZE[] = {0.71, 0.43, 0.18, 1.0};
static GLfloat AMBIENT_YELLOW[] = {0.65, 0.55, 0.15, 1.0};
static GLfloat DIFFUSE_YELLOW[] = {0.75, 0.45, 0.15, 1.0};
static GLfloat SPECULAR_YELLOW[] = {0.85, 0.35, 0.15, 1.0};
static GLfloat AMBIENT_LILA[] = {0.45, 0.15, 0.75, 1.0};
static GLfloat DIFFUSE_LILA[] = {0.55, 0.15, 0.65, 1.0};
static GLfloat SPECULAR_LILA[] = {0.35, 0.15, 0.85, 1.0};

// Functions
void drawAxes(GLint axes);
void drawSuspension(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
void drawTires(GLint wireFrame);
void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight);
void drawLights();
void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint competition);
