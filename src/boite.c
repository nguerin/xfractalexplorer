/*
 * boite.c
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

static Widget bouton,texte;                                                                                       

typedef struct Double{
	Widget w1;
	Widget w2;
}  DoubleWidget;

typedef struct Triple{
	Widget w1;
	Widget w2;
	Widget w3;
}  TripleWidget;

typedef struct parametre_image{
	lcomplex z0;
	lcomplex z1;
}im_param;

static DoubleWidget texte2;
static TripleWidget texte3;

static lcomplex pt1,pt2;
static int nbre_anim=1;
static int iter1,iter2;

static im_param param1,param2;
static int type_anim;
extern void nbrecycles2();
extern void Changertaille();
extern void point_source2();
extern void ch_coord3();
extern void ch_coord2();
extern void change_iter2();
extern void change_delta2();
extern void change_ip2();
extern void taille_tampon2();
extern void chbailout2();
extern void nom_anim();
extern void nbre_images();
extern void Changertailleanim();
extern void point_sourceb();
extern void point_sourcea();
extern void Changertailleanim();


/*************************************************************************************************************************/

void entrer_1_valeur(titre,texte1,vtxt1)
char *titre;
char *texte1;                                
char *vtxt1;   
{             
	Arg args[15];
	Widget tmp,dialog_board; 
	int height=90;
	int width=220;
	int swidth=90;   

                
  XtSetArg(args[0],XmNdialogTitle,XmStringCreateLtoR(titre,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNheight,height);                        
  XtSetArg(args[2],XmNmaxHeight,height);                        
  XtSetArg(args[3],XmNminHeight,height);                        

  XtSetArg(args[4],XmNwidth,width);                        
  XtSetArg(args[5],XmNmaxWidth,width);                        
  XtSetArg(args[6],XmNminWidth,width); 
  dialog_board=XmCreateBulletinBoardDialog(env.board,"dialogue",args,6); 
 
  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,0);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte=XtCreateWidget("Saisie1",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte,vtxt1);
  XtManageChild(texte); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR("OK",XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,50);                        
  XtSetArg(args[3],XmNwidth,100);                        
  XtSetArg(args[4],XmNheight,40);                        
  bouton=XtCreateWidget("Bouton1",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(bouton);
/*  XtAddCallback(tmp,XmNactivateCallback,Changertaille,texte);*/

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(CP[119],XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,130);                        
  XtSetArg(args[2],XmNy,50);                        
  XtSetArg(args[3],XmNwidth,80);                        
  XtSetArg(args[4],XmNheight,40);                        
  tmp=XtCreateWidget("Bouton2",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(tmp);                                             

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(texte1,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,15);                        
  tmp=XtCreateWidget("Texte1",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 


XtManageChild(dialog_board);  

}
/*************************************************************************************************************************/

void entrer_2_valeur(titre,text1,text2,vtxt1,vtxt2)
char *titre;
char *text1,*text2;                                       
char *vtxt1,*vtxt2;
 
{             
	Arg args[15];
	Widget tmp,dialog_board;    
	int height=150;
	int width=330;
	int swidth=180;   

                
  XtSetArg(args[0],XmNdialogTitle,XmStringCreateLtoR(titre,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNheight,height);                        
  XtSetArg(args[2],XmNmaxHeight,height);                        
  XtSetArg(args[3],XmNminHeight,height);                        

  XtSetArg(args[4],XmNwidth,width);                        
  XtSetArg(args[5],XmNmaxWidth,width);                        
  XtSetArg(args[6],XmNminWidth,width);                        
  dialog_board=XmCreateBulletinBoardDialog(env.board,"dialogue",args,6); 
 
  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,0);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte2.w1=XtCreateWidget("Saisie1",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte2.w1,vtxt1);
  XtManageChild(texte2.w1); 

  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,50);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte2.w2=XtCreateWidget("Saisie2",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte2.w2,vtxt2);
  XtManageChild(texte2.w2); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR("OK",XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,50);                        
  XtSetArg(args[2],XmNy,100);                        
  XtSetArg(args[3],XmNwidth,80);                        
  XtSetArg(args[4],XmNheight,40);                        
  bouton=XtCreateWidget("Bouton1",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(bouton);

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(CP[119],XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,200);                        
  XtSetArg(args[2],XmNy,100);                        
  XtSetArg(args[3],XmNwidth,80);                        
  XtSetArg(args[4],XmNheight,40);                        
  tmp=XtCreateWidget("Bouton2",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(tmp);                                             

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(text1,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,15);                        
  tmp=XtCreateWidget("Texte1",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(text2,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,60);                        
  tmp=XtCreateWidget("Texte2",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 


XtManageChild(dialog_board);  

}
 
/**************************************************************************************/

void entrer_3_valeur(titre,text1,text2,text3,vtxt1,vtxt2,vtxt3)
char *titre;
char *text1,*text2,*text3;                                       
char *vtxt1,*vtxt2,*vtxt3;
 
{             
	Arg args[15];
	Widget tmp,dialog_board;    
	int height=200;
	int width=330;
	int swidth=180;   

                
  XtSetArg(args[0],XmNdialogTitle,XmStringCreateLtoR(titre,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNheight,height);                        
  XtSetArg(args[2],XmNmaxHeight,height);                        
  XtSetArg(args[3],XmNminHeight,height);                        

  XtSetArg(args[4],XmNwidth,width);                        
  XtSetArg(args[5],XmNmaxWidth,width);                        
  XtSetArg(args[6],XmNminWidth,width);                        
  dialog_board=XmCreateBulletinBoardDialog(env.board,"dialogue",args,6); 
 
  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,0);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte3.w1=XtCreateWidget("Saisie1",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte3.w1,vtxt1);
  XtManageChild(texte3.w1); 

  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,50);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte3.w2=XtCreateWidget("Saisie2",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte3.w2,vtxt2);
  XtManageChild(texte3.w2); 

  XtSetArg(args[0],XmNx,120);                        
  XtSetArg(args[1],XmNy,100);                        
  XtSetArg(args[2],XmNwidth,swidth);                        
  texte3.w3=XtCreateWidget("Saisie3",xmTextWidgetClass,dialog_board,args,3);
  XmTextSetString(texte3.w3,vtxt3);
  XtManageChild(texte3.w3); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR("OK",XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,50);                        
  XtSetArg(args[2],XmNy,150);                        
  XtSetArg(args[3],XmNwidth,80);                        
  XtSetArg(args[4],XmNheight,40);                        
  bouton=XtCreateWidget("Bouton1",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(bouton);

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(CP[119],XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,200);                        
  XtSetArg(args[2],XmNy,150);                        
  XtSetArg(args[3],XmNwidth,80);                        
  XtSetArg(args[4],XmNheight,40);                        
  tmp=XtCreateWidget("Bouton2",xmPushButtonWidgetClass,dialog_board,args,4);
  XtManageChild(tmp);                                             

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(text1,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,15);                        
  tmp=XtCreateWidget("Texte1",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(text2,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,60);                        
  tmp=XtCreateWidget("Texte2",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 

  XtSetArg(args[0],XmNlabelString,XmStringCreateLtoR(text3,XmSTRING_DEFAULT_CHARSET));                        
  XtSetArg(args[1],XmNx,0);                        
  XtSetArg(args[2],XmNy,105);                        
  tmp=XtCreateWidget("Texte3",xmLabelWidgetClass,dialog_board,args,3);     
  XtManageChild(tmp); 


XtManageChild(dialog_board);  

}
 
/**************************************************************************************/
             

void nbrecycles2(w, client_data, call_data)
     Widget   w;
     TripleWidget    *client_data;
     XmAnyCallbackStruct  *call_data;
{       

sscanf(XmTextGetString(client_data->w1),"%d",&nbre_cycles);
sscanf(XmTextGetString(client_data->w2),"%d",&sens_cycle); 
sscanf(XmTextGetString(client_data->w3),"%d",&vit_cycle); 
Cycling();
}

  
/**************************************************************************************/
             
void nbrecycles(w, client_data, call_data)
     Widget   w;
     char *client_data;
     XtPointer  call_data;
{
	char text1[10],text2[10],text3[10];
                                 
ecrire(CP[106]);
sprintf(text1,"%d",nbre_cycles);
sprintf(text2,"%d",sens_cycle);
sprintf(text3,"%d",vit_cycle);
entrer_3_valeur(CP[120],CP[121],CP[122],CP[196],text1,text2,text3); 
XtAddCallback(bouton,XmNactivateCallback,nbrecycles2,&texte3);   
 
}
/*************************************************************************************************/

void Changertaille(w, client_data, call_data)
     Widget   w;
/*     Widget    client_data;*/
     DoubleWidget    *client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data->w1),"%d",&image.width);
sscanf(XmTextGetString(client_data->w2),"%d",&image.height); 
resize();           
pt_en_cours=0;
/*ecrire("Nouvelle taille");*/
}

  
/**************************************************************************************/
             
void Entrer_taille(w, client_data, call_data)
     Widget   w;
     char *client_data;
     XtPointer  call_data;
{
	char text1[10],text2[10];
                                 
ecrire(CP[104]);
sprintf(text1,"%d",image.width);
sprintf(text2,"%d",image.height);
entrer_2_valeur(CP[105],CP[113],CP[114],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,Changertaille,&texte2);   
 
}
/*************************************************************************************************/

void point_source2(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{                            
FLOAT_SIZE x,y;

sscanf(XmTextGetString(client_data->w1),"%Le",&x);
sscanf(XmTextGetString(client_data->w2),"%Le",&y);

cz.re=x;
cz.im=y;
pt_en_cours=0;
}
  
/**************************************************************************************/
             
void point_source(w, client_data, call_data)
     Widget   w;
     char *client_data;
     XtPointer  call_data;
{
	char text1[20],text2[20];

pt_en_cours=0;                    
ecrire(CP[107]);
sprintf(text1,"%Le",cz.re);
sprintf(text2,"%Le",cz.im);
entrer_2_valeur(CP[123],CP[124],CP[125],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,point_source2,&texte2);   
 
}            
/**************************************************************************************/
void ch_coord3(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{                            

FLOAT_SIZE x,y;

sscanf(XmTextGetString(client_data->w1),FORMAT_LECTURE,&x);
sscanf(XmTextGetString(client_data->w2),FORMAT_LECTURE,&y);

z1.re=x;
z1.im=y;
pt_en_cours=0;
}

/*************************************************************************************************/

void ch_coord2(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{                            
FLOAT_SIZE x,y;
char text1[20],text2[20];

sscanf(XmTextGetString(client_data->w1),FORMAT_LECTURE,&x);
sscanf(XmTextGetString(client_data->w2),FORMAT_LECTURE,&y);

z0.re=x;
z0.im=y;  

ecrire(CP[108]);
sprintf(text1,FORMAT,z1.re);
sprintf(text2,FORMAT,z1.im);
entrer_2_valeur(CP[126],CP[124],CP[125],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,ch_coord3,&texte2);   
 

}
  
  
/**************************************************************************************/
             
void ch_coord(w, client_data, call_data)
     Widget   w;
     char *client_data;
     XtPointer  call_data;
{
	char text1[20],text2[20];
                    
pt_en_cours=0;                    
ecrire(CP[109]);
sprintf(text1,"%.10Le",z0.re);
sprintf(text2,"%.10Le",z0.im);
entrer_2_valeur(CP[127],CP[124],CP[125],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,ch_coord2,&texte2);   


 
}

/****************************************************************************************/

void change_iter2(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data),"%d",&iter);             
ecrire(CP[110]);
}
   
/****************************************************************************************/

void change_iter()
{     
	char text1[10];

pt_en_cours=0;                    
sprintf(text1,"%d",iter);
entrer_1_valeur(CP[128],CP[121],text1); 
XtAddCallback(bouton,XmNactivateCallback,change_iter2,texte);   
}

/***************************************************************************************************/
void change_delta2(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data),"%le",&render.delta); 
/*sprintf(nompalette,"%s/bw.env.cmap",PALETTE_DIR);
ChargePalette(); */
           
}
   
/****************************************************************************************/

void change_delta()
{     
	char text1[10];

pt_en_cours=0;                    
type_dessin=ESTIMATEUR;
ecrire(CP[111]);   
sprintf(text1,"%1.1e",render.delta);
entrer_1_valeur(CP[129],CP[130],text1); 
XtAddCallback(bouton,XmNactivateCallback,change_delta2,texte);   
}

/***************************************************************************************************/
void change_ip2(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data),"%d",&ip);
}
   
/****************************************************************************************/

void change_ip()
{     
	char text1[10];

pt_en_cours=0;                    
sprintf(text1,"%d",ip);
entrer_1_valeur(CP[131],CP[132],text1); 
XtAddCallback(bouton,XmNactivateCallback,change_ip2,texte);   
}

/***************************************************************************************************/
void taille_tampon2(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data),"%d",&maxpts);
}
   
