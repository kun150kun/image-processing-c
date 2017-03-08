#ifndef READ_IMAGE_H
#define READ_IMAGE_H

#include "image.h"

int read_image(char * filename,Image **Im);
void buffer_to_Im(Image* Im, unsigned char** buffer, int line);

#endif
