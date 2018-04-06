/*
#################################################################################
#	OpenGL futuristic soapbox car						#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)				#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)	#
#################################################################################
*/

#define BESTN "gegev.txt"
#define AANTA 20
#define NLEN 11
#define WLEN 53
#define PADDING 0.05
#define X_RAND 0.1
#define Y_RAND 0.2

typedef struct gebruik
        {
            char naam[NLEN];
            int uren[WLEN];
        } Gebruik;
