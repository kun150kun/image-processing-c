#ifndef READ_IMAGE_H
#define READ_IMAGE_H

#include "read_image.h"
#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>


void buffer_to_Im(Image* Im, unsigned char** buffer, int line){
    int j,k;
    for(j = 0;j<Im->col;j++){
        for(k = 0;k<Im->channel;k++){
            Im->data[k][line][j]=buffer[0][j*3+k];
        }
    }
    return;
}

int read_image(char * filename,Image ** Im){
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    FILE * infile;
    
    unsigned char** buffer;
    int row_stride;
    
    if((infile = fopen(filename,"rb")) == NULL){
        fprintf(stderr, "can't open %s\n",filename);
        return 1;
    }
    
    cinfo.err = jpeg_std_error(& jerr);
    
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo,TRUE);
    jpeg_start_decompress(&cinfo);
    
    *Im = new_Image(cinfo.output_height, cinfo.output_width, cinfo.output_components);
    
    
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (unsigned char**)malloc(sizeof(unsigned char*) * cinfo.output_height);
    buffer[0] = (unsigned char*)malloc(sizeof(unsigned char) * row_stride);
    int line = 0;
    while(cinfo.output_scanline < cinfo.output_height){
        jpeg_read_scanlines(&cinfo, buffer, 1);
        
        buffer_to_Im(*Im,buffer,line);
        line ++;
    }
    
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    
    fclose(infile);
    return 0;
}





#endif
