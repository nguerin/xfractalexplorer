/*
 * fractdef.c
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
  

int ancien_genre;

/*********************************************************************************************************/


/*********************************************************************************************************/

void init_fractal(genre)   
int genre;
{
pt_en_cours=0;
switch(genre) {
	case MANDELBROT :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.25;
			z0.im=1.4;
			z1.re=1.25;
			z1.im=-1.4;
		}
		bailout=4.0;
		break;
	
	case JULIA :
		symetrie=2;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		if (((cz.re==0.0)&&(cz.im==0.0))||(ancien_genre!=MANDELBROT)) {
			cz.re=-0.75;
			cz.im=0.17;
			}
		bailout=4.0;
		break;
		
	case MANDELN :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		ip=3;
		bailout=4.0;
		break;
	
	case JULIAN :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		if (((cz.re==0.0)&&(cz.im==0.0))||(ancien_genre!=MANDELN)) {
			cz.re=-0.75;
			cz.im=0.17;
			}
		ip=3;
		bailout=4.0;
		break;
		
	case MANDEL3 :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		bailout=4;
		break;
		
	case NEWTON :
		symetrie=1;
		if (ip==0) ip=3;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		break;  

	case JULIA3 :
		symetrie=0;         
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		if (((cz.re==0.0)&&(cz.im==0.0))||(ancien_genre!=MANDEL3)) {
			cz.re=-0.52;
			cz.im=0.1;
		}
		bailout=4;
		break;  

	case LAMBDA :
		symetrie=0;
		if (!initcoord) {
			z0.re=-1.5;
			z0.im=1.6;
			z1.re=2.5;
			z1.im=-1.6;
		}
		if (((cz.re==0.0)&&(cz.im==0.0))||(ancien_genre!=MANDELLAMBDA)) {
		cz.re=-0.2393;
		cz.im=1.0507;}
		bailout=16.0;
		break;
		
	case MANDELLAMBDA :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.3;
			z0.im=2.625;
			z1.re=4.3;
			z1.im=-2.65;
		}
		bailout=16.0;
		break;

	case MARKJ :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		if (((cz.re==0.0)&&(cz.im==0.0))||(ancien_genre!=MARKM)) {
		cz.re=0.54368;
		cz.im=0.603;}
		ip=1;
		bailout=4.0;
		break;
		
	case MARKM :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		ip=1;
		bailout=4.0;
		break;

	case SPIDER :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		
	case BARNJ1 :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0.55;
		cz.im=1.1;
		bailout=4;
		break;
		
	case BARNM1 :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		bailout=4;
		break;
		
	case BARNJ2 :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0.52;
		cz.im=1.0;
		bailout=4;
		break;
		
	case BARNM2 :
		symetrie=3;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		bailout=4;
		break;
		
	case BARNJ3 :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0.1;
		cz.im=0.36;
		bailout=4;
		break;
		
		
	case BARNM3 :
		symetrie=1;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		bailout=4;
		break;
		
	case JCOS :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=1.35;
		cz.im=0.4;
		bailout=4;
		break;
		
	case MCOS :
		symetrie=1;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		bailout=4;
		break;
		
	case JSIN :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=1;
		cz.im=0.25;
		bailout=4;
		break;
		
	case MSIN :
		symetrie=1;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		bailout=4;
		break;
		
	case JEXP :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		
	case MEXP :
		symetrie=0;
		if (!initcoord) {
			z0.re=-4.0;
			z0.im=3.2;
			z1.re=4.0;
			z1.im=-3.2;
		}
		bailout=4;
		break;
		
	case NOEL1 :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0))*/ 
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		
	case NOEL2 :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		
	case PHOENIX :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		/*if ((cz.re==0.0)&&(cz.im==0.0)) */
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		
	case TETRATE :
		symetrie=0;
		if (!initcoord) {
			z0.re=-2.0;
			z0.im=1.6;
			z1.re=2.0;
			z1.im=-1.6;
		}
		if ((cz.re==0.0)&&(cz.im==0.0)) 
		cz.re=0;
		cz.im=0;
		bailout=4;
		break;
		

		
	}
	initcoord=FALSE;
}

/*******************************************************************************************************************************/

int  calcul3(z)  
lcomplex z;
{
int k;   

switch (genre) {
	case MANDELBROT :
		k=lmandelbrot(z); 
		break;  
	default:                         
		k=lmandelbrot(z); 
	}

return(k);

}

/*******************************************************************************************************************************/

