/*
 * fractcalc.c
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
#include "complex.c"


extern int comp1, comp2,nbpl1, nbm1, nbau, nbav, nbavn;

/* Formulas
/*z=c_add(c_sqr(z),dc_mult(0.2,c_log(ci_pow(constant,5))));*/
/*z=z^3+3*c  (importance of 3*)  */

/************************************************************************************/

int decomp(im)
double im;
{
if (im>0) {return(bpx);}
	else {return(wpx);} 
}

/************************************************************************************/

int lmandelbrot(z0) 
lcomplex z0;          
 
{
	register int k;
	lcomplex z;
	FLOAT_SIZE temp,temp2,temp3;
                                
	temp2=(FLOAT_SIZE)0.0;
	temp3=(FLOAT_SIZE)0.0;
	z.re=(FLOAT_SIZE)0.0;
	z.im=(FLOAT_SIZE)0.0;
	
	for (k=0;(k<iter)&&((temp2+temp3)<(FLOAT_SIZE)bailout);++k){ 
		temp=z.re;
		temp2=temp*temp;
		temp3=z.im*z.im;
		z.re=temp2-temp3+z0.re;
		z.im=2*z.im*temp+z0.im; 
		/*z=z*z+z0;*/
		}  
 
	return(k);
}			
/************************************************************************************/

/*int mandelbrot(z0) 
complex z0;          
 
{
	register int k;
	complex z;
	double temp,temp2=0.0,temp3=0.0;
                                
	z.re=0;
	z.im=0;
	for (k=0;(k<iter)&&(temp2+temp3<bailout);++k){   
		temp=z.re;
		temp2=temp*temp;
		temp3=z.im*z.im;
		z.re=temp2-temp3+z0.re;
		z.im=2*z.im*temp+z0.im; 
/*		z=c_add(z0,c_sqr(z));*/
		/*z=z*z+z0;*/
/*		}   
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}*/			

/*******************************************************************************************************************************/

