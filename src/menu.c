/*
 * menu.c
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




typedef struct _menu_struct{
   char*                  name;           /* nom du bouton */    
   int			  type;           /* type de bouton: 1=push 2=toggle on 3 toggle off */
   void                  (*func)();       /* Callback */
   XtPointer                data;         /* Donnees pour le callback */
   struct _menu_struct   *sub_menu;       /* donnees du sous-menu  */
   int                    n_sub_items;    /* nbre d'elements du sous-menu */
   char                  *sub_menu_title; /* nom du sous-menu */
 } xs_menu_struct;
                 

/*****************************************************************/



/********************************************************/

static void en_cours(w,client,appel)
Widget w;
XtPointer client,appel; 
{
/*test*/
ecrire(CP[72]);
}

/*************************************************************************************/

void About(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{ 
ecrire(CP[73]);
} 

                
/*************************************************************************************/

/*void exist(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{ 
if (!env.shell_detruit) exist_env.shell=(!exist_env.shell);
env.shell_detruit=FALSE;
} 
*/
/******************************************************************************************************************************/  




void Info(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{         
}
/******************************************************************************************************************************/  

void quittons(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
XtCloseDisplay(XtDisplay(env.root));
/*system("lcm");
system("lcm -x");  */
exit(0);
}
  
/************************************************************************************************/
/*void OKback(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{   
Display *aff;

aff=XtDisplay(env.root);
XtUnmanageChild(env.board); 
XtUnmanageChild(env.drawing); 
XtUnmanageChild(env.shell); 
XtUnmanageChild(env.root); 
XtDestroyWidget(env.root);
XtDestroyWidget(env.shell);
XtDestroyWidget(env.board);
XSync(aff,False);
XSync(aff,False);
XtCloseDisplay(XtDisplay(env.root));

calculBG();
}*/
  
/************************************************************************************************/

void annulons(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{            
XtDestroyWidget(w);
}

/******************************************************************************************************************************/  


void Quit(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                            
Arg argu[10];
int nargs;
Widget warningbox;
                                                            
nargs=0;
XtSetArg(argu[nargs],XmNmessageString,XmStringCreate(CP[192],XmSTRING_DEFAULT_CHARSET));
nargs++;
warningbox=XmCreateWarningDialog(env.root,CP[193],argu,nargs);
XtUnmanageChild(XmMessageBoxGetChild(warningbox,XmDIALOG_HELP_BUTTON));
XtAddCallback(warningbox,XmNokCallback,(XtCallbackProc)quittons,NULL);
XtAddCallback(warningbox,XmNcancelCallback,(XtCallbackProc)annulons,NULL);  
XtManageChild(warningbox);      
}

/******************************************************************************************************************************/  
void okback(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{            
XtCloseDisplay(XtDisplay(env.root));
calculBG();
}

/******************************************************************************************************************************/  



void ask_back()
{                            
Arg argu[10];
int nargs;
Widget warningbox;

XtUnmanageChild(env.drawing);
/*XtUnmanageChild(env.shell);*/
XtDestroyWidget(env.shell);
/*XtCloseDisplay(XtDisplay(env.root));*/
XSync(XtDisplay(env.root),TRUE);
                                                            
nargs=0;
XtSetArg(argu[nargs],XmNmessageString,XmStringCreate(CP[194],XmSTRING_DEFAULT_CHARSET));
nargs++;
warningbox=XmCreateWarningDialog(env.root,CP[195],argu,nargs);
XtUnmanageChild(XmMessageBoxGetChild(warningbox,XmDIALOG_HELP_BUTTON));
XtAddCallback(warningbox,XmNokCallback,(XtCallbackProc)okback,NULL);
XtAddCallback(warningbox,XmNcancelCallback,(XtCallbackProc)annulons,NULL);  
XtManageChild(warningbox);      
}

/******************************************************************************************************************************/  


/* void background(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                            
Arg argu[10];
int nargs;
Widget warningbox;
                                                            
nargs=0;
XtSetArg(argu[nargs],XmNmessageString,XmStringCreate("Etes vous sur ?",XmSTRING_DEFAULT_CHARSET));
nargs++;
warningbox=XmCreateWarningDialog(env.root,"Tache de fond",argu,nargs);
XtUnmanageChild(XmMessageBoxGetChild(warningbox,XmDIALOG_HELP_BUTTON));
XtAddCallback(warningbox,XmNokCallback,OKback,NULL);
XtAddCallback(warningbox,XmNcancelCallback,annulons,NULL);  
XtManageChild(warningbox);      
}
*/


/************************************************************************************************/

void Editer_palette(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
}
/******************************************************************************************************************************/  


void Afficher_palette(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
int i;
XColor mycolor;
pt_en_cours=0;
mycolor.flags=DoRed|DoGreen|DoBlue;

for (i=0;i<256;i++) {
      mycolor.red  =rouge[i]*256;
      mycolor.green=vert[i]*256;
      mycolor.blue =bleu[i]*256;
      XAllocColor(XtDisplay(env.root),env.cmap,&mycolor);
      XSetForeground(XtDisplay(env.root),env.gc,mycolor.pixel);
      XFillRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,2*i,0,2*i+1,100);
}
} 
/******************************************************************************************************************************/  

void Sauver_palette(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
}
/******************************************************************************************************************************/  

void Recoloriage(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
/******************************************************************************************************************************/  
}

void type_trace(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{ 
if (strcmp(client_data,"Normal")==0) {
	type_dessin=NORMAL;
	ecrire(CP[71]);   
}
if (strcmp(client_data,"Decomposition")==0) {
	type_dessin=DECOMPOSITION;    
	ecrire(CP[74]);  
}
if (strcmp(client_data,"Inversion")==0) {
	type_dessin=INVERSION;
	ecrire(CP[75]);   
}
/*if (strcmp(client_data,"Estimateur")==0) {
	type_dessin=ESTIMATEUR;
	ecrire(CP[76]);   
}*/
pt_en_cours=0;


}
/******************************************************************************************************************************/  


void option(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                             

if (strcmp(client_data,"Ev")==0)  {
	gestion_ev=!gestion_ev;    
	if (gestion_ev) {ecrire(CP[77]);}
		else {ecrire(CP[78]);}  
}
if (calcul_en_cours) return;     
if (strcmp(client_data,"Tampon")==0) {
	tampon=!tampon; 
	if (tampon){ecrire(CP[79]);}
		else{ecrire(CP[80]);}
}
if (strcmp(client_data,"Prev")==0)  { 
	pt_en_cours=0;
	if (bloc0==8)  {	bloc0=1;
			ecrire(CP[81]);}
               else {   bloc0=8;
			ecrire(CP[82]);}   
}

/*if (strcmp(client_data,"calmem")==0)  { 
	pt_en_cours=0;
	calcul_virtuel=!calcul_virtuel;
	if (calcul_virtuel)
		ecrire("Selectionnez sauvegarde PPM ou Postscript");
	else ecrire("Affichage direct");
}*/

/*if (strcmp(client_data,"Iter")==0) {
	sauviter=!sauviter;     
	pt_en_cours=0;

	if (sauviter) {ecrire("Sauvegarde d'un fichier 'iter'");}
		else {ecrire("Pas de sauvegarde du fichier 'iter'");}  
}*/
if (strcmp(client_data,"Bip")==0) {
	bipbip=!bipbip;     

	if (bipbip) {ecrire(CP[83]);}
		else {ecrire(CP[84]);}  
}
/*if (strcmp(client_data,"Init")==0) {
	initfractal=!initfractal;     

	if (initfractal) {ecrire(CP[85]);}
		else {ecrire(CP[86]);}  
}*/
if (strcmp(client_data,"Palettelog")==0) {
	pt_en_cours=0;
	palettelog=!palettelog;     
	if (palettelog) {ecrire(CP[87]);}
		else {ecrire(CP[88]);} 
	
}
if (strcmp(client_data,"Precision")==0) {
	pt_en_cours=0;
	use_long_double=!use_long_double;
	if (use_long_double) ecrire(CP[89]);
	else ecrire(CP[90]);
}
}

/******************************************************************************************************************************/  

void Zoom_in(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{        
	FILE                    *fichierdisque;  
	/*complex fz0,fz1,fcz;  */
	FLOAT_SIZE fz0re,fz0im,fz1re,fz1im,fczre,fczim;
	int fiter,fwidth,fheight,fgenre,ftype_dessin,fip;
	double fbailout;
	char fnom[256];
	char valeur[256];           
	char fnom2[256];
	char	s[512];
	FLOAT_SIZE pasx,pasy;    
	long x0,x10,y0,y10;                
	double ecart,ecartmin;
	double ratio;
	int x1=0,x2=0,y1=0,y2=0,x3,y3;                                 
	XEvent evt;
	int annuler=FALSE;   
int                     i;
int			len;
char			commande[9];
int			temp;
                                                
if (calcul_en_cours) return;    
pt_en_cours=0;

XSetForeground(XtDisplay(env.root),env.gc,wpx);     

if ((fichierdisque = fopen("FractBibli","r"))==NULL)
{
   perror(CP[146]);
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
/*	if (!strcmp(commande,"NAME    "))
		sscanf(valeur,"%s",&fnom);*/
	if (!strcmp(commande,"LEFT    "))
		sscanf(valeur,FORMAT_LECTURE,&fz0re);
	if (!strcmp(commande,"TOP     "))
		sscanf(valeur,FORMAT_LECTURE,&fz0im);
	if (!strcmp(commande,"RIGHT   "))
		sscanf(valeur,FORMAT_LECTURE,&fz1re);
	if (!strcmp(commande,"BOTTOM  "))
		sscanf(valeur,FORMAT_LECTURE,&fz1im);
	if (!strcmp(commande,"ITER    "))
		sscanf(valeur,"%d",&fiter);
	if (!strcmp(commande,"WIDTH   "))
		sscanf(valeur,"%d",&fwidth);
	if (!strcmp(commande,"HEIGHT  "))
		sscanf(valeur,"%d",&fheight);
	if (!strcmp(commande,"TYPE    "))
		{
		sscanf(valeur,"%d",&fgenre);
		if (fgenre==genre) {
			if ((fgenre==MANDELBROT)||(fgenre==SPIDER)||(fgenre==MANDELLAMBDA)||((fgenre==NEWTON)&&(fip==ip))) {
				pasx=(z1.re-z0.re)/image.width;
				pasy=(z0.im-z1.im)/image.height; 
				/*if ((fabs(fz0re-z0.re)+fabs(fz1re-z0.re)+fabs(z0.im-fz0im)+fabs(z0.im-fz1im))<10000.0*pasx) {*/
				x0=(fz0re-z0.re)/pasx;
				y0=(z0.im-fz0im)/pasy;
				x10=(fz1re-z0.re)/pasx;
				y10=(z0.im-fz1im)/pasy;     
				/*if ((abs(x0)+abs(y0)+abs(x10)+abs(y10))<10000)*/
				XSetForeground(XtDisplay(env.root),env.gc,wpx);     
				XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x0,y0,x10-x0,y10-y0);  
				XSetForeground(XtDisplay(env.root),env.gc,bpx);     
				XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x0-1,y0-1,x10-x0+2,y10-y0+2);  
                        	/*}*/
				}
			}
		}
	if (!strcmp(commande,"C1.RE   "))
		sscanf(valeur,FORMAT_LECTURE,&fczre);
	if (!strcmp(commande,"C1.IM   "))
		sscanf(valeur,FORMAT_LECTURE,&fczim);
	if (!strcmp(commande,"N1      "))
		sscanf(valeur,"%d",&fip);
		

}

                                   
fclose(fichierdisque);

/* Selection d'une image */
ratio=(double)image.width/(double)image.height;
pasx=(z1.re-z0.re)/(FLOAT_SIZE)image.width;
pasy=(z0.im-z1.im)/(FLOAT_SIZE)image.height;
ecrire(CP[91]);
/*rafraichir(env.drawing,NULL,NULL);   */
XSetFunction(XtDisplay(env.root),env.gc,GXxor);
while(1) {
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),ButtonPressMask,&evt);
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==1)&&(evt.xbutton.x>=0)&&(evt.xbutton.y>=0)){  
			x2=x1=evt.xbutton.x;
			y2=y1=evt.xbutton.y;        
			XFlush(XtDisplay(env.root));   
			break; 
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)){  
			annuler=TRUE;
			break; 
		}
	} 
} 

