/*
 * complex.c
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



#include <math.h>
#define PI 3.14159365358979323846
#define LN10	2.30258509299404568402        

/*#define lfabs(A) (A)>0?(A):(-A)*/


/*******************************************************************************************************************************/
/*FLOAT_SIZE lfabs(a)
FLOAT_SIZE a;
{
return(a>0 ? a : -a);
}*/



/*******************************************************************************************************************************/
double c_mod(a)
complex a;

  {
   double x;
   if (a.im == 0.0)
      x = fabs(a.re);
   else
   {
      a.re = a.re * a.re;                  /* Square  */
      a.im = a.im * a.im;
      x = sqrt(a.re + a.im);            /* and Add */
   }
   return(x);
}
                 
/*******************************************************************************************************************************/
                  
double c_module2(z)
complex z;
{
	return(z.im*z.im+z.re*z.re);
}

/******************************************************************************************************************************/

complex c_add(x,y)
complex x,y;
{
	complex z;

	z.re=x.re+y.re;  
	z.im=x.im+y.im;
	return(z);
}                 


/******************************************************************************************************************************/

complex c_sub(x,y)
complex x,y;
{
	complex z;

	z.re=x.re-y.re;
	z.im=x.im-y.im;
	return(z);
}

/*****************************************************************************************************************************/

complex c_mult(x,y)          
complex x,y;
{
	complex z;
	z.re=x.re*y.re-x.im*y.im;
	z.im=x.re*y.im+x.im*y.re;
	return(z);
}

/******************************************************************************************************************************/

complex c_sqr(x)
complex x;
{        
	complex z;
	
	z.re=x.re*x.re-x.im*x.im; 
	z.im=2*x.im*x.re;
	return(z);
}

/*******************************************************************************************************************************/ 

complex c_opp(x)
complex x;
{        
	x.re=-x.re; 
	x.im=-x.im;
	return(x);
}

/*******************************************************************************************************************************/ 
        
complex c_div(a,b)
complex a,b;
{
      double ratio;
      double denom;
      complex result;
   if (fabs(b.re) >= fabs(b.im))     /* Don't square to avoid over or underflow */
  {   ratio = b.im/b.re; 
      denom = b.re + ratio*b.im; 
      result.re = (a.re + a.im*ratio)/denom; 
      result.im = (a.im - a.re*ratio)/denom; 
  }
   else
   { 
      ratio = b.re/b.im; 
      denom = b.im + ratio*b.re; 
      result.re = (a.re*ratio + a.im)/denom; 
      result.im = (a.im*ratio - a.re)/denom;
   }
   return(result);
/*	complex z;
	double denom;

	denom=1/(y.im*y.im+y.re*y.re);
	z.re=(x.re*y.re+x.im*y.im)*denom;
	z.im=(x.im*y.re-x.re*y.im)*denom;
	return(z);*/
}

/**************************************************************************************/

complex ci_pow(z,a)
complex z;
int a;
{
	complex x;
	int i;     
        x=z;
	for (i=2;i!=a+1;i++){
		x=c_mult(x,z);
		}
	return(x);   
}

/****************************************************************************************/
                                                         
complex complx(a,b)
FLOAT_SIZE a;
FLOAT_SIZE b;
{
	complex z;
	z.re=(double)a;
	z.im=(double)b;
	return (z);
}   
/****************************************************************************************/
                                                         
lcomplex lcomplx(a,b)
FLOAT_SIZE a;
FLOAT_SIZE b;
{
	lcomplex z;
	z.re=a;
	z.im=b;
	return (z);
}   

/**************************************************************************************/

complex dc_mult(a,z)
double a;
complex z;
{
	complex x;

	x.im=a*z.im;
	x.re=a*z.re;  
	return(x);
}

/**************************************************************************************/

complex dc_add(a,z)
double a;
complex z;
{       
	complex x;

	x.re=z.re+a; 
	x.im=z.im;
	return(x);
}

/**************************************************************************************/

complex c_conj(z)
complex z;
{       
	z.im=-z.im;
	return(z);
}

/**************************************************************************************/

double c_arg(a)
complex a;   

{
   double theta;
   if (a.im == 0.0)
      if (a.re >= 0.0) 
	 theta = 0.0;            /* positive real */
      else
	 theta = PI;            /* negative real */
   else  
     if (a.re == 0.0)
      if (a.im >= 0.0) 
	 theta = PI/2.0;         /* positive imag */
      else
	 theta = -PI/2.0;         /* negative imag */
      
   else
      theta = atan(a.im/a.re);
      if (a.re < 0.0)             /* make sure theta is in the correct quadrant */
	 if (a.im > 0.0)
	    theta = PI + theta;
	 else
	    theta = theta - PI;
	 
   return(theta);
}

/**************************************************************************************/

/* sqrt(z) = sqrt(r)*[cos(theta/2) + i*sin(theta/2)] */
complex c_sqrt (z,branch)
complex z;
int branch;

