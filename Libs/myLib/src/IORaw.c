#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "IORaw.h"
#include "log.h"

OK RAW_Input_RGB_FromFile(char *raw_image_fn, RGB *rgb){
	TRACE_IN;
	if IS_NULL(raw_image_fn)
	{
			ERROR("Input file is NULL");
			TRACE_OUT;
			return Bad_input;
	}
	if IS_NULL(rgb)
	{
			ERROR("rgb is NULL");
			TRACE_OUT;
			return Bad_input;
	}

	FILE *fp;
	if IS_NULL(fp = fopen(raw_image_fn,"rb") )
	{
		ERROR("Unable to open input file :%s", raw_image_fn);
		TRACE_OUT;
		return Unable_to_open_file;
	}
	memset(rgb->fname, '\0', 80);
	strcpy(rgb->fname, basename(raw_image_fn) );
	char bname[80];
	memset(bname, '\0', 80);
	strcpy(bname, basename(raw_image_fn) );
	char *width_p, *height_p;
	int i = strlen(bname)-4;
	bname[i] = '\0';
	while( bname[i] != '_' )i--;
	bname[i] = '\0';
	height_p = bname + i + 1;
	while( bname[i] != '_' )i--;
	width_p = bname+i+1;
	rgb->WIDTH = atoi(width_p);
	rgb->HEIGHT = atoi(height_p);
	if ( rgb->WIDTH == 0 || rgb->HEIGHT == 0 ){
		ERROR("Bad input from filename");
		return Bad_input;
	}
	if IS_NULL( rgb->buffer = malloc(rgb->HEIGHT* rgb->WIDTH * sizeof(RGB_PIXEL) ) )
	{
		ERROR("Malloc failed");
		return Memory_Failure;
	}
	if IS_NULL( rgb->img = malloc(rgb->HEIGHT * sizeof(*(rgb->img)) ) )
	{
		ERROR("Malloc failed");
		return Memory_Failure;
	}

	for ( int i = 0; i < rgb->HEIGHT; i++){
		rgb->img[i] = rgb->buffer + i*rgb->WIDTH;
	}
	rgb->init = 1;
	i = 0;
	size_t sz;
	char *buf;
	ASSERT(IS_NOT_NULL(buf = malloc(rgb->WIDTH*3) ) );
	while(!feof(fp))
	{
		INIT(buf, rgb->WIDTH*3 );
		sz = fread(buf, 1, rgb->WIDTH*3, fp);
		if ( i == rgb->HEIGHT){
			ASSERT(sz == 0);
			break;
		}else{
			memcpy(rgb->img[i], buf, rgb->WIDTH*3);
		}
		i += 1;
	}
	free(buf);
	ASSERT(i == rgb->HEIGHT);
	fclose(fp);
	TRACE_OUT;
	return __SUCCESS__;
}

OK RAW_Input_GREY_FromFile(char *raw_image_fn, GREY *grey){
	TRACE_IN;
	if IS_NULL(raw_image_fn)
	{
			ERROR("Input file is NULL");
			TRACE_OUT;
			return Bad_input;
	}
	if IS_NULL(grey)
	{
			ERROR("rgb is NULL");
			TRACE_OUT;
			return Bad_input;
	}
	FILE *fp;
	if IS_NULL( fp = fopen(raw_image_fn,"rb") )
	{
		ERROR("Unable to open input file :%s", raw_image_fn);
		TRACE_OUT;
		return Unable_to_open_file;
	}
	memset(grey->fname, '\0', 80);
	strcpy(grey->fname, basename(raw_image_fn) );

	char bname[80];
	memset(bname, '\0', 80);
	strcpy(bname, basename(raw_image_fn) );
	char *width_p, *height_p;
	int i = strlen(bname)-4;
	bname[i] = '\0';
	while( bname[i] != '_' )i--;
	bname[i] = '\0';
	height_p = bname + i + 1;
	while( bname[i] != '_' )i--;
	width_p = bname+i+1;
	grey->WIDTH = atoi(width_p);
	grey->HEIGHT = atoi(height_p);
	if ( grey->WIDTH == 0 || grey->HEIGHT == 0 ){
		ERROR("Bad input from filename");
		return Bad_input;
	}
	if IS_NULL( grey->buffer = malloc(grey->HEIGHT * grey->WIDTH *sizeof(GREY_PIXEL) ) )
	{
		ERROR("Malloc failed");
		return Memory_Failure;
	}
	if IS_NULL( grey->img = malloc(grey->HEIGHT*sizeof(grey->img[i]) ) )
	{
		ERROR("Malloc failed");
		return Memory_Failure;
	}
	for ( int i = 0; i < grey->HEIGHT; i++){
		grey->img[i] = grey->buffer + i*grey->WIDTH;
	}
	grey->init = 1;
	i = 0;
	size_t sz;
	char *buf;
	ASSERT(IS_NOT_NULL(buf = malloc(grey->WIDTH) ) );
	while(!feof(fp))
	{
		INIT(buf, grey->WIDTH);
		sz = fread(buf, 1, grey->WIDTH, fp);
		if ( i == grey->HEIGHT ){
			ASSERT(sz == 0 );
			break;
		}else{
			memcpy(grey->
					img[i], buf, grey->WIDTH);
		}
		i += 1;
	}
	free(buf);
	ASSERT(i == grey->HEIGHT);
	fclose(fp);
	TRACE_OUT;
	return __SUCCESS__;
}

