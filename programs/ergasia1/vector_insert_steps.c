#include <stdio.h>
#include <stdlib.h>
#include "ADTVector.h"

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

int main(int argc, char *argv[]){
        Vector vec = vector_create(1000, NULL);
int total; //previous, newtotal;
    for(int n = 1; n<1000 ; n++){
        vector_insert_last(vec, create_int(n));
        total = vector_steps(vec);
       // if( argv[1] == "real"){
            printf("%d, <steps for %d", total, n);
        //}
        //else{
          //  newtotal = (total + previous)/n;
            //printf("%d, <steps for %d", newtotal, n);       
            // }
       // previous = total;     
    }
}