while(!annuler) {     
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),Button1MotionMask|ButtonPressMask,&evt);
		if (evt.type==MotionNotify) {
			x3=x2;
			y3=y2;                   
			x2=evt.xbutton.x;
			y2=evt.xbutton.y;     
			/*if ((x2-x1)>(y2-y1)*ratio) {y2=y1+(int)((x2-x1)/ratio);}
				else {x2=x1+(int)((y2-y1)*ratio);}*/
			
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1,y1,x3-x1,y3-y1);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1,y1,x2-x1,y2-y1);
			XSetForeground(XtDisplay(env.root),env.gc,bpx);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1-1,y1-1,x3-x1+2,y3-y1+2);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1-1,y1-1,x2-x1+2,y2-y1+2);
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==2)) {
    			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1,y1,x2-x1,y2-y1);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1-1,y1-1,x2-x1+2,y2-y1+2);

			break;       
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)) {
    			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1,y1,x2-x1,y2-y1);
			XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x1-1,y1-1,x2-x1+2,y2-y1+2);
			annuler=TRUE;
			break;       
		}
	XFlush(XtDisplay(env.root));   
	}                     
}
     
if (annuler) 
	{
	ecrire(CP[187]);	                        
	XSetFunction(XtDisplay(env.root),env.gc,GXcopy);
	return;
	}  

/* nouvelles valeurs */
z1.im=z0.im-pasy*y2; 
z0.im-=pasy*y1;
z0.re+=pasx*x1;
z1.re=z0.re+(z0.im-z1.im)*ratio;  
                                            
/* initialisation */   

ecartmin=100.0;


