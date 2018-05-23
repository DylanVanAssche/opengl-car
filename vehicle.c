/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Draws the vehicle suspension
/*
 * GLint wireFrame: wireframe enabled
 * GLfloat* ambient: ambient color
 * GLfloat* diffuse: diffuse color
 * GLfloat* specular: specular color
 */
void drawSuspension(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular)
{
    printf("Drawing suspension\n");

    // Materials
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    // Main beam X axis
	glPushMatrix();
        // Scaling and translating
        glScalef(2.0, 0.125, 0.25);
        glTranslatef(0.75, 0.5, 0.5);

        // Wireframe or solid?
        if(wireFrame) {
            glutWireCube(1.0);
        }
        else {
            glutSolidCube(1.0);
        }
	glPopMatrix();

    // Main beam Y axis
    glPushMatrix();
        // Scaling and translating
        glScalef(0.4, 0.125, 1.0);
        glTranslatef(4.25, 0.5, 0.125);

        // Wireframe or solid?
        if(wireFrame) {
            glutWireCube(1.0);
        }
        else {
            glutSolidCube(1.0);
        }
	glPopMatrix();

    // Wheel holder X axis
    glPushMatrix();
        // Scaling and translating
        glScalef(0.5, 0.125, 0.0625);
        glTranslatef(0.5, 0.5, 0.5);

        // Wireframe or solid?
        if(wireFrame) {
            glutWireCube(1.0);
        }
        else {
            glutSolidCube(1.0);
        }
	glPopMatrix();

    // Seat
    GLUquadricObj *seatBottom = gluNewQuadric();
    GLUquadricObj *seatTop = gluNewQuadric();

	glPushMatrix();
        // Rotating, scaling and translating
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.125, 0.125, 0.125);
        glTranslatef(13.625, -1.0, 1.0);

        // Wireframe or solid?
    	if(wireFrame)
        {
        	gluQuadricDrawStyle(seatBottom, GLU_SILHOUETTE);
            gluQuadricDrawStyle(seatTop, GLU_SILHOUETTE);
        }
    	else
        {
        	gluQuadricDrawStyle(seatBottom, GLU_FILL);
            gluQuadricDrawStyle(seatTop, GLU_FILL);
        }
    	gluCylinder(seatBottom, 1.0, 0.5, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS); // Cone
        glTranslatef(0.0, 0.0, 1.0); // The seat is on top of the cone
        gluDisk(seatTop, 0.0, 0.75, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(seatBottom);
    gluDeleteQuadric(seatTop);
}

// Draws the tires of the soapbox car
/*
 * GLint wireFrame: wireframe enabled
 * GLfloat animationAngle: angle of the tire due animation
 * GLuint textureAddressing[]: texture addressing array
 * GLint texture: texture enabled
 */
void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[], GLint texture)
{
    GLfloat tirePos[3][3] = { // 3 tires, 3D
        {0.5, 0.5, 0.45},
        {11.25, 0.5, 0.75},
        {11.25, 0.5, -1.0}
    };

    GLfloat tireScale[3][3] = { // 3 tires, 3D
        {0.2, 0.2, 0.150},
        {0.2, 0.2, 0.33},
        {0.2, 0.2, 0.33}
    };

    // Loop through the 3 tires
    for(GLint i=0; i < 3; i++) {
        GLUquadricObj *wheelSide = gluNewQuadric();
        GLUquadricObj *wheelTop = gluNewQuadric();
    	GLUquadricObj *wheelBottom = gluNewQuadric();
        glPushMatrix();
            // Scaling and translating
        	glScalef(tireScale[i][0], tireScale[i][1], tireScale[i][2]);
            glTranslatef(tirePos[i][0], tirePos[i][1], tirePos[i][2]);

            // Animation angle
            glRotatef(animationAngle, 0.0, 0.0, 1.0);

            // Wireframe or solid?
            if(wireFrame)
            {
                gluQuadricDrawStyle(wheelSide, GLU_SILHOUETTE);
                gluQuadricDrawStyle(wheelTop, GLU_SILHOUETTE);
                gluQuadricDrawStyle(wheelBottom, GLU_SILHOUETTE);
            }
            else
            {
                gluQuadricDrawStyle(wheelSide, GLU_FILL);
                gluQuadricDrawStyle(wheelTop, GLU_FILL);
                gluQuadricDrawStyle(wheelBottom, GLU_FILL);
            }

            // Textures enabled?
            texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);

            // Bind texture for the tire quadric
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_TIRE]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelSide, GL_TRUE);

            // Set materials and draw tire quadric
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
        	gluCylinder(wheelSide, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            // Bind texture for the rim
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_RIM]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBottom, GL_TRUE);
            gluQuadricTexture(wheelTop, GL_TRUE);

            // Set materials and draw rim
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GRAY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GRAY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GRAY);
            gluDisk(wheelBottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glTranslatef(0.0, 0.0, 1.0);
            gluDisk(wheelTop, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glPopMatrix();
    	gluDeleteQuadric(wheelSide);
        gluDeleteQuadric(wheelTop);
        gluDeleteQuadric(wheelBottom);
        glDisable(GL_TEXTURE_2D);
    }
}

// Draws the soapbox car coachwork
// No separate function for the coachwork since the only drawing 'component' is glEvalMesh2, the rest are init functions
/*
 * GLint wireFrame: wireframe enabled
 * GLfloat* ambient: ambient color
 * GLfloat* diffuse: diffuse color
 * GLfloat* specular: specular color
 * GLint clear: glass mode (blending)
 * GLint checkpoints: show checkpoints of the complex curve
 * GLuint textureAddressing[]: texture addressing array
 * GLint texture: texture enabled
 */
