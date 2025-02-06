/*
 * fichier.c
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
 


XImage *image_gif;   


	                
/*******************************************************************************************************************************/

void charge(nom_image)
char *nom_image;
{       
                                                
if (calcul_en_cours) return;     
pt_en_cours=0;


/* On charge d'abord les parametres  */

if (!lire_bibli(nom_image)) ecrire(CP[141]);

/* Puis l'image */
load_gif(nom_image);
}

/*****************************************************************************/

void load_gif(fnom)
char *fnom;
{
	coordonnees benny;  

ReadGIF(fnom,XtDisplay(env.drawing),XDefaultScreen(XtDisplay(env.drawing)),&benny);
image.width=benny.x;
image.height=benny.y;
resize();
XPutImage(XtDisplay(env.root),env.pixmap,env.gc,image_gif,0,0,0,0,benny.x,benny.y);
XPutImage(XtDisplay(env.root),XtWindow(env.drawing),env.gc,image_gif,0,0,0,0,benny.x,benny.y);
/*printf("%d %d\n",benny.x,benny.y);  */
} 
	
/************************************************************************************************/

void OKOuvrir_param(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;
        char nom[256];

XtDestroyWidget(w);
fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);  
/*strcpy(nom,fichier_choisi);  */
sprintf(nom,"%s.par",fichier_choisi); 
sauvparam(nom);
}          

/************************************************************************************************/

void OKOuvrir_PPM(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
strcpy(nomPPM,fichier_choisi);   
sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sauvPPM=TRUE;
XtDestroyWidget(w);
}                         
/************************************************************************************************/

void OKOuvrir_Postscript(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
strcpy(nomPostscript,fichier_choisi);   
sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sauvPostscript=TRUE;
XtDestroyWidget(w);
calcul();
}                         
/************************************************************************************************/

void OKOuvrir_GIF(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;	
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
XtDestroyWidget(w);
ecrire(CP[143]);
XSync(XtDisplay(env.root),1);

/* obtenir le nom seul (ex: mandel50) */
strcpy(nomGIF,fichier_choisi);   
sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sprintf(nom,"%s.gif",fichier_choisi);      
strcpy(nomGIF,nom);
sauvGIF=TRUE;
SaveGIF(nom,env.pixmap,image.width,image.height,rouge,vert,bleu);
/*ecrire_bibli(nomGIF);*/
ecrire(CP[144]);
}                         
/************************************************************************************************/

