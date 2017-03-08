#ifndef JPEG_IMIO_H
#define JPEG_IMIO_H

#include "image.h"
/*
 * Read the image from the file and transform the image to the matrix.
 */
int read_image(char * filename,Image **Im);
void buffer_to_Im(Image* Im, unsigned char** buffer, int line);


int write_image(char * filename,Image **Im,int quality);
void Im_to_buffer(Image* Im, unsigned char** buffer, int line);


#endif
