/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

void drawArc(int wireFrame) {
    // Cylinders
    GLUquadricObj *cylinder1 = gluNewQuadric();
    GLUquadricObj *cylinder2 = gluNewQuadric();

	glPushMatrix();
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.25, 1.25);
        glTranslatef(0.0, -5.0, 0.0);
    	if(wireFrame)
        {
        	gluQuadricDrawStyle(cylinder1, GLU_SILHOUETTE);
            gluQuadricDrawStyle(cylinder2, GLU_SILHOUETTE);
        }
    	else
        {
        	gluQuadricDrawStyle(cylinder1, GLU_FILL);
            gluQuadricDrawStyle(cylinder2, GLU_FILL);
        }
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_YELLOW);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_YELLOW);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_YELLOW);
    	gluCylinder(cylinder1, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glTranslatef(0.0, 10.0, 0.0);
        gluCylinder(cylinder1, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(cylinder1);
    gluDeleteQuadric(cylinder2);
}
