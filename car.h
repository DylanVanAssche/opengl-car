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

// My version of the GCC compiler doesn't support the constant M_PI
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// Window size 1920 x 1080
static GLint winWidth = 1280, winHeight = 720;

// Viewport coordinates
static GLdouble xmin = -2.0, xmax = 4.0, ymin = -2.0, ymax = 3.0, near = 1.0, far = 10.0, angle = 60.0;

// Enabled features
static GLint axes = 1;
static GLint flat = 1;
static GLubyte projectionMode = 'p';

// Eye
static GLdouble xLens = 1.0, yLens = 1.0, zLens = 3.0;
static GLdouble xRef = 1.0, yRef = 1.0, zRef = 0.0;
static GLdouble xVW = 0.0, yVW = 1.0, zVW = 0.0;

// Constants
#define AXIS_LENGTH 100.0
#define AXIS_LINE_WIDTH 2.0
#define CAR_LINE_WIDTH 5.0
static const GLfloat RED[] = { 0.19, 0.39, 0.74, 1.0 };

// Functions
void drawAxes();
void drawSuspension();