int newton(z0)
complex z0;      
{
	register int k=0;
	complex z,zz;
	double escape=1E-6;  

	z=z0;               
	zz.re=10.0;
	zz.im=10.0;
	for (k=0;(k<iter)&&(c_module2(c_sub(z,zz))>escape);++k){
		zz=z;
		/* z=((degre-1)*pow(z,ip)+1)/(degre*pow(z,ip-1)); */
		z=c_div(dc_add(1.0,dc_mult((double)ip-1.0,ci_pow(z,ip))),dc_mult((double)ip,ci_pow(z,ip-1)));
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}			

/*****************************************************************************/

int mandel(zz,c) 
/* int mandel(zz,c) */
complex zz,c; 
{
/*  const int num=8; */
#define num 8
  register int k,i;
  double temp,temp2=0,temp3=0;
  int iter2 = iter/num;
  double cre=c.re;
  double cim=c.im;

  double zre0=0,zre1=0,zre2=0,zre3=0,zre4=0,zre5=0,zre6=0,zre7=zz.re;
  double zim0=0,zim1=0,zim2=0,zim3=0,zim4=0,zim5=0,zim6=0,zim7=zz.im;

  double savedx=zz.re;
  double savedy=zz.im;
  int whensavenew=4;                  /*You should adapt these values*/
  int whenincsave=10;
  double lim=1e-6;

int iter3=0;

  k=0;
  while (k<iter2) {

	k++;

	temp2=zre7*zre7;
	temp3=zim7*zim7;

	if (temp2+temp3 > bailout) break;


    /* Loop unrollings */
	zre0=temp2-temp3+cre;
	zim0=(zim7+zim7)*zre7+cim;
    
    zre1=(zre0+zim0)*(zre0-zim0)+cre;
    zim1=(zim0+zim0)*zre0+cim; 
    zre2=(zre1+zim1)*(zre1-zim1)+cre;
    zim2=(zim1+zim1)*zre1+cim; 
    zre3=(zre2+zim2)*(zre2-zim2)+cre;
    zim3=(zim2+zim2)*zre2+cim; 
    zre4=(zre3+zim3)*(zre3-zim3)+cre;
    zim4=(zim3+zim3)*zre3+cim; 
    zre5=(zre4+zim4)*(zre4-zim4)+cre;
    zim5=(zim4+zim4)*zre4+cim; 
    zre6=(zre5+zim5)*(zre5-zim5)+cre;
    zim6=(zim5+zim5)*zre5+cim; 
    zre7=(zre6+zim6)*(zre6-zim6)+cre;
    zim7=(zim6+zim6)*zre6+cim; 

	/*Here starts period detection*/
/*	if ((k%whensavenew)==0) {
	  savedx=zre;
	  savedy=zim;
	  whenincsave--;
	  if (whenincsave==0) {
		whensavenew*=2;
		whenincsave=10;
	  }
	} else {
	  if ((fabs(savedx-zre)<lim)&&(fabs(savedy-zim)<lim)) {
		k=iter;
		break;
	  }
	}
*/

/*		z=c_add(c,c_sqr(z));*/
		/*z=z*z+z0;*/
  }

  /* Get accurate result */

/*  if (zre6*zre6+zim6*zim6<bailout) iter2=k*num;
  else if (zre5*zre5+zim5*zim5<bailout) iter2=k*num-1;
  else if (zre4*zre4+zim4*zim4<bailout) iter2=k*num-2;
  else if (zre3*zre3+zim3*zim3<bailout) iter2=k*num-3;
  else if (zre2*zre2+zim2*zim2<bailout) iter2=k*num-4;
  else if (zre1*zre1+zim1*zim1<bailout) iter2=k*num-5;
  else if (zre0*zre0+zim0*zim0<bailout) iter2=k*num-6;
  else iter2=k*num-7;
*/

  if (k>=iter2) iter2=iter;
  else if (zre0*zre0+zim0*zim0>bailout) iter2=k*num-7;
  else if (zre1*zre1+zim1*zim1>bailout) iter2=k*num-6;
  else if (zre2*zre2+zim2*zim2>bailout) iter2=k*num-5;
  else if (zre3*zre3+zim3*zim3>bailout) iter2=k*num-4;
  else if (zre4*zre4+zim4*zim4>bailout) iter2=k*num-3;
  else if (zre5*zre5+zim5*zim5>bailout) iter2=k*num-2;
  else if (zre6*zre6+zim6*zim6>bailout) iter2=k*num-1;
  else iter2=k*num;

/* Methode approchee du bon pixel */

/*
  iter3=k*num-(1.4427*log(log(temp2+temp3))+0.528766)+2;
  if ((iter3<0)||(iter3>iter)) iter3=iter;

  if (iter2!=iter3) {
	int tmpdiff=iter2-iter3;
	comp1++;
	nbav+=tmpdiff;
	if (tmpdiff>0) nbavn+=tmpdiff;
	else nbavn-=tmpdiff;
	if ((tmpdiff)==1) nbpl1++;
	else if ((tmpdiff)==-1) nbm1++;
	else {
	  nbau++;
	  printf("%d %d     %d\n",iter2,iter3,iter2-iter3 );}
  } else comp2++;
iter2=iter3;
*/
  /* Dichotomie */

/*  if (k>=iter2) iter2=iter;
  else if (zre3*zre3+zim3*zim3<bailout) {
	if (zre5*zre5+zim5*zim5<bailout) {
	  if (zre6*zre6+zim6*zim6<bailout) iter2=k*num;
	  else  iter2=k*num-1;
	} else if (zre4*zre4+zim4*zim4<bailout) iter2=k*num-2;
	else iter2=k*num-3;
  } else if (zre1*zre1+zim1*zim1<bailout) {
	if (zre2*zre2+zim2*zim2<bailout) iter2=k*num-4;
    else iter2=k*num-5;
  } else if (zre0*zre0+zim0*zim0<bailout) iter2=k*num-6;
  else iter2=k*num-7;
*/

/* No unroll rectification */
/*
  if (k>=iter2) iter2=iter;
  else iter2=k*num;
*/

  if (type_dessin==DECOMPOSITION) {return(decomp(zim0));}
  return iter2;
/*  	   return (k*num<iter ? k*num : iter); */
}			
/*****************************************************************************/

int mandel_std(zz,c) 
/* int mandel(zz,c) */
complex zz,c; 
{
  register int k,i;
  double temp,temp2=0,temp3=0;
  double zre=zz.re;
  double zim=zz.im; 
  double cre=c.re;
  double cim=c.im;

  double savedx=zz.re;
  double savedy=zz.im;
  int whensavenew=4;                  /*You should adapt these values*/
  int whenincsave=10;
  double lim=1e-6;

/*  for (k=0;(k<iter)&&(temp2+temp3<bailout);k++){ */

  k=0;
  while (k<iter) {

	k++;

	temp2=zre*zre;
	temp3=zim*zim;

	if (temp2+temp3>bailout) break;

	/* Standard */
	temp=zre;
	zre=temp2-temp3+cre;
	zim=(zim+zim)*temp+cim; 
	

	/*Here starts period detection*/
/*	if ((k%whensavenew)==0) {
	  savedx=zre;
	  savedy=zim;
	  whenincsave--;
	  if (whenincsave==0) {
		whensavenew*=2;
		whenincsave=10;
	  }
	} else {
	  if ((fabs(savedx-zre)<lim)&&(fabs(savedy-zim)<lim)) {
		k=iter;
		break;
	  }
	}
*/

/*		z=c_add(c,c_sqr(z));*/
		/*z=z*z+z0;*/
  }

  return k;
}

/*******************************************************************************************************************************/

int mandel_weird(zz,c)
complex zz,c; 
{
  register int k,i;
  double temp,temp2=0,temp3=0;
  double zre=zz.re;
  double zim=zz.im; 
  double cre=c.re;
  double cim=c.im;

  double savedx=zz.re;
  double savedy=zz.im;
  int whensavenew=4;                  /*You should adapt these values*/
  int whenincsave=10;
  double lim=1e-6;

  double close=100;
  double closer=100;
  double closei=100;
  int numit=0;

/*  for (k=0;(k<iter)&&(temp2+temp3<bailout);k++){ */

  k=0;
  while (k<iter) {

	k++;

	temp2=zre*zre;
	temp3=zim*zim;

	if (temp2+temp3>bailout) break;

	if (temp2+temp3<close) {
	  close=temp2+temp3;
	  numit=k;
	}

	
	if (temp2+temp3<close) close=temp2+temp3;
/*	if (fabs(zim)<closei) closei=fabs(zim);
	if (fabs(zre)<closer) closer=fabs(zre);
*/
	/* Standard */
	temp=zre;
	zre=temp2-temp3+cre;
	zim=(zim+zim)*temp+cim; 

	/*Here starts period detection*/
/*	if ((k%whensavenew)==0) {
	  savedx=zre;
	  savedy=zim;
	  whenincsave--;
	  if (whenincsave==0) {
		whensavenew*=2;
		whenincsave=10;
	  }
	} else {
	  if ((fabs(savedx-zre)<lim)&&(fabs(savedy-zim)<lim)) {
		k=iter;
		break;
	  }
	}
*/

/*		z=c_add(c,c_sqr(z));*/
		/*z=z*z+z0;*/
  }

/*  return k;*/
/*  if (k==iter) return ((int)(close*10000)%256); */
   if (k==iter) return ((int)(close*render.int_mult_mod)%256);
   return ((int)(close*render.ext_mult_mod)%254+1);
/*  return k;*/
}

/* Title 14 - ip=1500
  if (k==iter) return ((int)(closer*ip+numit*3)%256);
  return ((int)(closer*ip/3+numit*3)%256);
*/
/* Title 15
  if (k==iter) return ((int)(closer*ip+numit*6)%256); ip=1000
*/

/*******************************************************************************************************************************/

int mandel3(z0,c)
complex z0,c;   
{
	register int k;
	complex z;
	double temp2,temp3;
                                
	z=z0;
	temp2=z.re*z.re;
	temp3=z.im*z.im;
	for (k=0;(k<iter)&&(temp2+temp3<bailout);k++){
		/* z=z*z*z+z0; */
		/*z=c_add(z0,c_mult(z,c_sqr(z)));*/
		z.re=z.re*(temp2-3*temp3)+c.re;
		z.im=z.im*(3*temp2-temp3)+c.im;
		temp2=z.re*z.re;
		temp3=z.im*z.im;
		}   
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}			
  

/*******************************************************************************************************************************/
		
int mandellambda(z0)
complex z0; 
{
	register int k=0;
	complex z; 
	double zim2,zre2; 
	double temp1,temp2;

 	z.im=0;      
	z.re=0.5;
	zim2=0;
	zre2=z.re*z.re;
	for (k=0;(k<iter)&&(zim2+zre2<bailout);k++){ 
		zre2=z.re*z.re;
		zim2=z.im*z.im;
		temp1=z.re-zre2+zim2;
		temp2=z.im-2*z.re*z.im;
		z.re=z0.re*temp1-z0.im*temp2;
		z.im=z0.im*temp1+z0.re*temp2;  
		/* z=z0z(1-z)  */
		/*z=c_mult(z0,c_mult(z,dc_add(-1.0,z)));   */
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}    
	return(k); 
}			

/*******************************************************************************************************************************/

/*int mandellambda(z0)
complex z0; 
{
	register int k=0;
	complex z;
	double temp;  

	z.re=z0.re;
	z.im=z0.im;
	for (k=0;(k<iter)&&(c_module2(z)<bailout);k++){       
		/* z=z0z(1-z)  */
/*		temp=z.re;
		z.re=z.re*z.re-z.im*z.im+z0.re; 
		z.im=2*temp*z.im+0.2+z0.im;  
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}    
	return(k);
/*		z.re=(z.re*z.re-z.im*z.im)*z0.re+z.re; 
		z.im=2*temp*z.im+z0.im+z0.re;  
*/
/*}			

/*******************************************************************************************************************************/

int lambda(zz,c)
complex zz,c; 
{
	register int k=0;
	complex z; 
	double zim2,zre2; 
	double temp1,temp2;

 	z.im=zz.im;      
	z.re=zz.re;
	zim2=0;
	zre2=z.re*z.re;
	for (k=0;(k<iter)&&(zim2+zre2<bailout);k++){ 
		zre2=z.re*z.re;
		zim2=z.im*z.im;
		temp1=z.re-zre2+zim2;
		temp2=z.im-2*z.re*z.im;
		z.re=c.re*temp1-c.im*temp2;
		z.im=c.im*temp1+c.re*temp2;  
		/* z=cz(1-z)  ou (z-1)?*/
		/*z=c_mult(c,c_mult(z,dc_add(-1.0,z)));*/
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}			

/*******************************************************************************************************************************/

int spider(pixel,c)
complex pixel;
{
    
    int counter;
    complex z,w,x; 
    x.re=2.0;
    x.im=0.0;
    w=pixel;
    z=pixel;
/*    z=c_add(pixel,c);*/
    for (counter = 1; counter <= iter;counter++)
   {
      z=c_add(c_sqr(z),w);
      w=c_add(c_div(w,x),z); 
      if (c_module2(z)>bailout)  
                       return(counter);
         }
      return(0); 
   }

/**************************************************************************************************/

int barnsley1(pixel,constant)
complex pixel,constant;

{       
       int counter;
        complex z,x;
	double temp;
 
       z=pixel;
       x.re=1.0;
       x.im=0.0;
       for (counter=1;counter <=iter;counter++)
   {
/*       if (z.re >= 0)  z=c_mult(z0,c_sub(z,x));
        else  z=c_mult(c_conj(z0),c_add(z,x));*/

/*       if (z.re >= 0)  z=c_mult(constant,c_sub(z,x));
        else  z=c_mult(constant,c_add(z,x));
       if (c_module2(z)>bailout)  
                     return(counter);*/

       temp=z.re;
       if (z.re >= 0)  {
		z.re=constant.re*(z.re-(double)1.0)-constant.im*z.im;
		z.im=constant.im*(temp-(double)1.0)+constant.re*z.im;
		}
       else     {
		z.re=constant.re*(z.re+(double)1.0)-constant.im*z.im;
		z.im=constant.im*(temp+(double)1.0)+constant.re*z.im;
		}		
       if (z.re*z.re+z.im*z.im>bailout)  
                     return(counter);
        }
    return(0);
}

/***************************************************************************************************/

int barnsley2(pixel,constant)
complex pixel,constant;

{       
       int counter;
       complex z,x;
	double temp;
 
       z=pixel;
       x.re=1.0;
       x.im=0.0;
       for (counter=1;counter <=iter;counter++)
   {
       temp=z.re*constant.im+constant.re*z.im;
       if ( temp >= 0)   {
		z.re=constant.re*(z.re-(double)1.0)-constant.im*z.im;
		z.im=temp-constant.im;
		}
       else     {
		z.re=constant.re*(z.re+(double)1.0)-constant.im*z.im;
		z.im=temp+constant.im;
		}		
       if (z.re*z.re+z.im*z.im>bailout)  
                     return(counter);
        }
    return(0);
}

/*******************************************************************************************************************************/

int barnsley3(pixel,constant)
complex pixel,constant;

{       
       int counter;
       complex z;
       double temp1,temp2,temp3,temp4; 
       z=pixel;

       for (counter=1;counter <=iter;counter++)
   {
       temp3=z.re*z.re;
       temp4=z.im*z.im;
       temp1= temp3-temp4 -1;
       temp2= 2*z.re*z.im;
       if ( z.re >= 0) 
                  {  z.re=temp1;
                     z.im=temp2;
                   }
       else
                  { temp1=temp1+constant.re*z.re;
                    temp2=temp2+constant.im*z.re;
                    z.re=temp1;
                    z.im=temp2;
                  }
       if (temp3+temp4>bailout)  
                     return(counter);
        }
    return(0);
}



/*******************************************************************************************************************************/


int jcos(pixel,constant)  
complex pixel,constant; 

 {  int counter;
    complex z;

    z=pixel;
    for (counter = 1;counter <= iter;counter++)
    {  
      z=c_mult(constant,c_cos(z)); 
      if (fabs(z.im) > 50.0)  
                       return(counter);
         }
   return(0);
   }

/*******************************************************************************************************************************/

int jsin(pixel,constant)  
complex pixel,constant; 

 {  int counter;
    complex z;

    z=pixel;
    for (counter = 1;counter <= iter;counter++)
    {  
      z=c_mult(constant,c_sin(z));
      if (fabs(z.im) > 50)  
                       return(counter);
         }
   return(0);
   }


/*******************************************************************************************************************************/

int jexp(pixel,constant)
complex pixel,constant;

{
    int counter;
    complex z;

    z=pixel;
    for (counter = 1; counter <= iter;counter++)
     {
      z=c_mult(constant,c_exp(z));
      if (z.re > 50)  
                       return(counter);
         }
      return(0);
}

/*******************************************************************************************************************************/

int noel1(pixel,constant)
complex pixel,constant;

{
    int counter;
    complex temp,zprev,z;
    double temp1,temp2;

    z=pixel;
    zprev=constant;
      temp1=z.re*z.re;
      temp2=z.im*z.im;
    for (counter = 0; counter < iter;counter++)
    { 
      temp=z;
/*      z=c_add(c_sqr(z),zprev);*/
      z.re=temp1-temp2+zprev.re;
      z.im=2*temp.re*z.im+zprev.im;
      zprev=temp;
      temp1=z.re*z.re;
      temp2=z.im*z.im;
      if (temp2+temp1>bailout)  
                       return(counter);
         }
      return(0); 
   }

/*******************************************************************************************************************************/

int noel2(pixel,constant)
complex pixel,constant;

{
    int counter;
    complex z,zp1,zp2,temp;
    double temp1,temp2;

    z=c_add(pixel,constant);
    zp1.re=zp1.im=0.0;
    zp2=constant;
      temp1=z.re*z.re;
      temp2=z.im*z.im;
    for (counter = 1; counter <= iter;counter++)
     {
      temp=z;
/*      z=c_sub(c_sqr(z),zp2);*/
      z.re=temp1-temp2-zp2.re;
      z.im=2*temp.re*z.im-zp2.im;
      
      zp2=zp1;
      zp1.re=temp.re;
      zp1.im=-temp.im;
      temp1=z.re*z.re;
      temp2=z.im*z.im;
      if ( temp1+temp2 >bailout)  
                       return(counter);
         }
      return(0); 
   }

/*******************************************************************************************************************************/

int phoenix(pixel,constant)
complex pixel,constant;

{
    int counter;
    complex z,y,c,temp;
    double temp1,temp2;

    z=constant;
    c=pixel;
    y.re=y.im=0.0; 
      temp1=z.re*z.re;
      temp2=z.im*z.im;
    for (counter = 1; counter <= iter;counter++)
    {
/*      x.re=c.im;
      x.im=0.0;
      temp=c_mult(y,x);*/
      temp.re=y.re*c.im;
      temp.im=y.im*c.im;
      y=z;
/*      x.re=c.re;
      x.im=0.0; 
      z=c_add(c_add(c_sqr(z),temp),x); */
      z.re=c.re+temp.re+temp1-temp2;
      z.im=temp.im+2*z.im*y.re;
      temp1=z.re*z.re;
      temp2=z.im*z.im;
      if ( temp1+temp2 >bailout)  
                       return(counter);
         }
      return(0); 
   }

/*******************************************************************************************************************************/

int tetrate(pixel,constant)
complex pixel,constant;

{    
      complex z,c;
      int counter;
 
      c=pixel;
      z=c_add(constant,pixel);
      for(counter=1;counter<=iter;counter++)
    { 
      z=c_raise(c,z,0);
      if(c_module2(z)>bailout)
                 return(counter);
     }
   
   return(0);

}
/*******************************************************************************************************************************/
		
int mandeln(zz,c)
complex zz,c; 
{
	register int k;
	complex z;  

 	z=zz;      
	for (k=0;((k<iter)&&(c_module2(z)<bailout));++k){
		/* z=z*z*z+c;  */
		z=c_add(c,ci_pow(z,ip));
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}			
  
/*******************************************************************************************************************************/
		
int markm(zz,c)
complex zz,c; 
{
	register int k;
	complex z;  

 	z=zz;      
	for (k=0;((k<iter)&&(c_module2(z)<bailout));++k){
		/* z=z*z*z+c;  */
		z=c_add(c,c_mult(ci_pow(c,ip),c_sqr(z)));
		}
        if (type_dessin==DECOMPOSITION) {return(decomp(z.im));}
	return(k);
}			