/****************************************************************************************/

void taille_tampon()
{     
	char text1[10];
                        
ecrire(CP[112]);
sprintf(text1,"%d",maxpts);
entrer_1_valeur(CP[133],CP[134],text1); 
XtAddCallback(bouton,XmNactivateCallback,taille_tampon2,texte);   
}

/***************************************************************************************************/

void chbailout2(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       

sscanf(XmTextGetString(client_data),"%le",&bailout);
}
   
/****************************************************************************************/

void chbailout()
{     
	char text1[10];
                        
pt_en_cours=0;                    
sprintf(text1,"%f",bailout);
entrer_1_valeur(CP[135],CP[136],text1); 
XtAddCallback(bouton,XmNactivateCallback,chbailout2,texte);   
}

/***************************************************************************************************/

void nom_anim(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       
char toto[100];

sscanf(XmTextGetString(client_data),"%s",toto);
if (type_anim==1) anim_pt_source(toto,image.width,image.height,nbre_anim,pt1,pt2,z0,z1);
if (type_anim==0) anim_image(toto,image.width,image.height,nbre_anim,param1.z0,param1.z1,param2.z0,param2.z1,iter1,iter2);

}


/***************************************************************************************************/

void nbre_images(w, client_data, call_data)
     Widget   w;
     Widget    client_data;
     XtPointer  call_data;
{       
char *toto=ANIM_DEF;

sscanf(XmTextGetString(client_data),"%d",&nbre_anim);
entrer_1_valeur(CP[137],CP[138],toto); 
XtAddCallback(bouton,XmNactivateCallback,nom_anim,texte);   

}
   
