/*
 * xfe.c - main section of xfe.
 *
 *  Author:    Nicolas GUERIN, ENSAE (Sup'Aero) Toulouse FRANCE
 *                (guerin@reseau.onecert.fr)
 *
 */

/* Copyright Notice
 * ================
 * Copyright 1994 by Nicolas GUERIN
 * 
 * Permission to use, copy, and distribute xfe in its entirety, for 
 * non-commercial purposes, is hereby granted without fee, provided that
 * this license information and copyright notice appear in all copies.
 *
 * The software may be modified for your own purposes, but modified
 * versions may NOT be distributed without prior consent of the author.
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the author be held liable for any damages
 * arising from the use of this software.
 * 
 * If you would like to do something with xfe that this copyright
 * prohibits (such as distributing it with a commercial product, 
 * using portions of the source in some other program, etc.), please
 * contact the author (preferably via email).  Arrangements can
 * probably be worked out.
 *
 * xfe is freeware for PERSONAL USE only.  You may use xfe for your own
 * amusement, and if you find it nifty, useful, generally cool, or of
 * some value to you, please register so as to receive the latest versions
 * of xfe, and to make me happy. Just send me an email with your impressions
 * ideas, bugs...
 * 
 *
 * The author may be contacted via:
 *       Mail:  Nicolas Guerin
 *              168 Avenue Parmentier
 *              75010 PARIS
 *              FRANCE
 *
 *    EMail:    guerin@reseau.onecert.fr
 */


#include "include.h"

#ifdef TIMER_ON  
#include <time.h>
#endif

#include "var1.h"


static struct {
  XPoint pts [MAXCOULEURS][MAXPOINTS];
  int    nbre[MAXCOULEURS];
} points;


extern void initialiser_couleurs();  
extern void Entrer_taille();   
extern void init_fractal();
extern void initx();
extern int calcul2();
extern int calcul3();
extern void resize();
extern void calculBG();
extern void rafraichir();

static int compteur_postscript=0; /*Pour aller a la ligne */
static int compteur_postscript2=0;/* Pour les fins de lignes */
static int ligne_postscript=0;
static int tampon_postscript=0;
static int exposant_postscript=0;
static FILE *fichier; 

int comp1=0;
int comp2=0;
int nbpl1=0; 
int nbm1=0; 
int nbau=0; 
int nbav=0;
int nbavn=0;

/*****************************************************************************/
int pow2(i)
  int i;
{
  int j,k=1;

  for (j=0;j!=i;j++) 
	k*=2;
  return(k);
}
	                  
/*****************************************************************************/
                   
void ecrire(chaine)   
  char *chaine;     
{                  
                             
  XSetForeground(XtDisplay(env.root),env.gc,bpx2);      /* a modifier ? */
  XFillRectangle(XtDisplay(env.root),XtWindow(env.message),env.gc,0,0,MESSAGE_L,MESSAGE_H);
  XFillRectangle(XtDisplay(env.root),env.mes_pix,env.gc,0,0,MESSAGE_L,MESSAGE_H);
  /*XClearWindow(XtDisplay(env.root),XtWindow(env.message));*/
  /*XClearWindow(XtDisplay(env.root),XtWindow(env.pixmap));*/
  /*XSetForeground(XtDisplay(env.root),env.gc,coul_for);*/
  XSetForeground(XtDisplay(env.root),env.gc,wpx2);
  XDrawString(XtDisplay(env.root),XtWindow(env.message),env.gc,10,18,chaine,strlen(chaine));
  XDrawString(XtDisplay(env.root),env.mes_pix,env.gc,10,18,chaine,strlen(chaine));
}
 
/******************************************************************************************************************************/

void ecrire_bibli(nom)
  char *nom;
{

  int                     len;
  FILE                    *fichierdisque;  
  char			temp[4];
                                                
  if ((fichierdisque = fopen("FractBibli","a"))==NULL)
	{
	  perror(CP[140]);
	}

  strcpy(toto,nom);                                      
  len=strlen(toto);
  strcpy(temp,&toto[len-4]);
  if (!strcmp(temp,".ppm")) toto[len-4]='\0'; 	
  /*if (strcmp(temp,".gif")) 	
	strcat(toto,".gif");*/	/* Add .gif if missing */

  fprintf(fichierdisque,"# Path and name of the associated GIF file (if exists)\n");
  fprintf(fichierdisque,"NAME    :%s\n",toto);
  fprintf(fichierdisque,"# Coordinates\n");
  fprintf(fichierdisque,"LEFT    :");
  fprintf(fichierdisque,FORMAT,z0.re);
  fprintf(fichierdisque,"\nTOP     :");
  fprintf(fichierdisque,FORMAT,z0.im);
  fprintf(fichierdisque,"\nRIGHT   :");
  fprintf(fichierdisque,FORMAT,z1.re);
  fprintf(fichierdisque,"\nBOTTOM  :");
  fprintf(fichierdisque,FORMAT,z1.im);
  fprintf(fichierdisque,"\n");
  fprintf(fichierdisque,"# Iterations\n");
  fprintf(fichierdisque,"ITER    :%d\n",iter);
  fprintf(fichierdisque,"# Image size\n");
  fprintf(fichierdisque,"WIDTH   :%d\n",image.width);
  fprintf(fichierdisque,"HEIGHT  :%d\n",image.height);
  fprintf(fichierdisque,"# Fractal type (see fractal_type.h)\n");
  fprintf(fichierdisque,"TYPE    :%d\n",genre);
  fprintf(fichierdisque,"# Display\n");
  fprintf(fichierdisque,"DISPLAY :%d\n",type_dessin);
  fprintf(fichierdisque,"# Bailout\n");
  fprintf(fichierdisque,"BAILOUT :%.16e\n",bailout);
  fprintf(fichierdisque,"# Complex parameter\n");
  fprintf(fichierdisque,"C1.RE   :");
  fprintf(fichierdisque,FORMAT,cz.re);
  fprintf(fichierdisque,"\nC1.IM   :");
  fprintf(fichierdisque,FORMAT,cz.im); 
  fprintf(fichierdisque,"\n");
  fprintf(fichierdisque,"# Integer parameter\n");
  fprintf(fichierdisque,"N1      :%d\n",ip);  
  fprintf(fichierdisque,"# Logarithmic palette on/off\n");
  fprintf(fichierdisque,"LOGPAL  :%d\n",palettelog);  
  fprintf(fichierdisque,"# Palette name\n");
  fprintf(fichierdisque,"PALETTE :%s\n",nompalette);  
  fprintf(fichierdisque,"\n\n");
                                   
  fclose(fichierdisque); 
}             

/*********************************************************************************/

void sauvparam(nom)
  char *nom;
{

  FILE                    *fichierdisque;  


  if ((fichierdisque = fopen(nom,"a"))==NULL)
	{
	  perror(CP[140]);
	}
                
  fprintf(fichierdisque,"# Path and name of the associated GIF file (if exists)\n");
  fprintf(fichierdisque,"NAME    :%s\n",nom);
  fprintf(fichierdisque,"# Coordinates\n");
  fprintf(fichierdisque,"LEFT    :");
  fprintf(fichierdisque,FORMAT,z0.re);
  fprintf(fichierdisque,"\nTOP     :");
  fprintf(fichierdisque,FORMAT,z0.im);
  fprintf(fichierdisque,"\nRIGHT   :");
  fprintf(fichierdisque,FORMAT,z1.re);
  fprintf(fichierdisque,"\nBOTTOM  :");
  fprintf(fichierdisque,FORMAT,z1.im);
  fprintf(fichierdisque,"\n");
  fprintf(fichierdisque,"# Iterations\n");
  fprintf(fichierdisque,"ITER    :%d\n",iter);
  fprintf(fichierdisque,"# Image size\n");
  fprintf(fichierdisque,"WIDTH   :%d\n",image.width);
  fprintf(fichierdisque,"HEIGHT  :%d\n",image.height);
  fprintf(fichierdisque,"# Fractal type (see fractal_type.h)\n");
  fprintf(fichierdisque,"TYPE    :%d\n",genre);
  fprintf(fichierdisque,"# Display\n");
  fprintf(fichierdisque,"DISPLAY :%d\n",type_dessin);
  fprintf(fichierdisque,"# Bailout\n");
  fprintf(fichierdisque,"BAILOUT :%.16e\n",bailout);
  fprintf(fichierdisque,"# Complex parameter\n");
  fprintf(fichierdisque,"C1.RE   :");
  fprintf(fichierdisque,FORMAT,cz.re);
  fprintf(fichierdisque,"\nC1.IM   :");
  fprintf(fichierdisque,FORMAT,cz.im); 
  fprintf(fichierdisque,"\n");
  fprintf(fichierdisque,"# Integer parameter\n");
  fprintf(fichierdisque,"N1      :%d\n",ip);  
  fprintf(fichierdisque,"# Logarithmic palette on/off\n");
  fprintf(fichierdisque,"LOGPAL  :%d\n",palettelog);  
  fprintf(fichierdisque,"# Palette name\n");
  fprintf(fichierdisque,"PALETTE :%s\n",nompalette);  
                                   
  fclose(fichierdisque); 
}             