{  complex x;
   double r;
   if (z.im == 0.0 && z.re > 0.0) 
      { if (branch == 0) 
	 x.re = sqrt(z.re);
      else
	 x.re = -sqrt(z.re);
      x.im = 0.0;
      }
   else
   {
      r = c_mod(z);
      x.re = (r + z.re)/2.0;
      x.im = (r - z.re)/2.0;
      x.re = sqrt(x.re);
      if(z.im>=0) x.im= sqrt(x.im);
       else x.im= -sqrt(x.im);
      
   }
   return(x);
}
/**************************************************************************************/


/* log(z) = log(z) = log|z| + i(theta + 2*PI*n)    where n is any integer
   Ln uses n = 0. */
complex c_ln (z,branch)
complex z;
int branch;

{  complex x;
   if (z.im == 0.0 && z.re >= 0.0) 
     { x.re = log(z.re);
       x.im = 0.0;
     }
   else
     { x.re = log(c_mod(z));
       x.im = c_arg(z);
       x.im = x.im + 2*PI*branch;
     }
   return(x);
}

/**************************************************************************************/

complex c_log (z,branch)
complex z;
int branch;

{  complex x;
   x = c_ln(z, branch);
   x.re = x.re/LN10;
   x.im = x.im/LN10;
   return(x);
}

/**************************************************************************************/

/* exp(z) = e^x*[cos(y) + i*sin(y)] */
complex c_exp (z)
complex z;
   
 { 
   complex x;
   double a;
   if (z.im == 0.0) 
    {  x.re = exp(z.re);
       x.im = 0.0;
    }
   else
    { a = exp(z.re);
      x.re = a*cos(z.im);
      x.im= a*sin(z.im);
    }
   return(x);
}

/**************************************************************************************/


/* z^n = r^n*[cos(n*theta) + i*sin(n*theta)] */
complex ci_pow2 (z,n)
complex z;
int n;
  
 {
   complex x;
   double r,t;
   if (z.im == 0.0) 
      if (z.re == 0.0) 
	 if (n == 0) 
	    { x.re = 0;   /*WARNING: 0^0 should be undefined */
	      x.im = 0;
	    }
	 else
	    { x.re = 0.0;
	      x.im = 0.0;
	    }
      else if (z.re == 1.0)
	{ x.re = 1.0;
	  x.im = 0.0;
	}
	   else
	    { x.re = pow(z.re,(double)(n));
	     x.im = 0.0;
	    }
    
   else if (n == 0)
      { x.re = 1.0;
       x.im = 0.0; 
       }

	else if (n == 1) 
	     x = z;
	      else
		{  r = c_mod(z);
		   t = c_arg(z);
		   r = pow(r,(double)(n));
		   t = n*t;
		   x.re = r*cos(t);
		   x.im = r*sin(t);
		}
   return(x); 
 }

/**************************************************************************************/
/* 
   z^c = exp(c*log(z))
   NOTE:
      Because log(z) is a many valued function z^c does not, in general,
      have a unique value. In particular if we let j and k be any integer
      then if:
	 c = k 
	    there is one power
	 c = 1/k 
	    there are k distinct powers
	 c = j/k, with j and k having no common factors
	    there are k distinct powers
	 if c is not an integer or a rational number
	    there are an infinite number of powers
      This can result in some unexpected answers with roots of negative
      reals. For example -8^(1/3) will come out as (1+1.732i) the second
      value (n = 1) yields the expected result: -2.
*/

/**************************************************************************************/

complex c_raise (z,c,branch)
complex z,c;
int branch;
   
 {
   double r,t;
   complex x,y;
   if ((z.re == 0.0) && (z.im == 0.0)) 
      if ((c.im == 0.0) && (c.im == 0.0)) 
	{ x.re = 0;       /*WARNING: 0^0 should be undefined */
	  x.im = 0;
	}
      else
	{ x.re = 0.0;
	  x.im = 0.0;
	 } 
      
   else 
      if ((c.re == 0.0) && (c.im == 0.0)) 
	  { x.re = 1.0;
	    x.im = 0.0; }
       else  if ((c.re == 1.0) && (c.im == 0.0)) 
		 x = z;
	     else  if (c.im == 0.0) 
		       if (((int)(c.re) - c.re) == 0) 
		       x = ci_pow(z, (int)(c.re));
		       else
			  {  r = c_mod(z);
			     t = c.re*c_arg(z);
			     r = pow(r, c.re);
			     x.re = r*cos(t);
			     x.im = r*sin(t);
			  }
		  else
		     {  y = c_ln(z, branch);
			y = c_mult(c, y);
			x = c_exp(y);
		    }
   return(x);
}


/**************************************************************************************/

complex c_sin (z)
complex z; 
   
{
   complex x;
   if (z.im == 0.0)
      { x.re = sin(z.re);
	x.im = 0.0;
      }
   else
      { x.re = sin(z.re)*cosh(z.im);
	x.im = cos(z.re)*sinh(z.im);
      }
   return(x);
}

/**************************************************************************************/


complex c_cos (z)
complex z; 
   
