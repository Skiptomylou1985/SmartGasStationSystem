#pragma once
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
extern "C"
{
#include "jpeglib.h"
}
#include <setjmp.h> 
#ifdef WIN32  
#include <windows.h>  
#else  
#include <unistd.h>       // linux下头文件  
#endif  


void savebmp(unsigned char * pdata, char * bmp_file, int width, int height);
void get_local_time(char* buffer);
long get_file_size(char* filename);
void write_log_file(char* filename, long max_size, char* buffer, unsigned buf_size);
void save_image_file(char* filename, char *imageBuff, long imageLenth);
//void encode_jpeg_file(char * filename, int quality, unsigned char *pbuffer, int image_height, int image_width);
