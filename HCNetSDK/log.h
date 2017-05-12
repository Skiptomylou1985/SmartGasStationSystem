#pragma once
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  

#ifdef WIN32  
#include <windows.h>  
#else  
#include <unistd.h>       // linux下头文件  
#endif  

#define ActionLog "logs/action.txt"

void get_local_time(char* buffer);
long get_file_size(char* filename);
void write_log_file(char* buffer, unsigned buf_size);
void set_log_level(int loglevel);
