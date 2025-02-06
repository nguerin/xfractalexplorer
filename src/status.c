/*
 * status.c
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

extern unsigned long wpx,bpx,mask,wpx2,bpx2;
static Widget shell_status;
static Widget drawing2;
static Pixmap pix2;
static int exist_status=FALSE;
static int status_detruit=FALSE;

#define LARGEUR_STATUS	500
#define HAUTEUR_STATUS	350


/*************************************************************************************/
void rafraichir2(w,client,appel)
Widget w;
XtPointer client; 
XmDrawingAreaCallbackStruct *appel;
{                         
	XCopyArea(XtDisplay(w),pix2,XtWindow(drawing2),env.gc,0,0,LARGEUR_STATUS,HAUTEUR_STATUS,0,0); 
} 

/*********************************************************************************************************/


void detruire_status(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{ 
if (!status_detruit) exist_status=(!exist_status);
/*printf("exist\n");*/
status_detruit=FALSE;
} 

/******************************************************************************************************************************/  

static void ecrire2(chaine,x,y)
     char *chaine;
     int x,y;
{

XDrawString(XtDisplay(env.root),XtWindow(drawing2),env.gc,x,y,chaine,strlen(chaine));
XDrawString(XtDisplay(env.root),pix2,env.gc,x,y,chaine,strlen(chaine));
}

/******************************************************************************************************************************/  


void print_status(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
int nargs;
Arg argu[20];
char chaine[200];

if (exist_status) {
	XtDestroyWidget(drawing2);
	XtDestroyWidget(shell_status);
	status_detruit=TRUE;
}
exist_status=TRUE;

shell_status=XtCreatePopupShell("Status",topLevelShellWidgetClass,env.root,NULL,0);
XtAddCallback(shell_status,XtNdestroyCallback,(XtCallbackProc)detruire_status,NULL);

nargs=0;    
XtSetArg(argu[nargs],XmNwidth,LARGEUR_STATUS); nargs++;
XtSetArg(argu[nargs],XmNheight,HAUTEUR_STATUS); nargs++; 
XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,0);nargs++;
XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
drawing2=XmCreateDrawingArea(shell_status,"Area",argu,nargs);   
XtAddCallback(drawing2,XmNexposeCallback,(XtCallbackProc)rafraichir2,NULL);
XtManageChild(drawing2);   
XtPopup(shell_status,XtGrabNone); 

pix2= XCreatePixmap(XtDisplay(env.root),
                           DefaultRootWindow(XtDisplay(env.root)),
                           LARGEUR_STATUS,HAUTEUR_STATUS, 
                           DefaultDepthOfScreen(XtScreen(env.root)));

         
/*	On nettoie	*/                    
XSetForeground(XtDisplay(env.root),env.gc,bpx2);      /* a modifier ? */
XFillRectangle(XtDisplay(env.root),XtWindow(drawing2),env.gc,0,0,LARGEUR_STATUS,HAUTEUR_STATUS);
XFillRectangle(XtDisplay(env.root),pix2,env.gc,0,0,LARGEUR_STATUS,HAUTEUR_STATUS);

/*	On ecrit	*/
XSetForeground(XtDisplay(env.root),env.gc,wpx2);
/*XSetFont(XtDisplay(env.root),env.gc,XLoadFont(XtDisplay(env.root),
	"-adobe-helvetica-bold-r-normal--*-240-*-*-*-*-*-*"));*/
ecrire2(CP[157],180,25);
/*XSetFont(XtDisplay(env.root),env.gc,XLoadFont(XtDisplay(env.root),
	"-adobe-helvetica-bold-o-normal--*-140-*-*-*-*-*-*"));*/
ecrire2(CP[158],10,45);
ecrire2(CP[159],10,80);
ecrire2(CP[160],30,100);
ecrire2(CP[161],30,120);
ecrire2(CP[162],30,140);
ecrire2(CP[163],30,160);
ecrire2(CP[164],10,190);
ecrire2(CP[165],10,220);
ecrire2(CP[166],10,240);
ecrire2(CP[186],10,270);
/*XSetFont(XtDisplay(env.root),env.gc,XLoadFont(XtDisplay(env.root),
	"-adobe-times-medium-r-normal--*-180-*-*-*-*-*-*"));
	*/
switch(genre) {
	case MANDELBROT :
		sprintf(chaine,"MANDELBROT");
		break;
	
	case JULIA :
		sprintf(chaine,"JULIA");
		break;
		
	case MANDELN :
		sprintf(chaine,"MANDEL-%d",ip);
		break;
	
	case JULIAN :
		sprintf(chaine,"JULIA-%d",ip);
		break;
		
	case MANDEL3 :
		sprintf(chaine,"MANDEL3");
		break;
		
	case NEWTON :
		sprintf(chaine,"NEWTON");
		break;  

	case JULIA3 :
		sprintf(chaine,"JULIA3");
		break;  

	case LAMBDA :
		sprintf(chaine,"LAMBDA ");
		break;
		
	case MANDELLAMBDA :
		sprintf(chaine,"MANDELLAMBDA");
		break;

	case MARKM :
		sprintf(chaine,"MARK'S MANDEL");
		break;

	case MARKJ :
		sprintf(chaine,"MARK'S JULIA");
		break;

	case SPIDER :
		sprintf(chaine,"SPIDER");
		break;
		
	case BARNM1 :
		sprintf(chaine,"BARNSLEY-MANDEL 1");
		break;
		
	case BARNJ1 :
		sprintf(chaine,"BARNSLEY-JULIA 1");
		break;
		
	case BARNM2 :
		sprintf(chaine,"BARNSLEY-MANDEL 2");
		break;
		
	case BARNJ2 :
		sprintf(chaine,"BARNSLEY-JULIA 2");
		break;
		
	case BARNM3 :
		sprintf(chaine,"BARNSLEY-MANDEL 3");
		break;
		
	case BARNJ3 :
		sprintf(chaine,"BARNSLEY-JULIA 3");
		break;
		
	case MCOS :
		sprintf(chaine,"MANDEL-COS");
		break;
		
	case JCOS :
		sprintf(chaine,"JULIA-COS");
		break;
		
	case MSIN :
		sprintf(chaine,"MANDEL-SIN");
		break;
		
	case JSIN :
		sprintf(chaine,"JULIA-SIN");
		break;
		
	case MEXP :
		sprintf(chaine,"MANDEL-EXP");
		break;
		
	case JEXP :
		sprintf(chaine,"JULIA-EXP");
		break;
		
	case NOEL1 :
		sprintf(chaine,"NOEL1");
		break;
		
	case NOEL2 :
		sprintf(chaine,"NOEL2");
		break;
		
	case PHOENIX :
		sprintf(chaine,"PHOENIX");
		break;
		
	case TETRATE :
		sprintf(chaine,"TETRATE");
		break;
		

		
	}
ecrire2(chaine,150,60);
/*XSetFont(XtDisplay(env.root),env.gc,XLoadFont(XtDisplay(env.root),
	"-adobe-helvetica-bold-r-normal--*-140-*-*-*-*-*-*"));
*/
if (use_long_double) {
	sprintf(chaine,FORMAT,z0.im); /* haut */
	ecrire2(chaine,100,100);
	sprintf(chaine,FORMAT,z1.im); /* bas */
	ecrire2(chaine,100,120);
	sprintf(chaine,FORMAT,z0.re); /* gauche */
	ecrire2(chaine,100,140);
	sprintf(chaine,FORMAT,z1.re); /* droite */
	ecrire2(chaine,100,160);
	sprintf(chaine,"%.1e",(double)(10/((z1.re-z0.re)*(z0.im-z1.im)))); /* grossissement */
	ecrire2(chaine,150,190);
	sprintf(chaine,FORMAT2,cz.re); 
	ecrire2(chaine,150,220);
	sprintf(chaine,FORMAT2,cz.im); 
	ecrire2(chaine,150,240);
} else {
	sprintf(chaine,FORMAT2,z0.im); /* haut */
	ecrire2(chaine,100,100);
	sprintf(chaine,FORMAT2,z1.im); /* bas */
	ecrire2(chaine,100,120);
	sprintf(chaine,FORMAT2,z0.re); /* gauche */
	ecrire2(chaine,100,140);
	sprintf(chaine,FORMAT2,z1.re); /* droite */
	ecrire2(chaine,100,160);
	sprintf(chaine,"%.1e",(double)(1/(z1.re-z0.re))); /* grossissement */
	ecrire2(chaine,150,190);
	sprintf(chaine,FORMAT2,cz.re); 
	ecrire2(chaine,150,220);
	sprintf(chaine,FORMAT2,cz.im); 
	ecrire2(chaine,150,240);
}


sprintf(chaine,"%d",iter); 
ecrire2(chaine,200,270);


}
