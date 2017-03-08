#include "read_image.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char * filename;
    filename = (char *)malloc(19*sizeof(char));
    strcpy(filename,"compressed_dog.jpg");
    Image * inIm;
    read_image(filename, &inIm);
    
    return 0;
}
