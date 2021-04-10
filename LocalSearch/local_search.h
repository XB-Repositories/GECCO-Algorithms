/*
 *  local_search.h
 *  LocalSearch
 *
 *  Created by Leticia Hernando on 3/16/11.
 *  Copyright 2011 Intelligent System Group. All rights reserved.
 *
 */



#ifndef __COM_H_
#define __COM_H_


typedef struct strct_optimo{
	int *opt_permu;
	long double opt_fitness;
}strct_optimo;

void local_search (int fitnessFunctionId,strct_optimo* optimo, int * permu);

#endif