int  calcul2(z)  
complex z;
{
int k;   
complex cz1;

cz1.re=(double)cz.re;
cz1.im=(double)cz.im;
       
switch (genre) {
	case MANDELBROT :
		k=mandel(z,z); 
		break;  
	case JULIA :
		k=mandel(z,cz1);  
		break;    
	case MANDELN :
		if (ip==3) k=mandel3(z,z);
		else k=mandeln(z,z); 
		break;  
	case JULIAN :
		if (ip==3) k=mandel3(z,cz1);
		else k=mandeln(z,cz1);  
		break;    
	case NEWTON  :
		k=newton(z);
		break;             
	case LAMBDA  :
		k=lambda(z,cz1);
		break;    
	case MANDELLAMBDA  :
		k=mandellambda(z);
		break;    
	case MARKJ  :
		k=markm(z,cz1);
		break;    
	case MARKM  :
		k=markm(z,z);
		break;    
	case SPIDER :
		k=spider(z,cz1);
		break; 
	case BARNJ1 :
		k=barnsley1(z,cz1);
		break;   
	case BARNJ2 :
		k=barnsley2(z,cz1);
		break;   
	case BARNJ3 :
		k=barnsley3(z,cz1);
		break;   
	case BARNM1 :
		k=barnsley1(z,z);
		break;   
	case BARNM2 :
		k=barnsley2(z,z);
		break;   
	case BARNM3 :
		k=barnsley3(z,z);
		break;   
	case MCOS :
		k=jcos(z,z);
		break;
	case MSIN :
		k=jsin(z,z);
		break;
	case MEXP :
		k=jexp(z,z);
		break;
	case JCOS :
		k=jcos(z,cz1);
		break;
	case JSIN :
		k=jsin(z,cz1);
		break;
	case JEXP :
		k=jexp(z,cz1);
		break;
	case NOEL1 :
		k=noel1(z,cz1);
		break;
	case NOEL2 :
		k=noel2(z,cz1);
		break;
	case PHOENIX :
		k=phoenix(z,cz1);
		break;
	case TETRATE :
		k=tetrate(z,cz1);
		break;
	default:                         
		k=mandel(z,z); 
	}
/*if (k==iter) {k=0;}   */
return(k);

}
/**************************************************************************************/
/******************************************************************************************************************************/  


void Change_genre(w, client_data, call_data)
     Widget   w;
     char    *client_data;
     XtPointer  call_data;
{     
int selec=FALSE;
char numero[100];
pt_en_cours=0;
 
ancien_genre=genre;
   
if (strcmp(client_data,"Mandelbrot")==0) {
	genre=MANDELBROT;
	selec=TRUE;
}

if (strcmp(client_data,"Julia")==0) {
	genre=JULIA;
	selec=TRUE;
}

if (strcmp(client_data,"Mandel-n")==0) {
	genre=MANDELN;
	selec=TRUE;
}

if (strcmp(client_data,"Julia-n")==0) {
	genre=JULIAN;
	selec=TRUE;
}

if (strcmp(client_data,"Newton")==0) {
	genre=NEWTON;
	selec=TRUE;
}

if (strcmp(client_data,"Lambda")==0) {
	genre=LAMBDA;
	selec=TRUE;
}

if (strcmp(client_data,"Mandellambda")==0) {
	genre=MANDELLAMBDA;
	selec=TRUE;
}

if (strcmp(client_data,"Spider")==0) {
	genre=SPIDER;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleyj1")==0) {
	genre=BARNJ1;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleyj2")==0) {
	genre=BARNJ2;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleyj3")==0) {
	genre=BARNJ3;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleym1")==0) {
	genre=BARNM1;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleym2")==0) {
	genre=BARNM2;
	selec=TRUE;
}

if (strcmp(client_data,"Barnsleym3")==0) {
	genre=BARNM3;
	selec=TRUE;
}

if (strcmp(client_data,"Jcos")==0) {
	genre=JCOS;
	selec=TRUE;
}

if (strcmp(client_data,"Jsin")==0) {
	genre=JSIN;
	selec=TRUE;
}

if (strcmp(client_data,"Jexp")==0) {
	genre=JEXP;
	selec=TRUE;
}

if (strcmp(client_data,"Mcos")==0) {
	genre=MCOS;
	selec=TRUE;
}

if (strcmp(client_data,"Msin")==0) {
	genre=MSIN;
	selec=TRUE;
}

if (strcmp(client_data,"Mexp")==0) {
	genre=MEXP;
	selec=TRUE;
}

if (strcmp(client_data,"Noel1")==0) {
	genre=NOEL1;
	selec=TRUE;
}

if (strcmp(client_data,"Noel2")==0) {
	genre=NOEL2;
	selec=TRUE;
}

if (strcmp(client_data,"Phoenix")==0) {
	genre=PHOENIX;
	selec=TRUE;
}

if (strcmp(client_data,"Tetrate")==0) {
	genre=TETRATE;
	selec=TRUE;
}

if (strcmp(client_data,"Mark's Mandel")==0) {
	genre=MARKM;
	selec=TRUE;
}

if (strcmp(client_data,"Mark's Julia")==0) {
	genre=MARKJ;
	selec=TRUE;
}

if (selec) {
/*	init0(genre);
	if (initfractal) init_fractal(genre);    */
	init_fractal(genre); 
	sprintf(numero,"%s%s",CP[190],client_data);
	ecrire(numero);
	}

}
/******************************************************************************************************************************/  

