#ifndef JPEG_IMIO_H
#define JPEG_IMIO_H

#include "jpeg_imio.h"
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
    
    if(*Im == NULL)
        *Im = new_Image(cinfo.output_height, cinfo.output_width, cinfo.output_components);
    else{
        destroy_Image(*Im);
        *Im = new_Image(cinfo.output_height, cinfo.output_width, cinfo.output_components);
    }
    
    
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

void Im_to_buffer(Image* Im, unsigned char** buffer, int line){
    int j,k;
    for(j = 0;j<Im->col;j++){
        for(k = 0;k<Im->channel;k++){
            buffer[0][j*3+k] = Im->data[k][line][j];
        }
    }
    return;
}

int write_image(char * filename,Image **Im,int quality){
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    FILE * outfile;
    unsigned char **row_pointer = (unsigned char **) malloc(sizeof(unsigned char *));
    row_pointer[0] = (unsigned char*)malloc(sizeof(unsigned char) * (*Im)->row * (*Im)->channel);
    int row_stride;
    
    cinfo.err = jpeg_std_error(& jerr);
    jpeg_create_compress(&cinfo);
    
    if((outfile = fopen(filename,"wb"))==NULL){
        fprintf(stderr, "can't open %s\n",filename);
        return 1;
    }
    jpeg_stdio_dest(&cinfo,outfile);
    
    cinfo.image_width = (*Im)->row;
    cinfo.image_height = (*Im)->col;
    cinfo.input_components = (*Im)->channel;
    cinfo.in_color_space = JCS_RGB;
    
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo,quality,TRUE);
    
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = (*Im)->row * (*Im)->channel;
    int line = 0;
    while(cinfo.next_scanline < cinfo.image_height){
        Im_to_buffer(*Im, row_pointer,line);
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
        line ++;
    }
    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
    return 0;
}




#endif