/*********************************************************************************/

/*void lire_bibli(nom,z0re,z0im,z1re,z1im,fiter,larg,haut,fgenre,ftype_dessin,bail,czre,czim,fip)
char *nom;
FLOAT_SIZE *z0re;
FLOAT_SIZE *z0im;
FLOAT_SIZE *z1re;
FLOAT_SIZE *z1im;
int *fiter;
int *larg;
int *haut;
int *fgenre;
int *ftype_dessin;
double *bail;
FLOAT_SIZE *czre;
FLOAT_SIZE *czim;
int *fip;*/



/*****************************************************************************/

int lire_bibli(nom)
  char *nom;
{
  int                     i;
  FILE                    *fichierdisque;  
  char		s[512];
  int			len;
  char			commande[9];
  char			valeur[250];
  int			temp;
  int 			OK=FALSE;

  pt_en_cours=0;
                                                
  if ((fichierdisque = fopen("FractBibli","r"))==NULL)
	{
	  perror(CP[140]);
	  exit(1);
	} 

                                     
  while (fgets(s,sizeof(s),fichierdisque))
	{
	  if (s[0]=='#') continue;	/* commentaire */
	  if (s[0]=='\n') continue;
	  len=strlen(s);
	  if (s[8]!=':')
		{
		  printf(CP[188]);
		  printf("\n%s\n",s);
		  exit(1);
		}
	  strncpy(commande,s,8);
	  commande[8]='\0';
	  for (i=9;i<len-1;i++)
		valeur[i-9]=s[i];
	  valeur[len-10]='\0';	/* Permet de se debarasser du \n */
	  if (!strcmp(commande,"NAME    "))
		{
		  if (!strcmp(nom,valeur))
			{
			  OK=TRUE;
			  break;
			}
		  else continue;
		}
	}

  if (!OK)
	{
	  printf(CP[188]);
	  return(FALSE);
	}

  while (fgets(s,sizeof(s),fichierdisque))
	{
	  if (s[0]=='#') continue;	/* commentaire */
	  if (s[0]=='\n') continue;
	  len=strlen(s);
	  if (s[8]!=':')
		{
		  printf(CP[188]);
		  printf("\n%s\n",s);
		  exit(1);
		}
	  strncpy(commande,s,8);
	  commande[8]='\0';
	  for (i=9;i<=len;i++)
		valeur[i-9]=s[i];
	  if (!strcmp(commande,"NAME    "))
		break;
	  if (!strcmp(commande,"LEFT    "))
		sscanf(valeur,FORMAT_LECTURE,&z0.re);
	  if (!strcmp(commande,"TOP     "))
		sscanf(valeur,FORMAT_LECTURE,&z0.im);
	  if (!strcmp(commande,"RIGHT   "))
		sscanf(valeur,FORMAT_LECTURE,&z1.re);
	  if (!strcmp(commande,"BOTTOM  "))
		sscanf(valeur,FORMAT_LECTURE,&z1.im);
	  if (!strcmp(commande,"ITER    "))
		sscanf(valeur,"%d",&iter);
	  if (!strcmp(commande,"WIDTH   "))
		sscanf(valeur,"%d",&image.width);
	  if (!strcmp(commande,"HEIGHT  "))
		sscanf(valeur,"%d",&image.height);
	  if (!strcmp(commande,"TYPE    "))
		sscanf(valeur,"%d",&genre);
	  if (!strcmp(commande,"DISPLAY "))
		sscanf(valeur,"%d",&type_dessin);
	  if (!strcmp(commande,"BAILOUT "))
		sscanf(valeur,"%le",&bailout);
	  if (!strcmp(commande,"C1.RE   "))
		sscanf(valeur,FORMAT_LECTURE,&cz.re);
	  if (!strcmp(commande,"C1.IM   "))
		sscanf(valeur,FORMAT_LECTURE,&cz.im);
	  if (!strcmp(commande,"N1      "))
		sscanf(valeur,"%d",&ip);
	  if (!strcmp(commande,"LOGPAL  "))
		{
		  sscanf(valeur,"%d",&temp);
		  if (temp)
			palettelog=TRUE;
		  else
			palettelog=FALSE;
		}
	  if (!strcmp(commande,"PALETTE "))
		{
		  sscanf(nompalette,"%s",valeur);
		  ChargePalette();
		}
	}

                                   
  fclose(fichierdisque);
  return(TRUE); 
}

/*********************************************************************************/

void load_param(nom)
  char *nom;
{

  int                     i;
  FILE                    *fichierdisque;  
  char		s[512];
  int			len;
  char			commande[9];
  char			valeur[250];
  int			temp;

  if ((fichierdisque = fopen(nom,"r"))==NULL)
	{
printf("%s\n");
	  perror(CP[140]);
	}

  while (fgets(s,sizeof(s),fichierdisque))
	{
	  if (s[0]=='#') continue;	/* commentaire */
	  if (s[0]=='\n') continue;
	  len=strlen(s);
	  if (s[8]!=':')
		{
		  printf(CP[188]);
		  printf("\n%s\n",s);
		  exit(1);
		}
	  strncpy(commande,s,8);
	  commande[8]='\0';
	  for (i=9;i<=len;i++)
		valeur[i-9]=s[i];
	  if (!strcmp(commande,"LEFT    "))
		sscanf(valeur,FORMAT_LECTURE,&z0.re);
	  if (!strcmp(commande,"TOP     "))
		sscanf(valeur,FORMAT_LECTURE,&z0.im);
	  if (!strcmp(commande,"RIGHT   "))
		sscanf(valeur,FORMAT_LECTURE,&z1.re);
	  if (!strcmp(commande,"BOTTOM  "))
		sscanf(valeur,FORMAT_LECTURE,&z1.im);
	  if (!strcmp(commande,"ITER    "))
		sscanf(valeur,"%d",&iter);
	  if (!strcmp(commande,"WIDTH   "))
		sscanf(valeur,"%d",&image.width);
	  if (!strcmp(commande,"HEIGHT  "))
		sscanf(valeur,"%d",&image.height);
	  if (!strcmp(commande,"TYPE    "))
		sscanf(valeur,"%d",&genre);
	  if (!strcmp(commande,"DISPLAY "))
		sscanf(valeur,"%d",&type_dessin);
	  if (!strcmp(commande,"BAILOUT "))
		sscanf(valeur,"%le",&bailout);
	  if (!strcmp(commande,"C1.RE   "))
		sscanf(valeur,FORMAT_LECTURE,&cz.re);
	  if (!strcmp(commande,"C1.IM   "))
		sscanf(valeur,FORMAT_LECTURE,&cz.im);
	  if (!strcmp(commande,"N1      "))
		sscanf(valeur,"%d",&ip);
	  if (!strcmp(commande,"LOGPAL  "))
		{
		  sscanf(valeur,"%d",&temp);
		  if (temp)
			palettelog=TRUE;
		  else
			palettelog=FALSE;
		}
	  if (!strcmp(commande,"PALETTE "))
		{
		  sscanf(valeur,"%s",nompalette);
		  ChargePalette();
		}
	}
                                  
  fclose(fichierdisque); 
  ecrire(CP[189]);
}


/*****************************************************************************/

void definir_couleur(i)  
  int i;
{                  
  int j;

  if (i==iter) couleur=bpx; 
  else if (!palettelog) {
/*	couleur=i+1;
	for (j=i+1;j>=MAXCOULEURS;j-=MAXCOULEURS) {couleur-=MAXCOULEURS;}
	if (i==iter) couleur=bpx;  */
    couleur=i%(MAXCOULEURS-2)+2;
  }
  else {        
	for (j=0;j<255;j++) {
	  if ((i<palog[j+1])&&(i>=palog[j])) {
		couleur=j+1;
		break;
	  }
	}    
  }
	
}

/*****************************************************************************/

static void save_ppm1()   /* sauvegarde de l'image au format PPM - initialisation */
{
	         
  /*printf("%s\n",nomPPM);*/  
  if ((fichier = fopen(nomPPM,"w"))==NULL)
	{
	  perror(CP[170]);}   

  fprintf(fichier,"P6\n");               
  fprintf(fichier,"%d %d\n",image.width,image.height);    
  fprintf(fichier,"255\n");
}

/*****************************************************************************/

static void save_ppm2(i)
  int i;		              /* sauvegarde PPM - point par point */


{
  fprintf(fichier,"%c%c%c",rouge[i],vert[i],bleu[i]);   
} 



/*****************************************************************************/


