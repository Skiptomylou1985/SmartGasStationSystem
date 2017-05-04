#include "log.h"
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h> 



void get_local_time(char* buffer)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d %03d", st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}

/*
获得文件大小
@param filename [in]: 文件名
@return 文件大小
*/
long get_file_size(char* filename)
{
	long length = 0;
	FILE *fp = NULL;

	fp = fopen(filename, "rb");
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}

	return length;
}
void write_log_file(char* fileName, long max_size, char* buffer, unsigned buf_size)
{
	char filename[128] = "dlllog\\";
	strcpy(filename + strlen(filename), fileName);
	if (filename != NULL && buffer != NULL)
	{
		//文件超过最大限制, 删除  
		long length = get_file_size(filename);

		if (length > max_size)
		{
			_unlink(filename); // 删除文件  
		}

		// 写日志  
		{
			FILE *fp;
			fp = fopen(filename, "at+");
			if (fp != NULL)
			{
				char now[32];
				memset(now, 0, sizeof(now));
				get_local_time(now);
				fwrite(now, strlen(now) + 1, 1, fp);
				fwrite(buffer, buf_size, 1, fp);
				fwrite("\n", 2, 1, fp);
				fclose(fp);
				fp = NULL;
			}
		}
	}
}