typedef unsigned char                   UInt8;
typedef signed char                     SInt8;
typedef unsigned short                  UInt16;
typedef signed short                    SInt16;

#if __LP64__
typedef unsigned int                    UInt32;
typedef signed int                      SInt32;
#else
typedef unsigned long                   UInt32;
typedef signed long                     SInt32;
#endif

typedef 	UInt32		DWORD;
typedef 	UInt16		WORD;
typedef 	unsigned char	BYTE;

#ifndef bool
typedef		unsigned short bool;
#define false 0
#define true 0
#endif

typedef	UInt32		LONG;

typedef struct tagBITMAPFILEHEADER
{
    UInt16    bfType;
    UInt32   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER, * PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}RGBQUAD;

Boolean isLittleEndian = F;
//check the byte-order of the current OS
Boolean  IsLittleEndian()
{
	TRACE_IN;
	unsigned char x[2];
	*(unsigned short *)x=0xff00;
	//Check byte-endian
	isLittleEndian = (x[0]==0);
	return isLittleEndian;
}

void LongSwapA(unsigned long *X)
{
    if( IsLittleEndian() == F ){
	*X = (((*X & 0x000000FF) << 24)
		+ ((*X & 0x0000FF00) << 8)
		+ ((*X & 0x00FF0000) >> 8)
		+ ((*X & 0xFF000000) >> 24) );
    }else{
    	return;
    }
}

void ShortSwapA(unsigned short *X)
{
	if( IsLittleEndian() == F ){
		*X = (((*X & 0x00FF) << 8)
		+ ((*X & 0xFF00) >> 8));
	}else{
		return;
	}
}

void printBitMapFileHeader(BITMAPFILEHEADER bitmapFileHeader){
	printf("BITMAPFILEHEADER:\n");
	printf(" *** bfType: 0x%x\n", bitmapFileHeader.bfType);
	printf(" *** bfsize: 0x%x\n", bitmapFileHeader.bfSize);
	printf(" *** bfReserved1: 0x%x\n", bitmapFileHeader.bfReserved1);
	printf(" *** bfReserved2: 0x%x\n", bitmapFileHeader.bfReserved2);
	printf(" *** bfOffBits: 0x%x\n", bitmapFileHeader.bfOffBits);
}

void printBitMapInfoHeader(BITMAPINFOHEADER bitMapInfoHeader){
	printf("BITMAPINFOHEADER:\n");
	printf(" *** biPlanes: 0x%x\n", bitMapInfoHeader.biPlanes);
	printf(" *** biBitCount: 0x%x\n", bitMapInfoHeader.biBitCount);
}

