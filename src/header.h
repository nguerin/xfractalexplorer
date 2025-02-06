#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#include <X11/Xlib.h>  
 
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>  
#include <Xm/DrawingA.h>
#include <Xm/FileSB.h>
#include <Xm/Label.h> 
#include <Xm/List.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h> 
#include <Xm/Separator.h>  
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/Text.h>
#include <Xm/Xm.h>   

#define MAXCOULEURS      256     


typedef struct coord{
        int x;
        int y;
} coordonnees;

/*typedef struct _fractal{
} Fractal;
*/

typedef struct _image{
  int width; /* width of picture in pixels */
  int height; /* height of picture in pixels */
  int bloc0;	/* size of the blocs displayed... */
/*  int nbre de couleurs ? */
} Image;

typedef struct _render {
  int type; /* Rendering type: escape time, distance estimator etc. */
  /*double bailout;   Bailout value */

  /* Logarithmic palette */
  int palettelog;	/* Boolean = use logarithmic palette */
  int palog[MAXCOULEURS]; /* contains the intervals of iterations for
			the log palette mode */

  /* Distance estimator */
  double delta;    /* used with distance estimator method */

  /* Minimum module method */
  double int_mult_mod; /*Mult. factor for minimum module method: interior pts*/
  double ext_mult_mod; /*Mult. factor for minimum module method: exterior pts*/
} Render;


/* Palette structure */
typedef struct _palette {
    int nbCol;                 /* Number of colors in the palette */
    XColor color[MAXCOULEURS]; /* Array of colors in the palette */
} Palette;



typedef struct _environ {
    Colormap cmap;		/* colormap of the display window */
    Colormap default_palette; 
    Palette  palette;
    GC gc;
    Pixmap pixmap; 	/* Pixmap used to refresh the picture */
    Pixmap mes_pix;   	/* Pixmap used to refresh the message window */
    Widget message; 	/* Drawing area widget for the message window */
    Widget root; 	/* Root widget */
    Widget board; 	/* Bulletin board widget for the menu window */
    Widget drawing; 	/* Drawing area widget for the display window */
    Widget shell; 	/* Shell widget for the display window */
    Visual  *visual;    /* Default visual */
    Display *display;   /* Associated display */
    int  screen;    /* Default screen */
    int depth;          /* default screen depth */
    /*XColor color[256];*/
} Environ;


