#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
    unsigned char *** data;
    int row,col,channel;
}Image;

Image* new_Image(int row,int col,int channel);

#endif
