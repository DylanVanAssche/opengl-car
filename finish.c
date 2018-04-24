/*
#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################
*/
#include "car.h"

void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint competition, GLuint textureAddressing[], GLint texture, GLint checkpoints) {
    /*int u, v;
   for (u = 0; u < 4; u++) {
      for (v = 0; v < 4; v++) {
         arcCheckpoints[u][v][0] = 2.0*((GLfloat)u - 1.5);
         arcCheckpoints[u][v][1] = 2.0*((GLfloat)v - 1.5);

         if ( (u == 1 || u == 2) && (v == 1 || v == 2))
            arcCheckpoints[u][v][2] = 3.0;
         else
            arcCheckpoints[u][v][2] = -3.0;
      }
  }*/

    // Cylinders
    GLUquadricObj *cylinder1 = gluNewQuadric();
    GLUquadricObj *cylinder2 = gluNewQuadric();

	glPushMatrix();
        // Rotating, scaling and translating
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glScalef(0.25, 0.25, 1.25);
        competition? glTranslatef(0.0, 2*FINISH_START_PILLARS, 0.0): glTranslatef(0.0, FINISH_START_PILLARS, 0.0);

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
            competition? glTranslatef(0.0, 2*FINISH_DISTANCE_PILLARS, 0.0): glTranslatef(0.0, FINISH_DISTANCE_PILLARS, 0.0);
            gluCylinder(cylinder2, 1.0, 1.0, 1.0, CAR_SUBDIVIONS, CAR_SUBDIVIONS);

            // Arc (B-Spline) p72
            glPushMatrix();
                glScalef(0.25, 1.5, 1.0);
                glTranslatef(0.0, -0.875, 1.0);

                // Bind texture
                glBindTexture(GL_TEXTURE_2D, textureAddressing[TEXTURE_FINISH]);
            	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                // Set materials before drawing
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

                GLUnurbsObj *arcBSpline1 = gluNewNurbsRenderer();
                GLUnurbsObj *arcBSpline2 = gluNewNurbsRenderer();
                GLUnurbsObj *arcBSpline3 = gluNewNurbsRenderer();
                GLUnurbsObj *arcBSpline4 = gluNewNurbsRenderer();
                // https://www.talisman.org/opengl-1.1/Reference/gluNurbsProperty.html
                gluNurbsProperty(arcBSpline1, GLU_SAMPLING_TOLERANCE, FINISH_BSPLINE_SAMPLING);
                gluNurbsProperty(arcBSpline2, GLU_SAMPLING_TOLERANCE, FINISH_BSPLINE_SAMPLING);
                if(wireFrame) {
                    gluNurbsProperty(
                        arcBSpline1, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_OUTLINE_POLYGON // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline2, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_OUTLINE_POLYGON // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline3, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_OUTLINE_POLYGON // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline4, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_OUTLINE_POLYGON // Value of the property
                    );
                }
                else {
                    gluNurbsProperty(
                        arcBSpline1, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_FILL // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline2, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_FILL // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline3, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_FILL // Value of the property
                    );

                    gluNurbsProperty(
                        arcBSpline4, // GLUnurbsObj
                        GLU_DISPLAY_MODE, // Property
                        GLU_FILL // Value of the property
                    );
                }

                // Part 1
                gluBeginSurface(arcBSpline1);
                    // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                    /*
                        Note that a gluNurbsSurface with sKnotCount knots in the u direction
                        and tKnotCount knots in the v direction with orders sOrder and tOrder
                        must have (sKnotCount - sOrder) x (tKnotCount - tOrder) control points.
                    */
                    gluNurbsSurface(
                        arcBSpline1, // GLUnurbsObj
                        8, // Number of knots in the u direction
                        knots, // Array of knots in the u direction
                        8, // Number of knots in the v direction
                        knots, // Array of knots in the v direction
                        4*3, // The offset between 2 checkpoints in the u direction
                        3, // The offset between 2 checkpoints in the v direction
                        &arcCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                        4, //FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                        4, //FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                        GL_MAP2_VERTEX_3
                    );
                gluEndSurface(arcBSpline1);

                // Part 2
                glScalef(-1.0, 1.0, 1.0);
                gluBeginSurface(arcBSpline2);
                    // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                    /*
                        Note that a gluNurbsSurface with sKnotCount knots in the u direction
                        and tKnotCount knots in the v direction with orders sOrder and tOrder
                        must have (sKnotCount - sOrder) x (tKnotCount - tOrder) control points.
                    */
                    gluNurbsSurface(
                        arcBSpline2, // GLUnurbsObj
                        8, // Number of knots in the u direction
                        knots, // Array of knots in the u direction
                        8, // Number of knots in the v direction
                        knots, // Array of knots in the v direction
                        4*3, // The offset between 2 checkpoints in the u direction
                        3, // The offset between 2 checkpoints in the v direction
                        &arcCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                        4, //FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                        4, //FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                        GL_MAP2_VERTEX_3
                    );
                gluEndSurface(arcBSpline2);

                // Part 3
                glTranslatef(0.0, -5.0, 0.0);
                glScalef(-1.0, -1.0, 1.0);
                gluBeginSurface(arcBSpline3);
                    // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                    /*
                        Note that a gluNurbsSurface with sKnotCount knots in the u direction
                        and tKnotCount knots in the v direction with orders sOrder and tOrder
                        must have (sKnotCount - sOrder) x (tKnotCount - tOrder) control points.
                    */
                    gluNurbsSurface(
                        arcBSpline3, // GLUnurbsObj
                        8, // Number of knots in the u direction
                        knots, // Array of knots in the u direction
                        8, // Number of knots in the v direction
                        knots, // Array of knots in the v direction
                        4*3, // The offset between 2 checkpoints in the u direction
                        3, // The offset between 2 checkpoints in the v direction
                        &arcCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                        4, //FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                        4, //FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                        GL_MAP2_VERTEX_3
                    );
                gluEndSurface(arcBSpline3);

                // Part 4
                glScalef(-1.0, 1.0, 1.0);
                gluBeginSurface(arcBSpline4);
                    // https://www.talisman.org/opengl-1.1/Reference/gluNurbsSurface.html
                    /*
                        Note that a gluNurbsSurface with sKnotCount knots in the u direction
                        and tKnotCount knots in the v direction with orders sOrder and tOrder
                        must have (sKnotCount - sOrder) x (tKnotCount - tOrder) control points.
                    */
                    gluNurbsSurface(
                        arcBSpline4, // GLUnurbsObj
                        8, // Number of knots in the u direction
                        knots, // Array of knots in the u direction
                        8, // Number of knots in the v direction
                        knots, // Array of knots in the v direction
                        4*3, // The offset between 2 checkpoints in the u direction
                        3, // The offset between 2 checkpoints in the v direction
                        &arcCheckpoints[0][0][0], // Checkpoints for the B Spline arc
                        4, //FINISH_BSPLINE_ORDER, // Order of the B spline in the u direction
                        4, //FINISH_BSPLINE_ORDER, // Order of the B Spline in the v direction
                        GL_MAP2_TEXTURE_COORD_2
                    );
                gluEndSurface(arcBSpline4);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	gluDeleteQuadric(cylinder1);
    gluDeleteQuadric(cylinder2);
}