{  complex x;
   if (z.im == 0.0)
     { x.re = cos(z.re);
       x.im = 0.0;
     }
   else
     {  x.re = cos(z.re)*cosh(z.im);
	x.im = -sin(z.re)*sinh(z.im);
     }
   return(x);
}

/**************************************************************************************/


complex c_tan (z)
complex z; 
   
{  complex x,y;
   if (z.im == 0.0)
     { x.re = tan(z.re);
       x.im = 0.0;
     }
   else
     { x = c_sin(z);
       y = c_cos(z);
       x = c_div(x, y);
     }
   
   return(x);
}


/**************************************************************************************/


/* arcSin(z) = -i*log[i*z + sqrt(1 - z*z)] */
complex c_arcsin (z)
complex z; 
  
 {  
   complex x,y;
   if (z.im == 0.0) 
     { y.re =asin(z.re);
       y.im = 0.0;
     }
   else
    { x.re = -z.im;
      x.im = z.re;
      y = c_sqr(z);
      y.re = 1.0 - y.re;
      y = c_sqrt(y, 0);
      x = c_add(x, y);
      x = c_ln(x, 0);
      y.re = x.im;
      y.im = -x.re;
    }
   return(y);
}


/**************************************************************************************/

/* arcCos(z) = -i*log[z + i*sqrt(1 - z*z)] */
complex c_arccos (z)
complex z; 

{  
   complex x,y;
   if (z.im == 0.0) 
     { x.re = acos(z.re);
       x.im = 0.0;
     }
   else
    { y = c_sqr(z);
      y.re = 1.0 - y.re;
      y = c_sqrt(y, 0);
      x.re = -y.im;
      x.im = y.re;
      y = c_add(z, x);
      y = c_ln(y, 0);
      x.re = y.im;
      x.im = -y.re;
    }
   
   return(x);
 }


/**************************************************************************************/


/* arcTan(z) = i*log[(i + z)/(i - z)]/2 */
complex c_arctan (z)
complex z; 

 { complex x,y;
   if (z.im == 0.0)
    {  y.re = atan(z.re);
       y.im = 0.0;
    }
   else
   {  x.re = z.re;
      x.im = 1.0 + z.im;
      y.re = -z.re;
      y.im = 1.0 - z.im;
      x = c_div(x, y);
      x = c_ln(x, 0);
      y.re = x.im/2.0;    
      y.im = x.re/2.0;
    }
   return(y);
 }


/**************************************************************************************/


complex c_sinh (z)  
complex z; 
 
{  complex x;
   if (z.im == 0.0) 
   { x.re = sinh(z.re);
     x.im = 0.0;
   }
   else
    {  x.re = sinh(z.re)*cos(z.im);
       x.im = cosh(z.re)*sin(z.im);
    }
   return(x);
}


/**************************************************************************************/

complex c_cosh (z)
complex z; 
   
 {
   complex x;
   if (z.im == 0.0)
     {  x.re = cosh(z.re);
	x.im = 0.0;
     }
   else
    {  x.re = cosh(z.re)*cos(z.im);
       x.im = sinh(z.re)*sin(z.im);
    }
   return(x);
}


/**************************************************************************************/

complex c_tanh (z)
complex z; 
 
 { 
   complex x,y;
   if (z.im == 0.0) 
     { x.re = tanh(z.re);
       x.im = 0.0;
      }
   else
     { x = c_sinh(z);
       y = c_cosh(z);
       x = c_div(x, y);
     }
   return(x);
  }


/**************************************************************************************/


/* arcSinh(z) = log[z + sqrt(z*z + 1)] */
/*complex c_arcsinh (z) 
complex z; 
 
 {
   complex x;
   if (z.im == 0.0)
    {  x.re = asinh(z.re);
       x.im = 0.0;
    }
   else
     { x = c_sqr(z);
       x.re = 1.0 + x.re;
       x = c_sqrt(x, 0);
       x = c_add(x, z);
       x = c_ln(x, 0);
     }
   return(x);
 }*/

/**************************************************************************************/


/* arcCosh(z) = log[z + sqrt(z*z - 1)] */
/*complex c_arccosh (z)
complex z; 

 {
   complex x;
   if (z.im == 0.0) 
    {  x.re = acosh(z.re);
       x.im= 0.0;
     }
   else
     { x = c_sqr(z);
       x.re = x.re - 1.0;
       x = c_sqrt(x, 0);
       x = c_add(z, x);
       x = c_ln(x, 0);
     }
   
   return(x);
}*/

/**************************************************************************************/


/* arcTanh(z) = log[(1 + z)/(1 - z)]/2 */
/*complex c_arctanh (z)
complex z; 

{ 
   complex x,y;
   if (z.im == 0.0)
     { x.re = atanh(z.re);
      x.im = 0.0;
      }
   else
    { x = z;
      x.re = 1.0 + x.re;
      y = z;
      y.re = 1.0 - y.re;
      x = c_div(x, y);
      x = c_ln(x, 0);
      x.re = x.re/2.0;
      x.im = x.im/2.0;
    }
   return(x);
 }*/




