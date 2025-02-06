/*
 * anim.c
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

static FILE *fichier; 

#define LFABS(A)	(A)>0?(A):-(A)

/*******************************************************************************************************************************/

static void sauv_param_anim_im(nom,larg,haut,nbre,im1z0,im1z1,im2z0,im2z1,iter1,iter2)
char *nom;
int larg,haut,nbre;
lcomplex im1z0,im1z1,im2z0,im2z1;
int iter1,iter2;
{
FILE                    *fichierdisque;  
char			nomtempo[256];

sprintf(nomtempo,"%s.par",nom);                                                
if ((fichierdisque = fopen(nom,"a"))==NULL)
{
   perror(CP[140]);
} 
fprintf(fichierdisque,"%s\n",CP[177]);               
fprintf(fichierdisque,"%s\n",nom);
fprintf(fichierdisque,"%s\n",CP[180]);               
fprintf(fichierdisque,"%d\n",larg);
fprintf(fichierdisque,"%d\n",haut);
fprintf(fichierdisque,"%s\n",CP[181]);               
fprintf(fichierdisque,"%d\n",genre);
fprintf(fichierdisque,"%s\n",CP[182]);               
fprintf(fichierdisque,"%d\n",nbre);
fprintf(fichierdisque,"%s\n",CP[178]);               
fprintf(fichierdisque,FORMAT,im1z0.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im1z0.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im1z1.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im1z1.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,"%d\n",iter1);
fprintf(fichierdisque,"%s\n",CP[179]);               
fprintf(fichierdisque,FORMAT,im2z0.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im2z0.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im2z1.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,im2z1.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,"%d\n",iter2);
fprintf(fichierdisque,"%d\n",type_dessin);
fprintf(fichierdisque,"%.16e",bailout);
if ((genre==JULIA)||(genre==JULIA3)||(genre==LAMBDA)) {
	fprintf(fichierdisque,"\n");
	fprintf(fichierdisque,FORMAT,cz.re);
	fprintf(fichierdisque,"\n");
	fprintf(fichierdisque,FORMAT,cz.im); 
	}
if (genre==NEWTON) fprintf(fichierdisque,"\n%d",ip);  
                                   
fclose(fichierdisque); 
}             


/*******************************************************************************************************************************/

static void sauv_param_anim_pt(nom,larg,haut,nbre,pt1,pt2,z0,z1)
char *nom;
int larg,haut,nbre;
lcomplex pt1,pt2,z0,z1;
{
FILE                    *fichierdisque;  
char			nomtempo[256];

sprintf(nomtempo,"%s.par",nom);                                                
if ((fichierdisque = fopen(nom,"a"))==NULL)
{
   perror(CP[140]);
} 
fprintf(fichierdisque,"%s\n",CP[177]);               
fprintf(fichierdisque,"%s\n",nom);
fprintf(fichierdisque,"%s\n",CP[180]);               
fprintf(fichierdisque,"%d\n",larg);
fprintf(fichierdisque,"%d\n",haut);
fprintf(fichierdisque,"%s\n",CP[181]);               
fprintf(fichierdisque,"%d\n",genre);
fprintf(fichierdisque,"%s\n",CP[182]);               
fprintf(fichierdisque,"%d\n",nbre);
fprintf(fichierdisque,"%s\n",CP[183]);               
fprintf(fichierdisque,FORMAT,z0.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,z0.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,z1.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,z1.im);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,"%d\n",iter);
fprintf(fichierdisque,"%d\n",type_dessin);
fprintf(fichierdisque,"%.16e",bailout);
fprintf(fichierdisque,"%s\n",CP[184]);               
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,pt1.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,pt1.im); 
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,"%s\n",CP[185]);               
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,pt2.re);
fprintf(fichierdisque,"\n");
fprintf(fichierdisque,FORMAT,pt2.im); 
                                   
fclose(fichierdisque); 
}


/*******************************************************************************************************************************/

static void saveppm1(nom,larg,haut)   /* sauvegarde de l'image au format PPM - initialisation */
char *nom;
int larg,haut;

