#ifndef DICTH
#define DICTH
#define SIZE 50
#define TRUE 1 
#define FALSE 0 

#include "list.h"
#include <stdio.h>
#include <string.h>

#include <assert.h> 
#include <stdlib.h>


void keySearch(node_t *first, char *key, FILE *out); 
void insert(list_t *list, char *variable, data_t *dataBlob, int record); 

#endif


