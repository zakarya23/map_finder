#include "dict.h"
#include "list.h"


int main(int argc, char *argv[]) {
	char line[512]; 
	FILE *fptr = fopen(argv[1], "r");
	assert(fptr); 
	int rowNumber = 0;  
	list_t *list;  
	FILE *output = fopen(argv[2], "a");
	assert(output); 
	int record = 0;
	char comma[2] = ","; 
	char buffer[100]; 
	
	
	// Initialises the list
	list = make_empty_list(); 
	
	// Starts reading line by line from the CSV file 
	while(fgets(line, 512, fptr)) {
		
		rowNumber++; 
		
		// Skipping over the title line 
		if (rowNumber == 1){
			continue; 
		}
	
		// Separating by commas 
		char *variable = strtok(line, comma); 
		data_t *dataBlob; 
			
		// Allocating space for the data 
		dataBlob = (data_t *)malloc(SIZE * sizeof(*dataBlob));
		assert(dataBlob); 
		
		// Going through each field
		insert(list, variable, dataBlob, record); 
		
	}
	
	// If keys were provided in the terminal. 
	if (argv[3] != NULL) {
		for (int k = 3; argv[k] != NULL;k++) {
			keySearch(list->head, argv[k], output); 
		}
	}
	// If a file was provided 
	else {
		while(fgets(buffer, 100, stdin)){
			// Getting rid of the newline character found while using fgets()
			if (buffer[strlen(buffer) - 1] == '\n'){
				buffer[strlen(buffer) - 1] = '\0'; 
			}
			keySearch(list->head, buffer, output);
		}
	}
	
	
	
	// Freeing all memory being used. 
	free_list(list); 
	fclose(fptr); 
	fclose(output); 
 
	return 0;
}


void insert(list_t *list, char *variable, data_t *dataBlob, int record){
	int variableNum = 0; 
	char *des; 
	int quoteCount = 0;  
	int quote = FALSE; 
	char comma[2] = ","; 
	int letterNum = 0; 
	
	while (variable) {
			if (variableNum == 0) {
				dataBlob->year = (char *)malloc(SIZE * sizeof(*dataBlob->year)); 
				assert(dataBlob->year); 
				strcpy(dataBlob->year, variable); 
			}
			
			if (variableNum == 1) {
				dataBlob->blockID = (char *)malloc(SIZE * sizeof(*dataBlob->blockID));
				assert(dataBlob->blockID);
				strcpy(dataBlob->blockID, variable); 	
			}
			
			if (variableNum == 2){
				dataBlob->propertyID = (char *)malloc(SIZE * sizeof(*dataBlob->propertyID)); 
				assert(dataBlob->propertyID); 
				strcpy(dataBlob->propertyID, variable); 
			}
			
			if (variableNum == 3) {
				dataBlob->basePropertyID = (char *)malloc(SIZE * sizeof(*dataBlob->basePropertyID)); 
				assert(dataBlob->basePropertyID); 
				strcpy(dataBlob->basePropertyID, variable); 
			}

			if (variableNum == 4) {
				dataBlob->smallArea = (char *)malloc(SIZE * sizeof(*dataBlob->smallArea)); 
				assert(dataBlob->smallArea); 
				strcpy(dataBlob->propertyID, variable); 
			}
			
			if (variableNum == 5) {
				dataBlob->key = (char *)malloc(SIZE * sizeof(*dataBlob->key)); 
				assert(dataBlob->key); 
				strcpy(dataBlob->key, variable); 
			}
			
			if (variableNum == 6) {
				dataBlob->industryCode = (char *)malloc(SIZE * sizeof(*dataBlob->industryCode)); 
				assert(dataBlob->industryCode); 
				strcpy(dataBlob->industryCode, variable); 
				// Allocating space for the description here so it doesnt over write
				des = malloc(SIZE * SIZE * sizeof(*des));
				assert(des); 
			}

			if (variableNum == 7) {
				for (int a = 0; variable[a] != '\0';a++){
					char letter = variable[a];
					if (letter == '"' && a == 0) {
						quote = TRUE; 
						quoteCount++; 
					}
					else if (letter == '"') {
						quote = TRUE; 
						quoteCount++; 
					}
					else {
						des[letterNum] = letter;
						letterNum++; 
					}
					if (quote && quoteCount == 1){
						quote = FALSE; 
					}
					if (quote && quoteCount == 2){
						dataBlob->industryDescription = (char *)malloc(SIZE * sizeof(*dataBlob->industryDescription)); 
							
						assert(dataBlob->industryDescription); 
						strcpy(dataBlob->industryDescription, des); 
						quote = FALSE; 
						}
				}

				if (quoteCount == 1){
					des[letterNum] = ','; 
					letterNum++; 
					variableNum = 6; 
				}
				else {
					dataBlob->industryDescription = (char *)malloc(SIZE * sizeof(*dataBlob->industryDescription)); 
					assert(dataBlob->industryDescription); 
					strcpy(dataBlob->industryDescription, des); 
				}	
			}
			
			if (variableNum == 8) {
				// Making them zero again so in next loop it starts from start
				letterNum = 0;
				quoteCount = 0; 
				dataBlob->xCoor = (char *)malloc(SIZE * sizeof(*dataBlob->xCoor)); 
				assert(dataBlob->xCoor); 
				strcpy(dataBlob->xCoor, variable); 	
			}
			
			if (variableNum == 9) {
				dataBlob->yCoor = (char *)malloc(SIZE * sizeof(*dataBlob->yCoor)); 
				assert(dataBlob->yCoor); 
				strcpy(dataBlob->yCoor, variable); 
			}

			if (variableNum == 10) {
				// Do nothing
			}
				
			if (variableNum == 11) {
				// If first record then insert at head 
				if (record == 0){
				list = insert_at_head(list, dataBlob); 	
				record++; 
				}
				// Otherwise we keep inserting at the foot as a list needs a foot too. 
				else {
					list = insert_at_foot(list, dataBlob); 	
				}
			}
			variableNum++; 
			variable = strtok(NULL, comma);  	
		}
		variableNum = 0; 
}



void keySearch(node_t *first, char *key, FILE *out) {
	int found = FALSE; 
	while (first){
		if (strcmp(first->data->key, key) == 0){
			fprintf(out, "In a %s --> Census year: %s || Block ID: %s || Property ID: %s || Base Property ID: %s || CLUE small area: %s ||  Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: (%s, %s) ||\n\n", key, first->data->year, first->data->blockID, first->data->propertyID, first->data->basePropertyID, first->data->smallArea, first->data->industryCode, first->data->industryDescription, first->data->xCoor, first->data->yCoor, first->data->yCoor, first->data->xCoor); 
			found = TRUE; 
		}
		first = first->next; 
	}
	
	if (!found){
		fprintf(out, "In a %s --> NOT FOUND\n\n", key);  
	}
 
}
	
	
	

	
	