void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear, GLint checkpoints, GLuint textureAddressing[], GLint texture)
{
    GLfloat partScale[2][3] = { // 2 parts, 3D
        {1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0} // Mirror
    };

    GLfloat partTranslate[2][3] = { // 2 parts, 3D
        {0.0, 0.0, 0.0},
        {0.0, 0.0, -0.25} // Compensate non center of the vehicle
    };

    glPushMatrix();
        // Draw checkpoints if required
        if(checkpoints) {
            glPushMatrix();
                glTranslatef(0.0, 0.0, 0.125); // center on vehicle

                for(GLint k = 0; k < 2; k++) { // 2 pieces
                    for(GLint i = 0; i < COACHWORK_BEZIER_WIDTH; i++) {
                        for(GLint j = 0; j < COACHWORK_BEZIER_LENGTH; j++) {
                            glPushMatrix();
                                // Part 1
                                glTranslatef(coachworkCheckpoints[i][j][0], coachworkCheckpoints[i][j][1], coachworkCheckpoints[i][j][2]);
                                drawCheckpoint(RED);

                                // Part 2: Mirror (x2 to revert previous translation)
                                glTranslatef(0.0, 0.0, -2*coachworkCheckpoints[i][j][2]);
                                drawCheckpoint(GREEN);
                            glPopMatrix();
                        }
                    }
                }
            glPopMatrix();
        }

        // Materials
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

        // Texture binding
        texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_RIM]); // Just funny to put a rim on a coachwork ;-)

        // Bezier spline: u € [0,1] and v € [0,1] (definition of the Bezier forumula)
        // Bezier start and end are completely defined by P_first and P_last.
        // All the points between the first and last points are to define the spline itself (see p66).
        // No locale control possible with a Bezier spline, as soon as 1 point of the
        // checkpoints is changed, the whole spline is different.
        // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMap2.xml
        // Create Bezier spline map (checkpoints, limits, ...)
        glMap2f(
            GL_MAP2_VERTEX_3, // Type of vertex
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_DIMENSIONS, // uStride: number of floats or doubles between the beginning of control point Rij and the beginning of control point Ri(j+1)
            COACHWORK_BEZIER_LENGTH, // uOrder: dimension of the checkpoints array (u axis)
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_LENGTH*COACHWORK_BEZIER_DIMENSIONS, // vStride: number of floats or doubles between the beginning of control point Rij and the beginning of control point Ri(j+1)
            COACHWORK_BEZIER_WIDTH, // vOrder: dimension of the checkpoints array (v axis)
            &coachworkCheckpoints[0][0][0] // checkpoints
        );

        glEnable(GL_MAP2_VERTEX_3); // Enable Bezier spline
        // Bezier spline: u € [0,1] and v € [0,1] (definition of the Bezier forumula)
        // Bezier start and end are completely defined by P_first and P_last.
        // All the points between the first and last points are to define the spline itself (see p66).
        // No locale control possible with a Bezier spline, as soon as 1 point of the
        // checkpoints is changed, the whole spline is different.
        // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMap2.xml
        // Create Bezier spline map (checkpoints, limits, ...)
        glMap2f(
            GL_MAP2_TEXTURE_COORD_2, // Type of vertex
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_DIMENSIONS, // uStride: number of floats or doubles between the beginning of control point Rij and the beginning of control point Ri(j+1)
            COACHWORK_BEZIER_LENGTH, // uOrder: dimension of the checkpoints array (u axis)
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_LENGTH*COACHWORK_BEZIER_DIMENSIONS, // vStride: number of floats or doubles between the beginning of control point Rij and the beginning of control point Ri(j+1)
            COACHWORK_BEZIER_WIDTH, // vOrder: dimension of the checkpoints array (v axis)
            &coachworkCheckpoints[0][0][0] // checkpoints
        );

        glEnable(GL_MAP2_TEXTURE_COORD_2);

        // Uniform Bezier spline using MapGrid
        glMapGrid2f(
            COACHWORK_BEZIER_SUBDIVIONS, // Subdivions of the Bezier spline
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_SUBDIVIONS, // Subdivions of the Bezier spline
            0.0, // vMin
            1.0 // vMax
        );

        // Make the coachwork transparent when enabled
        clear? glEnable(GL_BLEND): glDisable(GL_BLEND);
        /*
            Order of drawing is important when handling transparent objects
            OpenGL should know which object comes first from the camera
            perspective to determine if you can see through the object or not.
            By making the depth buffer readonly we can avoid that newer objects
            interfere with the blending functions (p57).
            Solution:
                1. Draw all normal objects
                2. Make the depth buffer readonly
                3. Draw all blended objects
                4. Enable the depth buffer again
        */
        glDepthMask(GL_FALSE); // Disable depth mask before blending (p57)
    		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); // You can pick here different things to get other types of blending
            for(GLint i=0; i < 2; i++) {
                glScalef(partScale[i][0], partScale[i][1], partScale[i][2]); // Mirror
                glTranslatef(partTranslate[i][0], partTranslate[i][1], partTranslate[i][2]); // Car is not centered on the axis

                // Wireframe or not?
                if(wireFrame) {
                    glEvalMesh2(GL_LINE, 0, COACHWORK_GRID, 0, COACHWORK_GRID);
                }
                else {
                    glEvalMesh2(GL_FILL, 0, COACHWORK_GRID, 0, COACHWORK_GRID);
                }
            }
        glDepthMask(GL_TRUE); // Enable depth mask again
        glDisable(GL_BLEND); // Stop blending
        glDisable(GL_MAP2_TEXTURE_COORD_2);
        glDisable(GL_MAP2_VERTEX_3);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
