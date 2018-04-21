/*
#################################################################################
#	OpenGL futuristic soapbox car					                        	#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)			                      	#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	        #
#################################################################################
*/
#include "car.h"

void drawAxes(GLint axes) {
    if(axes) {
        printf("Drawing axes\n");
        glLineWidth(AXIS_LINE_WIDTH);

        // Z axis
        glColor4fv(RED);
    	glBegin(GL_LINES);
    		glVertex3d(0.0, 0.0, 0.0);
    		glVertex3d(0.0, 0.0, AXIS_LENGTH);
    	glEnd();

        // X axis
        glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            glColor4fv(GREEN);
            glBegin(GL_LINES);
        		glVertex3d(0.0, 0.0, 0.0);
        		glVertex3d(0.0, 0.0, AXIS_LENGTH);
        	glEnd();
        glPopMatrix();

        // Y axis
        glPushMatrix();
        	glRotatef(-90.0, 1.0, 0.0, 0.0);
            glColor4fv(BLUE);
            glBegin(GL_LINES);
        		glVertex3d(0.0, 0.0, 0.0);
        		glVertex3d(0.0, 0.0, AXIS_LENGTH);
        	glEnd();
        glPopMatrix();
    }
}

void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight) {
    GLfloat posLight0[] = {2.0, 5.0, 4.0, 1.0};
    GLfloat posLight1[] = {2.0, 5.0, 4.0, 1.0};
    GLfloat posLight2[] = {3.0, 3.0, 3.0, 1.0};
    GLfloat posLight3[] = {2.0, 5.0, 4.0, 1.0};

    // Light positions
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    glLightfv(GL_LIGHT1, GL_POSITION, posLight1);
    glLightfv(GL_LIGHT2, GL_POSITION, posLight2);
    glLightfv(GL_LIGHT3, GL_POSITION, posLight3);

    // Color of the lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, GREEN_BLUE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, RED);
	glLightfv(GL_LIGHT3, GL_SPECULAR, YELLOW);
    glLightfv(GL_LIGHT3, GL_SPECULAR, YELLOW);
    glLightfv(GL_LIGHT3, GL_SPECULAR, YELLOW);

    // Enable several lights
    ambientLight? glEnable(GL_LIGHT0): glDisable(GL_LIGHT0);
    diffuseLight? glEnable(GL_LIGHT1): glDisable(GL_LIGHT1);
    specularLight? glEnable(GL_LIGHT2): glDisable(GL_LIGHT2);
    spotLight? glEnable(GL_LIGHT3): glDisable(GL_LIGHT3);
}
