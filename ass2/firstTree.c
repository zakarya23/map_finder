#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h> 
#include "tree.h"
#include "readFile.h"
#include <math.h> 

#define FALSE 0 
#define TRUE 1 

// search tree 
	// implemet a blank pointer to a node 
	// Traverse tree calculating smallest distnace at every point 
	// Whenever the distance is the smallest make the blank pointer point at that node 
	// If whole tree is traversed then print out info at that node 

int
main(int argc, char *argv[]) {

// 	if(argc < 3){
//         fprintf(stderr, "Incorrect arguments\n");
//         fprintf(stderr, "Run in the form\n");
//         fprintf(stderr, "\tdict datafile outputfile < inputfile\n");
//         exit(1);
//     }

	// Making an empty tree
	kdtree_t *kdtree; 
 	kdtree = initialise_kdtree(); 
	assert(kdtree);
	
	// Filling up the tree
	kdtree = readFile(argv[1], kdtree);
	assert(kdtree);
	
	node_t *first; 
 	first = malloc(sizeof(*first)); 
	assert(first); 
	
	if (argv[3] != NULL) {
		for (int k = 3; argv[k] != NULL;k++) {
			search_and_print(kdtree, argv[k], first);  
		}
	}
	// If a file was provided 
	else {
		search_and_print(kdtree, argv[2], first);    
	}
 	free_tree(kdtree->root); 
	free(kdtree); 
}


void search_and_print(kdtree_t *kdtree, char *file, node_t *node) {
	char buffer[100]; 
 
	while(fgets(buffer, 100, stdin)){
			double smallest = 1000; 
			// Getting rid of the newline character found while using fgets()
			if (buffer[strlen(buffer) - 1] == '\n'){
				buffer[strlen(buffer) - 1] = '\0'; 
			}
 			char *coord = strtok(buffer, " "); 
			int count = 0; 
			double x, y; 
			while (coord){
				if (count == 0){
					x = atof(coord); 
					count++; 
				}
				else {
					y = atof(coord); 
				}
				coord = strtok(NULL, " "); 
			} 
			search_tree(kdtree->root, x, y, smallest, first); 
			recurse_print(node, x, y, file); 
		}
}

void 
recurse_print(node_t *first, double x, double y, char *output) {
	FILE *outFile = fopen(output, "a"); 
	
	while (first) {
		fprintf(outFile, "%f %f  --> Census year: %s || Block ID: %s || Property ID: %s || Base Property ID: %s || CLUE small area: %s ||  Trading Name: %s ||  Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: (%s, %s) ||\n\n",x, y, first->data->year, first->data->blockID, first->data->propertyID, first->data->basePropertyID, first->data->smallArea, first->data->tradingName , first->data->industryCode, first->data->industryDescription, first->data->x, first->data->y, first->data->y, first->data->x); 
		first = first->list; 
	}
	fclose(outFile); 
}

kdtree_t 
*initialise_kdtree() {
	kdtree_t *kdtree; 
	kdtree = malloc(sizeof(*kdtree)); 
	assert(kdtree); 
	kdtree->root = NULL; 
	return kdtree; 
}


double
calculate_distance(double startX, double startY, double endX, double endY) {
	return (sqrt(((endX - startX) * (endX - startX)) + ((endY - startY) * (endY - startY)))); 
}

void 
search_tree(node_t *root, double x, double y, double smallest, node_t *node) {
	
	if (root) {
		double dis = calculate_distance(atof(root->data->x), atof(root->data->y), x, y);
		if (dis <= smallest) {
			smallest = dis; 
			*node = *root; 
			printf("aaa %f \n", smallest); 
		}
		search_tree(root->left, x, y, smallest, node); 
		search_tree(root->right, x, y, smallest, node); 
		
	}

void 
free_tree(node_t *root) {
	if (root->list) {
		free_tree(root->list); 
	}
	
	if (root->left) {
		free_tree(root->left);
	}
	
	if (root->right) {
		free_tree(root->right); 
	}
	
	if (root) { 
	
		if (root->list) {
// 			printf("Dd "); 
// 			while (root) {
// 				if (root) {
// 					free_node(root);
// 				}
// 				root = root->list; 
// 			}
		}
	
// 	printf("%s %s\n", root->data->x, root->data->y); 
	 
		free_node(root); 
		}
	
}


void 
free_node(node_t *root) {
	free(root->data->year); 
	free(root->data->blockID); 
	free(root->data->propertyID); 
	free(root->data->basePropertyID); 
	free(root->data->smallArea); 
	free(root->data->tradingName); 
	free(root->data->industryCode); 
	free(root->data->industryDescription); 
	free(root->data->x); 
	free(root->data->y); 
	free(root->data);
	free(root); 
}






