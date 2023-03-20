#include <hellomake.h>
#include<stdio.h>
#include<stdlib.h>


int main(int argc,char *argv[]) {
	int a= atoi(argv[1]);
	int b= atoi(argv[2]);
	char *outputfilename=argv[3];

	//double array[a][b];
	
	double **array=(double **)malloc(a*sizeof(double*));
	for(int c=0; c<a; c++){
		array[c]=(double *)malloc(b*sizeof(double));
	}
	
	srand(18050171001);

	int h=0;
	int w=0;
	for (h=0; h<a ; h++){
		for(w=0; w<b; w++){
		
				
				double range= 100.0-1.0;
				double div = RAND_MAX / range;
				double random=1.0+(rand()/div);
				
				array[h][w]=random;
				printf("h:%d w:%d yeni sayi : %lf\n",h,w, array[h][w]);
	}
	}
	
	printf("\n************************************************\n");

	double *vector = (double *) malloc(b * sizeof(double));
  		for (int v = 0; v < b; v++) {
  				double range= 100.0-1.0;
				double div = RAND_MAX / range;
				double random=1.0+(rand()/div);
  			
    		vector[v] = random;
    						printf("v:%d yeni vector sayisi : %lf\n",v, vector[v]);
    		
  	}
	double *total=(double*)malloc(a*sizeof(double));
	
	
	// call a function in another file
	calculate(a,b, array, vector, total);

	
	FILE *out=fopen(outputfilename,"w");
	if(out==NULL){
		printf("%s acilamadi",outputfilename);
		
		return 1;
	}
		printf("\n********************OUTPUT**********************\n");
	for (int i = 0 ; i<a; i++){
		printf("%.2f \n", total[i]);
		fprintf(out,"%.2f \n", total[i]);
	}
	fclose(out);
	free(array);
	free(vector);
	free(total);




  return(0);
}
