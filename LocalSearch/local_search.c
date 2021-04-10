/*
 *  local_search.c
 *  LocalSearch
 *
 *  Created by Leticia Hernando on 3/16/11.
 *  Copyright 2011 Intelligent System Group. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "local_search.h"
#include "EvaluateQAP.h"
#include "globals.h"

//Local search under the swap neighborhood starting from a random permutation. The specified objective function is used (f, f_1, f_2, f_3).
void local_search (int fitnessFunctionId,  strct_optimo* optimo, int * permu){

	long double fitness,cost_opt,cost_neigh;
	int  * aux_perm, *opt, *opt_mejor;
	int seguir,j,k,z,aux,m;
	int best_k, best_j,best_m;


	aux_perm=malloc(PermuSize*sizeof(int));
	memcpy(aux_perm, permu, sizeof(int)*PermuSize);

	fitness=EvaluateQAP(fitnessFunctionId, permu);
	cost_opt=fitness;

    seguir=1;
    while (seguir) {
        seguir=0;
        for (k=0; k<PermuSize-1; k++) {
            for (j=k+1; j<PermuSize; j++) {
                aux=aux_perm[k];
                aux_perm[k]=aux_perm[j];
                aux_perm[j]=aux;

                cost_neigh=EvaluateQAP(fitnessFunctionId, aux_perm);

								//The algorithm moves to the best solution (Greedy).
                if (cost_neigh < cost_opt) {
                    best_k=k;
                    best_j=j;
                    cost_opt=cost_neigh;
                    seguir=1;
                }
                aux= aux_perm[j];
                aux_perm[j]=aux_perm[k];
                aux_perm[k]=aux;
            }
        }
        if (seguir) {
            aux=aux_perm[best_k];
            aux_perm[best_k]=aux_perm[best_j];
            aux_perm[best_j]=aux;
            cost_opt=EvaluateQAP(fitnessFunctionId, aux_perm);
        }
    }

	for (z=0;z<PermuSize;z++)
		optimo->opt_permu[z]=aux_perm[z];
    optimo->opt_fitness=cost_opt;

	free(aux_perm);
}