static void save_postscript1()   /* sauvegarde de l'image au format Postscript - initialisation */
{
  int larg,haut,paslarge=FALSE;
  int var=1;


  compteur_postscript=0;
  compteur_postscript2=0;
  tampon_postscript=0;
  exposant_postscript=3;
  if (image.width>=image.height) 
	{larg=image.width;
	haut=image.height;}
  else { larg=image.height;
  haut=image.width;}
	         
  if ((double)larg>1.41*haut) paslarge=TRUE;

  if ((fichier = fopen(nomPostscript,"w"))==NULL)
	{
	  perror(CP[170]);}   

  fprintf(fichier,"%%!PS-Adobe-2.0 EPSF-2.0\n");               
  fprintf(fichier,"%%%%Title: /users/promo_95/guerin/im4.ps\n");               
  fprintf(fichier,"%%%%Creator: XFractal_Explorer v1.1 - by N. GUERIN\n");               
  fprintf(fichier,"%%%%BoundingBox: 3 57 592 793\n");               
  fprintf(fichier,"%%%%Pages: 1\n");               
  fprintf(fichier,"%%%%DocumentFonts:\n");               
  fprintf(fichier,"%%%%EndComments\n");               
  fprintf(fichier,"%%%%EndProlog\n\n");               
  fprintf(fichier,"%%%%Page: 1 1\n\n");               
  fprintf(fichier,"%% remember original state\n");               
  fprintf(fichier,"/origstate save def\n\n");               
  fprintf(fichier,"%% build a temporary dictionary\n");               
  fprintf(fichier,"20 dict begin\n\n");               
  fprintf(fichier,"%% define string to hold a scanline's worth of data\n"); 
  if (type_postscript==NOIR) ligne_postscript=ceil(image.width/8.0);
  if (type_postscript==GRIS) ligne_postscript=image.width;
  fprintf(fichier,"/pix %d string def\n\n",ligne_postscript);             
  fprintf(fichier,"%% print in landscape mode\n");               
  fprintf(fichier,"90 rotate 0 -595 translate\n\n");               
  fprintf(fichier,"%% lower left corner\n");               
  if (paslarge) {
	fprintf(fichier,"12 %d translate\n\n",(int)(298-(412*haut)/larg));  }             
  else 	{	
	fprintf(fichier,"%d 6 translate\n\n",(int)(425-290*larg/haut)); }
  fprintf(fichier,"%% size of image (on paper, in 1/72inch coords)\n");               
  if (paslarge)
	fprintf(fichier,"825.00000 %f scale\n\n",825.0*(double)haut/larg);   /*  3.7 /pixel ????*/           
  else 	fprintf(fichier,"%f 580.00000 scale\n\n",580.0*(double)larg/haut);  
  if (type_postscript==NOIR) var=1;
  if (type_postscript==GRIS) var=8; 
  fprintf(fichier,"%d %d %d			%% dimensions of data\n",larg,haut,var);               
  fprintf(fichier,"[%d 0 0 -%d 0 %d]		%% mapping matrix\n",larg,haut,haut);               
  fprintf(fichier,"{currentfile pix readhexstring pop}\n");               
  fprintf(fichier,"image\n");             
}

/*****************************************************************************/

static void save_postscript2(val)
  int val;		              /* appelee apres chaque point */

{
  if (type_postscript==GRIS) {
	if (compteur_postscript>=72) {
	  compteur_postscript=0;
	  fprintf(fichier,"\n");
	}
	val=255-val;
	if (val<16) fprintf(fichier,"0%x",val); else fprintf(fichier,"%x",val);
	compteur_postscript+=2;
  }
  if (type_postscript==NOIR) {
	/*	if ((val!=0)&&(val!=1)) printf("erreur couleur!\n");*/
	compteur_postscript2++;
	tampon_postscript+=val*pow2(exposant_postscript);
	/*	if (tampon_postscript>15) printf("erreur tampon!\n");*/
	exposant_postscript--;
	if (exposant_postscript==-1) {
	  exposant_postscript=3;
	  fprintf(fichier,"%x",tampon_postscript); 
	  tampon_postscript=0;
	  compteur_postscript++;
	  if (compteur_postscript>=72) {
		compteur_postscript=0;
		fprintf(fichier,"\n");
	  }
	}
  }
} 



/*****************************************************************************/

static void save_postscript3() /*appelee a la fin de chaque ligne */
		             
{
  if ((type_postscript==NOIR)&&(exposant_postscript!=3)) {
	exposant_postscript=3;
	fprintf(fichier,"%x",tampon_postscript);
	tampon_postscript=0;
  }
  if ((type_postscript==NOIR)&&(compteur_postscript2<8*(int)ceil(image.width/8.0))) fprintf(fichier,"0");
  fprintf(fichier,"\n");
  compteur_postscript=0;
  compteur_postscript2=0;
}



/*****************************************************************************/

static void save_postscript4()
{
  fprintf(fichier,"\nshowpage\n\n");               
  fprintf(fichier,"%% stop using temporary dictionary\n");               
  fprintf(fichier,"end\n\n");               
  fprintf(fichier,"%% restore original state\n");               
  fprintf(fichier,"origstate restore\n\n");               
  fprintf(fichier,"%%%%Trailer\n");               
  fclose(fichier);
  sauvPostscript=FALSE;
} 



/*****************************************************************************/

XRectangle rectmaker(p,large)
  XPoint p;
int large;
{
  XRectangle rect;
  rect.x=p.x;
  rect.y=p.y;
  rect.width=large;
  rect.height=large;
  return (rect);
}

/*****************************************************************************/

void vider_tampons(bloc)
  int bloc;
{
  static XRectangle rectangles[MAXPOINTS];
  int k,l;

  for (k=0;k<MAXCOULEURS;k++){
	if (points.nbre[k]) {
	  XSetForeground(XtDisplay(env.root),env.gc,env.palette.color[k].pixel);
	  if (bloc==1){
		if (!tache_de_fond) XDrawPoints(XtDisplay(env.root),XtWindow(env.drawing),
					env.gc,points.pts[k],points.nbre[k],CoordModeOrigin);
		XDrawPoints(XtDisplay(env.root),env.pixmap,env.gc,    
					points.pts[k],points.nbre[k],CoordModeOrigin);
	  } else {
		for (l=0;l<points.nbre[k];l++) {  
		  rectangles[l]=rectmaker(points.pts[k][l],bloc);
		}
		if (!tache_de_fond) XFillRectangles(XtDisplay(env.root),
				XtWindow(env.drawing),env.gc,rectangles,points.nbre[k]);
		XFillRectangles(XtDisplay(env.root),env.pixmap,env.gc,    
						  rectangles,points.nbre[k]);
	  }    
	  points.nbre[k]=0;
	}
  }
}	    
			
/*****************************************************************************/

void trace_point(i,j,bloc,stopper_calc)   
  int i,j,bloc;                          
int *stopper_calc;  
{ 
  XEvent ev;
  static XRectangle rectangles[MAXPOINTS];
  int k;                       


  if (tampon) {
      points.pts[couleur][points.nbre[couleur]].x=i;
      points.pts[couleur][points.nbre[couleur]].y=j;
      points.nbre[couleur]++;  
      if (points.nbre[couleur] >= maxpts-1) {
	  /* Tampon plein */
/*          XColor mycolor;
          mycolor.red  =rouge[couleur]*256;
          mycolor.green=vert[couleur]*256;
          mycolor.blue =bleu[couleur]*256;
          mycolor.flags=DoRed|DoGreen|DoBlue;

          XAllocColor(XtDisplay(env.root),env.cmap,&mycolor);
*/
          XSetForeground(XtDisplay(env.root),env.gc,env.palette.color[couleur].pixel);
	  /*XSetForeground(XtDisplay(env.root),env.gc,couleur);*/
	  if (bloc==1) {
              if (!tache_de_fond) XDrawPoints(XtDisplay(env.root),XtWindow(env.drawing),env.gc,
                                              points.pts[couleur],points.nbre[couleur],CoordModeOrigin);
              XDrawPoints(XtDisplay(env.root),env.pixmap,env.gc,    
                          points.pts[couleur],points.nbre[couleur],CoordModeOrigin);
	  } else {               
              for (k=0;k<maxpts;k++) {  
		  rectangles[k]=rectmaker(points.pts[couleur][k],bloc);
              }
              if (!tache_de_fond) XFillRectangles(XtDisplay(env.root),XtWindow(env.drawing),
                                                  env.gc,rectangles,points.nbre[couleur]);
              XFillRectangles(XtDisplay(env.root),env.pixmap,env.gc,    
                              rectangles,points.nbre[couleur]);
	  }   
	  points.nbre[couleur]=0;     
      }
  }
  else    {
      XSetForeground(XtDisplay(env.root),env.gc,env.palette.color[couleur].pixel);

	/*XSetForeground(XtDisplay(env.root),env.gc,couleur);*/
	if (bloc==1){
	  /*	if (!tache_de_fond) XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,i,j,1,1);*/
	  if (!tache_de_fond) XDrawPoint(XtDisplay(env.root),XtWindow(env.drawing),env.gc,i,j);    /* ATTENTION */
	  XDrawPoint(XtDisplay(env.root),env.pixmap,env.gc,i,j);     /* A MODIFIER si bug */
	  /*	if (!tache_de_fond) XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,i,j,1,1);
			XFillRectangle(XtDisplay(env.root),env.pixmap,env.gc,i,j,1,1);*/
	}
	else
	  {
		if (!tache_de_fond) XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,i,j,bloc,bloc);
		XFillRectangle(XtDisplay(env.root),env.pixmap,env.gc,i,j,bloc,bloc);
	  }
  }

  if (gestion_ev) {
	/*if (XtPending()) {
	  XtNextEvent(&ev);
	  XtDispatchEvent(&ev);
	  }    
	  }*/
	if ((!tache_de_fond)&&(XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0)){
	  XNextEvent(XtDisplay(env.root),&ev);
	  if (ev.type==DestroyNotify){
		XtDestroyWidget(env.root);
	  }
	  if (ev.type==Expose){
		XFlush(XtDisplay(env.root));
		XCopyArea(XtDisplay(env.root),env.pixmap,XtWindow(env.drawing),env.gc,0,0,image.width,image.height,0,0); 
	  }
	  if ((ev.type==ButtonPress)&&(ev.xbutton.button==2)){
		XFlush(XtDisplay(env.root));
		*stopper_calc=TRUE;         
		if (tampon) vider_tampons(bloc);
	  }      
	  if ((ev.type==ButtonPress)&&(ev.xbutton.button==3)){
		XFlush(XtDisplay(env.root));
		if (tampon) vider_tampons(bloc);
	  }    
	  /* Pas utile sur hpux */  
	  /*if (ev.type==LeaveNotify) {
		XUninstallColormap(XtDisplay(env.root),env.cmap);      
		if (ev.type==EnterNotify) {
		XInstallColormap(XtDisplay(env.root),env.cmap);
		}   */
	}     
  }     

}
	                