{	         
if ((fichier = fopen(nom,"w"))==NULL)
		{
		perror(CP[170]);}   

fprintf(fichier,"P6\n");               
fprintf(fichier,"%d %d\n",larg,haut);    
fprintf(fichier,"255\n");
}

/*******************************************************************************************************************************/

static void saveppm2(i)
int i;		              /* sauvegarde PPM - point par point */


{
fprintf(fichier,"%c%c%c",env.palette.color[i].red,env.palette.color[i].green,env.palette.color[i].blue);   
} 


/*******************************************************************************************************************************/


static void sauver_ppm(nom,larg,haut,pt,z0,z1)
char *nom;
int larg,haut;
lcomplex pt,z0,z1;
{
FLOAT_SIZE pasx,pasy;
int i,j,iterations;
complex z;
lcomplex lz;

saveppm1(nom,larg,haut);

pasx=(z1.re-z0.re)/larg;
pasy=(z0.im-z1.im)/haut;    
cz=pt;                   
for(j=0;j<haut;j++){
	for(i=0;i<larg;i++){
		if (use_long_double) {
				lz.re=z0.re+i*pasx;
				lz.im=z0.im-j*pasy;
				iterations=calcul3(lz);}
		else {
				z.re=(double)(z0.re+i*pasx);
				z.im=(double)(z0.im-j*pasy);
				iterations=calcul2(z);}
		definir_couleur(iterations);
		saveppm2(couleur);
		}	
	}   
fclose(fichier);  
}   

/*******************************************************************************************************************************/


