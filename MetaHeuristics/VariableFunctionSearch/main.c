#include "VFS.h"
#include "RandomPerm.h"
#include "EvaluateQAP.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char * Instance;
int PermuSize, Repetition, TabuSize, MaxEvals;
long double ** flow_matrix;
long double ** zero_flow_matrix;
long double ** dist_matrix;
long double ** zero_dist_matrix;

//Reads a matrix from the instance.
void readMatrix(long double **mat,  FILE *fd){
    int i,j,a;

    for(i=0;i<PermuSize;i++){
        for(j=0;j<PermuSize;j++){
            fscanf(fd,"%d\t",&a);
            mat[i][j] = (long double) a;
        }
    }
}

//Evluates one repetition of the VFS.
void evalRandomSample(){

	  strct_optimo optimo;

	  optimo.opt_permu=malloc(PermuSize*sizeof(int));

    RandomPerm(optimo.opt_permu);
    optimo.opt_fitness=EvaluateQAP(0, optimo.opt_permu);

    VFS(&optimo,TabuSize,MaxEvals);

    //The results are printed in the following format: Instance, Algorithm, Repetition (seed), Solution, Fitness, Time.
    printf("%s , VFS , %d , ", Instance, Repetition);
		for (int i=0; i<PermuSize; i++) {
			  printf("%d ", optimo.opt_permu[i]);
		}
    printf(", %Lf", optimo.opt_fitness);

}

//Main function.
int main (int argc, char *argv[]) {

	  int i,j;
    FILE *fd;

    /*
     1.- Instance file
     2.- Repetition number (seed)
     3.- Tabu list size
     4.- Number of solution evaluations
     */
    if(argc != 5){
      printf("Incorrect format.\n");
      exit(1);
    }

    Instance = argv[1];
    Repetition = atoi(argv[2]);
    TabuSize = atoi(argv[3]);
    MaxEvals = atoi(argv[4]);

    srand(Repetition);

    fd=fopen(Instance,"r");

    if(fd==NULL){
      printf("The specified file doesn't exist.\n");
      exit(2);
    }

    fscanf(fd,"%d",&PermuSize);

    dist_matrix = malloc(PermuSize*sizeof(long double*));
    zero_dist_matrix = malloc(PermuSize*sizeof(long double*));
    flow_matrix = malloc(PermuSize*sizeof(long double*));
    zero_flow_matrix = malloc(PermuSize*sizeof(long double*));
    for ( i=0; i<PermuSize; i++) {
		    dist_matrix[i] = (long double *)malloc(PermuSize*sizeof(long double));
        zero_dist_matrix[i] = (long double *)malloc(PermuSize*sizeof(long double));
        flow_matrix[i] = (long double *)malloc(PermuSize*sizeof(long double));
        zero_flow_matrix[i] = (long double *)malloc(PermuSize*sizeof(long double));
	  }

    readMatrix(dist_matrix, fd);
    readMatrix(flow_matrix, fd);

    fclose(fd);

    for(i=0; i<PermuSize; i++){
      for(j=0; j<PermuSize; j++){
        if(i!=j){
          zero_dist_matrix[i][j] = dist_matrix[i][j];
          zero_flow_matrix[i][j] = flow_matrix[i][j];
        }else{
          zero_dist_matrix[i][j] = 0.0;
          zero_flow_matrix[i][j] = 0.0;
        }
      }
    }

    struct timeval start, stop;
    double secs = 0;
    gettimeofday(&start, NULL);

    evalRandomSample();

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf(" , %f\n", secs);
}
