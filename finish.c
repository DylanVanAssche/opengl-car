/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint competition, GLuint textureAddressing[], GLint texture, GLint checkpoints) {
    GLfloat partScale[4][3] = { // 4 parts, 3D
        {1.0, 1.0, 1.0},
        {-1.0, 1.0, 1.0},
        {-1.0, -1.0, 1.0},
        {-1.0, 1.0, 1.0}
    };

    GLfloat partTranslate[4][3] = { // 4 parts, 3D
        {0.0, -0.875, 1.0}, // center + above pillars
        {0.0, 0.0, 0.0},
        {0.0, -5.0, 0.0}, // other pillar
        {0.0, 0.0, 0.0}
    };

    // Cylinders
    GLUquadricObj *cylinder1 = gluNewQuadric();
    GLUquadricObj *cylinder2 = gluNewQuadric();

    glPushMatrix();
        // Rotating, scaling and translating
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.25, 1.25);
        competition? glTranslatef(0.0, 2*FINISH_START_PILLARS, 0.0): glTranslatef(0.0, FINISH_START_PILLARS, 0.0);

        // Draw checkpoints if required
        if(checkpoints) {
            glPushMatrix();
            for(GLint i = 0; i < FINISH_BSPLINE_ORDER; i++) {
                for(GLint j = 0; j < FINISH_BSPLINE_ORDER; j++) {
                    // Part 1
                    glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, RED);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, RED);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, RED);
                        glTranslatef(finishCheckpoints[i][j][0], finishCheckpoints[i][j][1], finishCheckpoints[i][j][2] + 1.0); // Move above pillars
                        glutSolidSphere(CHECKPOINT_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                    glPopMatrix();

                    // Part 2
                    glPushMatrix();
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GREEN);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GREEN);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GREEN);
                        glTranslatef(finishCheckpoints[i][j][0], -finishCheckpoints[i][j][1], finishCheckpoints[i][j][2] + 1.0); // Move above pillars
                        glutSolidSphere(CHECKPOINT_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                    glPopMatrix();

                    // Part 3
                    glPushMatrix();
                        competition? glTranslatef(0.0, 2*FINISH_DISTANCE_PILLARS, 0.0): glTranslatef(0.0, FINISH_DISTANCE_PILLARS, 0.0);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BLUE);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLUE);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BLUE);
                        glTranslatef(finishCheckpoints[i][j][0], -finishCheckpoints[i][j][1], finishCheckpoints[i][j][2] + 1.0); // Move above pillars
                        glutSolidSphere(CHECKPOINT_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                    glPopMatrix();

                    // Part 4
                    glPushMatrix();
                        competition? glTranslatef(0.0, 2*FINISH_DISTANCE_PILLARS, 0.0): glTranslatef(0.0, FINISH_DISTANCE_PILLARS, 0.0);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, BLACK);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, BLACK);
                        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, BLACK);
                        glTranslatef(finishCheckpoints[i][j][0], finishCheckpoints[i][j][1], finishCheckpoints[i][j][2] + 1.0); // Move above pillars
                        glutSolidSphere(CHECKPOINT_RADIUS, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
                    glPopMatrix();
                }
            }
            glPopMatrix();
        }

        // Wireframe or not?
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

        // Textures
        texture? glEnable(GL_TEXTURE_2D): glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_FINISH]);
        	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            gluQuadricTexture(cylinder1, GL_TRUE);
            gluQuadricTexture(cylinder2, GL_TRUE);

            // Set materials before drawing
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

            // Pillars (Cylinders)
        	gluCylinder(cylinder1, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);
            competition? glTranslatef(0.0, 2*FINISH_DISTANCE_PILLARS, 0.0): glTranslatef(0.0, FINISH_DISTANCE_PILLARS, 0.0);
            gluCylinder(cylinder2, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            // Arc (B-Spline) p72
            glPushMatrix();
                competition? glScalef(0.25, 3.0, 1.0): glScalef(0.25, 1.5, 1.0);
                glEnable(GL_MAP2_VERTEX_3);
                glEnable(GL_MAP2_TEXTURE_COORD_2);
                    for(GLint i=0; i < 4; i++) {
                        // Create GLUnurbsObj and configure it
                        GLUnurbsObj *arcBSplinePart = gluNewNurbsRenderer();
                        gluNurbsProperty(arcBSplinePart, GLU_SAMPLING_TOLERANCE, FINISH_BSPLINE_SAMPLING);
                        if(wireFrame) {
                            gluNurbsProperty(arcBSplinePart, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
                        }
                        else {
                            gluNurbsProperty(arcBSplinePart, GLU_DISPLAY_MODE, GLU_FILL);
                        }

                        // Translate and scale
                        glTranslatef(partTranslate[i][0], partTranslate[i][1], partTranslate[i][2]);
                        glScalef(partScale[i][0], partScale[i][1], partScale[i][2]);

                        // Draw Nurbs surface with texture (if enabled)
                        gluBeginSurface(arcBSplinePart);
                            // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                            // Texture mapping
                            gluNurbsSurface(
                                arcBSplinePart, // GLUnurbsObj
                                2*FINISH_BSPLINE_ORDER, // Number of knots in the u direction
                                knots, // Array of knots in the u direction
                                2*FINISH_BSPLINE_ORDER, // Number of knots in the v direction
                                knots, // Array of knots in the v direction
                                FINISH_BSPLINE_ORDER*FINISH_BSPLINE_DIMENSION, // The offset between 2 checkpoints in the u direction
                                FINISH_BSPLINE_DIMENSION, // The offset between 2 checkpoints in the v direction
                                &finishCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                                FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                                FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                                GL_MAP2_TEXTURE_COORD_2
                            );
                            // BSpline surface
                            gluNurbsSurface(
                                arcBSplinePart, // GLUnurbsObj
                                2*FINISH_BSPLINE_ORDER, // Number of knots in the u direction
                                knots, // Array of knots in the u direction
                                2*FINISH_BSPLINE_ORDER, // Number of knots in the v direction
                                knots, // Array of knots in the v direction
                                FINISH_BSPLINE_ORDER*FINISH_BSPLINE_DIMENSION, // The offset between 2 checkpoints in the u direction
                                FINISH_BSPLINE_DIMENSION, // The offset between 2 checkpoints in the v direction
                                &finishCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                                FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                                FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                                GL_MAP2_VERTEX_3
                            );
                        gluEndSurface(arcBSplinePart);
                    }
                glDisable(GL_MAP2_VERTEX_3);
                glDisable(GL_MAP2_TEXTURE_COORD_2);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	gluDeleteQuadric(cylinder1);
    gluDeleteQuadric(cylinder2);
}
