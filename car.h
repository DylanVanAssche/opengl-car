/*
#################################################################################
#	OpenGL futuristic soapbox car					                        	#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)			                      	#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	        #
#################################################################################
*/

#ifndef CAR_H
#define CAR_H // include guard

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
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 720
#define PROJECTION_XMIN -50.0
#define PROJECTION_YMIN -50.0
#define PROJECTION_XMAX 50.0
#define PROJECTION_YMAX 50.0
#define PROJECTION_NEAR 0.1
#define PROJECTION_FAR 25.0
#define PROJECTION_ANGLE 60.0
#define PROJECTION_ASPECT_RATIO 1.0
#define VIEW_RESET_POS 5.0
#define AXIS_LENGTH 100.0
#define AXIS_LINE_WIDTH 2.0
#define POINT_LINE_WIDTH 5.0
#define MENU_QUIT 0
#define MENU_COACHWORK_GRAY 1
#define MENU_COACHWORK_WHITE 2
#define MENU_SUSPENSION_CHROME 3
#define MENU_SUSPENSION_BRONZE 4
#define MENU_FINISH_YELLOW 5
#define MENU_FINISH_LILAC 6
#define CAR_LINE_WIDTH 5.0
#define CAR_SUBDIVIONS 50 // change this if rendering performance is bad on HP Thin CLients
#define ANIMATION_SPEED 50 // Don't fry the GPU please
#define ANIMATION_WHEEL_STEP 25
#define ANIMATION_CAR_STEP -0.5 // driving in the opposite direction
#define MATERIAL_SHININESS_STEP 5.0
#define MATERIAL_SHININESS_MIN 0.0
#define MATERIAL_SHININESS_MAX 128.0
#define SPOT_EXPONENT_DEFAULT 20.0
#define SPOT_EXPONENT_STEP 5.0
#define SPOT_ANGLE_DEFAULT 40.0
#define SPOT_HEIGHT_DEFAULT 3.0
#define NUMBER_OF_TEXTURES 3
#define TEXTURE_TIRE 0
#define TEXTURE_RIM 1
#define TEXTURE_FINISH 2
#define TEXTURE_NAME_LENGTH 30
#define CHECKPOINT_RADIUS 0.05
#define COACHWORK_BEZIER_DIMENSIONS 3 // 3D checkpoints
#define COACHWORK_BEZIER_LENGTH 6 // 6 checkpoints for the length of the coachwork
#define COACHWORK_BEZIER_WIDTH 4 // 4 checkpoints for the width of the coachwork
#define COACHWORK_BEZIER_SUBDIVIONS 20.0
#define COACHWORK_GRID 20
#define FINISH_PILLAR_HEIGHT 2.0
#define FINISH_BSPLINE_ORDER 4
#define FINISH_BSPLINE_DEGREE 3
#define FINISH_BSPLINE_CHECKPOINTS 4
#define FINISH_BSPLINE_SAMPLING 25.0
#define FINISH_BSPLINE_DIMENSION 3
#define FOG_DENSITY 0.25 // Exponent mode only
#define FOG_START 0.0 // Linear mode only

// Lights
extern GLfloat posLight0[];
extern GLfloat posLight1[];
extern GLfloat posLight2[];
extern GLfloat posLight3[];
extern GLfloat spotDirection[];

// Textures and complex surfaces
extern const char nameTexture[NUMBER_OF_TEXTURES][TEXTURE_NAME_LENGTH];
extern GLuint textureAddressing[NUMBER_OF_TEXTURES];

// Bezier surface 6x4 3D points (6 length (order n = 5), 4 width (order n = 3))
extern GLfloat coachworkCheckpoints[COACHWORK_BEZIER_WIDTH][COACHWORK_BEZIER_LENGTH][COACHWORK_BEZIER_DIMENSIONS];

// B Spline order = 4 (degree = 3), C X C checkpoints where C >= 4
// Circle math: X^2 + Y^2 = R^2 is required to figure out the checkpoints!
// I splitted the 2 circle cords to keep it understandable...
extern GLfloat finishCheckpoints[FINISH_BSPLINE_ORDER][FINISH_BSPLINE_ORDER][FINISH_BSPLINE_DIMENSION];
// Knots: how heavy each point weights on the B Spline
extern GLfloat knots[2*FINISH_BSPLINE_ORDER];

// Colors
extern GLfloat RED[];
extern GLfloat GREEN[];
extern GLfloat BLUE[];
extern GLfloat GREEN_BLUE[];
extern GLfloat YELLOW[];
extern GLfloat WHITE[];
extern GLfloat BLACK[];
extern GLfloat BLUE_GRAY[];

// Materials
extern GLfloat AMBIENT_GRAY[];
extern GLfloat DIFFUSE_GRAY[];
extern GLfloat SPECULAR_GRAY[];
extern GLfloat AMBIENT_BLACK[];
extern GLfloat DIFFUSE_BLACK[];
extern GLfloat SPECULAR_BLACK[];
extern GLfloat AMBIENT_WHITE[];
extern GLfloat DIFFUSE_WHITE[];
extern GLfloat SPECULAR_WHITE[];
extern GLfloat AMBIENT_CHROME[];
extern GLfloat DIFFUSE_CHROME[];
extern GLfloat SPECULAR_CHROME[];
extern GLfloat AMBIENT_BRONZE[];
extern GLfloat DIFFUSE_BRONZE[];
extern GLfloat SPECULAR_BRONZE[];
extern GLfloat AMBIENT_YELLOW[];
extern GLfloat DIFFUSE_YELLOW[];
extern GLfloat SPECULAR_YELLOW[];
extern GLfloat AMBIENT_LILA[];
extern GLfloat DIFFUSE_LILA[];
extern GLfloat SPECULAR_LILA[];

// Functions
void drawAxes(GLint axes);
void drawCheckpoint(const GLfloat* color);
void drawSuspension(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[], GLint texture);
void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear, GLint checkpoints, GLuint textureAddressing[], GLint texture);
void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight, GLint drawPositions);
void configureFog(GLint fog, GLint fogMode, GLfloat far);
void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLuint textureAddressing[], GLint texture, GLint checkpoints);

#endif // CAR_H