/*****************************************************************************/
void test(w,donnees,appels) 
  Widget w;
XtPointer donnees,appels;
{
  int i,j;   
  complex z;
  FLOAT_SIZE pasx,pasy;

	  
  pasx=(z1.re-z0.re)/image.width;
  pasy=(z0.im-z1.im)/image.height;

  for(j=0;j<image.height;++j){
	for(i=0;i<image.width;++i){
	  z.re=z0.re+i*pasx;
	  z.im=z0.im-j*pasy;
	  definir_couleur(calcul2(z));
	  trace_point(i,j,1);

					
	}   
  }
	
}
/*****************************************************************************/
double MSetDist(z)    /* Distance Estimator - Mandelbrot */
  complex z;
{
  int i,it;
  double x,y,x2,y2;
  double temp;
  double xder,yder;
  double xorbit[2000],yorbit[2000];
  double dist;
  int huge;
  int flag;
  double overflow=1E308;

  x=y=x2=y2=0.0;
  dist=0;
  xorbit[0]=yorbit[0]=0;
  huge=100000;
  for (it=0;(it<iter)&&((x2+y2)<huge);it++) {
	temp=x2-y2+z.re;
	y=2*x*y+z.im;
	x=temp;
	x2=x*x;
	y2=y*y;
	xorbit[it]=x;
	yorbit[it]=y;
  }
  if ((x2+y2)>huge) {
	xder=yder=0.0;
	flag=FALSE;
	for (i=0;((i<it)&&(!flag));i++) {
	  temp=2*(xorbit[i]*xder-yorbit[i]*yder)+1;
	  yder=2*(yorbit[i]*xder+xorbit[i]*yder);
	  xder=temp;
	  if (max(fabs(xder),fabs(yder))>overflow) flag=TRUE;
	}
	/*	printf("%f ",max(fabs(xder),fabs(yder)));*/
	/*	printf("%d ",flag);*/
	if (!flag) {
	  dist=log(x2+y2)*sqrt(x2+y2)/sqrt(xder*xder+yder*yder);}
  }
  /*if (dist!=0.0) printf("%f\n",dist);*/
  return (dist);
}


/*****************************************************************************/
void calcul(w,donnees,appels)    /* Procedure de calcul */
  Widget w;