/* On lit a nouveau le fichier fractbibli */   
/* et on cherche la fractale correspondante */


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
	for (i=9;i<=len;i++)
		valeur[i-9]=s[i];
	if (!strcmp(commande,"NAME    "))
		sscanf(valeur,"%s",fnom);
	if (!strcmp(commande,"LEFT    "))
		sscanf(valeur,FORMAT_LECTURE,&fz0re);
	if (!strcmp(commande,"TOP     "))
		sscanf(valeur,FORMAT_LECTURE,&fz0im);
	if (!strcmp(commande,"RIGHT   "))
		sscanf(valeur,FORMAT_LECTURE,&fz1re);
	if (!strcmp(commande,"BOTTOM  "))
		sscanf(valeur,FORMAT_LECTURE,&fz1im);
	if (!strcmp(commande,"ITER    "))
		sscanf(valeur,"%d",&fiter);
	if (!strcmp(commande,"WIDTH   "))
		sscanf(valeur,"%d",&fwidth);
	if (!strcmp(commande,"HEIGHT  "))
		sscanf(valeur,"%d",&fheight);
	if (!strcmp(commande,"TYPE    "))
		{
		sscanf(valeur,"%d",&fgenre);
		if (fgenre==genre) {
			if ((fgenre==MANDELBROT)||(fgenre==SPIDER)||(fgenre==MANDELLAMBDA)||((fgenre==NEWTON)&&(fip==ip))) {
				ecart=fabs((double)(z0.re-fz0re))+fabs((double)(z0.im-fz0im))
					+fabs((double)(z1.re-fz1re))+fabs((double)(z1.im-fz1im));
         			/*printf("ecart %f\n",ecart); */
        			if (ecart<ecartmin) {
					strcpy(fnom2,fnom);
					ecartmin=ecart;
				}
			}
		}
	}
	if (!strcmp(commande,"DISPLAY "))
		sscanf(valeur,"%d",&ftype_dessin);
	if (!strcmp(commande,"BAILOUT "))
		sscanf(valeur,"%le",&fbailout);
	if (!strcmp(commande,"C1.RE   "))
		sscanf(valeur,FORMAT_LECTURE,&fczre);
	if (!strcmp(commande,"C1.IM   "))
		sscanf(valeur,FORMAT_LECTURE,&fczim);
	if (!strcmp(commande,"N1      "))
		sscanf(valeur,"%d",&fip);
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
		}
	}                                          


                                   
fclose(fichierdisque);
XSetFunction(XtDisplay(env.root),env.gc,GXcopy);   
ecrire(CP[93]); 
charge(fnom2);

/*XSetFunction(XtDisplay(env.root),env.gc,GXcopy);   
if (annuler) ecrire(CP[187]);*/	                        

}
/******************************************************************************************************************************/  

void Zoom_out(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
}
/******************************************************************************************************************************/  

void Taille(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                         

if (calcul_en_cours) return;     
pt_en_cours=0;

if (strcmp(client_data,"1")==0) {
	image.width=1280;
	image.height=1024;    
	resize();
	}           

if (strcmp(client_data,"2")==0) {
	image.width=640;
	image.height=512;
	resize();
	}

if (strcmp(client_data,"3")==0) {
	image.width=320;
	image.height=256;
	resize();
	}                    

if (strcmp(client_data,"4")==0) {
	image.width=960;
	image.height=768;
	resize();
	}                    
        
if (strcmp(client_data,"x2")==0) {
	if(((image.width*2)<=LARGEUR_MAX)&&((image.height*2)<=HAUTEUR_MAX)) 
		{
		image.width=image.width*2;
		image.height=image.height*2;
		resize();
		}
		else { client_data="Max";
		ecrire(CP[94]);
		}
	}                    
        
if (strcmp(client_data,"x1.5")==0) {
	if(((image.width*1.5)<=LARGEUR_MAX)&&((image.height*1.5)<=HAUTEUR_MAX))
		{
		image.width=(image.width*1.5);
		image.height=(image.height*1.5);
		resize();
		}
		else { client_data="Max";
		ecrire(CP[94]);
		}
	}                    
        
if (strcmp(client_data,"/2")==0) {
	image.width=((double)image.width/2);
	image.height=((double)image.height/2);
	resize();
	}                    
        
if (strcmp(client_data,"/1.5")==0) {
	image.width=((double)image.width/1.5);
	image.height=((double)image.height/1.5);
	resize();
	}                    

if (strcmp(client_data,"Max")==0) {
	if ((image.width/image.height)>(LARGEUR_MAX/HAUTEUR_MAX))
		{
		image.height=image.height*(LARGEUR_MAX/image.width);
		image.width=LARGEUR_MAX;
		} else {
		image.width=image.width*(HAUTEUR_MAX/image.height);
		image.height=HAUTEUR_MAX;
	}
	resize();
	}                    

        
/*sprintf(numero,"%s : %dx%d",CP[95],image.width,image.height);
   ecrire(numero);
*/

}

/**************************************************************************************************/

void Entrer()
/*Widget texte;*/
{                                                                


}                 

/**************************************************************************************************/

void clik(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                                                                
FLOAT_SIZE pasx,pasy;
XEvent evt;   
int x1,y1;                                 

ecrire(CP[96]);
pt_en_cours=0;
if (calcul_en_cours) return;                                      
pasx=(z1.re-z0.re)/(FLOAT_SIZE)image.width;
pasy=(z0.im-z1.im)/(FLOAT_SIZE)image.height;
while(1) {
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),ButtonPressMask,&evt);
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==1)&&(evt.xbutton.x>=0)&&(evt.xbutton.y>=0)){  
			x1=evt.xbutton.x;
			y1=evt.xbutton.y;        
			cz.im=z0.im-pasy*y1;
			cz.re=z0.re+pasx*x1;
			XFlush(XtDisplay(env.root));   
			break; 
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==2)){  
			XFlush(XtDisplay(env.root));   
			break; 
		}
	} 

} 
ecrire(CP[97]);
}                

/*************************************************************************************************/

void tracer_rectangle(x,y,larg,haut) /* draws rectangle whatever the sign of larg & haut */
int x,y,larg,haut;
{
if (larg<0)
	{
	larg=-larg;
	x-=larg;
	}
if (haut<0)
	{
	haut=-haut;
	y-=haut;
	}

XDrawRectangle(XtDisplay(env.root),XtWindow(env.drawing),env.gc,x,y,larg,haut);
}



/*************************************************************************************************/

