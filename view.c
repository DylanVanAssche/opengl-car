/*
#################################################################################
#	OpenGL futuristic soapbox car					                        	#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)			                      	#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	        #
#################################################################################
*/
#include "car.h"

void drawAxes(int axes) {
    if(axes) {
        printf("Drawing axes\n");
        glLineWidth(AXIS_LINE_WIDTH);
        glColor4fv(RED);

        // Z axis
    	glBegin(GL_LINES);
    		glVertex3d(0.0, 0.0, 0.0);
    		glVertex3d(0.0, 0.0, AXIS_LENGTH);
    	glEnd();

        // X axis
        glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            glBegin(GL_LINES);
        		glVertex3d(0.0, 0.0, 0.0);
        		glVertex3d(0.0, 0.0, AXIS_LENGTH);
        	glEnd();
        glPopMatrix();

        // Y axis
        glPushMatrix();
        	glRotatef(-90.0, 1.0, 0.0, 0.0);
            glBegin(GL_LINES);
        		glVertex3d(0.0, 0.0, 0.0);
        		glVertex3d(0.0, 0.0, AXIS_LENGTH);
        	glEnd();
        glPopMatrix();
    }
}
