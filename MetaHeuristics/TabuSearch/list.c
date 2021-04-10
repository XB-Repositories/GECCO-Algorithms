/*
 *  list.c
 *  prueba_listas
 *
 *  Created by Leticia Hernando on 11/8/11.
 *  Copyright 2011 Intelligent System Group. All rights reserved.
 *
 */

#include "list.h"
#include "RandomPerm.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>



void initlist(List *ilist) {
	ilist->head = 0;
}


void insertback(List *ilist, int i, int j) {
	Listitem *ptr;
	Listitem *newitem;

	newitem = (Listitem *)malloc(sizeof(Listitem));
	newitem->i = i;
	newitem->j = j;
  newitem->next = 0;

	if (!ilist->head) {
		ilist->head = newitem;
		return;
	}

	ptr = ilist->head;
	while (ptr->next) {
		ptr = ptr->next;
	}
	ptr->next = newitem;
}

void popfront(List *ilist){
	if(ilist->head) ilist->head = ilist->head->next;
}

long long int length(List ilist){
	Listitem *ptr;
	long long int count = 1;

	if (!ilist.head) return 0;
	ptr = ilist.head;
	while (ptr->next) {
		ptr = ptr->next;
		count++;
	}
	return count;
}

int inlist(List ilist, int i, int j){
	Listitem *ptr;
	ptr = ilist.head;
	while (ptr) {
		if(i==ptr->i && j==ptr->j)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

void destroy(List *ilist) {
	Listitem *ptr1,*ptr2;

	if (!ilist->head) return;

	ptr1 = ilist->head;
	while (ptr1) {
		ptr2 = ptr1;
		ptr1 = ptr1->next;

		free(ptr2);
	}
	ilist->head = 0;
}
