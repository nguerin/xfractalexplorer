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
		rouge[i]=0; 
		vert[i]=0;
		bleu[i]=i*16;
		}               

	for (i=0;i!=64;i++) {   

		rouge[i+16]=0;
		vert[i+16]=i*4;
		bleu[i+16]=255-i*4;   
		}

	for (i=0;i!=64;i++) {   

		rouge[i+80]=i*4;
		vert[i+80]=255-i*4;
		bleu[i+80]=0;   
		}

	for (i=0;i!=64;i++) {   

		rouge[i+144]=255;
		vert[i+144]=0;
		bleu[i+144]=i*4;   
		}

	for (i=0;i!=48;i++) {

		rouge[i+208]=255;
		vert[i+208]=(int)(i*2.6666);
		bleu[i+208]=255;
		}

strcpy(nom_tab,"Palettes/rvb.env.cmap");
if ((fichierdisque = fopen(nom_tab,"w"))==NULL)
{
   perror("Echec ouverture en ecriture du fichier");
}                                                 
printf("fichier ouvert\n");
fprintf(fichierdisque,"%d\n",n);                                    
fprintf(fichierdisque,"%d\n",0);                                    
fprintf(fichierdisque,"%d\n",255);                                    
for(i=0;i<255;i++)
   {
   fprintf(fichierdisque,"%d %d %d\n",rouge[i],vert[i],bleu[i]);
   }   
fclose(fichierdisque); 
}             
