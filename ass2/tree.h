#ifndef TREEH
#define TREEH
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h> 

typedef struct node node_t;

typedef struct {
	char *x, *y;  
	char *year; 
	char *blockID; 
	char *propertyID; 
	char *basePropertyID; 
	char *smallArea;
	char *tradingName; 
	char *industryCode; 
	char *industryDescription; 
} data_t; 



struct node {
	data_t *data; 
	node_t *right; 
	node_t *left; 
	node_t *list; 
}; 


typedef struct {
	node_t *root; 
} kdtree_t; 


kdtree_t *initialise_kdtree(); 
void find_locations(kdtree_t *kdtree, char *file);  
node_t *insert_rec(node_t *root, node_t *leaf, int height, int elements); 
kdtree_t *insert_in_tree(kdtree_t *kdtree, data_t *data, int element_num); 
double calculate_distance(double startX, double startY, double endX, double endY); 
void recurse_print(node_t *first, double x, double y, char *output, int *comparisons); 
void free_tree(node_t *root); 
void free_node(node_t *root); 
void search_and_print(kdtree_t *kdtree, char *file); 
void closest_point(node_t *root, double x, double y, double smallest, node_t **node, int *count); 


#endif