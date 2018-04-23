/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint competition, GLuint textureAddressing[], GLint texture) {
    // Cylinders
    GLUquadricObj *cylinder1 = gluNewQuadric();
    GLUquadricObj *cylinder2 = gluNewQuadric();

	glPushMatrix();
        // Rotating, scaling and translating
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.25, 1.25);
        competition? glTranslatef(0.0, -15.0, 0.0): glTranslatef(0.0, -5.0, 0.0);

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
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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
            competition? glTranslatef(0.0, 20.0, 0.0): glTranslatef(0.0, 10.0, 0.0);
            gluCylinder(cylinder2, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            // Arc (B-Spline) p72 TODO
            GLUnurbsObj *arcBSpline = gluNewNurbsRenderer();
            // https://www.talisman.org/opengl-1.1/Reference/gluNurbsProperty.html
            if(wireFrame) {
                gluNurbsProperty(
                    arcBSpline, // GLUnurbsObj
                    NULL, // Properties
                    GLU_FILL // Drawing method
                );
            }
            else {
                gluNurbsProperty(
                    arcBSpline, // GLUnurbsObj
                    NULL, // Properties
                    GLU_FILL // Drawing method
                );
            }
            gluBeginSurface(arcBSpline);
                // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                /*
                    Note that a gluNurbsSurface with sKnotCount knots in the u direction
                    and tKnotCount knots in the v direction with orders sOrder and tOrder
                    must have (sKnotCount - sOrder) x (tKnotCount - tOrder) control points.
                */
                gluNurbsSurface(
                    arcBSpline, // GLUnurbsObj
                    , // Number of knots in the u direction
                    , // Array of knots in the u direction
                    , // Number of knots in the v direction
                    , // Array of knots in the v direction
                    , // The offset between 2 checkpoints in the u direction
                    , // The offset between 2 checkpoints in the v direction
                    &arcCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                    ARC_BSPLINE_ORDER, // Order of the B spline in the u direction
                    ARC_BSPLINE_ORDER, // Order of the B Spline in the v direction
                    GL_MAP2_TEXTURE_COORD_2
                );
            gluEndSurface(arcBSpline);
        glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	gluDeleteQuadric(cylinder1);
    gluDeleteQuadric(cylinder2);
}
