/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Draw the vehicle suspension
void drawSuspension() {
    printf("Drawing suspension\n");
    glLineWidth(CAR_LINE_WIDTH);
	glPushMatrix();
	   glColor3f(1.0, 0.0, 0.0);
	   glutWireCube(1.0);
	glPopMatrix();
}