void OKChargePalette(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{                    
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
XtDestroyWidget(w);
strcpy(nompalette,fichier_choisi);
ChargePalette();  
}

/************************************************************************************************/

void OKCharge(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{        
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
/*printf("%s\n",fichier_choisi);*/
XtDestroyWidget(w);      
charge(fichier_choisi);  
}
/************************************************************************************************/

void OKCharge_param(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;
{        
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
/*printf("%s\n",fichier_choisi);*/
XtDestroyWidget(w);      
load_param(fichier_choisi);   /* Dans xfe.c */
resize();
}

/************************************************************************************************/

void AnnulerOuvrir(w, client_data,appel)
     Widget   w;
     XtPointer client_data;
     XtPointer appel;
{
XtDestroyWidget(w);                    
}

/******************************************************************************************************************************/  

void Save(w,texte,appel)
     Widget   w;
     char    *texte;
     XtPointer  appel;
{                    
	Arg args[15];
	Widget dial_file=NULL;  

if (calcul_en_cours) return;     
pt_en_cours=0;

if (strcmp(texte,"NB")==0) type_postscript=NOIR;
if (strcmp(texte,"Gris")==0) type_postscript=GRIS;
                       
XtSetArg(args[0],XmNapplyLabelString,XmStringCreateLtoR(CP[147],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[1],XmNcancelLabelString,XmStringCreateLtoR(CP[148],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[2],XmNdialogTitle,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[3],XmNdirListLabelString,XmStringCreateLtoR(CP[150],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[4],XmNfilterLabelString,XmStringCreateLtoR(CP[151],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[5],XmNlistLabelString,XmStringCreateLtoR(CP[152],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[6],XmNokLabelString,XmStringCreateLtoR(CP[191],XmSTRING_DEFAULT_CHARSET)); 
                       
if (strcmp(texte,"param")==0) {
		sprintf(toto,"%s/*.par",PARAM_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));    
		dial_file=XmCreateFileSelectionDialog(env.board,CP[153],args,8);                                      
                }
if (strcmp(texte,"PPM")==0) {                   
		sprintf(toto,"%s/*",IMAGE_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[154],args,8);                           
        	}
if (strcmp(texte,"GIF")==0) {                   
		sprintf(toto,"%s/*",IMAGE_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[155],args,8);                            
        	}
if ((strcmp(texte,"NB")==0)||(strcmp(texte,"Gris")==0)) {                   
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR("*",XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[156],args,8);                            
        	}
XtUnmanageChild(XmFileSelectionBoxGetChild(dial_file,XmDIALOG_HELP_BUTTON));
XtAddCallback(dial_file,XmNcancelCallback,AnnulerOuvrir,NULL);
/*if ((strcmp(texte,"PPM")==0)||(strcmp(texte,"GIF")==0)) {XtAddCallback(dial_file,XmNokCallback,OKOuvrir_PPM,NULL);}
if (strcmp(texte,"param")==0) {XtAddCallback(dial_file,XmNokCallback,OKOuvrir_param,NULL);}
if (strcmp(texte,"GIF")==0) sauvGIF=TRUE;*/
if (strcmp(texte,"PPM")==0)   XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKOuvrir_PPM,NULL);
if (strcmp(texte,"param")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKOuvrir_param,NULL);
if (strcmp(texte,"GIF")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKOuvrir_GIF,NULL);
if ((strcmp(texte,"NB")==0)||(strcmp(texte,"Gris")==0)) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKOuvrir_Postscript,NULL);
XtManageChild(dial_file); 

}
/******************************************************************************************************************************/  

void Load(w, texte, call_data)
     Widget   w;
     char    *texte;
     XtPointer  call_data;
{
	Arg args[15];
	Widget dial_file=NULL;  

if (calcul_en_cours) return;     
pt_en_cours=0;
                        

XtSetArg(args[0],XmNapplyLabelString,XmStringCreateLtoR(CP[147],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[1],XmNcancelLabelString,XmStringCreateLtoR(CP[148],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[2],XmNdialogTitle,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[3],XmNdirListLabelString,XmStringCreateLtoR(CP[150],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[4],XmNfilterLabelString,XmStringCreateLtoR(CP[151],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[5],XmNlistLabelString,XmStringCreateLtoR(CP[152],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[6],XmNokLabelString,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
if (strcmp(texte,"param")==0) {
		sprintf(toto,"%s/*.par",PARAM_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));    
		dial_file=XmCreateFileSelectionDialog(env.board,CP[153],args,8);                                      
                }
if (strcmp(texte,"GIF")==0) {                   
		sprintf(toto,"%s/*.gif",IMAGE_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[155],args,8);                            
        	}
XtUnmanageChild(XmFileSelectionBoxGetChild(dial_file,XmDIALOG_HELP_BUTTON));
XtAddCallback(dial_file,XmNcancelCallback,AnnulerOuvrir,NULL);
if (strcmp(texte,"param")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKCharge_param,NULL);
if (strcmp(texte,"GIF")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKCharge,NULL);
XtManageChild(dial_file); 


} 
/******************************************************************************************************************************/  

void Charger_palette(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{
	Arg args[15];
	Widget dial_file=NULL;  

if (calcul_en_cours) return;     
                        

XtSetArg(args[0],XmNapplyLabelString,XmStringCreateLtoR(CP[147],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[1],XmNcancelLabelString,XmStringCreateLtoR(CP[148],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[2],XmNdialogTitle,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[3],XmNdirListLabelString,XmStringCreateLtoR(CP[150],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[4],XmNfilterLabelString,XmStringCreateLtoR(CP[151],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[5],XmNlistLabelString,XmStringCreateLtoR(CP[152],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[6],XmNokLabelString,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
sprintf(toto,"%s/*",PALETTE_DIR);
XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));    
dial_file=XmCreateFileSelectionDialog(env.board,CP[149],args,8);
XtUnmanageChild(XmFileSelectionBoxGetChild(dial_file,XmDIALOG_HELP_BUTTON));
XtAddCallback(dial_file,XmNcancelCallback,AnnulerOuvrir,NULL);  

XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKChargePalette,NULL);

XtManageChild(dial_file); 


} 

/************************************************************************************************/

void OKBack_GIF(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;	
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
XtDestroyWidget(w);
ecrire(CP[145]);


sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sprintf(nom,"%s.gif",fichier_choisi);      
strcpy(nomGIF,nom);
sauvGIF=TRUE;
tache_de_fond=TRUE;
gestion_ev=FALSE;
XtDestroyWidget(env.root);
XtCloseDisplay(XtDisplay(env.root));
XSync(XtDisplay(env.root),TRUE);
calcul();
/* On detruit ce qu'on peut */

/*XtCloseDisplay(XtDisplay(env.root));
XSync(XtDisplay(env.root),TRUE);
XtDestroyWidget(env.root);*/
SaveGIF(nom,env.pixmap,image.width,image.height,rouge,vert,bleu);
/*ecrire_bibli(nomGIF);*/

}      

/************************************************************************************************/

void OKBack_PPM(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;	
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
XtDestroyWidget(w);
ecrire(CP[145]);


sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sprintf(nom,"%s.ppm",fichier_choisi);      
strcpy(nomPPM,nom);
sauvPPM=TRUE;
tache_de_fond=TRUE;
gestion_ev=FALSE;
ask_back();

}      

/************************************************************************************************/

void OKBack_Postscript(w, client_data,appel)
     Widget   w;
     char    *client_data;
     XtPointer  appel;	
{            
	char nom[256];
	char *fichier_choisi;                    
	XmFileSelectionBoxCallbackStruct *fcb=(XmFileSelectionBoxCallbackStruct *)appel;

fichier_choisi=XtMalloc(256);
XmStringGetLtoR(fcb->value,XmSTRING_DEFAULT_CHARSET,&fichier_choisi);
XtDestroyWidget(w);
ecrire(CP[145]);


sprintf(nom,"%s.par",fichier_choisi);      
sauvparam(nom);          
sprintf(nom,"%s.ps",fichier_choisi);      
strcpy(nomPostscript,nom);
sauvPostscript=TRUE;
tache_de_fond=TRUE;
gestion_ev=FALSE;
ask_back();

}      


/******************************************************************************************************************************/  

void Save_background(w,texte,appel)
     Widget   w;
     char    *texte;
     XtPointer  appel;
{                    
	Arg args[15];
	Widget dial_file;  

if (calcul_en_cours) return;     
pt_en_cours=0;
                        
XtSetArg(args[0],XmNapplyLabelString,XmStringCreateLtoR(CP[147],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[1],XmNcancelLabelString,XmStringCreateLtoR(CP[148],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[2],XmNdialogTitle,XmStringCreateLtoR(CP[149],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[3],XmNdirListLabelString,XmStringCreateLtoR(CP[150],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[4],XmNfilterLabelString,XmStringCreateLtoR(CP[151],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[5],XmNlistLabelString,XmStringCreateLtoR(CP[152],XmSTRING_DEFAULT_CHARSET));                        
XtSetArg(args[6],XmNokLabelString,XmStringCreateLtoR(CP[191],XmSTRING_DEFAULT_CHARSET));                    
if (strcmp(texte,"PPM")==0) {                   
		sprintf(toto,"%s/*",IMAGE_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[154],args,8);                            
        	}
if (strcmp(texte,"GIF")==0) {                   
		sprintf(toto,"%s/*",IMAGE_DIR);
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR(toto,XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[155],args,8);                            
        	}
if (strcmp(texte,"Postscript")==0) {                   
		XtSetArg(args[7],XmNdirMask,XmStringCreateLtoR("*",XmSTRING_DEFAULT_CHARSET));                        
		dial_file=XmCreateFileSelectionDialog(env.board,CP[156],args,8);
        	}
XtUnmanageChild(XmFileSelectionBoxGetChild(dial_file,XmDIALOG_HELP_BUTTON));
XtAddCallback(dial_file,XmNcancelCallback,AnnulerOuvrir,NULL);
if (strcmp(texte,"PPM")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKBack_PPM,NULL);
if (strcmp(texte,"GIF")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKBack_Postscript,NULL);
if (strcmp(texte,"Postscript")==0) XtAddCallback(dial_file,XmNokCallback,(XtCallbackProc)OKBack_GIF,NULL);
XtManageChild(dial_file); 

}
