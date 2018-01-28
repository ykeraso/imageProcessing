#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"


GREY GREY_Init(){
	GREY grey = {0, 0, 0, NULL, NULL};
	return grey;
}

GREY GREY_cpy(GREY img){
	GREY grey = GREY_Init();
	grey.HEIGHT = img.HEIGHT;
	grey.WIDTH = img.WIDTH;
	memcpy(grey.fname, img.fname, 80);
	if IS_NULL ( grey.buffer = malloc(grey.HEIGHT * grey.WIDTH* sizeof(GREY_PIXEL))){
		grey = GREY_Init();
		return grey;
	}
	memcpy(grey.buffer, img.buffer, grey.HEIGHT * grey.WIDTH* sizeof(GREY_PIXEL) );
	if IS_NULL ( grey.img = malloc(grey.HEIGHT*sizeof(*(grey.img))))
	{
		free(grey.buffer);
		grey = GREY_Init();
		return grey;
	}
	for ( int i = 0; i < grey.HEIGHT; i++ ){
		grey.img[i] = grey.buffer + i* grey.WIDTH;
	}
	return grey;
}

RGB  RGB_Init(){
	RGB rgb = {0, 0, 0, NULL, NULL};
	return rgb;
}

RGB RGB_cpy(RGB img){
	RGB rgb = RGB_Init();
	rgb.HEIGHT = img.HEIGHT;
	rgb.WIDTH = img.WIDTH;
	memcpy(rgb.fname, img.fname, 80);
	if IS_NULL ( rgb.buffer = malloc(rgb.HEIGHT * rgb.WIDTH* sizeof(RGB_PIXEL))){
		rgb= RGB_Init();
		return rgb;
	}
	memcpy(rgb.buffer, img.buffer, rgb.HEIGHT * rgb.WIDTH* sizeof(RGB_PIXEL) );
	if IS_NULL ( rgb.img = malloc(rgb.HEIGHT*sizeof(*(rgb.img))))
	{
		free(rgb.buffer);
		rgb = RGB_Init();
		return rgb;
	}
	for ( int i = 0; i < rgb.HEIGHT; i++ ){
		rgb.img[i] = rgb.buffer + i*rgb.WIDTH;
	}
	return rgb;
}

void GREY_Destroy(GREY *grey){
	if ( grey->init ){
		free(grey->buffer);
		free(grey->img);
	}
	grey->buffer = NULL;
	grey->img = NULL;
	grey->HEIGHT = 0;
	grey->WIDTH = 0;
	grey->img = NULL;
	grey->init = 0;
	memset(grey->fname, '\0', 80);
}

void RGB_Destroy(RGB *rgb){
	if ( rgb->init ){
		free(rgb->buffer);
		free(rgb->img);
	}
	rgb->buffer = NULL;
	rgb->img = NULL;
	rgb->HEIGHT = 0;
	rgb->WIDTH = 0;
	rgb->img = NULL;
	memset(rgb->fname, '\0', 80);
	rgb->init = 0;
}

void RGB_PIXEL_swap(RGB_PIXEL *pixel){
	if ( pixel == NULL ){
		return;
	}
	char temp = (*pixel)[2];
	(*pixel)[2] = (*pixel)[0];
	(*pixel)[0] = temp;
}

