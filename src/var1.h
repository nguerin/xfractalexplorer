Render render;
Image image;
Environ env;

char nomGIF[256]; 
char nomPPM[256]; 
char nomPostscript[256]; 
char nompalette[256];
char toto[256];

lcomplex z0,z1,cz;                            
double bailout; 
double delta; /* With distance estimator */ 
unsigned long wpx,bpx,mask,wpx2,bpx2;

char *CP[CPSIZE];  /* Va contenir tout le texte */

char use_long_double;

int bipbip;
int bloc0;
int calcul_en_cours;
int calcul_virtuel;
int coul_back,coul_for;
int couleur;
/*int exist_status;*/
int genre;  
int gestion_ev;
int initcoord;
/*int initfractal;*/
int ip;
int iter;
/* int largeur,hauteur; */
int maxpts;
int nbr_colors; 
int nbre_cycles;
int palettelog;
int palog[MAXCOULEURS];
int phoenix();
int rouge[MAXCOULEURS],vert[MAXCOULEURS],bleu[MAXCOULEURS];
int sauviter;    
int sauvPPM,sauvGIF,sauvPostscript;  
int sens_cycle;
int symetrie;
int tampon;
int tache_de_fond;
int type_dessin;    
int type_postscript;
int vit_cycle;

long pt_en_cours;
