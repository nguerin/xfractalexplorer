#include "header.h"


#define MAX_CODES   4095

extern Environ env;

 static long code_mask[13]={
  0,0x0001,0x0003,0x0007,0x000f,0x001f,0x003f,0x007f,0x00ff,0x01ff,0x03ff,0x07ff,0x0fff};

 short curr_size;           
 short clear;           
 short ending; 
 short newcodes; 
 short top_slot;  
 short slot;      

 short navail_bytes; 
 short nbits_left; 
 unsigned char b1;
 unsigned char byte_buff[257];
 unsigned char *pbytes; 
 int bad_code_count; 
 
 extern XColor coul[256];
 unsigned char *gif_colour_map;

 int y_gif;   

extern XImage *image_gif;

/* typedef short WORD; */
typedef unsigned short UWORD;
typedef char TEXT;
typedef unsigned char UTINY;
typedef long LONG;
typedef unsigned long ULONG;
typedef int INT;


int out_line(unsigned char *pixels,int linelen)
{
   register int x,no_col;

   for (x=0;x<linelen;x++)
   {
      no_col=(int)(*pixels);

      XPutPixel(image_gif,x,y_gif,env.palette.color[no_col].pixel);
/*printf("%d ",*/
      pixels++;
   }
   y_gif++;
   return 0;
}



/* This function initializes the decoder for reading a new image.
 */
short init_exp(int i_size)
{
   short size;
   
   size=(short)i_size;
   curr_size=size+1;
   top_slot=1 << curr_size;
   clear=1 << size;
   ending=clear+1;
   slot=newcodes=ending+1;
   navail_bytes=nbits_left=0;
   return 0;
}

/* get_next_code()
 * - gets the next code from the GIF file.  Returns the code, or else
 * a negative number in case of file errors...
 */
short get_next_code(FILE *f)
{
   short i, x;
   ULONG ret;

   if (nbits_left == 0)
   {
      if (navail_bytes <= 0)
      {

         /* Out of bytes in current block, so read next block
          */
         pbytes = byte_buff;
         if ((navail_bytes=fgetc(f)) < 0)
            return(navail_bytes);
         else if (navail_bytes)
         {
            for (i = 0; i < navail_bytes; ++i)
            {
               if ((x =fgetc(f)) < 0)
                  return(x);
               byte_buff[i] = (unsigned char) x;
            }
         }
      }
      b1 = *pbytes++;
      nbits_left = 8;
      --navail_bytes;
   }

   ret = b1 >> (8 - nbits_left);
   while (curr_size > nbits_left)
   {
      if (navail_bytes <= 0)
      {

         /* Out of bytes in current block, so read next block
          */
         pbytes = byte_buff;
         if ((navail_bytes =fgetc(f)) < 0)
            return(navail_bytes);
         else if (navail_bytes)
         {
            for (i = 0; i < navail_bytes; ++i)
            {
               if ((x = fgetc(f)) < 0)
                  return(x);
               byte_buff[i] = (unsigned char) x;
            }
         }
      }
      b1 = *pbytes++;
      ret |= b1 << nbits_left;
      nbits_left += 8;
      --navail_bytes;
   }
   nbits_left -= curr_size;
   ret &= code_mask[curr_size];
   return((short)(ret));
}



static unsigned char *dstack;      /* Stack for storing pixels */
static unsigned char *suffix;      /* Suffix table */
static UWORD *prefix;      /* Prefix linked list */
 unsigned char *decoderline;              /* decoded line goes here */


void cleanup_gif_decoder()
{
   free(dstack);
   free(suffix);
   free(prefix);
}

short decoder(int i_linewidth,FILE *f)
{
   short linewidth;
   register unsigned char *sp, *bufptr;
   unsigned char *buf;
   register short code, fc, oc, bufcnt;
   short c, size, ret;

   linewidth = (short)i_linewidth;

   /* Initialize for decoding a new image...
    */
   if ((size =fgetc(f)) < 0)
      return(size);
   if (size < 2 || 9 < size)
      return -1;
   init_exp((int)size);        /* changed param to int */

   dstack = (unsigned char *) malloc((MAX_CODES + 1)*sizeof(unsigned char));
   suffix = (unsigned char *) malloc((MAX_CODES + 1)*sizeof(unsigned char));
   prefix = (UWORD *) malloc((MAX_CODES + 1)*sizeof(UWORD));

   /* Initialize in case they forgot to put in a clear code.
    * (This shouldn't happen, but we'll try and decode it anyway...)
    */
   oc = fc = 0;

   buf = decoderline;

   bad_code_count = 0;

   /* Set up the stack pointer and decode buffer pointer
    */
   sp = dstack;
   bufptr = buf;
   bufcnt = linewidth;

   while ((c = get_next_code(f)) != ending)
   {

      /* If we had a file error, return without completing the decode
       */
      if (c < 0) {
         cleanup_gif_decoder();
         return(0);
      }

      /* If the code is a clear code, reinitialize all necessary items.
       */
      if (c == clear)
      {
         curr_size = size + 1;
         slot = newcodes;
         top_slot = 1 << curr_size;

         while ((c = get_next_code(f)) == clear)
            ;

         if (c == ending)
            break;

         if (c >= slot)
            c = 0;

         oc = fc = c;

         *bufptr++ = (unsigned char) c;
         if (--bufcnt == 0)
         {
            if ((ret = out_line(buf, linewidth)) < 0) {
               cleanup_gif_decoder();
               return(ret);
            }

            bufptr = buf;
            bufcnt = linewidth;
         }
      }
      else
      {

         code = c;

         if (code >= slot)
         {
            if (code > slot)
               ++bad_code_count;
            code = oc;
            *sp++ = (unsigned char) fc;
         }

         while (code >= newcodes)
         {
            *sp++ = suffix[code];
            code = prefix[code];
         }

         *sp++ = (unsigned char) code;
         if (slot < top_slot)
         {
            fc = code;
            suffix[slot] = (unsigned char) fc;
            prefix[slot++] = oc;
            oc = c;
         }
         if (slot >= top_slot)
            if (curr_size < 12)
            {
               top_slot <<= 1;
               ++curr_size;
            }

         while (sp > dstack)
         {
            *bufptr++ = *(--sp);
            if (--bufcnt == 0)
            {
               if ((ret = out_line(buf, linewidth)) < 0) {
                  cleanup_gif_decoder();
                  return(ret);
               }
               bufptr = buf;
               bufcnt = linewidth;
            }
         }
      }
   }
   ret = 0;
   if (bufcnt != linewidth)
      ret = out_line(buf, (linewidth - bufcnt));

   cleanup_gif_decoder();
   return(ret);
}



