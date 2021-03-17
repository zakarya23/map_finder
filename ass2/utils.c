/*
    Simple utilities implementation.
*/
#include <stdio.h>
#include <string.h>


/*
    Simple utilities.
*/
#include <stdio.h>

/*
    Small wrapper around getline which drops the newline if it
    is present.
*/
ssize_t getlineClean(char **lineptr, size_t *n, FILE *stream);


ssize_t getlineClean(char **lineptr, size_t *n, FILE *stream){
    ssize_t ret_val = getline(lineptr, n, stream);
    if(ret_val != (-1) && strlen(*lineptr) > 0 && 
       (*lineptr)[strlen(*lineptr) - 1] == '\n'){
        (*lineptr)[strlen(*lineptr) - 1] = '\0';
    }
    if(ret_val != (-1) && strlen(*lineptr) > 0 && 
       (*lineptr)[strlen(*lineptr) - 1] == '\r'){
        (*lineptr)[strlen(*lineptr) - 1] = '\0';
    }
    return ret_val;
}

