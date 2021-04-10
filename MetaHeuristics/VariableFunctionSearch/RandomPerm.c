#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RandomPerm.h"
#include "globals.h"

//Creates a random permutation.
void RandomPerm(int *sigma){

    int pos,i,aux;


    for (i=0; i<PermuSize; i++) {
        sigma[i]=i;
    }

    for (i=0; i<PermuSize-1; i++) {
		pos=rand()%(PermuSize-i)+i;
		aux=sigma[i];
		sigma[i]=sigma[pos];
		sigma[pos]=aux;
	}

}
