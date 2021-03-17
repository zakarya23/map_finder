#include "readFile.h"
#include "tree.h"
 

kdtree_t *fill_tree(char *filename, kdtree_t *returnTree) {
	assert(returnTree); 
	char buffer[512]; 
	char token[1024];
	int count = 0; 
	int row = 0; 
	int field = 0; 
	int quotes = FALSE; 
	int token_pos = 0; 
	int i = 0; 
	
	// Opening the file to fill in the tree
	FILE *fptr = fopen(filename, "r"); 
	assert(fptr); 
		
	while (fgets(buffer, 512, fptr)) {
		// Reading through line by line
		// Each time a new data_t is made which will be attached to the node. 
		data_t *dataBlob; 
		dataBlob = (data_t *)malloc(sizeof(data_t));
		assert(dataBlob); 
		
		row++; 
		count++;
		
		// header row 
		if (row == 1) {
			continue; 
		}
		
		field = 0; 
		i = 0; 

		// As I didnt understand the solution provided and my ass1 wasnt working perfectly so I have this small section of code 
		// that I used to make sure I was reading the file correctly. Only the do-while loop. :) 
		// This is for making sure the quotes and commas dont affect the input
		do {
			token[token_pos++] = buffer[i]; 
			if (!quotes && (buffer[i] == ',' || buffer[i] == '\n')) {
				token[token_pos - 1] = 0; 
				token_pos = 0;
				fill_data(field++, token, returnTree, dataBlob); 
				
			}
			
			if (buffer[i] == '"' && buffer[i + 1] != '"') {
                token_pos--;
                quotes = !quotes;
            }
			
			if (buffer[i] == '"' && buffer[i + 1] == '"'){
                i++;
			}
		} while (buffer[++i]);
	}

	
	fclose(fptr); 
	free(fptr); 
	return returnTree; 
}

node_t 
*insert_rec(node_t *root, node_t *leaf, int height, int elements) {
	// This function inserts recursively into the tree. 
	// Calculating height to see if we are comparing x or y. 
 	int level = height % (elements+1); 

	if (level % 2 == 0) {
		// Comparing the x values 
		if (root == NULL) {	
			return leaf; 
		}
		else if (atof(root->data->x) > atof(leaf->data->x))   {
			root->left = insert_rec(root->left, leaf, height + 1, elements); 
		}
		else if (atof(root->data->x) < atof(leaf->data->x)) { 
			root->right = insert_rec(root->right, leaf, height + 1, elements); 
		}
		else {
			// If x is the same, we check y and if they equal we attach it to node in the form of a list. 
			if (atof(root->data->y) == atof(leaf->data->y)) {
				root->list = attach_to_node(root->list, leaf); 
			}
			else {
				root->right = insert_rec(root->right, leaf, height + 1, elements); 
			}
		}
		return root; 
	}
	
	else {
		if (root == NULL) {	
			return leaf; 
		}
		else if (atof(root->data->y) > atof(leaf->data->y))  {
			root->left = insert_rec(root->left, leaf, height + 1, elements); 
		}
		else if (atof(root->data->y) < atof(leaf->data->y)){ 
			root->right = insert_rec(root->right, leaf, height + 1, elements); 
		}
		else {
			// If y is the same, we check x and if they equal we attach it to node in the form of a list. 
			if (atof(root->data->x) == atof(leaf->data->x)) {
				root->list = attach_to_node(root->list, leaf); 
			}
			else {
				root->right = insert_rec(root->right, leaf, height + 1, elements); 
			}
		}
		return root; 
	}
}

node_t
*attach_to_node(node_t *root, node_t *node) {
	// This is when x and y values match and we recursivlely attacth it to the node. 
	if (root == NULL) {
		return node; 
	}
	return attach_to_node(root->list, node); 	
}

kdtree_t 
*insert_in_tree(kdtree_t *kdtree, data_t *data, int element_num) {
	// Makes a new node to be recursivley added in the tree. 
	node_t *new = (node_t *)malloc(sizeof(node_t));  
	assert(new); 
	assert(kdtree);
	new->left = new->right = NULL; 
	new->data = data; 
	new->list = NULL; 
	kdtree->root = insert_rec(kdtree->root, new, 0, element_num); 
	return kdtree; 
}

void fill_data(int variableNum, char *variable, kdtree_t *tree, data_t *dataBlob) {
	// This is for separating the different columns in the csv file. 
	assert(tree && dataBlob); 
	if (variableNum == 0) {
		dataBlob->year = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->year); 
		strcpy(dataBlob->year, variable); 
	}
	
	if (variableNum == 1) {
		dataBlob->blockID = (char *)malloc(SIZE * sizeof(char));
		assert(dataBlob->blockID);
		strcpy(dataBlob->blockID, variable); 
	}
	
	if (variableNum == 2) {
		dataBlob->propertyID = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->propertyID); 
		strcpy(dataBlob->propertyID, variable);  
	}
	
	if (variableNum == 3) {
		dataBlob->basePropertyID = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->basePropertyID); 
		strcpy(dataBlob->basePropertyID, variable); 
	}
	
	if (variableNum == 4) {
		dataBlob->smallArea = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->smallArea); 
		strcpy(dataBlob->smallArea, variable); 
	}
	if (variableNum == 5) {
		dataBlob->tradingName = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->tradingName); 
		strcpy(dataBlob->tradingName, variable); 
		
	}
	if (variableNum == 6) {
		dataBlob->industryCode = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->industryCode); 
		strcpy(dataBlob->industryCode, variable); 
	}
	
	if (variableNum == 7) {
		dataBlob->industryDescription = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->industryDescription); 
		strcpy(dataBlob->industryDescription, variable);
	}
	
	if (variableNum == 8) {
		dataBlob->x = (char *)malloc(SIZE* sizeof(char)); 
		assert(dataBlob->x); 
		strcpy(dataBlob->x, variable); 	
	}
	if (variableNum == 9) {
		dataBlob->y = (char *)malloc(SIZE * sizeof(char)); 
		assert(dataBlob->y); 
		strcpy(dataBlob->y, variable); 
	}
	if (variableNum == 10) {
		// Once we have filled in the data we add it into the tree.
		insert_in_tree(tree, dataBlob, 0); 
	}
}

