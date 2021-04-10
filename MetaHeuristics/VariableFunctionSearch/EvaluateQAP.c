/*
 *  EvaluateFSPTotalFlowtime_NonOverwrite.c
 *  FSP_LocalSearch
 *
 *  Created by Leticia Hernando on 12/1/11.
 *  Copyright 2011 Intelligent System Group. All rights reserved.
 *
 */

#include "EvaluateQAP.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>



/*
* Evaluates the fitness of a solution of the QAP
*
*/
long double  evaluateQAP_function0(int *genes){
    int FactA, i ,j;
    long double fitness = 0.0;
    for (i=0;i<PermuSize;i++){
        FactA = genes[i];
        for (j=0;j<PermuSize;j++){
            fitness= fitness + dist_matrix[i][j] * flow_matrix[FactA][genes[j]];
        }
    }
    return(fitness);
}

/*
*
*
*/

long double evaluateComp_function1(int n, int i, int j, int p, int q, int genes_i, int genes_j){
  if(genes_i==p){
    if(genes_j==q) return n-3; //alfa
    else return -2; //gamma
  }else if(genes_i==q){
    if(genes_j==p) return 1-n; //beta
    else return 0; //delta
  }else if(genes_j==p){
    return 0; //delta
  }else if(genes_j==q){
    return -2; //gamma
  }else{
    return -1; //epsilon
  }
}

long double evaluateQAP_function1(int *genes){
    int n, i, j, p, q;
    long double fitness, distAB;

    n = PermuSize;
    fitness = 0.0;

	  for( i = 0; i < n;i++){
		    for( j = 0; j < n; j++){
             //if(i==j) continue;
             distAB = zero_dist_matrix[i][j];
             if(abs(distAB) < 0.000001) continue;
			       for( p = 0; p < n; p++){
				           for( q = 0; q < n; q++){
                        //if(p==q || flow_matrix[p][q] == 0) continue;
                        fitness = fitness + evaluateComp_function1(n, i, j, p, q, genes[i], genes[j]) * distAB * zero_flow_matrix[p][q];
				           }
             }
		    }
	  }

    fitness = fitness/(2*n);
    return (fitness);
}

/*
*
*
*/

long double evaluateComp_function2(int n, int i, int j, int p, int q, int genes_i, int genes_j){
  if(genes_i==p){
    if(genes_j==q) return n-3; //alfa
    else return 0; //gamma
  }else if(genes_i==q){
    if(genes_j==p) return n-3; //beta
    else return 0; //delta
  }else if(genes_j==p){
    return 0; //delta
  }else if(genes_j==q){
    return 0; //gamma
  }else{
    return 1; //epsilon
  }
}

long double evaluateQAP_function2(int *genes){
    int n, i, j, p, q;
    long double fitness, distAB;

    n = PermuSize;
    fitness = 0.0;

    for( i = 0; i < n;i++){
        for( j = 0; j < n; j++){
             //if(i==j) continue;
             distAB = zero_dist_matrix[i][j];
             if(abs(distAB) < 0.000001) continue;
             for( p = 0; p < n; p++){
                   for( q = 0; q < n; q++){
                        //if(p==q || flow_matrix[p][q] == 0) continue;
                        fitness = fitness + evaluateComp_function2(n, i, j, p, q, genes[i], genes[j]) * distAB * zero_flow_matrix[p][q];
                   }
             }
        }
    }
    fitness = fitness/(2*(n-2));
    return (fitness);
}

/*
*
*
*/

long double evaluateComp1_function3(int n, int i, int j, int p, int q, int genes_i, int genes_j){
  if(genes_i==p){
    if(genes_j==q) return 2*n-3; //alfa
    else return n-2; //gamma
  }else if(genes_i==q){
    if(genes_j==p) return 1; //beta
    else return 0; //delta
  }else if(genes_j==p){
    return 0; //delta
  }else if(genes_j==q){
    return n-2; //gamma
  }else{
    return -1; //epsilon
  }
}

long double evaluateComp2_function3(int i, int p, int genes_i){
	if(genes_i == p) return 1;
	else return 0;
}


long double evaluateQAP_function3(int *genes){
    int n, i, j, p, q;
    long double fitness, distAB;

    n = PermuSize;
    fitness = 0.0;

    for( i = 0; i < n;i++){
        for( j = 0; j < n; j++){
             //if(i==j) continue;
             distAB = zero_dist_matrix[i][j];
             if(abs(distAB) < 0.000001) continue;
             for( p = 0; p < n; p++){
                   for( q = 0; q < n; q++){
                        //if(p==q || flow_matrix[p][q] == 0) continue;
                        fitness = fitness + evaluateComp1_function3(n, i, j, p, q, genes[i], genes[j]) * distAB * zero_flow_matrix[p][q];
                   }
             }
        }
    }

    fitness = fitness/(n*(n-2));

    for (i=0;i<n;i++){
        distAB = dist_matrix[i][i];
        if(abs(distAB) < 0.000001) continue;
        for( p = 0; p < n; p++){
            //if(flow_matrix[p][p] == 0) continue;
            fitness = fitness + evaluateComp2_function3(i, p, genes[i]) * distAB * flow_matrix[p][p];
        }
    }

    return (fitness);
}

/*
*
*
*/
long double EvaluateQAP(int fitnessFunctionId, int * genes){
    long double fitness = INT_MAX;
    switch (fitnessFunctionId){
        case 1:
            fitness = evaluateQAP_function1(genes);
            break;
        case 2:
            fitness = evaluateQAP_function2(genes);
            break;
        case 3:
            fitness = evaluateQAP_function3(genes);
            break;
        default:
            fitness = evaluateQAP_function0(genes);
            break;
    }

    return fitness;
}
