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
#define MENU_BODYWORK_GREY 1
#define MENU_BODYWORK_WHITE 2
#define MENU_SUSPENSION_CHROME 3
#define MENU_SUSPENSION_BRONZE 4
#define MENU_FINISH_YELLOW 5
#define MENU_FINISH_LILAC 6
#define CAR_LINE_WIDTH 5.0
#define CAR_SUBDIVIONS 16 // change this if rendering performance is bad
static const GLfloat RED[] = {0.19, 0.39, 0.74, 1.0};

// Functions
void drawAxes(int axes);
void drawSuspension(int wireFrame);
void drawTires(int wireFrame);
