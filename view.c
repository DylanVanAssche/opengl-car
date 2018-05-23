/*
#################################################################################
#	OpenGL futuristic soapbox car					                        	#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)			                      	#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	        #
#################################################################################
*/
#include "car.h"

// Draws the axes in the view
/*
 * GLint axes: show axes
 */
void drawAxes(GLint axes)
{
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
        glColor4fv(GREEN);
        glBegin(GL_LINES);
    		glVertex3d(0.0, 0.0, 0.0);
    		glVertex3d(AXIS_LENGTH, 0.0, 0.0);
    	glEnd();

        // Y axis
        glColor4fv(BLUE);
        glBegin(GL_LINES);
    		glVertex3d(0.0, 0.0, 0.0);
    		glVertex3d(0.0, AXIS_LENGTH, 0.0);
    	glEnd();
    }
}

// Draws a single checkpoint
/*
 * const GLfloat* color: color of the checkpoint
 */
void drawCheckpoint(const GLfloat* color)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
    glPointSize(POINT_LINE_WIDTH);
    glBegin(GL_POINTS);
        glVertex3d(0, 0, 0);
    glEnd();
}

// Configure all the light sources
/*
 * GLint ambientLight: ambient light enabled
 * GLint diffuseLight: diffuse light enabled
 * GLint specularLight: specular light enabled
 * GLint spotLight: spot light enabled
 * GLint spotAngle: spot angle in degrees
 * GLint spotExponent: spot exponent
 * GLint spotHeight: spot height
 * GLint drawPositions: show light positions
 */
void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight, GLint drawPositions) {
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

    // Draw positions if needed
    if(drawPositions) {
        glPointSize(POINT_LINE_WIDTH);
        glBegin(GL_POINTS);
            glVertex3fv(posLight0);
            glVertex3fv(posLight1);
            glVertex3fv(posLight2);
            glVertex3fv(posLight3);
        glEnd();
    }

    // Enable several lights
    ambientLight? glEnable(GL_LIGHT0): glDisable(GL_LIGHT0);
    diffuseLight? glEnable(GL_LIGHT1): glDisable(GL_LIGHT1);
    specularLight? glEnable(GL_LIGHT2): glDisable(GL_LIGHT2);
    spotLight? glEnable(GL_LIGHT3): glDisable(GL_LIGHT3);
}

// Configures the fog
/*
 * GLint fog: fog enabled
 * GLint fogMode: type of fog
 * GLfloat far: set the fog LINEAR END to far, we can't see further in projections
 */
void configureFog(GLint fog, GLint fogMode, GLfloat far)
{
    fog? glEnable(GL_FOG): glDisable(GL_FOG);
    glFogfv(GL_FOG_COLOR, BLUE_GRAY);

    if(fogMode) {
        // Exponent mode enabled
        // No start or end must be defined in this mode
        glFogf(GL_FOG_MODE, GL_EXP); // GL_EXP2 is also an option
        glFogf(GL_FOG_DENSITY, FOG_DENSITY);
    }
    else {
        // Lineair mode enabled
        // No density must be defined in this mode
        glFogf(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, FOG_START);
        glFogf(GL_FOG_END, far);
    }
}
