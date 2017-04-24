#include "log.h"
#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h> 
#include <windows.h>
#include <atlimage.h>

extern "C"
{
#include "jpeglib.h"
}
#include <setjmp.h> 

typedef struct {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BMPFILEHEADER_T;

typedef struct {
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BMPINFOHEADER_T;

void ContructBhh(int nWidth, int nHeight, BITMAPFILEHEADER& bhh) //add 2010-9-04  
{
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8; //每行实际占用的大小（每行都被填充到一个4字节边界）  
	bhh.bfType = ((WORD)('M' << 8) | 'B');  //'BM'  
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;
	bhh.bfReserved1 = 0;
	bhh.bfReserved2 = 0;
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

}


//构建BMP文件信息头  
void ConstructBih(int nWidth, int nHeight, BITMAPINFOHEADER& bih)
{
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8;

	bih.biSize = 40;       // header size  
	bih.biWidth = nWidth;
	bih.biHeight = nHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;     // RGB encoded, 24 bit  
	bih.biCompression = BI_RGB;   // no compression 非压缩  
	bih.biSizeImage = widthStep*nHeight * 3;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

}




//void encode_jpeg_file(char * filename, int quality,unsigned char *pbuffer, int image_height, int image_width)
//{
//	struct jpeg_compress_struct cinfo;
//	struct jpeg_error_mgr jerr;
//	FILE * outfile;        /* target file */
//	JSAMPROW row_pointer[1];    /* pointer to JSAMPLE row[s] */
//	int row_stride;        /* physical row width in image buffer */
//	cinfo.err = jpeg_std_error(&jerr);
//	jpeg_create_compress(&cinfo);
//
//	if ((outfile = fopen(filename, "wb")) == NULL) {
//		fprintf(stderr, "can't open %s\n", filename);
//		exit(1);
//	}
//	jpeg_stdio_dest(&cinfo, outfile);
//
//	cinfo.image_width = image_width;
//	cinfo.image_height = image_height;
//	cinfo.input_components = 3;
//	cinfo.in_color_space = JCS_RGB;
//
//	jpeg_set_defaults(&cinfo);
//
//	jpeg_set_quality(&cinfo, quality, TRUE);
//
//	jpeg_start_compress(&cinfo, TRUE);
//
//	row_stride = image_width * 3;
//
//	while (cinfo.next_scanline < cinfo.image_height)
//	{
//		/* jpeg_write_scanlines expects an array of pointers to scanlines.
//		* Here the array is only one element long, but you could pass
//		* more than one scanline at a time if that's more convenient.
//		*/
//		row_pointer[0] = &pbuffer[cinfo.next_scanline * row_stride];
//		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
//	}
//	jpeg_finish_compress(&cinfo);
//	fclose(outfile);
//	jpeg_destroy_compress(&cinfo);
//}

//void savebmp(unsigned char * pdata, char * bmp_file, int width, int height)
//{      //分别为rgb数据，要保存的bmp文件名，图片长宽  
//	int size = width*height * 3 * sizeof(char); // 每个像素点3个字节  
//												// 位图第一部分，文件信息  
//	BMPFILEHEADER_T bfh;
//	bfh.bfType = (WORD)0x4d42;  //bm  
//	bfh.bfSize = size  // data size  
//		+ sizeof(BMPFILEHEADER_T) // first section size  
//		+ sizeof(BMPINFOHEADER_T) // second section size  
//		;
//	bfh.bfReserved1 = 0; // reserved  
//	bfh.bfReserved2 = 0; // reserved  
//	bfh.bfOffBits = sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T);//真正的数据的位置  
//
//																	  // 位图第二部分，数据信息  
//	BMPINFOHEADER_T bih;
//	bih.biSize = sizeof(BMPINFOHEADER_T);
//	bih.biWidth = width;
//	bih.biHeight = -height;//BMP图片从最后一个点开始扫描，显示时图片是倒着的，所以用-height，这样图片就正了  
//	bih.biPlanes = 1;//为1，不用改  
//	bih.biBitCount = 24;
//	bih.biCompression = 0;//不压缩  
//	bih.biSizeImage = size;
//	bih.biXPelsPerMeter = 2835;//像素每米  
//	bih.biYPelsPerMeter = 2835;
//	bih.biClrUsed = 0;//已用过的颜色，24位的为0  
//	bih.biClrImportant = 0;//每个像素都重要  
//	FILE * fp = fopen(bmp_file, "wb");
//	if (!fp) return;
//
//	fwrite(&bfh, 8, 1, fp);//由于linux上4字节对齐，而信息头大小为54字节，第一部分14字节，第二部分40字节，所以会将第一部分补齐为16自己，直接用sizeof，打开图片时就会遇到premature end-of-file encountered错误  
//	fwrite(&bfh.bfReserved2, sizeof(bfh.bfReserved2), 1, fp);
//	fwrite(&bfh.bfOffBits, sizeof(bfh.bfOffBits), 1, fp);
//	fwrite(&bih, sizeof(BMPINFOHEADER_T), 1, fp);
//	fwrite(pdata, size, 1, fp);
//	fclose(fp);
//}
void get_local_time(char* buffer)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	/*time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
	(timeinfo->tm_year + 1900), timeinfo->tm_mon, timeinfo->tm_mday,
	timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);*/
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
void write_log_file(char* filename, long max_size, char* buffer, unsigned buf_size)
{
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

				fclose(fp);
				fp = NULL;
			}
		}
	}
}
void save_image_file(char* filename, char *imageBuff, long imageLenth)
{
	FILE *imageFile = NULL;
	imageFile = fopen(filename, "wb");
	fwrite(imageBuff, imageLenth, 1, imageFile);
	fclose(imageFile);
	imageFile = NULL;
}