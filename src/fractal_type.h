/* Types of fractals */

#define MANDELBROT	1
#define JULIA 		2
#define MANDEL3		3
#define JULIA3		4
#define NEWTON		5   
#define LAMBDA		6
#define MANDELLAMBDA	7
#define SPIDER		8
#define BARNM1		9
#define BARNJ1		10
#define BARNM2		11
#define BARNJ2		12
#define BARNM3		13
#define BARNJ3		14
#define MCOS		15
#define JCOS		16
#define MSIN		17
#define JSIN		18
#define MEXP		19
#define JEXP		20
#define NOEL1		21
#define NOEL2		22
#define PHOENIX		23
#define TETRATE		24
#define MARKM		25
#define MARKJ		26
#define MANDELN		27
#define JULIAN		28




/* Types de trace */

#define NORMAL 		1
#define INVERSION 	2
#define DECOMPOSITION	3
#define ESTIMATEUR	4


/* Valeurs par defaut */

#define HAUTEUR_DEF	512
#define LARGEUR_DEF	640
#define MAXPOINTS 	500   
#define MAXCOULEURS	256     
#define MESSAGE_L 	640
#define MESSAGE_H 	27
#define LARGEUR_MAX	1280*16
#define HAUTEUR_MAX	1024*16
#define LONG_MAX	200
#define NOIR		1
#define GRIS		2
#define CPSIZE 		235    /* size of lang file max */

/* long doubles ? */
#ifdef _NO_LONG_DOUBLE
#define FORMAT_LECTURE	"%le"
#define FORMAT		"%.16e"
#define FORMAT2		"%.16e"
#define FLOAT_SIZE	double
#else
#define FORMAT_LECTURE	"%Le"
#define FORMAT		"%.33Le"
#define FORMAT2		"%.16Le"
#define FLOAT_SIZE	long double
#endif

/* Directories */
#ifndef IMAGE_DIR
#define IMAGE_DIR	"./Images"
#endif
#ifndef PALETTE_DIR
#define PALETTE_DIR	"./Palettes"
#endif
#ifndef PARAM_DIR
#define PARAM_DIR	"./Param"
#endif
#ifndef LANG_FILE
#define LANG_FILE	"./xfe.lang"
#endif
#ifndef ANIM_DEF
#define ANIM_DEF	"./Anim/def"
#endif
#ifndef PAL_DEF
#define PAL_DEF		"greycolor.cmap"
#endif
