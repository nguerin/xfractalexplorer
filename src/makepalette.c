#include <stdio.h> 
#include <string.h> 
#include <math.h>


main()
{
int rouge[256],vert[256],bleu[256]; 
FILE                    *fichierdisque;  
char			nom_tab[30];
int i,n;

n=254;
for (i=0;i!=16;i++) {
		rouge[i]=255; 
		vert[i]=255-i*16;
		bleu[i]=255-i*16;
		}               

	for (i=0;i!=32;i++) {   

		rouge[i+16]=255-i*4;
		vert[i+16]=i*4;
		bleu[i+16]=i*8;   
		}

	for (i=0;i!=48;i++) {

		rouge[i+48]=128-(int)(i*2.6666);
		vert[i+48]=128+(int)(i*2.6666);
		bleu[i+48]=255-(int)(i*2.6666);
		}
	for (i=0;i!=64;i++) {
                           
		rouge[i+96]=i*2;
		vert[i+96]=255-i*2;
		bleu[i+96]=127-i*2;

		rouge[i+160]=128+i*2;
		vert[i+160]=127-i*2;
		bleu[i+160]=0;   }

	for (i=0;i!=32;i++) {
		rouge[i+224]=255-i*8;
		vert[i+224]=0;
		bleu[i+224]=0;
		} 

strcpy(nom_tab,"Palettes/glow.env.cmap");
if ((fichierdisque = fopen(nom_tab,"w"))==NULL)
{
   perror("Echec ouverture en ecriture du fichier");
}                                                 
printf("fichier ouvert\n");
fprintf(fichierdisque,"%d\n",n);                                    
fprintf(fichierdisque,"%d\n",255);                                    
fprintf(fichierdisque,"%d\n",0);                                    
for(i=0;i<255;i++)
   {
   fprintf(fichierdisque,"%d %d %d\n",rouge[i],vert[i],bleu[i]);
   }   
fclose(fichierdisque); 
}             
