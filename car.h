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
#include "InitJPG.h"

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
#define ANIMATION_WHEEL_STEP 5
#define ANIMATION_CAR_STEP -0.05 // driving in the opposite direction
#define MATERIAL_SHININESS_STEP 5.0
#define SPOT_EXPONENT_DEFAULT 20.0
#define SPOT_EXPONENT_STEP 5.0
#define SPOT_ANGLE_DEFAULT 0.0
#define SPOT_HEIGHT_DEFAULT 0.0
#define NUMBER_OF_TEXTURES 3
#define TEXTURE_TIRE 0
#define TEXTURE_RIM 1
#define TEXTURE_FINISH 2
#define TEXTURE_NAME_LENGTH 30
#define COACHWORK_BEZIER_DIMENSIONS 3 // 3D checkpoints
#define COACHWORK_BEZIER_LENGTH 6 // 6 checkpoints for the length of the coachwork
#define COACHWORK_BEZIER_WIDTH 4 // 4 checkpoints for the width of the coachwork
#define COACHWORK_BEZIER_SUBDIVIONS 20.0
#define COACHWORK_BEZIER_MESH_RADIUS 0.05
#define COACHWORK_GRID 20
#define ARC_BSPLINE_ORDER 4
#define ARC_BSPLINE_DEGREE 3
#define ARC_BSPLINE_CHECKPOINTS 4

// Textures and complex surfaces
static const char tireTexture[TEXTURE_NAME_LENGTH] = "./images/tire.jpg";
static const char rimTexture[TEXTURE_NAME_LENGTH] = "./images/rim.jpg";
static const char finishTexture[TEXTURE_NAME_LENGTH] = "./images/finish.jpg";
static GLuint textureAddressing[NUMBER_OF_TEXTURES];

// Bezier surface 6x4 3D points (6 length, 4 width)
static GLfloat coachworkCheckpoints[COACHWORK_BEZIER_WIDTH][COACHWORK_BEZIER_LENGTH][COACHWORK_BEZIER_DIMENSIONS] = {
    // 2 points extra for the length of the coachwork to provide a cutout for the seat
   {
       {0.5, 0.0, 0.33},
       {1.0, 0.0, 0.66},
       {1.5, 0.0, 0.66},
       {1.7, 0.0, 0.66},
       {1.9, 0.0, 0.66},
       {2.0, 0.0, 0.66}
   },
   {
       {0.0, 0.25, 0.33},
       {0.5, 0.25, 0.66},
       {1.5, 0.25, 0.66},
       {1.7, 0.25, 0.66},
       {1.9, 0.25, 0.66},
       {2.0, 0.25, 0.66}
   },
   {
       {0.0, 0.375, 0.33},
       {0.5, 0.375, 0.66},
       {1.5, 0.375, 0.66},
       {1.7, 0.375, 0.66},
       {1.9, 0.375, 0.66},
       {2.0, 0.375, 0.66}
   },
   {
       {0.0, 0.4, 0.125},
       {0.5, 0.4, 0.125},
       {1.5, 0.4, 0.125},
       {1.8, 0.4, 0.125},
       {1.9, 0.4, 0.45},
       {2.5, 0.4, 0.5}
   }
};

// B Spline order = 4 (degree = 3), C X C checkpoints where C >= 4
static GLfloat arcCheckpoints[COACHWORK_BEZIER_WIDTH][COACHWORK_BEZIER_LENGTH][COACHWORK_BEZIER_DIMENSIONS] = // 6x4 3D points (6 length, 4 width)
{
    {}
}

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
void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[], GLint texture);
void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear, GLint mesh);
void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight);
void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint competition, GLuint textureAddressing[], GLint texture);
