extern Render render;
extern Image image;
extern Environ env;


extern unsigned long wpx,bpx,mask,wpx2,bpx2;

extern char nomGIF[256]; 	/* string containing the GIF filename */
extern char nomPPM[256]; 	/* string containing the PPM filename */
extern char nomPostscript[256]; /* string containing the Postscript filename */
extern char nompalette[256];    /* string containing the palette filename */
extern char toto[256];  	/* temporary string */

extern lcomplex z0;	/* Upper left corner in the complex plane  */
extern lcomplex z1;	/* Lower right corner in the complex plane */
extern lcomplex cz;     /* Complex constant (e.g. Julia sets)  */
extern double bailout;  /* Bailout value */
    extern double delta;    /* used with distance estimator method */ 

extern char *CP[CPSIZE];  /* string array containing the text displayed */

extern char use_long_double; /* Boolean: TRUE -> using the long double format */
			     /* for complex numbers */

extern int bipbip;	/* Boolean: TRUE -> ring the bell when the computation is finished */
    extern int bloc0;	/* size of the blocs displayed... */
extern int calcul_en_cours; /* Boolean = computation in progress */
extern int calcul_virtuel;  /* Boolean = background computation */
extern int coul_back,coul_for; /* colors */
extern int couleur;	/* color of current point displayed */
extern int genre;  	/* fractal type */
extern int gestion_ev;	/* Boolean = hevent handling */
extern int initcoord;	/* Boolean, works with function click_constant */
extern int ip;		/* integer parameter of fractal type */
extern int iter;	/* number of iterations */
extern int maxpts;  	/* size of the display buffer */
extern int nbr_colors;	/* number of colors in the current palette */
extern int nbre_cycles; /* number of color cycles	*/
    extern int palettelog;	/* Boolean = use logarithmic palette */
    extern int palog[MAXCOULEURS]; /* contains the intervals of iterations for
			the log palette mode */
extern int rouge[MAXCOULEURS],vert[MAXCOULEURS],bleu[MAXCOULEURS];
			/* contains the rgb values of the palette */
extern int sauviter;    /* Boolean not used */
extern int sauvPPM,sauvGIF,sauvPostscript;  /* Boolean = saving file */
extern int sens_cycle;	/* for color cycling */
extern int symetrie;	/* contains the type of symetry of the current
			fractal type. see xfe.c */
extern int tampon;	/* Boolean = using display buffer */
extern int tache_de_fond; /* Boolean = background computation */
    extern int type_dessin;		/* drawing method */    
extern int type_postscript;	/* type of Postscript: B&W or grey */
extern int vit_cycle;		/* speed of color cycling */
extern long pt_en_cours;	/* number of the current point being calculated */

extern int barnsley1();
extern int barnsley2();
extern int barnsley3();
extern int calcul2();
extern int calcul3();
extern int jcos();
extern int jexp();
extern int jsin();
extern int lambda();
extern int lire_bibli();
extern int mandel3();
extern int mandel();
extern int mandellambda();
extern int mandeln();
extern int markm();
extern int newton();
extern int noel1();
extern int noel2();
extern int phoenix();
extern int spider();
extern int tetrate();

extern void Animim();
extern void Animpt();
extern void Change_genre();
extern void Charger_palette();
extern void ChargePalette();
extern void Cycling();
extern void Entrer_taille();
extern void Load();
extern void Save();
extern void SaveGIF();
extern void Save_background();
extern void anim_image();
extern void anim_pt_source();
extern void ask_back();
extern void calcul();
extern void calculBG();
extern void calculBG_Postscript();
extern void ch_coord();
extern void change_ip();
extern void change_iter();
extern void change_delta();
extern void chbailout();
extern void definir_couleur();
extern void ecrire(); 
extern void ecrire_bibli();
extern void init_fractal();
extern void initialiser_couleurs();  
extern void initx();
extern void load_gif();
extern void load_param();
extern void nbrecycles();
extern void point_source();
extern void print_status();
extern void rafraichir();
extern void rafraichir_mes();
extern void readGIF();   
extern void resize();
extern void sauvparam();
extern void taille_tampon();
extern void trace_point();
extern void vider_tampon();