void  SetBitmapInfoHeader(BITMAPFILEHEADER * g_BitmapFileHeader,BITMAPINFOHEADER * g_BitmapInfoHeader,int Width,int Height,int nBitNumber)
{
    //BITMAPINFOHEADER g_BitmapInfoHeader;
    //BITMAPFILEHEADER g_BitmapFileHeader;
    DWORD m_dwDibSize;
    DWORD m_Width;
    DWORD m_Height;
    m_Width  = Width;//m_lScanRight-m_lScanLeft+1;
    m_Height = Height;//m_lScanBottom-m_lScanTop+1;
    m_dwDibSize = m_Width*m_Height*nBitNumber/8;// RGB,24Bits

    //BITMAPFLEHEADER
    memset(&(g_BitmapFileHeader->bfType), 0x42, 1);
    memset((BYTE*)&(g_BitmapFileHeader->bfType)+1, 0x4D, 1);

    g_BitmapFileHeader->bfSize=14+sizeof(BITMAPINFOHEADER)+m_dwDibSize;
    g_BitmapFileHeader->bfOffBits = 14+sizeof(BITMAPINFOHEADER);//NO PLATTE HERE!
	if(nBitNumber==8)
		g_BitmapFileHeader->bfOffBits+=256*4;
	else if(nBitNumber == 1)
		g_BitmapFileHeader->bfOffBits+=2*4;
    //Swap bits
	ShortSwapA((unsigned short*)&(g_BitmapFileHeader->bfType));
    LongSwapA((unsigned long*)&(g_BitmapFileHeader->bfSize));
    LongSwapA((unsigned long*)&(g_BitmapFileHeader->bfOffBits));

    g_BitmapFileHeader->bfReserved1 = 0;
    g_BitmapFileHeader->bfReserved2 = 0;

    //BITMAPINFOHEADER
    g_BitmapInfoHeader->biSize = 40;
    g_BitmapInfoHeader->biPlanes = 1;
    g_BitmapInfoHeader->biWidth = m_Width;
    g_BitmapInfoHeader->biHeight = -1*m_Height;
    g_BitmapInfoHeader->biBitCount = nBitNumber;
    g_BitmapInfoHeader->biCompression = 0;
    g_BitmapInfoHeader->biSizeImage = m_dwDibSize;
    g_BitmapInfoHeader->biXPelsPerMeter = 0;
    g_BitmapInfoHeader->biYPelsPerMeter = 0;
    g_BitmapInfoHeader->biClrUsed = 0;
    g_BitmapInfoHeader->biClrImportant = 0;
    //SWAP
    LongSwapA((unsigned long*)&(g_BitmapInfoHeader->biSize));
    LongSwapA((unsigned long*)&(g_BitmapInfoHeader->biWidth));
    LongSwapA((unsigned long*)&(g_BitmapInfoHeader->biHeight));
    ShortSwapA((unsigned short*)&(g_BitmapInfoHeader->biPlanes));
    LongSwapA((unsigned long*)&(g_BitmapInfoHeader->biSizeImage));
    ShortSwapA((unsigned short*)&(g_BitmapInfoHeader->biBitCount));
}

OK RAW_Output_RGB_ToFile(RGB *rgb, ImageType itype, const char *fname){
	TRACE_IN;
	if IS_NULL(rgb){
		ERROR("Bad input arguments");
		TRACE_OUT;
		return Bad_input;
	}
	int nameLen;
	char l_fname[80];
	if IS_NULL ( fname )
	{
		strcpy(l_fname, rgb->fname);
		nameLen = strlen(l_fname);
		switch( itype )
		{
			case rawImage:
				l_fname[nameLen-3] = 'r';
				l_fname[nameLen-2] = 'a';
				l_fname[nameLen-1] = 'w';
				LOG("Output rawImage: %s", l_fname);
				break;

			case bmpImage:
				l_fname[nameLen-3] = 'b';
				l_fname[nameLen-2] = 'm';
				l_fname[nameLen-1] = 'p';
				LOG("Output bmpImage: %s", l_fname);
				break;

			default:
				ERROR("Bad input arguments (ImageType)");
				TRACE_OUT;
				return Bad_input;
		}
	}else{
		strcpy(l_fname, fname);
	}
	FILE *fp;
	if IS_NULL (fp = fopen(rgb->fname,"wb+") )
	{
		fclose(fp);
		ERROR("Unable to create the bitmap file");
		return Unable_to_create_file;
	}
	if ( itype == bmpImage )
	{
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;

		SetBitmapInfoHeader(&bitmapFileHeader, &bitmapInfoHeader, rgb->WIDTH, rgb->HEIGHT, 24);
		printBitMapFileHeader(bitmapFileHeader);
		printBitMapInfoHeader(bitmapInfoHeader);

		int Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfType,Len,1,fp);
		Len=4;
		fwrite((unsigned char *)&bitmapFileHeader.bfSize,Len,1,fp);
		Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfReserved1,Len,1,fp);
		Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfReserved2,Len,1,fp);
		Len=4;
		fwrite((unsigned char *)&bitmapFileHeader.bfOffBits,Len,1,fp);
		fwrite((unsigned char *)&bitmapInfoHeader,40,1,fp);
		RGB_PIXEL *line;
		if IS_NULL ( line = malloc( rgb->WIDTH*sizeof(RGB_PIXEL) ) )
		{
			ERROR("Unable to allocate memory");
			fclose(fp);
			TRACE_OUT;
			return Memory_Failure;
		}
		for ( int i = 0; i < rgb->HEIGHT; i++){
			memcpy(line, rgb->img[i], rgb->WIDTH * sizeof(RGB_PIXEL) );
			for ( int j = 0; j < rgb->WIDTH; j++){
				RGB_PIXEL_swap(&(line[j]));
			}
			fwrite(rgb->img[i], 1, rgb->WIDTH*3, fp);
		}
		free(line);
	}else if ( itype == rawImage ){
		for ( int i = 0; i < rgb->HEIGHT; i++){
			fwrite(rgb->img[i], 1, rgb->WIDTH*3, fp);
		}
	}
    fclose(fp);
	TRACE_OUT;
	return __SUCCESS__;
}

