//
//  main.c
//  LocalSearch_AllProblems
//
//  Created by Leticia Hernando on 3/5/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//


#include "local_search.h"
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
int PermuSize, FitnessFunction, Repetition;
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

void evalRandomSample(){

    int *permu;
	  strct_optimo optimo;

    /* Initialize the array and structures that will hold each permutation to test
    * and the solutions found
    */
	  permu=malloc(PermuSize*sizeof(int));
	  optimo.opt_permu=malloc(PermuSize*sizeof(int));

    // Conduct one local search on a Random permutation
    RandomPerm(permu);

    local_search(FitnessFunction,&optimo,permu);

    /*
    * Print the results: Instance, Function (0,1,2,3), Algorithm, Repetition (seed), Solution, Fitness, Time.
    */

    printf("%s , %d , LS , %d , ", Instance, FitnessFunction, Repetition);
		for (int i=0; i<PermuSize; i++) {
			  printf("%d ", optimo.opt_permu[i]);
		}
    printf(", %Lf", optimo.opt_fitness);

    // Free memory
	  free(permu);
}

int main (int argc, char *argv[]) {

	  int i,j;
    FILE *fd;

    /*
     1.- Instance file
     2.- Repetition number (seed)
     3.- Objective function: f (0), f_1 (1), f_2 (2), f_3 (3)
     */
    if(argc != 4){
      printf("Formato incorrecto.\n");
      exit(1);
    }

    Instance = argv[1];
    Repetition = atoi(argv[2]);
    FitnessFunction = atoi(argv[3]);


    srand(Repetition);

    /*
    * Open the file and read the problem matrices,
    *
    */
    fd=fopen(Instance,"r");

    if(fd==NULL){
      printf("El fichero especificado no existe.\n");
      exit(2);
    }

    // Read size of matrix
    fscanf(fd,"%d",&PermuSize);

    // Allocate memory for each matrix depending on size
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

    // Read the instance and close file
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

    //
    // Execution block
    // -------------------------------------------------------------------------------

    struct timeval start, stop;
    double secs = 0;
    gettimeofday(&start, NULL);

    evalRandomSample();

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf(" , %f\n", secs);
}
