#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "tabu_search.h"
#include "list.h"
#include "EvaluateQAP.h"
#include "globals.h"

//Updates the best solution found.
void check(strct_optimo* optimo, strct_optimo* actual){
	if(actual->opt_fitness < optimo->opt_fitness){
			optimo->opt_fitness=actual->opt_fitness;
			memcpy(optimo->opt_permu, actual->opt_permu, sizeof(int)*PermuSize);
	}
}

//One step of the local search.
int local_search (int func, int *evals, int max_evals, int iteration, strct_optimo* actual, strct_optimo* optimo, List* tabu, int tabu_size){
		long double cost_neigh;
		int i, j, best_i, best_j, aux, cont;

		cont=0;
		//Exploration of the swap neighborhood.
	  for (i=0; i<PermuSize-1; i++) {
				if(*evals>=max_evals) break;

	      for (j=i+1; j<PermuSize; j++) {
						if(*evals>=max_evals) break;

	          aux=actual->opt_permu[i];
	          actual->opt_permu[i]=actual->opt_permu[j];
	          actual->opt_permu[j]=aux;

	          cost_neigh=EvaluateQAP(func, actual->opt_permu);
						*evals+=1;

						//The algorithm moves to the best solution.
						//Tabu movements are not considered.
	          if ((cont==0 || cost_neigh < actual->opt_fitness) && (!inlist(*tabu,i,j) || cost_neigh < optimo->opt_fitness)) {
	              best_i=i;
	              best_j=j;
	              actual->opt_fitness=cost_neigh;
								cont=1;
	          }

	          aux= actual->opt_permu[j];
	          actual->opt_permu[j]=actual->opt_permu[i];
	          actual->opt_permu[i]=aux;
	      }
	  }
		//The tabu list is updated.
	  if (cont) {
	      aux=actual->opt_permu[best_i];
	      actual->opt_permu[best_i]=actual->opt_permu[best_j];
	      actual->opt_permu[best_j]=aux;
				insertback(tabu,best_i,best_j);
				if(length(*tabu)>tabu_size) popfront(tabu);
				//The best solution found is updated.
				check(optimo, actual);
	  }
		return cont;
}

//Tabu search.
void tabu_search(int func, strct_optimo* optimo, int tabu_size, int max_evals){
		int evals,iteration,cost;
		strct_optimo actual;
		List* tabu;

		tabu = malloc(sizeof(List));
		initlist(tabu);

		actual.opt_permu=malloc(PermuSize*sizeof(int));
		memcpy(actual.opt_permu, optimo->opt_permu, sizeof(int)*PermuSize);
    actual.opt_fitness=EvaluateQAP(0, actual.opt_permu);

		iteration=1;
		evals=1;

		//Main local search.
		while(evals < max_evals){
				local_search(func, &evals, max_evals, iteration, &actual, optimo, tabu, tabu_size);
				iteration++;
		}
}