OK RAW_Output_GREY_ToFile(GREY *grey, ImageType itype, const char *fname){
	TRACE_IN;
	if IS_NULL(grey){
		ERROR("Bad input arguments");
		TRACE_OUT;
		return Bad_input;
	}
	int nameLen;
	char l_fname[80];
	if IS_NULL(fname)
	{
		strcpy(l_fname, grey->fname);
		nameLen = strlen(l_fname);
		switch( itype )
		{
			case rawImage:
				l_fname[nameLen-3] = 'r';
				l_fname[nameLen-2] = 'a';
				l_fname[nameLen-1] = 'w';
				LOG("Output rawImage: %s", l_fname);
				break;

			case bmpImage:
				l_fname[nameLen-3] = 'b';
				l_fname[nameLen-2] = 'm';
				l_fname[nameLen-1] = 'p';
				LOG("Output bmpImage: %s", l_fname);
				break;

			default:
				ERROR("Bad input arguments (ImageType)");
				TRACE_OUT;
				return Bad_input;
		}
	}else{
		strcpy(l_fname, fname);
	}
	FILE *fp;
	if IS_NULL (fp = fopen(l_fname,"wb+") )
	{
		fclose(fp);
		ERROR("Unable to create the bitmap file");
		return Unable_to_create_file;
	}
	if ( itype == bmpImage ){
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;
		RGBQUAD rgbQuad[256];

		SetBitmapInfoHeader(&bitmapFileHeader, &bitmapInfoHeader, grey->WIDTH, grey->HEIGHT, 8);
		int Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfType, Len, 1, fp);
		Len=4;
		fwrite((unsigned char *)&bitmapFileHeader.bfSize, Len, 1, fp);
		Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfReserved1, Len, 1, fp);
		Len=2;
		fwrite((unsigned char *)&bitmapFileHeader.bfReserved2,Len,1,fp);
		Len=4;
		fwrite((unsigned char *)&bitmapFileHeader.bfOffBits,Len,1,fp);
		fwrite((unsigned char *)&bitmapInfoHeader,40,1,fp);
		for( int i = 0; i < 256; i++)
		{
			rgbQuad[i].rgbBlue =
			rgbQuad[i].rgbGreen =
			rgbQuad[i].rgbRed = i;
		}
		fwrite((unsigned char *)rgbQuad, 4, 256, fp);
		for ( int i = 0; i < grey->HEIGHT; i++){
			fwrite(grey->img[i], 1, grey->WIDTH, fp);
		}
    }else{
		for ( int i = 0; i < grey->HEIGHT; i++){
			fwrite(grey->img[i], 1, grey->WIDTH, fp);
		}
    }
	//Close files
	fclose(fp);
	TRACE_OUT;
	return __SUCCESS__;
}
