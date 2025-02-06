# Makefile for xfe

#
# You may have to change this for your system
#
# Includes
#
XINCLUDE=	-I/usr/X11R6/include
MOTIFINCLUDE=	-I/usr/include
#EXTRAINCLUDE=   -I/usr/include/math.h
#
# Libraries
#
XLIBRARY=       -L/usr/X11R6/lib
MOTIFLIBRARY=	-L/usr/lib
#EXTRALIBRARY=	-L/usr/lib/sparcv9
#XLIBRARY=       -L/usr/openwin/lib
#MOTIFLIBRARY=	-L/usr/dt/lib
#EXTRALIBRARY=	-L/usr/lib
LIBS=		-lXm -lXt -lX11 -lm

#
# If you want the program to run in French uncomment this:
# Si vous voulez que le programme utilise le Francais decommenter:
#
#LANGUAGE=  -DFRENCH
#

# If you don't get errors you can uncomment this to know
# the computing time
TIME= -DTIMER_ON

# For HP-UX uncomment these lines
#CC = cc
#CFLAGS=		-Aa +O3 -D_HPUX_SOURCE
#CC = gcc
#CFLAGS=		-ansi -O


# For IBM RS6000 uncomment these lines
#CC = cc
#CFLAGS=         -g -D_BSD -DSOCKS -O3



# for Apollo uncomment these lines
#CC = cc
#CFLAGS= -A ansi -O
#DOUBLE= -D_NO_LONG_DOUBLE

# for Solaris7 uncomment these lines
#CC = cc
#CFLAGS= -g -xarch=v9
#CFLAGS= -fast -xarch=v9a



# Other UNIX systems:
# Change the CFLAGS and CC for your platform. xfe is known
# to run also on MIPS and SUN under SunOs. If you can run
# it on a different platform, please email me...
#
# Your C compiler:
CC = gcc
# You can use gcc
#
# The compiler options:
#CFLAGS=
#  If you use gcc, then use this CFLAGS line:
CFLAGS=		-O4 -ansi -W
#CFLAGS=         -ansi -Wall -g
# -O -pedantic
#
# If your system doesn't handle the 'long double' format uncomment this:
#DOUBLE= -D_NO_LONG_DOUBLE
#



# Choose the place for the different files
XFE_DIR = /home/guerin/xfractal_explorer
ANIM_DIR = $(XFE_DIR)/Anim
IMAGE_DIR = $(XFE_DIR)/Images
PALETTE_DIR = $(XFE_DIR)/Palettes
PARAM_DIR = $(XFE_DIR)/Param
LANG_FILE = $(XFE_DIR)/src/xfe.lang



################ END OF CONFIGURATION OPTIONS #################


DEFINES = -DIMAGE_DIR=\"$(IMAGE_DIR)\" -DPALETTE_DIR=\"$(PALETTE_DIR)\"\
          -DPARAM_DIR=\"$(PARAM_DIR)\" -DLANG_FILE=\"$(LANG_FILE)\"\
          -DANIM_DEF=\"$(ANIM_DIR)/def\" $(TIME) $(LANGUAGE) $(DOUBLE)

INCLUDES = $(XINCLUDE) $(MOTIFINCLUDE) $(EXTRAINCLUDE)
LIBRARIES=	$(XLIBRARY) $(MOTIFLIBRARY) $(EXTRALIBRARY) $(LIBS)

OBJS = 	xfe.o anim.o gifencod.o gifcompr.o boite.o fichier.o couleur.o\
        fractcalc.o fractdef.o menu.o readGIF.o status.o

.c.o:	; $(CC) -c $(CFLAGS) $(DEFINES) $(INCLUDES) $*.c


xfe: $(OBJS)
	$(CC) -o xfe $(CFLAGS) $(DEFINES) $(INCLUDES) $(OBJS) $(LIBRARIES)

$(OBJS):   include.h header.h var.h fractal_type.h
xfe.o  :   var1.h
