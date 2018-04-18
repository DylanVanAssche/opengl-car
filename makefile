#################################################################################
#	OpenGL futuristic soapbox car												#
#	Van Assche Dylan - 3 ABA EI (2017 - 2018)									#
#	Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven)			#
#################################################################################

# C target
TARGETS = \
    car

all All: $(TARGETS)

# Include OpenGL libs
INCPATH = -I/usr/local/include
LIBPATH = -L. -L/usr/local/lib/hpux32
LIBS = -lglut -lGLU -lGL -lGLw -lXt -lXext -lX11 -ljpeg -lm
CFLAGS = $(INCPATH) -std=c99

# Define the sources and object files
SRCS = \
	car.c \
	view.c \
	vehicle.c \
	arc.c

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

# Makefile build commands
.c.o:
	cc -c $< $(CFLAGS)


car:	clean $(OBJS)
	LDOPTS= \
	cc -o car $(CFLAGS) $(OBJS) $(LIBPATH) $(LIBS)

clean:
	rm -f car $(OBJS) core

print:
	listing car.h $(SRCS)
