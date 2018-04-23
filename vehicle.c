/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

// Draw the vehicle suspension
void drawSuspension(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular) {
    printf("Drawing suspension\n");
    glLineWidth(CAR_LINE_WIDTH);

    // Main beam X axis
	glPushMatrix();
        // Materials
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

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
        // Materials
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

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
        // Materials
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

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

        // Set materials before drawing
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    	gluCylinder(seatBottom, 1.0, 0.5, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS); // cone
        glTranslatef(0.0, 0.0, 1.0);
        gluDisk(seatTop, 0.0, 0.75, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(seatBottom);
    gluDeleteQuadric(seatTop);
}

void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[], GLint texture) {
    GLUquadricObj *wheelFrontSide = gluNewQuadric();
    GLUquadricObj *wheelFrontTop = gluNewQuadric();
	GLUquadricObj *wheelFrontBottom = gluNewQuadric();

    // Front wheel
	glPushMatrix();
        // Scaling and translating
    	glScalef(0.2, 0.2, 0.150);
        glTranslatef(0.5, 0.5, 0.45);

        // Animation angle
        glRotatef(animationAngle, 0.0, 0.0, 1.0);

        // Wireframe or solid?
    	if(wireFrame)
        {
        	gluQuadricDrawStyle(wheelFrontSide, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelFrontTop, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelFrontBottom, GLU_SILHOUETTE);
        }
    	else
        {
        	gluQuadricDrawStyle(wheelFrontSide, GLU_FILL);
            gluQuadricDrawStyle(wheelFrontTop, GLU_FILL);
            gluQuadricDrawStyle(wheelFrontBottom, GLU_FILL);
        }

        // Add textures
        texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_TIRE]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelFrontSide, GL_TRUE);

            // Set materials before drawing
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
        	gluCylinder(wheelFrontSide, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_RIM]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelFrontBottom, GL_TRUE);
            gluQuadricTexture(wheelFrontTop, GL_TRUE);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            gluDisk(wheelFrontBottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glTranslatef(0.0, 0.0, 1.0);
            gluDisk(wheelFrontTop, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glDisable(GL_TEXTURE_2D); // Only the tire, not the rim

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);

    // Back wheel 1
    GLUquadricObj *wheelBack1Side = gluNewQuadric();
    GLUquadricObj *wheelBack1Top = gluNewQuadric();
	GLUquadricObj *wheelBack1Bottom = gluNewQuadric();

    glPushMatrix();
        // Scaling and translating
    	glScalef(0.2, 0.2, 0.33);
        glTranslatef(11.25, 0.5, 0.75);

        // Animation angle
        glRotatef(animationAngle, 0.0, 0.0, 1.0);

        // Wireframe or solid?
    	if(wireFrame)
        {
        	gluQuadricDrawStyle(wheelBack1Side, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelBack1Top, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelBack1Bottom, GLU_SILHOUETTE);
        }
    	else
        {
        	gluQuadricDrawStyle(wheelBack1Side, GLU_FILL);
            gluQuadricDrawStyle(wheelBack1Top, GLU_FILL);
            gluQuadricDrawStyle(wheelBack1Bottom, GLU_FILL);
        }

        // Set materials before drawing
        texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_TIRE]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBack1Side, GL_TRUE);

            // Set materials before drawing
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
        	gluCylinder(wheelBack1Side, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_RIM]);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBack1Bottom, GL_TRUE);
            gluQuadricTexture(wheelBack1Top, GL_TRUE);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            gluDisk(wheelBack1Bottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glTranslatef(0.0, 0.0, 1.0);
            gluDisk(wheelBack1Top, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);

    // Back wheel 2
    GLUquadricObj *wheelBack2Side = gluNewQuadric();
    GLUquadricObj *wheelBack2Top = gluNewQuadric();
	GLUquadricObj *wheelBack2Bottom = gluNewQuadric();

    glPushMatrix();
        // Scaling and translating
    	glScalef(0.2, 0.2, 0.33);
        glTranslatef(11.25, 0.5, -1.0);

        // Animation angle
        glRotatef(animationAngle, 0.0, 0.0, 1.0);

        // Wireframe or solid?
    	if(wireFrame)
        {
        	gluQuadricDrawStyle(wheelBack2Side, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelBack2Top, GLU_SILHOUETTE);
            gluQuadricDrawStyle(wheelBack2Bottom, GLU_SILHOUETTE);
        }
    	else
        {
        	gluQuadricDrawStyle(wheelBack2Side, GLU_FILL);
            gluQuadricDrawStyle(wheelBack2Top, GLU_FILL);
            gluQuadricDrawStyle(wheelBack2Bottom, GLU_FILL);
        }

        // Set materials before drawing
        texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_TIRE]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBack2Side, GL_TRUE);

            // Set materials before drawing
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
        	gluCylinder(wheelBack2Side, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_RIM]);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBack2Bottom, GL_TRUE);
            gluQuadricTexture(wheelBack2Top, GL_TRUE);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_GREY);
            gluDisk(wheelBack2Bottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glTranslatef(0.0, 0.0, 1.0);
            gluDisk(wheelBack2Top, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glDisable(GL_TEXTURE_2D); // Only the tire, not the rim

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);
}

