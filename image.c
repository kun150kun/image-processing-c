#ifndef IMAGE_H
#define IMAGE_H

#include "image.h"
#include <stdlib.h>

typedef struct{
    unsigned char *** data;
    int row,col,channel;
}Image;

Image* new_Image(int row,int col,int channel){
    Image * p = (Image *)malloc(sizeof(Image));
    p->row = row;
    p->col = col;
    p->channel = channel;
    
    p->data = (unsigned char ***)malloc(channel*sizeof(unsigned char**));
    int i,j;
    for(i = 0;i < channel;i++){
        p->data[i] = (unsigned char **) malloc(row * sizeof(unsigned char*));
        for(j = 0;j<row;j++){
            p->data[i][j] = (unsigned char *) malloc(col * sizeof(unsigned char));
        }
    }
    return p;
}

void destroy_Image(Image* Im){
    free(Im);
    return;
}

#endif
