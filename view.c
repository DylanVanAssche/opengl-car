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

void drawCheckpoints(GLfloat*** checkpoints, GLfloat color[], GLint u, GLint v) {
    for(GLint i=0; i < u; i++) {
        for(GLint j=0; j < v; j++) {
            glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
                glTranslatef(checkpoints[i][j][0], checkpoints[i][j][1], checkpoints[i][j][2]); // Move above pillars
                glutSolidSphere(CHECKPOINT_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glPopMatrix();
        }
    }
}

void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight) {
    // Update spot height
    posLight3[1] = spotHeight;

    // Light positions
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    glLightfv(GL_LIGHT1, GL_POSITION, posLight1);
    glLightfv(GL_LIGHT2, GL_POSITION, posLight2);
    glLightfv(GL_LIGHT3, GL_POSITION, posLight3);

    // Color of the lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, WHITE);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, GREEN_BLUE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, RED);
	glLightfv(GL_LIGHT3, GL_AMBIENT, YELLOW);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, YELLOW);
    glLightfv(GL_LIGHT3, GL_SPECULAR, YELLOW);

    // Spot
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponent);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection);

    // Enable several lights
    ambientLight? glEnable(GL_LIGHT0): glDisable(GL_LIGHT0);
    diffuseLight? glEnable(GL_LIGHT1): glDisable(GL_LIGHT1);
    specularLight? glEnable(GL_LIGHT2): glDisable(GL_LIGHT2);
    spotLight? glEnable(GL_LIGHT3): glDisable(GL_LIGHT3);
}

void configureFog(GLint fog, GLint fogMode, GLfloat far) {
    fog? glEnable(GL_FOG): glDisable(GL_FOG);
    glFogfv(GL_FOG_COLOR, BLUE_GRAY);

    if(fogMode) {
        glFogf(GL_FOG_MODE, GL_EXP); // GL_EXP2 is also an option
        glFogf(GL_FOG_DENSITY, FOG_DENSITY);
    }
    else {
        glFogf(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, FOG_START);
        glFogf(GL_FOG_END, far);
    }
}