int ReadGIF(char *nom,Display *aff,int ecran,coordonnees *benny)
{
   register int i,j,status,colourmap_size;
   unsigned finished,planes;
   unsigned char buffer[16];    
   FILE *f;
XColor                 newcolor;

   status=0;

   f=fopen(nom,"rb");
   if (!f)
     return 0;
     
   decoderline=(unsigned char *)malloc(2049);
   if (!decoderline)
   {
     fclose(f);
     return 0;
   }
     
   for (i=0;i<2049;i++)
      decoderline[i]=(unsigned char)0;

   /* Get the screen description */
   for (i=0;i<13;i++)
      buffer[i]=(unsigned char)fgetc(f);

   if ((strncmp((char *)buffer,"GIF",3)) ||          /* use updated GIF specs */
       (buffer[3]<'0') || (buffer[3]>'9') ||
       (buffer[4]<'0') || (buffer[4]>'9') ||
       (buffer[5]<'A') || (buffer[5]>'z'))
   {
     free(decoderline);
     fclose(f);
     return 0;
   }


   planes=((unsigned)buffer[10] & 0x0F)+1;
   colourmap_size=(int)(1 << planes);

   gif_colour_map=(unsigned char *)malloc(3*colourmap_size);
   if (!gif_colour_map)
   {
     free(decoderline);
     fclose(f);
     return 0;
   }
     

   if ((buffer[10] & 0x80)==0)
   {  
     free(decoderline);
     free(gif_colour_map);
     fclose(f);
     return 0;
   }

   j=0;
   for (i=0;i<colourmap_size;i++)
   {
      gif_colour_map[j]=(unsigned char)fgetc(f); /* rouge */
      gif_colour_map[j+1]=(unsigned char)fgetc(f); /* vert */
      gif_colour_map[j+2]=(unsigned char)fgetc(f); /* bleu */
      j+=3;
   }

/************* alloue les couleurs sous X *********************/
       

/*  env.cmap=XDefaultColormap(aff,ecran);*/  

	for (i=0;i<colourmap_size;++i)
        {
	newcolor.red=((unsigned int)gif_colour_map[3*i])*256;
	newcolor.green=((unsigned int)gif_colour_map[3*i+1])*256;
	newcolor.blue=((unsigned int)gif_colour_map[3*i+2])*256;
	newcolor.pixel=i;  
	newcolor.flags=DoRed|DoGreen|DoBlue;
	XStoreColor(XtDisplay(env.root),env.cmap,&newcolor);  
        }

   /* Now display one or more GIF objects */
   finished=FALSE;
   
   while (!finished)
   {
      switch (fgetc(f))
      {
        case ';':                /* End of the GIF dataset */
          finished=TRUE;
          status=0;
          break;

        case '!':                /* GIF Extension Block */
          fgetc(f);           /* read (and ignore) the ID */
          while ((i=fgetc(f))>0) /* get data len*/
            for (j=0;j<i;j++)
              fgetc(f); /* flush data */
          break;

        case ',': /* Start of image object. get description */
          for (i=0;i<9;i++)
          {
            if ((j=fgetc(f)) < 0)
            {	/* EOF test (?) */
              status=-1;
              break;
            }
            buffer[i]=(unsigned char)j;
          }
 
          if (status<0)
          {
             finished=TRUE;
             break;
          }
          benny->x=buffer[4] | (buffer[5] << 8);
          benny->y=buffer[6] | (buffer[7] << 8);
          
          image_gif=XCreateImage(aff,XDefaultVisual(aff,ecran),8,ZPixmap,0,0,benny->x,benny->y,8,0);
          image_gif->data=(char *)malloc(image_gif->bytes_per_line*benny->x);

          y_gif=0;

          /* Setup the color palette for the image */
          status=decoder(benny->x,f); /*put bytes in Buf*/
          /* changed param to int */
          finished=TRUE;
          break;

       default:
         status=-1;
         finished=TRUE;
         break;
     }
   }
  free(decoderline);
  free(gif_colour_map);
  fclose(f);
  
  return 1;
}



