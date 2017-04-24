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
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8; //ÿ��ʵ��ռ�õĴ�С��ÿ�ж�����䵽һ��4�ֽڱ߽磩  
	bhh.bfType = ((WORD)('M' << 8) | 'B');  //'BM'  
	bhh.bfSize = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + widthStep * nHeight;
	bhh.bfReserved1 = 0;
	bhh.bfReserved2 = 0;
	bhh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

}


//����BMP�ļ���Ϣͷ  
void ConstructBih(int nWidth, int nHeight, BITMAPINFOHEADER& bih)
{
	int widthStep = (((nWidth * 24) + 31) & (~31)) / 8;

	bih.biSize = 40;       // header size  
	bih.biWidth = nWidth;
	bih.biHeight = nHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;     // RGB encoded, 24 bit  
	bih.biCompression = BI_RGB;   // no compression ��ѹ��  
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
//{      //�ֱ�Ϊrgb���ݣ�Ҫ�����bmp�ļ�����ͼƬ����  
//	int size = width*height * 3 * sizeof(char); // ÿ�����ص�3���ֽ�  
//												// λͼ��һ���֣��ļ���Ϣ  
//	BMPFILEHEADER_T bfh;
//	bfh.bfType = (WORD)0x4d42;  //bm  
//	bfh.bfSize = size  // data size  
//		+ sizeof(BMPFILEHEADER_T) // first section size  
//		+ sizeof(BMPINFOHEADER_T) // second section size  
//		;
//	bfh.bfReserved1 = 0; // reserved  
//	bfh.bfReserved2 = 0; // reserved  
//	bfh.bfOffBits = sizeof(BMPFILEHEADER_T) + sizeof(BMPINFOHEADER_T);//���������ݵ�λ��  
//
//																	  // λͼ�ڶ����֣�������Ϣ  
//	BMPINFOHEADER_T bih;
//	bih.biSize = sizeof(BMPINFOHEADER_T);
//	bih.biWidth = width;
//	bih.biHeight = -height;//BMPͼƬ�����һ���㿪ʼɨ�裬��ʾʱͼƬ�ǵ��ŵģ�������-height������ͼƬ������  
//	bih.biPlanes = 1;//Ϊ1�����ø�  
//	bih.biBitCount = 24;
//	bih.biCompression = 0;//��ѹ��  
//	bih.biSizeImage = size;
//	bih.biXPelsPerMeter = 2835;//����ÿ��  
//	bih.biYPelsPerMeter = 2835;
//	bih.biClrUsed = 0;//���ù�����ɫ��24λ��Ϊ0  
//	bih.biClrImportant = 0;//ÿ�����ض���Ҫ  
//	FILE * fp = fopen(bmp_file, "wb");
//	if (!fp) return;
//
//	fwrite(&bfh, 8, 1, fp);//����linux��4�ֽڶ��룬����Ϣͷ��СΪ54�ֽڣ���һ����14�ֽڣ��ڶ�����40�ֽڣ����ԻὫ��һ���ֲ���Ϊ16�Լ���ֱ����sizeof����ͼƬʱ�ͻ�����premature end-of-file encountered����  
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
����ļ���С
@param filename [in]: �ļ���
@return �ļ���С
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
		//�ļ������������, ɾ��  
		long length = get_file_size(filename);

		if (length > max_size)
		{
			_unlink(filename); // ɾ���ļ�  
		}

		// д��־  
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