void Nouvelle(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{                                                                                                        
double ratio;
int x1=0,x2=0,y1=0,y2=0,x3=0,y3=0;                                 
XEvent evt;   
FLOAT_SIZE pasx,pasy,temp;
int sortir=FALSE;

pt_en_cours=0;

if (calcul_en_cours) return;                                      
ratio=(double)image.width/(double)image.height;
pasx=(z1.re-z0.re)/(double)image.width;
pasy=(z0.im-z1.im)/(double)image.height;

XSetForeground(XtDisplay(env.root),env.gc,wpx);



if ((strcmp(client_data,"Center")==0)||(strcmp(client_data,"Corner")==0)||(strcmp(client_data,"Cornern")==0)) {    

	ecrire(CP[91]);
	rafraichir(env.drawing,NULL,NULL);
	XSetFunction(XtDisplay(env.root),env.gc,GXxor);  /* Mode XOR */

	/* acquisition du point initial */

	while(1) {
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		/*XNextEvent(XtDisplay(env.root),&ev); */
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),ButtonPressMask,&evt);
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==1)&&(evt.xbutton.x>=0)&&(evt.xbutton.y>=0)){  
			x2=x1=evt.xbutton.x;
			y2=y1=evt.xbutton.y;        
			XFlush(XtDisplay(env.root));   
			break; 
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)) {sortir=TRUE;break;}
		} 
	} 
	/* zoom coin prop */
	if ((strcmp(client_data,"Corner")==0)&&(!sortir)) {
	
	/* Displaying first rectangle */
	XSetForeground(XtDisplay(env.root),env.gc,wpx);
	tracer_rectangle(x1,y1,x2-x1,y2-y1);
	XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
	tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
	    
	while(1) {     
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),Button1MotionMask|ButtonPressMask,&evt);
		if (evt.type==MotionNotify) {
			x3=x2;
			y3=y2;                   
			x2=evt.xbutton.x;
			y2=evt.xbutton.y;     
			if ((x2-x1)>(y2-y1)*ratio) {y2=y1+(int)((x2-x1)/ratio);}
				else {x2=x1+(int)((y2-y1)*ratio);}
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			tracer_rectangle(x1,y1,x3-x1,y3-y1);
			tracer_rectangle(x1,y1,x2-x1,y2-y1);
			XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
			tracer_rectangle(x1-1,y1-1,x3-x1+2,y3-y1+2);
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==2)) {
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
    			tracer_rectangle(x1,y1,x2-x1,y2-y1);

			break;       
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)) {
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
    			tracer_rectangle(x1,y1,x2-x1,y2-y1);
			sortir=TRUE;
			break;
			}

	XFlush(XtDisplay(env.root));   
	}                     
	} 
	if (!sortir) {       
		z1.im=z0.im-pasy*y2; 
		/*z1.re=z0.re+pasx*x2;   */
		z0.im-=pasy*y1;
		z0.re+=pasx*x1;
		z1.re=z0.re+(z0.im-z1.im)*ratio;  
	        if (z0.re>z1.re) {
			temp=z0.re;
			z0.re=z1.re;
			z1.re=temp;
			}
		if (z0.im<z1.im) {
			temp=z0.im;
			z0.im=z1.im;
			z1.im=temp;
			}
		}
	}                           
	if ((strcmp(client_data,"Cornern")==0)&&(!sortir)) {    
	XSetForeground(XtDisplay(env.root),env.gc,wpx);
	tracer_rectangle(x1,y1,x2-x1,y2-y1);
	XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
	tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
	while(1) {     
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),Button1MotionMask|ButtonPressMask,&evt);
		if (evt.type==MotionNotify) {
			x3=x2;
			y3=y2;                   
			x2=evt.xbutton.x;
			y2=evt.xbutton.y;     
			/*if ((x2-x1)<(y2-y1)) {y2=y1+(x2-x1);}*/
			/*sprintf(texte,"%d %d\n",x2,y2);  
			ecrire (texte);        attention fonction     */
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			tracer_rectangle(x1,y1,x3-x1,y3-y1);
			tracer_rectangle(x1,y1,x2-x1,y2-y1);
			XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
			tracer_rectangle(x1-1,y1-1,x3-x1+2,y3-y1+2);
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==2)) {
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2); /* efface le rectangle en cours */
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
    			tracer_rectangle(x1,y1,x2-x1,y2-y1);

			break;       
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)) {
			tracer_rectangle(x1-1,y1-1,x2-x1+2,y2-y1+2);
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
    			tracer_rectangle(x1,y1,x2-x1,y2-y1);
			sortir=TRUE;
			break;
			}
	XFlush(XtDisplay(env.root));   
	}                     
	} 
/*	if (x2>x1) { */
	if (!sortir){      
		z1.im=z0.im-pasy*y2; 
		z1.re=z0.re+pasx*x2;   
		z0.im-=pasy*y1;
		z0.re+=pasx*x1;
	        if (z0.re>z1.re) {
			temp=z0.re;
			z0.re=z1.re;
			z1.re=temp;
			}
		if (z0.im<z1.im) {
			temp=z0.im;
			z0.im=z1.im;
			z1.im=temp;
			}
		if ((z0.im-z1.im)<(z1.re-z0.re)) {
/*			image.height=(int)((double)LARGEUR_DEF*(z0.im-z1.im)/(z1.re-z0.re));
			image.width=LARGEUR_DEF;
			}
			else{
			image.width=(int)((double)HAUTEUR_DEF*(z1.re-z0.re)/(z0.im-z1.im));
			image.height=HAUTEUR_DEF;
			}*/
			image.height=(int)((double)image.width*(z0.im-z1.im)/(z1.re-z0.re));}
			else
			image.width=(int)((double)image.height*(z1.re-z0.re)/(z0.im-z1.im));
/*		printf("coucou %d %d\n",image.width,image.height);*/
		XSetFunction(XtDisplay(env.root),env.gc,GXcopy);
		resize();
	}

	}
   	if ((strcmp(client_data,"Center")==0)&&(!sortir)) {    
	XSetForeground(XtDisplay(env.root),env.gc,wpx);
	tracer_rectangle(2*x1-x2,2*y1-y2,2*(x2-x1),2*(y2-y1));
	XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
	tracer_rectangle(2*x1-x2-1,2*y1-y2-1,2*(x2-x1)+2,2*(y2-y1)+2);
	while(1) {     
	if (XEventsQueued(XtDisplay(env.root),QueuedAfterReading)!=0){
		XWindowEvent(XtDisplay(env.root),XtWindow(env.drawing),Button1MotionMask|ButtonPressMask,&evt);
		if (evt.type==MotionNotify) {
			x3=x2;
			y3=y2;                   
			x2=evt.xbutton.x;
			y2=evt.xbutton.y;     
			if ((x2-x1)>(y2-y1)*ratio) {y2=y1+(int)((x2-x1)/ratio);}
				else {x2=x1+(int)((y2-y1)*ratio);}
			/*sprintf(texte,"%d %d\n",x2,y2);  
			ecrire (texte);        attention fonction     */
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			tracer_rectangle(2*x1-x3,2*y1-y3,2*(x3-x1),2*(y3-y1));
			tracer_rectangle(2*x1-x2,2*y1-y2,2*(x2-x1),2*(y2-y1));
			XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
			tracer_rectangle(2*x1-x3-1,2*y1-y3-1,2*(x3-x1)+2,2*(y3-y1)+2);
			tracer_rectangle(2*x1-x2-1,2*y1-y2-1,2*(x2-x1)+2,2*(y2-y1)+2);
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==2)) {
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			tracer_rectangle(2*x1-x2,2*y1-y2,2*(x2-x1),2*(y2-y1));
			XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
			tracer_rectangle(2*x1-x2-1,2*y1-y2-1,2*(x2-x1)+2,2*(y2-y1)+2);
			break;       
		}
		if ((evt.type==ButtonPress)&&(evt.xbutton.button==3)) {
			XSetForeground(XtDisplay(env.root),env.gc,wpx);
			tracer_rectangle(2*x1-x2,2*y1-y2,2*(x2-x1),2*(y2-y1));
			XSetForeground(XtDisplay(env.root),env.gc,nbr_colors-1);
			tracer_rectangle(2*x1-x2-1,2*y1-y2-1,2*(x2-x1)+2,2*(y2-y1)+2);
			sortir=TRUE;
			break;
			}
	XFlush(XtDisplay(env.root));   
	}                     
	}
	if (!sortir) { 
		z1.im=z0.im-pasy*y2;            
		/*z1.re=z0.re+pasx*x2;  */
		z0.im-=pasy*(2*y1-y2);
		z0.re+=pasx*(2*x1-x2);
		z1.re=z0.re+(z0.im-z1.im)*ratio;  
	        if (z0.re>z1.re) {
			temp=z0.re;
			z0.re=z1.re;
			z1.re=temp;
			}
		if (z0.im<z1.im) {
			temp=z0.im;
			z0.im=z1.im;
			z1.im=temp;
			}
		}
	}
	
	XSetFunction(XtDisplay(env.root),env.gc,GXcopy);
	if (sortir) ecrire(CP[187]);   
	/*ecrire("Il ne reste plus qu'a calculer");*/
}

