#ifndef READFILEH
#define READFILEH

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"
#define COMMA ","
#define SIZE 128
#define TRUE 1 
#define FALSE 0 


kdtree_t *fill_tree(char *filename, kdtree_t *returnTree); 
void fill_data(int variableNum, char *variable, kdtree_t *tree, data_t *dataBlob);
node_t *attach_to_node(node_t *root, node_t *node); 

#endif