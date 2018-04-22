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

void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[]) {
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
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[0]);
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

            glBindTexture(GL_TEXTURE_2D, textureAddressing[1]);
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
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[0]);
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

            glBindTexture(GL_TEXTURE_2D, textureAddressing[1]);
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
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[0]);
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

            glBindTexture(GL_TEXTURE_2D, textureAddressing[1]);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(wheelBack2Bottom, GL_TRUE);
            gluQuadricTexture(wheelBack2Top, GL_TRUE);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
            gluDisk(wheelBack2Bottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            glTranslatef(0.0, 0.0, 1.0);
            gluDisk(wheelBack2Top, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glDisable(GL_TEXTURE_2D); // Only the tire, not the rim

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);
}

void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear) {
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &coachworkCheckpoints[0][0][0]);
   	glEnable(GL_MAP2_VERTEX_3);
   	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

    glPushMatrix ();
	glColor3f(1.0, 0.0, 0.0);
	   for (int j = 0; j <= 8; j++) {
	      glBegin(GL_LINE_STRIP);
	      for (int i = 0; i <= 30; i++)
	         glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
	      glEnd();
	      glBegin(GL_LINE_STRIP);
	      for (int i = 0; i <= 30; i++)
	         glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
	      glEnd();
	   }
   glPopMatrix ();

    // Make the coachwork transparent when enabled
    if(clear) {
        glEnable(GL_BLEND);
    }

	glDepthMask(GL_FALSE); // Disable depth mask before blending
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA); // You can pick here different things to get other types of blending
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_GREY);
   		//glutSolidCone(0.4, 1.2, 10, 8);
	glDepthMask(GL_TRUE); // Enable depth mask again
	glDisable(GL_BLEND); // Stop blending
}
