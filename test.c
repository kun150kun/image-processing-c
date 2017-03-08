#include "jpeg_imio.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char * filename;
    filename = (char *)malloc(19*sizeof(char));
    strcpy(filename,"compressed_dog.jpg");
    Image * inIm;
    if(read_image(filename, &inIm) != 0){
        exit(1);
    }
    strcpy(filename,"new_dog.jpg");
    if(write_image(filename, &inIm, 100) != 0){
        exit(2);
    }
    free(filename);
    return 0;
}