void anim_pt_source(nom,larg,haut,nbre,pt1,pt2,z0,z1)
char *nom;
int larg,haut,nbre;
lcomplex pt1,pt2,z0,z1;
{
int numero=0;
lcomplex pt;
char txt[LONG_MAX];
FLOAT_SIZE param;

/*Preliminaires*/
/* On veut une image proportionnelle */
if (((z1.re-z0.re)/(z0.im-z1.im))>((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(z0.im-z1.im)/2+z1.im;
	z1.im=param-(z1.re-z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	z0.im=param+(z1.re-z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	}

if (((z1.re-z0.re)/(z0.im-z1.im))<((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(z1.re-z0.re)/2+z0.re;
	z1.re=param+(z0.im-z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	z0.re=param-(z0.im-z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	}

sauv_param_anim_pt(nom,larg,haut,nbre,pt1,pt2,z0,z1);

/* Calcul des images de l'animation */

for (numero=0;numero<nbre;numero++) {
	sprintf(txt,"%s%03d.ppm",nom,numero);
	printf("Image: %s\n",txt);	 
	pt.re=pt1.re+numero*((pt2.re-pt1.re)/(FLOAT_SIZE)(nbre-1));
	pt.im=pt1.im+numero*((pt2.im-pt1.im)/(FLOAT_SIZE)(nbre-1));
	sauver_ppm(txt,larg,haut,pt,z0,z1);
	}
}

/*******************************************************************************************************************************/


static void sauver_ppm_im(nom,larg,haut,z0,z1,nbre_iter)
char *nom;
int larg,haut;
lcomplex z0,z1;
{
FLOAT_SIZE pasx,pasy;
int i,j;
int itmax,itmin,iterations;
double coef;
complex z;
lcomplex lz;

saveppm1(nom,larg,haut);

pasx=(z1.re-z0.re)/larg;
pasy=(z0.im-z1.im)/haut;  
iter=nbre_iter;  
/* Palette logarithmique ? => premier passage */
if (palettelog) {                   
	itmax=0;
	itmin=320000;
	for(j=0;j<haut;j+=8){
		for(i=0;i<larg;i+=8){
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
		printf("iterations %d %d\n",itmin,itmax);
		coef=exp(log((double)itmax/(double)(itmin+1))/(double)(255));
/*	coef=pow((double)(itmax/(itmin+1)),(double)(-255));     */
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
	
}
for(j=0;j<haut;j++){
	for(i=0;i<larg;i++){
		if (use_long_double) {
				lz.re=z0.re+i*pasx;
				lz.im=z0.im-j*pasy;
				iterations=calcul3(lz);}
		else {
				z.re=(double)(z0.re+i*pasx);
				z.im=(double)(z0.im-j*pasy);
				iterations=calcul2(z);}
		definir_couleur(iterations);
		saveppm2(couleur);
		}	
	}   
fclose(fichier);
  
}   

/*******************************************************************************************************************************/

void anim_image(nom,larg,haut,nbre,im1z0,im1z1,im2z0,im2z1,iter1,iter2)
char *nom;
int larg,haut,nbre;
lcomplex im1z0,im1z1,im2z0,im2z1;
int iter1,iter2;
{
int numero=0;
lcomplex ptz0,ptz1;
char txt[LONG_MAX];
FLOAT_SIZE param;
FLOAT_SIZE z0re,z0im,z1re,z1im;
FLOAT_SIZE z0re2,z0im2,z1re2,z1im2;
int nbre_iter;
lcomplex centre;

/*Preliminaires*/
/* On veut une image proportionnelle */
if (((im1z1.re-im1z0.re)/(im1z0.im-im1z1.im))>((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(im1z0.im-im1z1.im)/2+im1z1.im;
	im1z1.im=param-(im1z1.re-im1z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	im1z0.im=param+(im1z1.re-im1z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	}

if (((im1z1.re-im1z0.re)/(im1z0.im-im1z1.im))<((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(im1z1.re-im1z0.re)/2+im1z0.re;
	im1z1.re=param+(im1z0.im-im1z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	im1z0.re=param-(im1z0.im-im1z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	}

if (((im2z1.re-im2z0.re)/(im2z0.im-im2z1.im))>((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(im2z0.im-im2z1.im)/2+im2z1.im;
	im2z1.im=param-(im2z1.re-im2z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	im2z0.im=param+(im2z1.re-im2z0.re)*(FLOAT_SIZE)haut/(FLOAT_SIZE)larg/2.0;
	}

if (((im2z1.re-im2z0.re)/(im2z0.im-im2z1.im))<((FLOAT_SIZE)larg/(FLOAT_SIZE)haut)) {
	param=(im2z1.re-im2z0.re)/2+im2z0.re;
	im2z1.re=param+(im2z0.im-im2z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	im2z0.re=param-(im2z0.im-im2z1.im)*(FLOAT_SIZE)larg/(FLOAT_SIZE)haut/2.0;
	}

sauv_param_anim_im(nom,larg,haut,nbre,im1z0,im1z1,im2z0,im2z1,iter1,iter2);

/* zoom logarithmique */

centre.re=(im2z0.re+im2z1.re)/2;
centre.im=(im2z0.im+im2z1.im)/2;
z0re2=LFABS(centre.re-im1z0.re);
z1re2=LFABS(centre.re-im1z1.re);
z0im2=LFABS(centre.im-im1z0.im);
z1im2=LFABS(centre.im-im1z1.im);
z0re=(FLOAT_SIZE)exp(log((double)(centre.re-im2z0.re)/(double)(centre.re-im1z0.re))/(nbre-1));
z0im=(FLOAT_SIZE)exp(log((double)(centre.im-im2z0.im)/(double)(centre.im-im1z0.im))/(nbre-1));
z1re=(FLOAT_SIZE)exp(log((double)(centre.re-im2z1.re)/(double)(centre.re-im1z1.re))/(nbre-1));
z1im=(FLOAT_SIZE)exp(log((double)(centre.im-im2z1.im)/(double)(centre.im-im1z1.im))/(nbre-1));
for (numero=0;numero<nbre;numero++) {
	sprintf(txt,"%s%03d.ppm",nom,numero);
	printf("Image: %s\n",txt);
	nbre_iter=iter1+(int)((iter2-iter1)*((double)numero/(double)nbre));
	ptz0.re=centre.re-z0re2;
	ptz0.im=centre.im+z0im2;
	ptz1.re=centre.re+z1re2;
	ptz1.im=centre.im-z1im2;
	z0re2=z0re2*z0re;
	z1re2=z1re2*z1re;
	z0im2=z0im2*z0im;
	z1im2=z1im2*z1im;
	sauver_ppm_im(txt,larg,haut,ptz0,ptz1,nbre_iter);
	}
}

