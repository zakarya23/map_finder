all: map1 map2 

map1: tree.o readFile.o 
	gcc -Wall -o map1 tree.o readFile.o -g -lm 
	
map2: radius.o readFile.o 
	gcc -Wall -o map2 radius.o readFile.o -g -lm 
	
radius.o: radius.c tree.h 
	gcc -Wall -c -o radius.o radius.c -g 

tree.o: tree.c tree.h 
	gcc -Wall -c -o tree.o tree.c -g 
	
readFile.o: readFile.c readFile.h 
	gcc -Wall -c -o readFile.o readFile.c -g 
	