/*************************************************************************************************/

void Changertailleanim(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{       
int larg,haut;
int nargs;
Arg argu[20];
char toto[100];

sscanf(XmTextGetString(client_data->w1),"%d",&larg);
sscanf(XmTextGetString(client_data->w2),"%d",&haut);
image.width=larg;
image.height=haut; 
              
/* Le chargement d'image ne marche qu'avec des tailles + larges que hautes */
/*if (fmod(image.width,2.0)==0.5) image.width++; 
if (fmod(image.height,2.0)==0.5) image.height++;*/
/*if (((image.width/2)*2)!=image.width) image.width++;
if (((image.height/2)*2)!=image.height) image.height++;
printf("%d %d %f %f\n",image.width,image.height,fmod(image.width,2.0),fmod(image.height,2.0));*/
/*if (image.width<image.height) {
	ecrire("la fenetre doit etre plus large que haute");
	return;
	}*/

XtDestroyWidget(env.drawing);
XtDestroyWidget(env.shell);

/*****************/
/* Fenetre Image */
/*****************/

nargs=0;    
XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
env.shell=XtCreateApplicationShell("Fenetre",topLevelShellWidgetClass,argu,nargs);


/* Initialisation des ressources */
nargs=0;    
XtSetArg(argu[nargs],XmNwidth,image.width); nargs++;
XtSetArg(argu[nargs],XmNheight,image.height); nargs++; 
XtSetArg(argu[nargs],XmNx,0);nargs++;
XtSetArg(argu[nargs],XmNy,0);nargs++;
XtSetArg(argu[nargs],XmNmarginHeight,0);nargs++;
XtSetArg(argu[nargs],XmNmarginWidth,0);nargs++;
env.drawing=XmCreateDrawingArea(env.shell,"env.drawing",argu,nargs);   
XtAddCallback(env.drawing,XmNexposeCallback,rafraichir,NULL);

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
/* Nombre d'images */
sprintf(toto,"%d",nbre_anim);
entrer_1_valeur(CP[139],CP[121],toto); 
XtAddCallback(bouton,XmNactivateCallback,nbre_images,texte);   
}  
  
  
/*************************************************************************************************/

void point_sourceb(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{                            
FLOAT_SIZE x,y;
char text1[20],text2[20];

sscanf(XmTextGetString(client_data->w1),FORMAT_LECTURE,&x);
sscanf(XmTextGetString(client_data->w2),FORMAT_LECTURE,&y);

pt2.re=x;
pt2.im=y;
ecrire(CP[104]);
sprintf(text1,"%d",image.width);
sprintf(text2,"%d",image.height);
entrer_2_valeur(CP[105],CP[113],CP[114],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,Changertailleanim,&texte2);   
}
/*************************************************************************************************/

void point_sourcea(w, client_data, call_data)
     Widget   w;
     DoubleWidget    *client_data;
     XtPointer  call_data;
{                            
char text1[20],text2[20];
FLOAT_SIZE x,y;

sscanf(XmTextGetString(client_data->w1),FORMAT_LECTURE,&x);
sscanf(XmTextGetString(client_data->w2),FORMAT_LECTURE,&y);

pt1.re=x;
pt1.im=y;
ecrire(CP[115]);
sprintf(text1,FORMAT,cz.re);
sprintf(text2,FORMAT,cz.im);

entrer_2_valeur(CP[123],CP[124],CP[125],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,point_sourceb,&texte2);   
}
  
/*****************************************************************************/
             
void Animpt(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
char text1[20],text2[20];

if (strcmp(client_data,"param1")==0) {   
	pt1.re=cz.re;
	pt1.im=cz.im;
}
if (strcmp(client_data,"param2")==0) {   
	pt2.re=cz.re;
	pt2.im=cz.im;
}
if (strcmp(client_data,"calcul")==0) {   
  ecrire(CP[104]);
  type_anim=1;                  
  sprintf(text1,"%d",image.width);
  sprintf(text2,"%d",image.height);
  entrer_2_valeur(CP[105],CP[113],CP[114],text1,text2); 
  XtAddCallback(bouton,XmNactivateCallback,Changertailleanim,&texte2);   

}

if (strcmp(client_data,"manual")==0) {   
  /* Entree manuelle */

  pt_en_cours=0;  
  type_anim=1;                  
  ecrire(CP[116]);
  sprintf(text1,FORMAT,cz.re);
  sprintf(text2,FORMAT,cz.im);

  entrer_2_valeur(CP[123],CP[124],CP[125],text1,text2); 
  XtAddCallback(bouton,XmNactivateCallback,point_sourcea,&texte2);   
}
}            

/*****************************************************************************/  

void Animim(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{            
char text1[20],text2[20];

if (strcmp(client_data,"param1")==0) {   
	param1.z0=z0;
	param1.z1=z1;
	iter1=iter;
	ecrire(CP[117]);
}
if (strcmp(client_data,"param2")==0) {   
	param2.z0=z0;
	param2.z1=z1;
	iter2=iter;
	ecrire(CP[118]);
}
if (strcmp(client_data,"calcul")==0) {   
ecrire(CP[104]);
type_anim=0;                  
sprintf(text1,"%d",image.width);
sprintf(text2,"%d",image.height);
entrer_2_valeur(CP[105],CP[113],CP[114],text1,text2); 
XtAddCallback(bouton,XmNactivateCallback,Changertailleanim,&texte2);   

}

}