XtPointer donnees,appels;
{
  int i,j,bloc;   
  complex z;
  lcomplex lz;
  FLOAT_SIZE pasx,pasy;
  int height2;
  int superlarge;
  int larg1,larg2;
  int hau1,hau2;
  int sym=0;                                   
  int pourcent=0;
  char numero[LONG_MAX];      
  int stopper_calc=FALSE;
  /* char nom_fichier[LONG_MAX];      */  
  int iterations;                                        
  int bloc_buffer;           
  long itmax,itmin;                                         
  double coef;
  FLOAT_SIZE lparam;
  long repere=0; /* Pour permettre de reprendre le calcul */
  double dist;
  double threshold=0; /* Distance Estimator Variable */
  char toto[LONG_MAX];

#ifdef TIMER_ON  
  clock_t debut,fin;
#endif

  if (calcul_virtuel) {
	calculBG();
	return;
  }
  /*if (!exist_env.shell) resize();*/
	    
  XSetFunction(XtDisplay(env.root),env.gc,GXcopy);   
  ecrire(CP[167]);

  calcul_en_cours=TRUE;
  stopper_calc=FALSE;         
  bloc_buffer=bloc0;

#ifdef TIMER_ON  
  debut=clock();
#endif

  /* On efface */
  if ((pt_en_cours==0)&&(!tache_de_fond)) {
	XSetForeground(XtDisplay(env.root),env.gc,bpx2);
	XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,0,0,image.width,image.height); 
	XFillRectangle(XtDisplay(env.root),env.pixmap,env.gc,0,0,image.width,image.height); 
  }

  /*Preliminaires*/
  /* On veut une image proportionnelle */
  if (((z1.re-z0.re)/(z0.im-z1.im))>((FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height)) {
	lparam=(z0.im-z1.im)/2+z1.im;
	z1.im=lparam-(z1.re-z0.re)*(FLOAT_SIZE)image.height/(FLOAT_SIZE)image.width/2.0;
	z0.im=lparam+(z1.re-z0.re)*(FLOAT_SIZE)image.height/(FLOAT_SIZE)image.width/2.0;
  }

  if (((z1.re-z0.re)/(z0.im-z1.im))<((FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height)) {
	lparam=(z1.re-z0.re)/2+z0.re;
	z1.re=lparam+(z0.im-z1.im)*(FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height/2.0;
	z0.re=lparam-(z0.im-z1.im)*(FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height/2.0;
  }

  pasx=(z1.re-z0.re)/image.width;
  pasy=(z0.im-z1.im)/image.height;                       


  /* Automatic iteration control */
/*
  iter = iter * 5;
  if ((pt_en_cours==0)&&(type_dessin==NORMAL)) {                   
	itmax=0;
	if (!tache_de_fond) ecrire(CP[168]);
	for(j=0;j<image.height;j+=8){
	  for(i=0;i<image.width;i+=8){
		z.re=(double)(z0.re+i*pasx);
		z.im=(double)(z0.im-j*pasy);
		iterations=calcul2(z);
		if ((iterations>itmax)&&(iterations<iter)) itmax=iterations;
	  }	
	}
       j=0;
         for(i=0;i<image.width;i+=8){
               z.re=(double)(z0.re+i*pasx);
               z.im=(double)(z0.im-j*pasy);
               iterations=calcul2(z);
               if ((iterations>itmax)&&(iterations<iter)) itmax=iterations;
       }      
       j=image.height-1;
         for(i=0;i<image.width;i+=8){
               z.re=(double)(z0.re+i*pasx);
               z.im=(double)(z0.im-j*pasy);
               iterations=calcul2(z);
               if ((iterations>itmax)&&(iterations<iter)) itmax=iterations;
       }      
       for(j=0;j<image.height;j+=8){
         i=0;
               z.re=(double)(z0.re+i*pasx);
               z.im=(double)(z0.im-j*pasy);
               iterations=calcul2(z);
               if ((iterations>itmax)&&(iterations<iter)) itmax=iterations;
       }      
       for(j=0;j<image.height;j+=8){
         i=image.width-1;
               z.re=(double)(z0.re+i*pasx);
               z.im=(double)(z0.im-j*pasy);
               iterations=calcul2(z);
               if ((iterations>itmax)&&(iterations<iter)) itmax=iterations;
       }
  }
  if (iterations <100) iterations=100;
  iter = iterations * 1.5;
 */
  /*XtSetSensitive(env.board,FALSE);*/                      
  /* Palette logarithmique ? => premier passage */
  if ((palettelog)&&(pt_en_cours==0)&&(type_dessin==NORMAL)) {                   
	itmax=0;
	itmin=2147483640;
	if (!tache_de_fond) ecrire(CP[168]);
	for(j=0;j<image.height;j+=8){
	  for(i=0;i<image.width;i+=8){
		if (use_long_double) {
		  lz.re=z0.re+i*pasx;
		  lz.im=z0.im-j*pasy;
		  iterations=calcul3(lz);}
		else {
		  z.re=(double)(z0.re+i*pasx);
		  z.im=(double)(z0.im-j*pasy);
		  iterations=calcul2(z);}
		if (iterations>itmax) itmax=iterations;
		if (iterations<itmin) itmin=iterations;
	  }	
	}      
	if (itmax<MAXCOULEURS) {
	  palettelog=FALSE;
	} 
	else{        
	  /*		printf("iterations %ld %ld\n",itmin,itmax); */
	  coef=exp(log((double)itmax/(double)(itmin+1))/(double)(255));
	  /*	coef=pow((double)(itmax/(itmin+1)),(double)(-255));     */
	  /*printf("coef %f\n",coef);*/
	  palog[0]=0;        
	  palog[1]=itmin;      
	  palog[255]=itmax;                                  
	  for (i=2;i<255;i++) {
		palog[i]=floor(palog[i-1]*coef+0.5);
		if (palog[i]<=palog[i-1]) palog[i]=palog[i-1]+1;   
		if (palog[i]>=itmax) palog[i]=itmax-255+i;
		/* printf("%d %d\n",i,palog[i]); */
	  }
	  if (!tache_de_fond) ecrire(CP[169]);
	  /*printf("%d %d\n",palog[254],palog[255]);*/
	}
  }	
                     


  /*for (i=0;i!=256;i++) {
 	printf("%d\n",palog[i]);} 
	*/

  /* Prise en compte de la symetrie ? */
  if  ((symetrie==1) && ((z1.im*z0.im<0))) 
	sym=1;
  if  ( (symetrie==2) && (z0.re<0.) && (z1.re>0.) && (z0.im>0.) && (z1.im<0.) )
	sym=2;  
  if  ((symetrie==3) && ((z1.re*z0.re<0))) 
	sym=3;
        
  /*if (sauviter) {          
	hau1=(int)(image.height*(z0.im/(z0.im-z1.im)));
	hau2=(int)(image.height*(-z1.im/(z0.im-z1.im)));
	larg1=(int)(image.width*(-z0.re/(z1.re-z0.re)));
	larg2=(int)(image.width*(z1.re/(z1.re-z0.re)));
	strcpy(nom_fichier,"iter.xfe");      
	if ((fichier = fopen(nom_fichier,"w"))==NULL)
	{perror(CP[170]);}   
	fprintf(fichier,"%d\n",sym);
	fprintf(fichier,"%d\n",bloc0);
	fprintf(fichier,"%d\n",iter);
	fprintf(fichier,"%d %d\n",image.width,image.height);
	fprintf(fichier,"%d %d\n",hau1,hau2);
	fprintf(fichier,"%d %d\n",larg1,larg2);
	}*/

  if (type_dessin==ESTIMATEUR) {
	threshold=1E-5*render.delta*(z1.re-z0.re)/(image.width-1);
	bloc_buffer=bloc0;
	bloc0=1;
  }

  if (sauvPPM) {
	pt_en_cours=0;
	save_ppm1();    
	sym=0;     
	bloc_buffer=bloc0;
	bloc0=1;}


  if (sauvPostscript) {
	pt_en_cours=0;
	save_postscript1();  
	sym=0;    
	bloc_buffer=bloc0;
	/*tampon=FALSE;*/
	bloc0=1;}

  if (tache_de_fond) {
	bloc_buffer=bloc0;
	bloc0=1;}


  repere=0;

  if (sym==0){	/* No symetry */

	for(bloc=bloc0;bloc>=1;bloc/=2){
	  for(j=0;j<image.height;j+=bloc){
		for(i=0;i<image.width;i+=bloc){
		  if ((bloc0==1)|| (bloc==8) || (i%(bloc*2) !=0) || (j%(bloc*2)!=0) ) {
			repere++;
			if (repere>pt_en_cours) {
			  z.re=(double)(z0.re+i*pasx);
			  z.im=(double)(z0.im-j*pasy);
			  if (type_dessin==ESTIMATEUR) {	
				dist=MSetDist(z);
				if (dist>threshold) {couleur=wpx;} 
				else {couleur=bpx;}
			  }
			  if (type_dessin==NORMAL) {
				if (use_long_double) {
				  lz.re=z0.re+i*pasx;
				  lz.im=z0.im-j*pasy;
				  iterations=calcul3(lz);}
				else iterations=calcul2(z);
				definir_couleur(iterations);
				if (sauviter) fprintf(fichier,"%d ",iterations);
			  }
			  if (sauvPPM) save_ppm2(couleur);
			  if (sauvPostscript) save_postscript2(couleur);
			  /*if (!sauvPostscript) */ trace_point(i,j,bloc,&stopper_calc); 
			}
		  }	
		  if (stopper_calc) break;
		}    
		if  (sauvPostscript) save_postscript3(); 
		if (bloc==1) {pourcent=(j*75)/image.height+25;}
		else if (bloc==2) {pourcent=(j*12)/image.height+6;}
		else if (bloc==4) {pourcent=(j*3)/image.height+1;}
		else {pourcent=0;}    
		if (bloc_buffer==1) pourcent=(j*100)/image.height;
			
		sprintf(numero,"%d %% %s",pourcent,CP[171]);
		if ((repere>pt_en_cours)&&(!tache_de_fond)) ecrire(numero);
		if (stopper_calc) break;
	  }  
	  if (stopper_calc) break;
	  if (tampon) vider_tampons(bloc);
	}
	/*printf("%ld\n",repere);*/
	if (!stopper_calc) pt_en_cours=0;
  }



  if (sym==1){	/* x-axis symetry e.g.: Mandelbrot set */

	hau1=(int)(image.height*(z0.im/(z0.im-z1.im)));
	hau2=(int)(image.height*(-z1.im/(z0.im-z1.im)));
	height2=max(hau1,hau2);

	for(bloc=bloc0;bloc>=1;bloc/=2){
	  for(j=0;j<=height2;j+=bloc){
		for(i=0;i<image.width;i+=bloc){   
		  if ((bloc0==1)|| (bloc==8) || (i%(bloc*2) !=0) || (j%(bloc*2)!=0) ) {
			repere++;
			if (repere>pt_en_cours) {
			  z.re=(double)(z0.re+i*pasx);
			  z.im=(double)(j*pasy);
			  if (type_dessin==ESTIMATEUR) {	
				dist=MSetDist(z);
				if (dist>threshold) couleur=wpx; else couleur=bpx;
			  }
			  if (type_dessin==NORMAL) {
				if (use_long_double) {
				  lz.re=z0.re+i*pasx;
				  lz.im=j*pasy;
				  iterations=calcul3(lz);}
				else iterations=calcul2(z);
				if (sauviter) fprintf(fichier,"%d ",iterations);
				definir_couleur(iterations);
			  }
			  if (j<=hau1) trace_point(i,hau1-j,bloc,&stopper_calc);
			  if (j<=hau2) trace_point(i,j+hau1,bloc,&stopper_calc);
			}
		  }
		  if (stopper_calc) break;
		}   
		if (stopper_calc) break;
		if (bloc==1) {pourcent=(j*75)/height2+25;}
		else if (bloc==2) {pourcent=(j*12)/height2+6;}
		else if (bloc==4) {pourcent=(j*3)/height2+1;}
		else {pourcent=0;}
		if (bloc_buffer==1) pourcent=(j*100)/height2;

		sprintf(numero,"%d %% %s",pourcent,CP[171]);
		if ((repere>pt_en_cours)&&(!tache_de_fond)) ecrire(numero);
	  }     
	  if (stopper_calc) break;
	  if (tampon) vider_tampons(bloc);
	}
	if (!stopper_calc) pt_en_cours=0;
  }



  if (sym==2){	/* Origin symetry. e.g: Julia sets */

	hau1=(int)(image.height*(z0.im/(z0.im-z1.im)));
	hau2=(int)(image.height*(-z1.im/(z0.im-z1.im)));
	larg1=(int)(image.width*(-z0.re/(z1.re-z0.re)));
	larg2=(int)(image.width*(z1.re/(z1.re-z0.re)));
	superlarge=max(larg1,larg2);
	height2=max(hau1,hau2);


	for(bloc=bloc0;bloc>=1;bloc/=2){
	  for(j=0;j<=height2;j+=bloc){
		for(i=-superlarge;i<=superlarge;i+=bloc){
		  if ((bloc0==1)|| (bloc==8) || (i%(bloc*2) !=0) || (j%(bloc*2)!=0) ) {
			repere++;
			if (repere>pt_en_cours) {
			  if ( (i<=0) && ( ((j<=hau2)&&(-i<=larg2)) ||
							   ((j<=hau1)&&(-i<=larg1)) ) ) {
				z.re=(double)(i*pasx);
				z.im=(double)(j*pasy);
				if (type_dessin==ESTIMATEUR) {								
				  dist=MSetDist(z);
				  if (dist>threshold) couleur=wpx; else couleur=bpx;
				}
				if (type_dessin==NORMAL) {	
				  if (use_long_double) {
					lz.re=i*pasx;
					lz.im=j*pasy;
					iterations=calcul3(lz);}
				  else iterations=calcul2(z);
				  if (sauviter) fprintf(fichier,"%d ",iterations);
				  definir_couleur(iterations);
				}
				if ((j<=hau1)&&(-i<=larg1)) trace_point(i+larg1,hau1-j,bloc,&stopper_calc);
				if ((j<=hau2)&&(-i<=larg2))
				  trace_point(-i+larg1,hau1+j,bloc,&stopper_calc);
			  }
			  if ( (i>=0) && ( ((j<=hau2)&&(i<=larg1)) ||
							   ((j<=hau1)&&(i<=larg2)) ) ) {
				z.re=(double)(i*pasx);
				z.im=(double)(j*pasy);
				if (type_dessin==ESTIMATEUR) {								
				  dist=MSetDist(z);
				  if (dist>threshold) couleur=wpx; else couleur=bpx;
				}
				if (type_dessin==NORMAL) {	
				  if (use_long_double) {
					lz.re=i*pasx;
					lz.im=j*pasy;
					iterations=calcul3(lz);}
				  else iterations=calcul2(z);
				  if (sauviter) fprintf(fichier,"%d ",iterations);
				  definir_couleur(iterations);
				}
				if ((j<=hau1)&&(i<=larg2)) trace_point(i+larg1,hau1-j,bloc,&stopper_calc);
				if ((j<=hau2)&&(i<=larg1))
				  trace_point(-i+larg1,hau1+j,bloc,&stopper_calc);
			  }
			}
		  }
		  if (stopper_calc) break;
		}   
		if (stopper_calc) break;
		if (bloc==1) {pourcent=(j*75)/height2+25;}
		else if (bloc==2) {pourcent=(j*12)/height2+6;}
		else if (bloc==4) {pourcent=(j*3)/height2+1;}
		else {pourcent=0;}
		if (bloc_buffer==1) pourcent=(j*100)/height2;

		sprintf(numero,"%d %% %s",pourcent,CP[171]);
		if ((repere>pt_en_cours)&&(!tache_de_fond)) ecrire(numero);
	  }
	  if (stopper_calc) break;
	  if (tampon) vider_tampons(bloc);
	}
	pt_en_cours=0;
	if (!stopper_calc) pt_en_cours=0;
  }

  if (sym==3){	/* y-axis symetry e.g.: Barnsley M2 */

	larg1=(int)(image.width*(-z0.re/(z1.re-z0.re)));
	larg2=(int)(image.width*(z1.re/(z1.re-z0.re)));
	superlarge=max(larg1,larg2);

	for(bloc=bloc0;bloc>=1;bloc/=2){
	  for(j=0;j<image.height;j+=bloc){
		for(i=0;i<superlarge;i+=bloc){   
		  if ((bloc0==1)|| (bloc==8) || (i%(bloc*2) !=0) || (j%(bloc*2)!=0) ) {
			repere++;
			if (repere>pt_en_cours) {
			  z.re=(double)(i*pasx);
			  z.im=(double)(z0.im-j*pasy);
			  if (type_dessin==ESTIMATEUR) {	
				dist=MSetDist(z);
				if (dist>threshold) couleur=wpx; else couleur=bpx;
			  }
			  if (type_dessin==NORMAL) {
				if (use_long_double) {
				  lz.re=z0.re+i*pasx;
				  lz.im=j*pasy;
				  iterations=calcul3(lz);}
				else iterations=calcul2(z);
				if (sauviter) fprintf(fichier,"%d ",iterations);
				definir_couleur(iterations);
			  }
			  if (i<=larg1) trace_point(larg1-i,j,bloc,&stopper_calc);
			  if (i<=larg2) trace_point(i+larg1,j,bloc,&stopper_calc);
			}
		  }
		  if (stopper_calc) break;
		}   
		if (stopper_calc) break;
		if (bloc==1) {pourcent=(j*75)/image.height+25;}
		else if (bloc==2) {pourcent=(j*12)/image.height+6;}
		else if (bloc==4) {pourcent=(j*3)/image.height+1;}
		else {pourcent=0;}    
		if (bloc_buffer==1) pourcent=(j*100)/image.height;

		sprintf(numero,"%d %% %s",pourcent,CP[171]);
		if ((repere>pt_en_cours)&&(!tache_de_fond)) ecrire(numero);
	  }     
	  if (stopper_calc) break;
	  if (tampon) vider_tampons(bloc);
	}
	if (!stopper_calc) pt_en_cours=0;
  }




  if (sauviter) fclose(fichier);   
  if  (sauvPostscript) save_postscript4();  
  if (sauvPPM) {
	sauvPPM=FALSE;
	fclose(fichier);  
	ecrire(CP[172]); 
	ecrire_bibli(nomPPM);
  }    
  calcul_en_cours=FALSE;   
  pt_en_cours=repere;
  /*printf("%d\n",pt_en_cours);*/

  sprintf(toto,"%s",CP[173]);

#ifdef TIMER_ON  
  fin=clock();
  sprintf(toto,"%s %ld s",CP[173],(long)((fin-debut)/(CLOCKS_PER_SEC)));
#endif

  if ((bipbip)&&(!tache_de_fond)) XBell(XtDisplay(env.root),100);  
  if (!tache_de_fond) ecrire(toto);  
  bloc0=bloc_buffer;
/*
  printf("Erreurs: %d, soit %2.2f %%\n", comp1, (float)comp1*100.0/(comp1+comp2));
  printf("+1 : %d, -1: %d, autres: %d, moyenne: %f, somme: %d, somme absolue:%d\n", nbpl1, nbm1, nbau, (float)nbav/(comp1+comp2) ,nbav, nbavn);
  comp1=0; comp2=0; nbpl1=0; nbm1=0; nbau=0; nbav=0; nbavn=0;
*/
}     

/*****************************************************************************/
void calculBG()    /* Procedure de calcul en tache de fond */
{
  int i,j;   
  complex z;
  FLOAT_SIZE pasx,pasy;
  int iterations;                                        
  long itmin,itmax;
  double coef;
  FLOAT_SIZE param;
  lcomplex lz;
  double dist;
  double threshold=0;
	                                        
  /*Preliminaires*/
  /* On veut une image proportionnelle */
  if (((z1.re-z0.re)/(z0.im-z1.im))>((FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height)){
	param=(z0.im-z1.im)/2+z1.im;
	z1.im=param-(z1.re-z0.re)*(FLOAT_SIZE)image.height/(FLOAT_SIZE)image.width/2.0;
	z0.im=param+(z1.re-z0.re)*(FLOAT_SIZE)image.height/(FLOAT_SIZE)image.width/2.0;
  }

  if (((z1.re-z0.re)/(z0.im-z1.im))<((FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height)){
	param=(z1.re-z0.re)/2+z0.re;
	z1.re=param+(z0.im-z1.im)*(FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height/2.0;
	z0.re=param-(z0.im-z1.im)*(FLOAT_SIZE)image.width/(FLOAT_SIZE)image.height/2.0;
  }

  pasx=(z1.re-z0.re)/image.width;
  pasy=(z0.im-z1.im)/image.height;                       
 
  /*XtSetSensitive(env.board,FALSE);*/                      
  /* Palette logarithmique ? => premier passage */
  if (palettelog) {                   
	itmax=0;
	itmin=320000;
	for(j=0;j<image.height;j+=8){
	  for(i=0;i<image.width;i+=8){
		if (use_long_double) {
		  lz.re=z0.re+i*pasx;
		  lz.im=z0.im-j*pasy;
		  iterations=calcul3(lz);}
		else {
		  z.re=(double)(z0.re+i*pasx);
		  z.im=(double)(z0.im-j*pasy);
		  iterations=calcul2(z);}
		if (iterations>itmax) itmax=iterations;
		if (iterations<itmin) itmin=iterations;
	  }	
	}      
	if (itmax<MAXCOULEURS) {
	  palettelog=FALSE;
	} 
	else{        
	  printf("iterations %ld %ld\n",itmin,itmax);
	  coef=exp(log((double)itmax/(double)(itmin+1))/(double)(255));
	  /*	coef=pow((double)(itmax/(itmin+1)),(double)(-255));     */
	  printf("coef %f\n",coef);
	  palog[0]=0;        
	  palog[1]=itmin;      
	  palog[255]=itmax;                                  
	  for (i=2;i<255;i++) {
		palog[i]=floor(palog[i-1]*coef+0.5);
		if (palog[i]<=palog[i-1]) palog[i]=palog[i-1]+1;   
		if (palog[i]>=itmax) palog[i]=itmax-255+i;
		/*printf("%d %d\n",i,palog[i]);*/
	  }
	  /*ecrire("Palette calculee");*/
	  printf("%d %d %d %d\n",palog[252],palog[253],palog[254],palog[255]);
	}
  }
  /*if (sauviter) {          
	strcpy(nom_fichier,"iter.xfe");      
	if ((fichier = fopen(nom_fichier,"w"))==NULL)
	{perror(CP[170]);}   
	fprintf(fichier,"%d\n",iter);
	fprintf(fichier,"%d %d\n",image.width,image.height);
	}*/

  if (sauvPPM) {
	save_ppm1(); }  
 
  if (sauvPostscript) {
	save_postscript1();    
  }
  if (type_dessin==ESTIMATEUR) {
	threshold=1E-5*render.delta*(z1.re-z0.re)/(image.width-1);
  }  

  /* boucle de calcul */ 	    
  for(j=0;j<image.height;j++){
	for(i=0;i<image.width;i++){
	  z.re=(double)(z0.re+i*pasx);
	  z.im=(double)(z0.im-j*pasy);
	  if (type_dessin==ESTIMATEUR) {	
		dist=MSetDist(z);
		if (dist>threshold) couleur=1; 
		else couleur=0;
	  }
	  if (type_dessin==NORMAL) {
		if (use_long_double) {
		  lz.re=z0.re+i*pasx;
		  lz.im=z0.im-j*pasy;
		  iterations=calcul3(lz);}
		else iterations=calcul2(z);
		definir_couleur(iterations);
		if (sauviter) fprintf(fichier,"%d ",iterations);
	  }
	  if (sauvPPM) save_ppm2(couleur);
	  if (sauvPostscript) save_postscript2(couleur);
	}       
	if  (sauvPostscript) save_postscript3();  
  }

  if  (sauvPostscript) save_postscript4(); 
  if (sauviter) fclose(fichier);   
  if (sauvPPM) {
	sauvPPM=FALSE;
	fclose(fichier);  
	ecrire_bibli(nomPPM);
  }    
  if (sauvGIF) {     
	sauvGIF=FALSE; 
  }
  exit(0);
  return;
}     




/*****************************************************************************/


void init()
{

  render.int_mult_mod=1e4;
  render.ext_mult_mod=1e3;

  use_long_double=FALSE;
  bailout=4.0;
  render.delta=1.0;
  coul_for=255;
  coul_back=0;  
  type_postscript=NOIR;
  tache_de_fond=FALSE;
  initcoord=FALSE;
  sauvPPM=FALSE;
  sauvGIF=FALSE; 
  sauvPostscript=FALSE;
  calcul_en_cours=FALSE;   
  calcul_virtuel=FALSE;
  nbre_cycles=3;
  sens_cycle=1;
  vit_cycle=2;

  bpx=0;
  wpx=1;

  maxpts=200;
  tampon=TRUE;
  gestion_ev=TRUE;
  bipbip=FALSE;
  bloc0=8;
  sauviter=FALSE;   
  type_dessin=NORMAL;    
  palettelog=FALSE;

  /*palette_en_cours=FALSE;*/

  cz.re=0.0;
  cz.im=0.0;
  z0.re=z0.im=z1.re=z1.im=0.0;
  ip=0;	

  iter=250;               
  image.width=640;
  image.height=512;
	
  pt_en_cours=0;

  genre=MANDELBROT;      
	       
  calcul_en_cours=FALSE;
  sprintf(nompalette,"%s/%s",PALETTE_DIR,PAL_DEF);
	
}

/*****************************************************************************/


void init_texte(char *lang) /* Routine tiree de GNUchess */
{
  FILE *constfile;
  char s[512];
  char sl[5];
  int len, entry;
  char *p, *q;
  constfile = fopen (LANG_FILE, "r");

  if (!constfile)
    {
      fprintf (stderr,"NO LANGFILE (%s)\n",LANG_FILE);
      exit (1);
    }
  while (fgets (s, sizeof (s), constfile))
    {
      if (s[0] == '!') continue;
      len = strlen (s);
      for (q = &s[len]; q > &s[8]; q--) if (*q == '}') break;
      if (q == &s[8])
		{
		  printf ("{ error in constfile\n");
		  exit (1);
		}
      *q = '\0';
      if (s[3] != ':' || s[7] != ':' || s[8] != '{')
		{
		  printf ("Langfile format error %s\n", s);
		  exit (1);
		}
      s[3] = s[7] = '\0';
      if (lang == NULL)
		{
		  lang = sl;
		  strcpy (sl, &s[4]);
		}
      if (strcmp (&s[4], lang))
		continue;
      entry = atoi (s);
      if (entry < 0 || entry >= CPSIZE)
		{
		  printf ("Langfile number error\n");
		  exit (1);
		}
      for (q = p = &s[9]; *p; p++)
		{
		  if (*p != '\\')
			{
			  *q++ = *p;
			}
		  else if (*(p + 1) == 'n')
			{
			  *q++ = '\n';
			  p++;
			}
		}
      *q = '\0';
      if (entry < 0 || entry > 255)
		{
		  printf ("Langfile error %d\n", entry);
		  exit (0);
		}
      CP[entry] = (char *) malloc ((unsigned) strlen (&s[9]) + 1);
      if (CP[entry] == NULL)
		{
		  perror ("malloc");
		  exit (0);
		}
      strcpy (CP[entry], &s[9]);

    }
  fclose (constfile);
}


/**********************************************************************************************************/

void rafraichir(w,client,appel)
  Widget w;
XtPointer client; 
XmDrawingAreaCallbackStruct *appel;
{                         
  /*XExposeEvent *evt = (XExposeEvent*) appel->event;     

	XCopyArea(XtDisplay(w),env.pixmap,XtWindow(env.drawing),env.gc,evt->x,evt->y,evt->width,evt->height,evt->x,evt->y);*/
        
  XCopyArea(XtDisplay(w),env.pixmap,XtWindow(env.drawing),env.gc,0,0,image.width,image.height,0,0); 
} 


/*****************************************************************************/

void rafraichir_mes(w,client,appel)
  Widget w;
XtPointer client; 
XmDrawingAreaCallbackStruct *appel;
{                         
  XCopyArea(XtDisplay(w),env.mes_pix,XtWindow(env.message),env.gc,0,0,MESSAGE_L,MESSAGE_H,0,0); 
} 

/*****************************************************************************/


void map(w,client,appel)
  Widget w;
XtPointer client,appel; 
{
  XInstallColormap(XtDisplay(env.root),env.cmap);                         
} 
/*****************************************************************************/

void unmap(w,client,appel)
  Widget w;
XtPointer client,appel; 
{                         
  XUninstallColormap(XtDisplay(env.root),env.cmap);                         
} 

/*****************************************************************************/

void detruire(w,client,appel)
  Widget w;
XtPointer client,appel; 
{                         
  XtDestroyWidget(env.root);                         
} 

/*****************************************************************************/

/*void Change_palette(w,client,appel)
Widget w;
XtPointer client,appel; 
{       
if (palette_en_cours==FALSE) {    
	XSetWindowColormap(XtDisplay(env.root),XtWindow(env.root),env.cmap); 
	ecrire(CP[174]); }
else {
	XSetWindowColormap(XtDisplay(env.root),XtWindow(env.root),pal_def); 
	ecrire(CP[175]); }
palette_en_cours=!palette_en_cours;
} */


/*****************************************************************************/

void efface()                              
{  
  /* On efface tout */
  XSetForeground(XtDisplay(env.root),env.gc,bpx2);
  XFillRectangle(XtDisplay(env.root),env.pixmap,env.gc,0,0,image.width,image.height);  
  XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,0,0,image.width,image.height);  

}

/*****************************************************************************/

void resize()                            
{                                             
  int nargs;
  Arg argu[20];
  char toto[100];

  pt_en_cours=0;
  /*printf("resize\n");*/

  if ((image.width>LARGEUR_MAX)||(image.height>HAUTEUR_MAX)) {
	ecrire(CP[176]);
	calcul_virtuel=TRUE;
	return;
  }   
  else  	calcul_virtuel=FALSE;          
  /* Le chargement d'image ne marche qu'avec des tailles + larges que hautes */

  XtDestroyWidget(env.drawing);
  XtDestroyWidget(env.shell);


  /*****************/
  /* Fenetre Image */
  /*****************/

  nargs=0;    
  XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
  XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
  XtSetArg(argu[nargs],XmNdeleteResponse, XmDO_NOTHING);nargs++;
  env.shell=XtCreateApplicationShell("Fenetre",topLevelShellWidgetClass,argu,nargs);
  /*XtAddCallback(env.shell,XtNdestroyCallback,exist,NULL);*/


  /* Initialisation des ressources */
  nargs=0;    
  XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
  XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
  XtSetArg(argu[nargs],XmNx,0);nargs++;
  XtSetArg(argu[nargs],XmNy,0);nargs++;
  XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
  XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
  env.drawing=XtCreateManagedWidget("env.drawing",xmDrawingAreaWidgetClass,env.shell,argu,nargs);
  /* env.drawing=XmCreateDrawingArea(env.shell,"env.drawing",argu,nargs);   */
  XtAddCallback(env.drawing,XmNexposeCallback,rafraichir,NULL);
  /* XtMoveWidget(env.drawing,0,50); */

  XtManageChild(env.drawing);   
  XtRealizeWidget(env.shell);
    
  /* on remplace l'ancien env.pixmap */
  XFreePixmap (XtDisplay(env.root),env.pixmap);  
  /*XtFree(env.pixmap);*/
  /*printf("avant malloc\n");
	env.pixmap=XtMalloc(image.width*image.height);
	printf("apres malloc\n");*/

  env.pixmap= XCreatePixmap(XtDisplay(env.root),
						DefaultRootWindow(XtDisplay(env.root)),
						image.width,image.height, 
						DefaultDepthOfScreen(XtScreen(env.root)));
 
  sprintf(toto,"%s: %d  %s: %d",CP[113],image.width,CP[114],image.height);
  ecrire(toto);
  XSetWindowColormap(XtDisplay(env.shell),XtWindow(env.shell),env.cmap);  
  XSetWindowColormap(XtDisplay(env.shell),XtWindow(env.drawing),env.cmap);  
  efface();
}  
/*****************************************************************************/

void display_window()
{                                             
  int nargs;
  Arg argu[20];
  char dispString[255];

  pt_en_cours=0;


  /*****************/
  /* Fenetre Image */
  /*****************/

  nargs=0;    
  XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
  XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
  XtSetArg(argu[nargs],XmNdeleteResponse, XmDO_NOTHING);nargs++;
  env.shell=XtCreateApplicationShell("Fenetre",topLevelShellWidgetClass,argu,nargs);
  /*XtAddCallback(env.shell,XtNdestroyCallback,exist,NULL);*/


  /* Initialisation des ressources */
  nargs=0;    
  XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
  XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
  XtSetArg(argu[nargs],XmNx,0);nargs++;
  XtSetArg(argu[nargs],XmNy,0);nargs++;
  XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
  XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
  env.drawing=XtCreateManagedWidget("env.drawing",xmDrawingAreaWidgetClass,env.shell,argu,nargs);
  /* env.drawing=XmCreateDrawingArea(env.shell,"env.drawing",argu,nargs);   */
  XtAddCallback(env.drawing,XmNexposeCallback,rafraichir,NULL);
  /* XtMoveWidget(env.drawing,0,50);*/

  XtManageChild(env.drawing);   
  XtRealizeWidget(env.shell);
    
  /* on remplace l'ancien env.pixmap */
  XFreePixmap (XtDisplay(env.root),env.pixmap);  
  /*XtFree(env.pixmap);*/
  /*printf("avant malloc\n");
	env.pixmap=XtMalloc(image.width*image.height);
	printf("apres malloc\n");*/

  env.pixmap= XCreatePixmap(XtDisplay(env.root),
						DefaultRootWindow(XtDisplay(env.root)),
						image.width,image.height, 
						DefaultDepthOfScreen(XtScreen(env.root)));
 
  sprintf(dispString,"%s: %d  %s: %d",CP[113],image.width,CP[114],image.height);
  ecrire(dispString);
  XSetWindowColormap(XtDisplay(env.shell),XtWindow(env.shell),env.cmap);  
  XSetWindowColormap(XtDisplay(env.shell),XtWindow(env.drawing),env.cmap);  
  efface();
}  
  
/*****************************************************************************/

int main(argc,argv)
  int argc;
char **argv;  
{      
  int ecran;
  int i;
  char Lang[4];
  char option[256];
#ifdef FRENCH
  strcpy(Lang,"fra");
#else
  strcpy(Lang,"eng");
#endif


  init();   
  if (argc!=1) {
	if ((!strcmp(*(argv+1),"-help"))||(!strcmp(*(argv+1),"-h"))||(!strcmp(*(argv+1),"?")))
	  { 
		printf("\n");
		printf("	XFractal_Explorer v1.1\n");
		printf("	======================\n");
		printf("				Nicolas GUERIN 1994\n");
		printf("usage:\n");
		printf("xfe [-lang (eng/fra)] \n"); 
		printf("    [-type (mandel/julia/newton/mandellambda/lambda/noel1/noel2/spider/phoenix\n");
		printf("            mandel-n/julia-n/barnm1/barnj1/barnm2/barnj2/barnm3/barnj3/tetrate\n");
		printf("            mcos/jcos/msin/jsin/mexp/jexp/markm/markj)] \n");
		printf("    [-size width height] \n");
		printf("    [-iter n] \n");
		printf("    [-const Re(c) Im(c)] \n");
		printf("    [-int n] \n");
		printf("    [-coord left up right down] \n");
		printf("    [-logpalette] \n");
		printf("    [-estimator] \n");
		printf("    [-nobuffer] \n");
		printf("    [-palette filename.map] \n");
		printf("\n");
		exit(0); 
	  } 
   
	i=1; 
	while (i<argc-1) 
	  { 
		strcpy(option,*(argv+i)); i++; 
    
		if (!strcmp(option,"-lang")) 
		  { 
			sscanf(*(argv+i),"%s",Lang); 
			i++; 
		  } 

		if (!strcmp(option,"-type")) 
		  { 
                      char toto[256]; 
                      
                      sscanf(*(argv+i),"%s",toto); 
			i++; 
			if (!strcmp(toto,"mandel")) genre=MANDELBROT;
			if (!strcmp(toto,"julia")) genre=JULIA ;
			if (!strcmp(toto,"newton")) genre=NEWTON;
			if (!strcmp(toto,"mandel-n")) genre=MANDELN;
			if (!strcmp(toto,"julia-n")) genre=JULIAN;
			if (!strcmp(toto,"mandellambda")) genre=MANDELLAMBDA;
			if (!strcmp(toto,"lambda")) genre=LAMBDA;
			if (!strcmp(toto,"markj")) genre=MARKJ;
			if (!strcmp(toto,"markm")) genre=MARKM;
			if (!strcmp(toto,"barnm1")) genre=BARNM1;
			if (!strcmp(toto,"barnj1")) genre=BARNJ1;
			if (!strcmp(toto,"barnm2")) genre=BARNM2;
			if (!strcmp(toto,"barnj2")) genre=BARNJ2;
			if (!strcmp(toto,"barnm3")) genre=BARNM3;
			if (!strcmp(toto,"barnj3")) genre=BARNJ3;
			if (!strcmp(toto,"noel1")) genre=NOEL1;
			if (!strcmp(toto,"noel2")) genre=NOEL2;
			if (!strcmp(toto,"mcos")) genre=MCOS;
			if (!strcmp(toto,"jcos")) genre=JCOS;
			if (!strcmp(toto,"msin")) genre=MSIN;
			if (!strcmp(toto,"jsin")) genre=JSIN;
			if (!strcmp(toto,"mexp")) genre=MEXP;
			if (!strcmp(toto,"jexp")) genre=JEXP;
			if (!strcmp(toto,"spider")) genre=SPIDER;
			if (!strcmp(toto,"phoenix")) genre=PHOENIX;
			if (!strcmp(toto,"tetrate")) genre=TETRATE;
		  } 

		if (!strcmp(option,"-iter")) 
		  { 
			sscanf(*(argv+i),"%d",&iter); 
			i++; 
		  } 

		if (!strcmp(option,"-size")) 
		  { 
			sscanf(*(argv+i),"%d",&image.width); 
			i++; 
			sscanf(*(argv+i),"%d",&image.height); 
			i++; 
		  } 


		if (!strcmp(option,"-coord")) 
		  { 
			sscanf(*(argv+i),"%Le",&z0.re); 
			i++; 
			sscanf(*(argv+i),"%Le",&z0.im); 
			i++; 
			sscanf(*(argv+i),"%Le",&z1.re); 
			i++; 
			sscanf(*(argv+i),"%Le",&z1.im); 
			i++; 
			initcoord=TRUE;
		  } 

		if (!strcmp(option,"-const")) 
		  { 
			sscanf(*(argv+i),"%Le",&cz.re); 
			i++; 
			sscanf(*(argv+i),"%Le",&cz.im); 
			i++; 
		  } 

		if (!strcmp(option,"-int")) 
		  { 
			sscanf(*(argv+i),"%d",&ip); 
			i++; 
		  } 

		if (!strcmp(option,"-logpalette")) 
		  { 
			palettelog=TRUE;
		  } 

		if (!strcmp(option,"-nobuffer")) 
		  { 
			tampon=FALSE;
		  } 

		if (!strcmp(option,"-estimator")) 
		  { 
			type_dessin=ESTIMATEUR;
		  } 
		if (!strcmp(option,"-palette")) 
		  { 
			sscanf(*(argv+i),"%s",nompalette); 
			i++;
		  }
	  }
  } 

  env.root=XtInitialize(argv[0],"Fractal",NULL,0,&argc,argv); 

  /*nargs=0;    
	XtSetArg(argu[nargs],XmNwidth,300); nargs++;
	XtSetArg(argu[nargs],XmNheight,300); nargs++; 
	XtCreateManagedWidget("XFE 1.1",widgetClass,env.root,argu,nargs);*/

  ecran=DefaultScreen(XtDisplay(env.root));
  bpx2=BlackPixel(XtDisplay(env.root),ecran);
  wpx2=WhitePixel(XtDisplay(env.root),ecran);

  /* initialise le tampon */
  for (i=0; i<MAXCOULEURS;i++) points.nbre[i]=0;

  init_texte(Lang);       
  init_fractal(genre);  
  initx();       
  initialiser_couleurs();                

  XtRealizeWidget(env.root);   
  /*XtRealizeWidget(env.shell); */  
   

  /*XSetWindowColormap(XtDisplay(env.shell),XtWindow(env.shell),env.cmap); */
  display_window(); 
  ecrire(CP[73]); 
  XtMainLoop();

  return 0;
}
		
