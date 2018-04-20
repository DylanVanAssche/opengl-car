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
        glColor3f(1.0, 0.0, 0.0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glScalef(2.0, 0.125, 0.25);
        glTranslatef(0.75, 0.5, 0.5);
        if(wireFrame) {
            glutWireCube(1.0);
        }
        else {
            glutSolidCube(1.0);
        }
	glPopMatrix();

    // Main beam Y axis
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glScalef(0.4, 0.125, 1.0);
        glTranslatef(4.25, 0.5, 0.125);
        if(wireFrame) {
            glutWireCube(1.0);
        }
        else {
            glutSolidCube(1.0);
        }
	glPopMatrix();

    // Wheel holder X axis
    glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glScalef(0.5, 0.125, 0.0625);
        glTranslatef(0.5, 0.5, 0.5);
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
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.125, 0.125, 0.125);
        glTranslatef(13.625, -1.0, 1.0);
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

void drawTires(GLint wireFrame) {
    GLUquadricObj *wheelFrontSide = gluNewQuadric();
    GLUquadricObj *wheelFrontTop = gluNewQuadric();
	GLUquadricObj *wheelFrontBottom = gluNewQuadric();

    // Front wheel
	glPushMatrix();
    	glScalef(0.2, 0.2, 0.150);
        glTranslatef(0.5, 0.5, 0.45);
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
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
    	gluCylinder(wheelFrontSide, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        gluDisk(wheelFrontBottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glTranslatef(0.0, 0.0, 1.0);
        gluDisk(wheelFrontTop, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);

    // Back wheel 1
    GLUquadricObj *wheelBack1Side = gluNewQuadric();
    GLUquadricObj *wheelBack1Top = gluNewQuadric();
	GLUquadricObj *wheelBack1Bottom = gluNewQuadric();

    glPushMatrix();
    	glScalef(0.2, 0.2, 0.33);
        glTranslatef(11.25, 0.5, 0.75);
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
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
    	gluCylinder(wheelBack1Side, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        gluDisk(wheelBack1Bottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glTranslatef(0.0, 0.0, 1.0);
        gluDisk(wheelBack1Top, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);

    // Back wheel 2
    GLUquadricObj *wheelBack2Side = gluNewQuadric();
    GLUquadricObj *wheelBack2Top = gluNewQuadric();
	GLUquadricObj *wheelBack2Bottom = gluNewQuadric();

    glPushMatrix();
    	glScalef(0.2, 0.2, 0.33);
        glTranslatef(11.25, 0.5, -1.0);
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
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_BLACK);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_BLACK);
    	gluCylinder(wheelBack2Side, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
        gluDisk(wheelBack2Bottom, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
        glTranslatef(0.0, 0.0, 1.0);
        gluDisk(wheelBack2Top, 0.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

	glPopMatrix();
	gluDeleteQuadric(wheelFrontSide);
    gluDeleteQuadric(wheelFrontTop);
    gluDeleteQuadric(wheelFrontBottom);
}

void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular) {
    /*
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AMBIENT_GREY);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DIFFUSE_GREY);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SPECULAR_GREY);
    */
    // TODO: Bezier curve
}
