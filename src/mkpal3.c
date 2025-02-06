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
for (i=0;i!=100;i++) {
		rouge[i]=255; 
		vert[i]=255;
		bleu[i]=255;
		}               


for (i=100;i!=255;i++) {
		rouge[i]=0; 
		vert[i]=0;
		bleu[i]=0;
		}               




strcpy(nom_tab,"Palettes/nb100.env.cmap");
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
