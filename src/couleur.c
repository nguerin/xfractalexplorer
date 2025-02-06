/*
 * couleur.c
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


void StoreColor(Palette *pal,int index,int red,int green,int blue) 
{

    pal->color[index].red   = red*256;
    pal->color[index].green = green*256;
    pal->color[index].blue  = blue*256;
    pal->color[index].flags=DoRed|DoGreen|DoBlue;
    if (env.depth > 8) {
        /* For Read Only visuals (e.g. True Color displays) */
        XAllocColor(XtDisplay(env.root),env.cmap,&(pal->color[index]));
    } else {
        /* For palette-based displays (i.e. 256 colors) */
        pal->color[index].pixel = index;
        XStoreColor(env.display,env.cmap,&(pal->color[index]));
    }
    pal->nbCol++;
}



int initCMAP(Palette *pal) {
    pal->nbCol=0;
    if (env.depth <= 8) {
        int ncoul;
        /* For palette-based displays (i.e. 256 colors) */
        ncoul=DisplayCells(env.display, env.screen); 
        if (ncoul > MAXCOULEURS) return -1;
        XQueryColors(env.display,env.default_palette,pal->color,ncoul);
        env.cmap=XCreateColormap(env.display,DefaultRootWindow(env.display),
                                 env.visual,AllocAll);
    } else {
        /* We suppose a read only visual */
        env.cmap=XCreateColormap(env.display,DefaultRootWindow(env.display),
                                 env.visual,AllocNone);
    }
    return 0;
}
      


/**** cette procedure charge une palette graphique ****/

void ChargePalette()
{
int                    r,g,b;
XColor                 newcolor;
FILE                    *fichierdisque;  

nbr_colors=2;

/* Store Black and White */
StoreColor(&env.palette, 0, 0, 0, 0);
StoreColor(&env.palette, 1, 255, 255, 255);

/* Opening file */

if ((fichierdisque = fopen(nompalette,"r"))==NULL)
{
   /*perror(CP[140]);*/
   ecrire(CP[140]);
   return;
} 

/* Reading data */

/* skips first line */
fgets (toto, sizeof (toto), fichierdisque);
while (fgets (toto, sizeof (toto), fichierdisque))
   {
   sscanf(toto,"%d %d %d\n",&r,&g,&b);
   StoreColor(&env.palette, nbr_colors, r, g, b);
   nbr_colors++;
   if (nbr_colors>=MAXCOULEURS) break;
   }   
fclose(fichierdisque); 

}                                                    

/**********************************************************************************/

void Cycling()
{
	static int i,j,k,l;
	long tmpxcolor;
	int spinlength=MAXCOULEURS;
	int mincolindex=0;
	int numcolors=MAXCOULEURS;
        Palette *pal = &env.palette;
spinlength=pal->nbCol-2;
numcolors=pal->nbCol-2;
mincolindex=2;
for (k=0;k<nbre_cycles;k++) {
	if (sens_cycle==1) {				
		for (j=0;j<spinlength;j++) {
			for (l=0;l<(10-vit_cycle)*100000;l++);
			tmpxcolor = pal->color[mincolindex].pixel;
			for (i=mincolindex;i<numcolors-1;i++)
				pal->color[i].pixel = pal->color[i+1].pixel;
			pal->color[numcolors-1].pixel = tmpxcolor;
			XStoreColors(env.display, env.cmap, pal->color, numcolors);
		}
	} else {
		for (j=0;j<spinlength;j++) {
			for (l=0;l<(10-vit_cycle)*100000;l++);
			tmpxcolor = pal->color[numcolors-1].pixel;
			for (i=numcolors-1;i>mincolindex;i--)
				pal->color[i].pixel = pal->color[i-1].pixel;
			pal->color[mincolindex].pixel = tmpxcolor;
			XStoreColors(XtDisplay(env.root), env.cmap, pal->color, numcolors);
		}
	}
}
	
}


/**********************************************************************************/

void initialiser_couleurs() 
{
initCMAP(&env.palette);
ChargePalette();

}

/*********************************************************************************/

