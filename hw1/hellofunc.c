#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
// Fatih Gülmez 18050171001

void calculate(int a, int b, char *outp) {
  int matrix_r= a;
  int matrix_c=a;
  int vector_r=a;
  int vector_c=1;
  float matrix[matrix_r][matrix_c],vector[vector_r][vector_c],total[matrix_r][vector_c];
  int rank,size,i,j,k,local_a,local_b,part; 
  int master_tag=1;
  int slave_tag=4;
  double start;
  double finish;
  MPI_Status status;
  MPI_Request request;

  MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {


    srand(18050171001);

    for (int h=0; h<matrix_r ; h++){
        for(int w=0; w<matrix_r; w++){
        
                
                float range= 100.0-1.0;
                float div = RAND_MAX / range;
                float random=1.0+(rand()/div);
                
                matrix[h][w]=random;
              //  printf("h:%d w:%d yeni sayi : %lf\n",h,w, matrix[h][w]);
    }
    }



        for (int h=0; h<vector_r ; h++){
            for(int w=0; w<vector_c; w++){
        
                
                float range= 100.0-1.0;
                float div = RAND_MAX / range;
                float random=1.0+(rand()/div);
                
                vector[h][w]=random;
              //  printf("h:%d w:%d vector yeni sayi : %f\n",h,w, vector[h][w]);
            }
        }



        start = MPI_Wtime();
        for (i = 1; i < size; i++) {
            part = (matrix_r / (size - 1));
            local_a = (i - 1) * part;
            if (((i + 1) == size) && ((matrix_r % (size - 1)) != 0)) {
                local_b = matrix_r;
            } else {
                local_b = local_a + part;
            }
            MPI_Isend(&local_a, 1, MPI_INT, i, master_tag, MPI_COMM_WORLD, &request);
            MPI_Isend(&local_b, 1, MPI_INT, i, master_tag + 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&matrix[local_a][0], (local_b - local_a) * matrix_r, MPI_DOUBLE, i, master_tag + 2, MPI_COMM_WORLD, &request);
        }
        if(size==1){
        for (i = 0; i < matrix_r; i++) {
            for (j = 0; j < vector_c; j++) {
                total[i][j]=0;
                for (k = 0; k < vector_r; k++) {
                    total[i][j] += (matrix[i][k] * vector[k][j]);
                }
            }
        }
    }
    }
    MPI_Bcast(&vector, vector_r*vector_c, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (rank > 0) {
        MPI_Recv(&local_a, 1, MPI_INT, 0, master_tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&local_b, 1, MPI_INT, 0, master_tag + 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&matrix[local_a][0], (local_b - local_a) * matrix_r, MPI_DOUBLE, 0, master_tag + 2, MPI_COMM_WORLD, &status);
        for (i = local_a; i < local_b; i++) {
            for (j = 0; j < vector_c; j++) {
                total[i][j]=0;
                for (k = 0; k < vector_r; k++) {
                    total[i][j] += (matrix[i][k] * vector[k][j]);
                }
            }
        }
        MPI_Isend(&local_a, 1, MPI_INT, 0, slave_tag, MPI_COMM_WORLD, &request);
        MPI_Isend(&local_b, 1, MPI_INT, 0, slave_tag + 1, MPI_COMM_WORLD, &request);
        MPI_Isend(&total[local_a][0], (local_b - local_a) * vector_c, MPI_DOUBLE, 0, slave_tag + 2, MPI_COMM_WORLD, &request);
    }
    if (rank == 0) {
        for (i = 1; i < size; i++) {
            MPI_Recv(&local_a, 1, MPI_INT, i, slave_tag, MPI_COMM_WORLD, &status);
            MPI_Recv(&total[local_a][0], (local_b - local_a) * vector_c, MPI_DOUBLE, i, slave_tag + 2, MPI_COMM_WORLD, &status);
        }
        finish = MPI_Wtime();

    FILE *out ;   
   
    out =fopen(outp,"w");
    if(out==NULL){
        printf("%s acilamadi",outp);
        

    }
        printf("\n********************OUTPUT for %d CORE **********************\n",size);
        printf("TOTAL TIME FOR %d CORE= %f\n",size, (finish - start));
    for (int i = 0 ; i<matrix_r; i++){
       // printf("%.2f \n", total[i][0]);
        fprintf(out,"%.2f \n", total[i][0]);
    }
            fprintf(out, "TOTAL TIME FOR %d CORE= %f\n",size, (finish - start));

    fclose(out);

    }


    MPI_Finalize();






 
}