if (strcmp(client_data,"Arriere2")==0) {
	ecrire(CP[98]); 
	pasx=(z1.re-z0.re)/2.0;
	pasy=(z0.im-z1.im)/2.0;
	z0.re-=pasx;
	z0.im+=pasy;
	z1.im-=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

if (strcmp(client_data,"Arriere5")==0) {   
	ecrire(CP[99]);
	pasx=(z1.re-z0.re)*2.0;
	pasy=(z0.im-z1.im)*2.0;
	z0.re-=pasx;
	z0.im+=pasy;
	z1.im-=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

if (strcmp(client_data,"Arriere20")==0) {   
	ecrire(CP[100]);
	pasx=(z1.re-z0.re)*8.5;
	pasy=(z0.im-z1.im)*8.5;
	z0.re-=pasx;
	z0.im+=pasy;
	z1.im-=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

if (strcmp(client_data,"Avant2")==0) {
	ecrire(CP[101]); 
	pasx=(z1.re-z0.re)/4.0;
	pasy=(z0.im-z1.im)/4.0;
	z0.re+=pasx;
	z0.im-=pasy;
	z1.im+=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

if (strcmp(client_data,"Avant5")==0) {   
	ecrire(CP[102]);
	pasx=(z1.re-z0.re)/2.0*(1.0-1.0/5.0);
	pasy=(z0.im-z1.im)/2.0*(1.0-1.0/5.0);
	z0.re+=pasx;
	z0.im-=pasy;
	z1.im+=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

if (strcmp(client_data,"Avant20")==0) {   
	ecrire(CP[103]);
	pasx=(z1.re-z0.re)/2.0*(1.0-1.0/20.0);
	pasy=(z0.im-z1.im)/2.0*(1.0-1.0/20.0);
	z0.re+=pasx;
	z0.im-=pasy;
	z1.im+=pasy;   
	z1.re=z0.re+(z0.im-z1.im)*ratio;  
}                          

/*rafraichir(env.drawing,NULL,NULL);   */
/*XtDispatchEvent(&ev);   */

}
/***********************************************************************/
void xs_create_menu_buttons(title, menu, menulist, nitems)
     char           *title;
     Widget          menu;
     xs_menu_struct *menulist;
     int             nitems;   
     
{  
  int nargs;
  Arg argu[20];
  Arg        wargs[1];
  int        i;
  WidgetList buttons;
  int        separators = 0;
  
   
  buttons = (WidgetList) XtMalloc(nitems * sizeof(Widget));
  
/* LessTif crashes on this...
  if(title){
printf("creating label %s and separator\n",title);
    XtVaCreateManagedWidget(title, xmLabelWidgetClass, menu,
                          NULL);
    XtVaCreateManagedWidget("separator", xmSeparatorWidgetClass,
                          menu, NULL);
  }
*/
  

  for(i=0;i<nitems;i++){
    
    if(menulist[i].name == NULL){

      XtVaCreateManagedWidget("separator",
			    xmSeparatorWidgetClass,
			    menu, NULL);
      separators++; /* Count how many entries aren't buttons */
    }
    
    else if(menulist[i].func){          
      if(menulist[i].type==1){/**/

	buttons[i-separators] = XtVaCreateManagedWidget(menulist[i].name,
					       xmPushButtonWidgetClass,
					       menu, NULL);
	XtAddCallback(buttons[i-separators], XmNactivateCallback,
		      (XtCallbackProc)menulist[i].func, menulist[i].data);  }
      if ((menulist[i].type==2)||(menulist[i].type==3)){ 
	nargs=0;
	XtSetArg(argu[nargs],XmNindicatorOn,TRUE);nargs++;
	if (menulist[i].type==2) {XtSetArg(argu[nargs],XmNset,TRUE);nargs++;}
	else  {XtSetArg(argu[nargs],XmNset,FALSE);nargs++;}
	XtSetArg(argu[nargs],XmNindicatorType,XmONE_OF_MANY);nargs++;  /**/

	buttons[i-separators] = XtCreateManagedWidget(menulist[i].name,
					       xmToggleButtonWidgetClass,
					       menu,argu,nargs);
	XtAddCallback(buttons[i-separators], XmNvalueChangedCallback,
		      menulist[i].func, menulist[i].data);  }
     
    }
    
    else if(!menulist[i].sub_menu)/**/ {

      buttons[i-separators] = XtVaCreateManagedWidget(menulist[i].name,
					     xmLabelWidgetClass,
					     menu, NULL);
    
    }else{  
      Widget sub_menu;

      sub_menu =XmCreatePulldownMenu(menu,
				     menulist[i].sub_menu_title,
				     NULL, 0);
      XtSetArg(wargs[0], XmNsubMenuId, sub_menu);

      buttons[i-separators] =/**/
	XtCreateManagedWidget(menulist[i].name,
		       xmCascadeButtonWidgetClass,
		       menu, wargs, 1);
      xs_create_menu_buttons(menulist[i].sub_menu_title,
			     sub_menu, menulist[i].sub_menu,
			     menulist[i].n_sub_items);
    }
  } 

  XtManageChildren(buttons, nitems - separators);

}

/*void quitter(w,donnees,appels)   
Widget w;
XtPointer donnees,appels;  
{
XtCloseDisplay(XtDisplay(w));
exit(0);
} */
 /*****************************************************************************************************/


void initx()
{
Widget quit,go,status; 
Widget menubar;                              
int nargs;
Arg argu[20];

/**********************/
/* Creation des menus */   
/**********************/

static xs_menu_struct sub_menu_save_postscript[] = {
  {"N&B",1,Save, "NB"},   
  {"Gris",1,Save, "Gris"},
/*  NULL,*/
};       
static xs_menu_struct sub_menu_save[] = {
  {"Image PPM (fond)",1,Save_background, "PPM"},
  {"Image GIF",1,Save, "GIF"},
  {"Postscript (fond)",1,NULL, NULL,sub_menu_save_postscript,XtNumber(sub_menu_save_postscript),"Postscript (fond)" },
  {"Parametres",1,Save, "param"},
 /* {"Iterations",1,Save, "iter"}*/
/*  NULL,*/
};  
     
/*static xs_menu_struct sub_menu_back[] = {
  {"Image PPM",1,Save_background, "PPM"},
  {"Image GIF",1,Save_background, "GIF"},
  {"Iterations",1,Save_background, "iter"},
  {"Postscript",1,Save_background, "Postcript"}
};*/  
     
static xs_menu_struct sub_menu_load[] = {
/*  {"Image PPM",1,Load, "PPM"},   */
  {"Image GIF",1,Load, "GIF"},
  {"Parametres",1,Load, "param"},
/*  NULL,*/
};       

static xs_menu_struct Menu1Data[] = { 
	{"A propos...",1,About,NULL,NULL,0,"A propos..."}, 
	{"Sauvegarde",1,NULL, NULL,sub_menu_save,XtNumber(sub_menu_save), "Sauvegarde"},
	{"Charge",1,NULL,NULL,sub_menu_load,
      		XtNumber(sub_menu_load),"Charge"}, 
/*	{"Tache de fond",1,NULL, NULL,sub_menu_back,XtNumber(sub_menu_back), NULL},*/
/*     	{"Imprime",1,en_cours,NULL,NULL,0,NULL},*/
	{"Quitter",1,Quit,NULL, NULL, 0 ,"Quitter" },
/*	NULL,*/
};


static xs_menu_struct Menu2Data[] = {
	{"Normal",1,type_trace,"Normal",NULL,0,"Normal"},
/*	{"Inversion",1,type_trace,"Inversion",NULL,0,NULL},*/
/*	{"Decomposition",1,type_trace,"Decomposition",NULL,0,NULL}, */  
	{"Estimateur (n&b)",1,change_delta,"Estimateur",NULL,0,"Estimateur (n&b)"},
/*	{"Interieur",1,type_trace,"Interieur",NULL,0,NULL}*/
/*  NULL,*/
};

#ifdef _NO_LONG_DOUBLE
static xs_menu_struct Menu3Data[] = {
/*	{"Test periodicite",2,option,"Periodicite",NULL,0,NULL},*/
	{"Palette logarithmique",2,option,"Palettelog",NULL,0,"Palette logarithmique"},   
/*	{"Calcul en memoire",2,option,"calmem",NULL,0,NULL},  */ 
	{"Calcul tampon",3,option,"Tampon",NULL,0,"Calcul tampon"}, 
	{"Gestion evenements",3,option,"Ev",NULL,0,"Gestion evenements"},  
	{"Rectangles->Pixels",3,option,"Prev",NULL,0,"Rectangles->Pixels"}, 
/*	{"Sauver fichier 'iter'",2,option,"Iter",NULL,0,NULL},*/
	{"Bip en fin de calcul",2,option,"Bip",NULL,0,"Bip en fin de calcul"}
/*	{"Grande precision",2,option,"Precision",NULL,0,NULL},*/
/*	{"Calcul en tache de fond",2,background,NULL,NULL,0,NULL}*/
/*	NULL,*/
};
#else
static xs_menu_struct Menu3Data[] = {
/*	{"Test periodicite",2,option,"Periodicite",NULL,0,NULL},*/
	{"Palette logarithmique",2,option,"Palettelog",NULL,0,"Palette logarithmique"},   
/*	{"Calcul en memoire",2,option,"calmem",NULL,0,NULL},  */ 
	{"Calcul tampon",3,option,"Tampon",NULL,0,"Calcul tampon"}, 
	{"Gestion evenements",3,option,"Ev",NULL,0,"Gestion evenements"},  
	{"Rectangles->Pixels",3,option,"Prev",NULL,0,"Rectangles->Pixels"}, 
/*	{"Sauver fichier 'iter'",2,option,"Iter",NULL,0,NULL},*/
	{"Bip en fin de calcul",2,option,"Bip",NULL,0,"Bip en fin de calcul"},
	{"Grande precision",2,option,"Precision",NULL,0,"Grande precision"},
/*	{"Calcul en tache de fond",2,background,NULL,NULL,0,NULL}*/
/*	NULL,*/
};
#endif

static xs_menu_struct Menu4Data[] = {
/*	{"Editer palette",1,Editer_palette,NULL,NULL,0,NULL}, */
	{"Charger palette",1,Charger_palette,NULL,NULL,0,"Charger palette"},
/*	{"Sauver palette",1, Sauver_palette, NULL,  NULL, 0, NULL}, */
	{"Afficher palette",1, Afficher_palette, NULL,  NULL, 0,"Afficher palette" }, 
	{"Cycler couleurs",1,nbrecycles,NULL,NULL,0,"Cycler couleurs"},
/*	NULL,*/
};

static xs_menu_struct sub_menu_taille[] = {
  {"1280 x 1024",1,Taille, "1"},
  {"960 x 768",1,Taille,"4"},
  {"640 x 512",1,Taille, "2"},
  {"320 x 256",1,Taille, "3"},
  {"Taille max.",1,Taille,"Max"},
  {"Taille x2",1,Taille,"x2"},
  {"Taille x1.5",1,Taille,"x1.5"},
  {"Taille /2",1,Taille,"/2"},
  {"Taille /1.5",1,Taille,"/1.5"},
 {"Entrer taille",1,Entrer_taille, "Enter"},
/*	NULL,*/
};  

/*static xs_menu_struct sub_menu_nbrec[] = { 
  {"1",1,point_source,"1"},
  {"2",1,point_source,"2"}
};

static xs_menu_struct sub_menu_nbree[] = { 
  {"1",1,change_ip,"1"},
  {"2",1,change_ip,"2"}
};

static xs_menu_struct sub_menu_type[] = { 
  {"Complexe",1,NULL,NULL,sub_menu_nbrec,
      		XtNumber(sub_menu_nbrec), "Numero"},
  {"Entiere ",1,NULL,NULL,sub_menu_nbree,
      		XtNumber(sub_menu_nbree), "Numero"}
};*/

static xs_menu_struct sub_menu_type[] = { 
  {"Complexe",1,point_source,"1"},
  {"Entiere ",1,change_ip,"1"},
/*	NULL,*/
};

static xs_menu_struct Menu5Data[] = {
/*	{"Recoloriage",1,Recoloriage,NULL,NULL,0,NULL}, */
	{"Constante",1,NULL,NULL,sub_menu_type,
      		XtNumber(sub_menu_type), "Type"}, 
	{"Taille image",1,NULL,NULL,sub_menu_taille,
      		XtNumber(sub_menu_taille), "Nouvelle Taille"},
	{"Cliquer constante",1,clik,NULL,NULL,0,"Cliquer constante"},
	{"Nbre d'iterations",1,change_iter, NULL,  NULL, 0, "Nbre d'iterations"}, 
	{"Taille tampon",1,taille_tampon, NULL,  NULL, 0, "Taille tampon"}, 
	{"Val. echapp.",1,chbailout, NULL,  NULL, 0,"Val. echapp." }, 
/*	{"Nbre couleurs",1,en_cours, NULL,  NULL, 0, NULL}, 
	{"Police",1,en_cours, NULL,  NULL, 0, NULL}*/
/*	NULL,*/
};

static xs_menu_struct Menu6Data[] = {
	{"Mandelbrot",1,Change_genre,"Mandelbrot",NULL,0,"Mandelbrot"}, 
	{"Julia",1,Change_genre,"Julia",NULL,0,"Julia"},
	{"Mandel-n",1,Change_genre,"Mandel-n",  NULL, 0,"Mandel-n" }, 
	{"Julia-n",1,Change_genre,"Julia-n",  NULL, 0,"Julia-n" }, 
	{"Newton",1,Change_genre,"Newton",NULL,0,"Newton"},
	{"MandelLambda",1,Change_genre,"Mandellambda",  NULL, 0,"Mandellambda" }, 
	{"Lambda",1,Change_genre,"Lambda",  NULL, 0,"Lambda" },
	{"Mark's Mandel",1,Change_genre,"Mark's Mandel",  NULL, 0,"Mark's Mandel" },
	{"Mark's Julia",1,Change_genre,"Mark's Julia",  NULL, 0,"Mark's Julia" },
	{"BarnsleyM1",1,Change_genre,"Barnsleym1",  NULL, 0,"Barnsleym1" },
	{"BarnsleyJ1",1,Change_genre,"Barnsleyj1",  NULL, 0,"Barnsleyj1" },
	{"BarnsleyM2",1,Change_genre,"Barnsleym2",  NULL, 0,"Barnsleym2" },
	{"BarnsleyJ2",1,Change_genre,"Barnsleyj2",  NULL, 0,"Barnsleyj2" },
	{"BarnsleyM3",1,Change_genre,"Barnsleym3",  NULL, 0,"Barnsleym3" },
	{"BarnsleyJ3",1,Change_genre,"Barnsleyj3",  NULL, 0,"Barnsleyj3" },
	{"MandelCos",1,Change_genre,"Mcos",  NULL, 0,"Mcos" },
	{"JuliaCos",1,Change_genre,"Jcos",  NULL, 0,"Jcos" },
	{"MandelSin",1,Change_genre,"Msin",  NULL, 0,"Msin" },
	{"JuliaSin",1,Change_genre,"Jsin",  NULL, 0,"Jsin" },
/*	{"MandelExp",1,Change_genre,"Mexp",  NULL, 0, NULL},
	{"JuliaExp",1,Change_genre,"Jexp",  NULL, 0, NULL},*/
	{"Noel1",1,Change_genre,"Noel1",  NULL, 0,"Noel1" },
	{"Noel2",1,Change_genre,"Noel2",  NULL, 0, "Noel2"},
	{"Phoenix",1,Change_genre,"Phoenix",  NULL, 0, "Phoenix"},
	{"Spider",1,Change_genre,"Spider",  NULL, 0,"Spider" },
/*	{"Tetrate",1,Change_genre,"Tetrate",  NULL, 0, NULL}*/
/*	NULL,*/
};

static xs_menu_struct Menu7Data[] = {
	{"Zoom Avant",1,Zoom_in,NULL,NULL,0,"Zoom Avant"}, 
/*	{"Zoom Arriere",1,Zoom_out,NULL,NULL,0,NULL},
	{"Enlever image",1,en_cours, NULL,  NULL, 0, NULL}, 
	{"Slide show",1,en_cours, NULL,  NULL, 0, NULL} */
/*	NULL,*/
};

static xs_menu_struct sub_menu_zoomin[] = { 
  {"x2",1,Nouvelle,"Avant2"},
  {"x5",1,Nouvelle,"Avant5"},
  {"x20",1,Nouvelle,"Avant20"},
 /* NULL,*/
};

static xs_menu_struct sub_menu_zoomout[] = { 
  {"x2",1,Nouvelle,"Arriere2"},
  {"x5",1,Nouvelle,"Arriere5"},
  {"x20",1,Nouvelle,"Arriere20"},
/*  NULL,*/
};

static xs_menu_struct sub_menu_coord[] = { 
  {"Ancienne taille",1,ch_coord,"ancienne"},
  {"Nouvelle taille",1,ch_coord,"nouvelle"},
 /* NULL,*/
};

static xs_menu_struct Menu8Data[] = {
	{"Zoom centre prop",1,Nouvelle,"Center",  NULL, 0,"Center" }, 
	{"Zoom coin prop",1,Nouvelle,"Corner",  NULL, 0,"Corner" }, 
	{"Zoom coin non p",1,Nouvelle,"Cornern",  NULL, 0, "Cornern"}, 
	{"Zoom Avant",1,NULL,NULL,sub_menu_zoomin,
      		XtNumber(sub_menu_zoomin), "Facteur"}, 
	{"Zoom Arriere",1,NULL,NULL,sub_menu_zoomout,
      		XtNumber(sub_menu_zoomout), "Facteur"}, 
	{"Entrer coord.",1,NULL,NULL,sub_menu_coord,
      		XtNumber(sub_menu_coord), "Ecran"}, 
/*	{"Affiche orbite",1,en_cours,NULL,NULL,0,NULL}*/
/*  NULL,*/
};

static xs_menu_struct sub_menu_anim_im[] = { 
  {"Param image 1",1,Animim,"param1"},
  {"Param image 2",1,Animim,"param2"},
  {"calcul",1,Animim,"calcul"},
 /* NULL,*/
};

static xs_menu_struct sub_menu_anim_pt[] = { 
  {"Current for image 1",1,Animpt,"param1"},
  {"Current for image 2",1,Animpt,"param2"},
  {"calcul",1,Animpt,"calcul"},
  {"Manual entry",1,Animpt,"manual"},
/*  NULL,*/
};

static xs_menu_struct Menu9Data[] = {
	{"Image a image",1,NULL,NULL,sub_menu_anim_im,
      		XtNumber(sub_menu_anim_im), "Zoom"}, 
	{"Pt source a pt source",1,NULL,NULL,sub_menu_anim_pt,
      		XtNumber(sub_menu_anim_pt), "Pt source"},
 /* NULL,*/
};


static xs_menu_struct PulldownData[] = {
  { "Fichier ",1, NULL,  NULL, 
    Menu1Data,XtNumber(Menu1Data) ,"Fi chier" },
  {"Affichage",1, NULL,  NULL,  
    Menu2Data, XtNumber(Menu2Data),"Affichage"}, 
  { "Options  ",1, NULL,  NULL,  
    Menu3Data, XtNumber(Menu3Data), "Options  "},
  {"Palette  ",1, NULL,  NULL,  
    Menu4Data, XtNumber(Menu4Data), "Palette  "},
  { "Parametres",1, NULL,  NULL,  
    Menu5Data, XtNumber(Menu5Data),"Parametres" },
  { "Type  ",1, NULL,  NULL,  
    Menu6Data, XtNumber(Menu6Data),"Type  " },
  { "Bibli. ",1, NULL,  NULL,  
    Menu7Data, XtNumber(Menu7Data), "Bibli. "},
  { "Calcul ",1, NULL,  NULL,  
    Menu8Data, XtNumber(Menu8Data),"Calcul " },
  { "Animation",1, NULL,  NULL,  
    Menu9Data, XtNumber(Menu9Data), "Animation"},
};

PulldownData[0].name=CP[5];
PulldownData[1].name=CP[6];
PulldownData[2].name=CP[7];
PulldownData[3].name=CP[8];
PulldownData[4].name=CP[9];
PulldownData[5].name=CP[10];
PulldownData[6].name=CP[11];
PulldownData[7].name=CP[12];
PulldownData[8].name=CP[13];

sub_menu_save_postscript[0].name=CP[14];
sub_menu_save_postscript[1].name=CP[15];

sub_menu_save[0].name=CP[17];
sub_menu_save[1].name=CP[18];
sub_menu_save[2].name=CP[19];
sub_menu_save[3].name=CP[20];

sub_menu_load[0].name=CP[21];
sub_menu_load[1].name=CP[20];

Menu1Data[0].name=CP[23];
Menu1Data[1].name=CP[24];
Menu1Data[2].name=CP[25];
Menu1Data[3].name=CP[26];

Menu2Data[0].name=CP[27];
/*Menu2Data[1].name=CP[28];*/
Menu2Data[1].name=CP[29];

Menu3Data[0].name=CP[30];
Menu3Data[1].name=CP[31];
Menu3Data[2].name=CP[32];
Menu3Data[3].name=CP[33];
/*Menu3Data[4].name=CP[34];*/
Menu3Data[4].name=CP[35];
Menu3Data[5].name=CP[36];

Menu4Data[0].name=CP[37];
Menu4Data[1].name=CP[38];
Menu4Data[2].name=CP[39];

sub_menu_type[0].name=CP[41];
sub_menu_type[1].name=CP[42];

sub_menu_taille[4].name=CP[49];
sub_menu_taille[5].name=CP[50];
sub_menu_taille[6].name=CP[51];
sub_menu_taille[7].name=CP[52];
sub_menu_taille[8].name=CP[53];
sub_menu_taille[9].name=CP[54];

Menu5Data[0].name=CP[40];
Menu5Data[1].name=CP[43];
Menu5Data[1].sub_menu_title=CP[48];
Menu5Data[2].name=CP[44];
Menu5Data[3].name=CP[45];
Menu5Data[4].name=CP[46];
Menu5Data[5].name=CP[47];

Menu7Data[0].name=CP[55];

sub_menu_coord[0].name=CP[64];
sub_menu_coord[1].name=CP[65];

Menu8Data[0].name=CP[56];
Menu8Data[1].name=CP[57];
Menu8Data[2].name=CP[58];
Menu8Data[3].name=CP[59];
Menu8Data[3].sub_menu_title=CP[62];
Menu8Data[4].name=CP[60];
Menu8Data[4].sub_menu_title=CP[62];
Menu8Data[5].name=CP[61];
Menu8Data[5].sub_menu_title=CP[63];

sub_menu_anim_im[0].name=CP[68];
sub_menu_anim_im[1].name=CP[69];
sub_menu_anim_im[2].name=CP[70];

sub_menu_anim_pt[0].name=CP[197];
sub_menu_anim_pt[1].name=CP[198];
sub_menu_anim_pt[2].name=CP[199];
sub_menu_anim_pt[3].name=CP[200];

Menu9Data[0].name=CP[66];
Menu9Data[1].name=CP[67];

/*** Creation des autres Widgets **/


nargs=0;    
/*XtSetArg(argu[nargs],XmNwidth,640); nargs++;*/
/*XtSetArg(argu[nargs],XmNheight,image.height+100); nargs++;*/    
/*XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,0);nargs++; */
env.board=XmCreateBulletinBoard(env.root,"env.board",argu,nargs);    
/*XtManageChild(env.board);*/


menubar = XmCreateMenuBar(env.board,"menubar", NULL, 0);
XtManageChild(menubar); 
xs_create_menu_buttons(NULL, menubar, PulldownData,
                         XtNumber(PulldownData));

XtManageChild(env.board);

nargs=0;
XtSetArg(argu[nargs],XmNwidth,150); nargs++;
XtSetArg(argu[nargs],XmNheight,40); nargs++;    
XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,100);nargs++;
/*quit=XmCreatePushButton(env.board,"Quitter",argu,nargs); */
quit=XtCreateWidget(CP[2],xmPushButtonGadgetClass,env.board,argu,nargs);
XtAddCallback(quit,XmNactivateCallback,(XtCallbackProc)Quit,NULL);
XtManageChild(quit);
 
nargs=0;
XtSetArg(argu[nargs],XmNwidth,240); nargs++;
XtSetArg(argu[nargs],XmNheight,40); nargs++;    
XtSetArg(argu[nargs],XmNx,400);nargs++;
XtSetArg(argu[nargs],XmNy,100);nargs++;
go=XmCreatePushButton(env.board,CP[4],argu,nargs); 
XtAddCallback(go,XmNactivateCallback,calcul,NULL);
XtManageChild(go); 

nargs=0;
XtSetArg(argu[nargs],XmNwidth,150); nargs++;
XtSetArg(argu[nargs],XmNheight,40); nargs++;    
XtSetArg(argu[nargs],XmNx,200);nargs++;
XtSetArg(argu[nargs],XmNy,100);nargs++;
status=XmCreatePushButton(env.board,CP[3],argu,nargs); 
XtAddCallback(status,XmNactivateCallback,print_status,NULL);
XtManageChild(status); 

nargs=0;    
XtSetArg(argu[nargs],XmNwidth,MESSAGE_L); nargs++;
XtSetArg(argu[nargs],XmNheight,MESSAGE_H); nargs++; 
XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,60);nargs++;
XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
env.message=XmCreateDrawingArea(env.board,"message",argu,nargs);   
XtAddCallback(env.message,XmNexposeCallback,rafraichir_mes,NULL);
XtManageChild(env.message); 

/*****************/
/* Fenetre Image */
/*****************/

/*env.shell=XtCreateApplicationShell("Fenetre",topLevelShellWidgetClass,NULL,0);
XtAddCallback(env.shell,XtNdestroyCallback,exist,NULL);*/
/*XtAddEventHandler(env.shell,DestroyWidgetMask,FALSE,detruire,NULL);*/

/* Initialisation des ressources */
/*nargs=0;    
XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,0);nargs++;
XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
env.drawing=XmCreateDrawingArea(env.shell,"env.drawing",argu,nargs);   
XtAddCallback(env.drawing,XmNexposeCallback,rafraichir,NULL);
XtManageChild(env.drawing);   */
                
/*XtAddEventHandler(env.board,ButtonPressMask,FALSE,arret_calcul,NULL);
XtAddEventHandler(env.board,ExposureMask,FALSE,rafraichir,NULL);*/
/*XtAddEventHandler(env.root,EnterWindowMask,FALSE,unmap,NULL);
XtAddEventHandler(env.root,LeaveWindowMask,FALSE,map,NULL);*/
                           
env.pixmap= XCreatePixmap(XtDisplay(env.root),
                           DefaultRootWindow(XtDisplay(env.root)),
                           image.width,image.height, 
                           DefaultDepthOfScreen(XtScreen(env.root)));
env.mes_pix= XCreatePixmap(XtDisplay(env.root),
                           DefaultRootWindow(XtDisplay(env.root)),
                           MESSAGE_L,MESSAGE_H, 
                           DefaultDepthOfScreen(XtScreen(env.root)));



/*XStoreName(XtDisplay(env.root),fractwin,"Oh! Que c'est beau!!");
XSelectInput(XtDisplay(env.root),fractwin,ButtonPressMask|ExposureMask);*//*|VisibilityChangeMask);*/    

/* Get display */
env.display= XtDisplay(env.root);
env.screen = DefaultScreen(env.display);
env.visual = DefaultVisual(env.display,env.screen);
env.depth  = DefaultDepth(env.display,env.screen);
env.default_palette=DefaultColormap(env.display,env.screen);


/* Contexte Graphique                                    */
env.gc=XCreateGC(env.display,DefaultRootWindow(env.display),0,NULL);
XtRealizeWidget(env.root);   
/*XtRealizeWidget(env.shell);  */ 

/*XSetFont(XtDisplay(env.root),env.gc,XLoadFont(XtDisplay(env.root),
	"-adobe-helvetica-bold-r-normal--*-140-*-*-*-*-*-*"));
*/

/* On efface tout dessin */
XSetForeground(XtDisplay(env.root),env.gc,bpx);
XFillRectangle(XtDisplay(env.root),env.pixmap,env.gc,0,0,image.width,image.height);  
XFillRectangle(XtDisplay(env.root),env.mes_pix,env.gc,0,0,MESSAGE_L,MESSAGE_H);  

}
/**********************************************************************************/