void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear, GLint mesh) {
    glPushMatrix();
        // Bezier spline: u € [0,1] and v € [0,1] (definition of the Bezier forumula)
        // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMap2.xml
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
        glEnable(GL_MAP2_VERTEX_3);
        glMapGrid2f(
            COACHWORK_BEZIER_SUBDIVIONS, // Subdivions of the Bezier spline
            0.0, // uMin
            1.0, // uMax
            COACHWORK_BEZIER_SUBDIVIONS, // Subdivions of the Bezier spline
            0.0, // vMin
            1.0 // vMax
        );

        // Draw point mesh if required
        if(mesh) {
            printf("Drawing mesh\n");
            glPushMatrix();
                for(GLint i = 0; i < COACHWORK_BEZIER_WIDTH; i++) {
                    for(GLint j = 0; j < COACHWORK_BEZIER_LENGTH; j++) {
                        // Normal
                        glPushMatrix();
                            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RED);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, RED);
                            glTranslatef(coachworkCheckpoints[i][j][0], coachworkCheckpoints[i][j][1], coachworkCheckpoints[i][j][2]);
                            glutSolidSphere(COACHWORK_BEZIER_MESH_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                        glPopMatrix();

                        // Mirror
                        glPushMatrix();
                            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREEN);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GREEN);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GREEN);
                            glTranslatef(coachworkCheckpoints[i][j][0], coachworkCheckpoints[i][j][1], -coachworkCheckpoints[i][j][2]);
                            glutSolidSphere(COACHWORK_BEZIER_MESH_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                        glPopMatrix();
                    }
                }
            glPopMatrix();
        }

        // Make the coachwork transparent when enabled
        clear? glEnable(GL_BLEND): glDisable(GL_BLEND);

        /*
            Order of drawing is important when handling transparent objects
            OpenGL should know which object comes first from the camera
            perspective to determine if you can see through the object or not.
            By making the depth buffer readonly we can avoid that newer objects
            interfere with the blending functions.
            Solution:
                1. Draw all normal objects
                2. Make the depth buffer readonly
                3. Draw all blended objects
                4. Enable the depth buffer again
        */
        glDepthMask(GL_FALSE); // Disable depth mask before blending (p57)
    		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); // You can pick here different things to get other types of blending
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
            // Part 1
            if(wireFrame) {
                glEvalMesh2(GL_LINE, 0, COACHWORK_GRID, 0, COACHWORK_GRID);
            }
            else {
                glEvalMesh2(GL_FILL, 0, COACHWORK_GRID, 0, COACHWORK_GRID);
            }
            // Part 2 (mirror)
            glScalef(1.0, 1.0, -1.0); // mirror
            glTranslatef(0.0, 0.0, -0.25); // car is not centered on the axis
            if(wireFrame) {
                glEvalMesh2(GL_LINE, 0, 20, 0, 20);
            }
            else {
                glEvalMesh2(GL_FILL, 0, 20, 0, 20);
            }
            glDisable(GL_MAP2_VERTEX_3);
        glDepthMask(GL_TRUE); // Enable depth mask again
        glDisable(GL_BLEND); // Stop blending
    glPopMatrix();
}
