#include "tree.h"
#include "readFile.h"

/* FOR MAP1 */

int
main(int argc, char *argv[]) {

	// Making an empty tree
	kdtree_t *kdtree; 
 	kdtree = initialise_kdtree(); 
	assert(kdtree);
	
	// Filling up the tree
	kdtree = fill_tree(argv[1], kdtree);
	assert(kdtree);
	
	// Finds all the locations of the key file provided
	find_locations(kdtree, argv[2]); 
	free(kdtree); 
}


void 
find_locations(kdtree_t *kdtree, char *file) {
	// Reading the locations file provided from stdin
	assert(file); 
	char buffer[100]; 
	while(fgets(buffer, 100, stdin)) {
			// Getting rid of the newline character found while using fgets()
			if (buffer[strlen(buffer) - 1] == '\n'){
				buffer[strlen(buffer) - 1] = '\0'; 
			}
			
			// Separating the coordinates separated by spaces
 			char *coord = strtok(buffer, " "); 
			int count = 0; 
			double x, y; 
			// Assigning x and y values 
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
			
			// Target is the x and y we are going to search for 
			node_t *target = (node_t *)malloc(3 * sizeof(node_t)); 
			assert(target); 
			target = NULL; 
			// Smallest distance is set to the one the target has from root point 
			double smallest = calculate_distance(atof(kdtree->root->data->x), atof(kdtree->root->data->y), x, y);
			assert(kdtree->root); 
			
			// For the comparison pointer to be passed in the function 
			int cmp = 0; 
			int *comp; 
			comp = &cmp;  
			// Calculates the smallest distance 
 			closest_point(kdtree->root, x, y, smallest, &target, comp); 
			// If node is found this prints it out. 
 			recurse_print(target, x, y, file, comp);
// 			free(target); 
		}
}

void 
recurse_print(node_t *first, double x, double y, char *output, int *comparisons) {
	FILE *outFile = fopen(output, "a"); 
	assert(outFile); 
	while (first) {
		fprintf(outFile, "%f %f  --> Census year: %s || Block ID: %s || Property ID: %s || Base Property ID: %s || CLUE small area: %s ||  Trading Name: %s ||  Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: (%s, %s) ||\n\n",x, y, first->data->year, first->data->blockID, first->data->propertyID, first->data->basePropertyID, first->data->smallArea, first->data->tradingName , first->data->industryCode, first->data->industryDescription, first->data->x, first->data->y, first->data->y, first->data->x); 
		first = first->list; 
	}
	printf("%f %f ---> %d\n", x, y, *comparisons); 
	fclose(outFile); 
}


kdtree_t 
*initialise_kdtree() {
	// Function makes a new empty tree
	kdtree_t *kdtree; 
	kdtree = malloc(sizeof(*kdtree)); 
	assert(kdtree); 
	kdtree->root = NULL; 
	return kdtree; 
}

void
closest_point(node_t *root, double x, double y, double smallest, node_t **node, int *count) {
	*count = *count + 1; 
	if (root != NULL) {
		double dis = calculate_distance(atof(root->data->x), atof(root->data->y), x, y);
		if (dis <= smallest) {
			smallest = dis; 
			*node = root;
		}
		
		if (atof(root->data->x) < x && root->left) {
			closest_point(root->left, x, y, smallest, node, count); 
		}
		else if (root->right) {
			closest_point(root->right, x, y, smallest, node, count); 
		}
	}
}


double
calculate_distance(double startX, double startY, double endX, double endY) {
	return (sqrt(((endX - startX) * (endX - startX)) + ((endY - startY) * (endY - startY)))); 
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
	
	// If a node has no left, right or list pointers then we free the node so we dont lose it before. 
	if (root) { 
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

