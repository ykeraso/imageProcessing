#ifndef __shared
#define __shared

#include <stdio.h>
#include <stdlib.h>

#define IS_NULL(a)       ( (a) == NULL )
#define IS_NOT_NULL(a)   ( (a) != NULL )
#define INIT(buffer, size) memset((buffer), 0, (size) )

typedef char GREY_PIXEL;
typedef char RGB_PIXEL[3];

typedef struct _Sgrey{
	unsigned int init : 1;
	int WIDTH;
	int HEIGHT;
	GREY_PIXEL **img;
	GREY_PIXEL *buffer;
	char fname[80];
}GREY;


typedef struct _Srgb{
	unsigned int init : 1;
	int WIDTH;
	int HEIGHT;
	RGB_PIXEL **img;
	RGB_PIXEL *buffer;
	char fname[80];
}RGB;

GREY GREY_Init();
RGB  RGB_Init();

void GREY_Destroy(GREY *grey);
void RGB_Destroy(RGB *rgb);
void RGB_PIXEL_swap(RGB_PIXEL *pixel);
GREY GREY_cpy(GREY img);
RGB RGB_cpy(RGB img);

#endif
