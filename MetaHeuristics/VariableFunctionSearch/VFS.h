#ifndef __COM_H_
#define __COM_H_


typedef struct strct_optimo{
	int *opt_permu;
	long double opt_fitness;
}strct_optimo;

void VFS(strct_optimo* optimo, int tabu_size, int max_evals);
#endif
