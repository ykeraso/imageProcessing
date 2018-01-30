#include <stdio.h>
#include <stdlib.h>

#include "Filters.h"
#include "shared.h"
#include "log.h"

typedef unsigned char rgb_pixel_area[3][3][3];
typedef unsigned char grey_pixel_area[3][3];

void Print_grey_pixel_area(grey_pixel_area area){
	printf("+--------+--------+--------+\n");
	printf("| 0x%4x | 0x%4x | 0x%4x |\n", area[0][0], area[0][1], area[0][2]);
	printf("+--------+--------+--------+\n");
	printf("| 0x%4x | 0x%4x | 0x%4x |\n", area[1][0], area[1][1], area[1][2]);
	printf("+--------+--------+--------+\n");
	printf("| 0x%4x | 0x%4x | 0x%4x |\n", area[2][0], area[2][1], area[2][2]);
	printf("+--------+--------+--------+\n\n");
}

GREY_PIXEL TransformGreyArea(grey_pixel_area area, filter_3x3 filter){
	GREY_PIXEL grey_pixel = 0;
	int i, j;
	for ( i = 0; i < 3; i++){
		for ( j =0; j < 3; j++){
			grey_pixel += ( area[i][j]*filter[i][j] );
		}
	}
	return grey_pixel;
}

OK SimpleApplyFilter_3x3_Grey(GREY img, GREY *res, filter_3x3 filter, int numOfIter){
	TRACE_IN;
	*res = GREY_cpy(img);
	int i, j;
	grey_pixel_area area;
	int iter = 0;
	Boolean diff = T;
	while ( iter < numOfIter || diff ){
		diff = F;
		for ( i = 0; i < img.HEIGHT; i++){
			for ( j = 0; j < img.WIDTH; j++){

				area[0][0] = img.img[i==0?0:i-1][j==0?0:j-1];
				area[0][1] = img.img[i==0?0:i-1][j];
				area[0][2] = img.img[i==0?0:i-1][j==img.WIDTH-1?img.WIDTH-1:j+1];

				area[1][0] = img.img[i][j==0?0:j-1];
				area[1][1] = img.img[i][j];
				area[1][2] = img.img[i][j==img.WIDTH-1? img.WIDTH-1:j+1];

				area[2][0] = img.img[i==img.HEIGHT-1?img.HEIGHT-1:i+1][j==0?0:j-1];
				area[2][1] = img.img[i==img.HEIGHT-1?img.HEIGHT-1:i+1][j];
				area[2][2] = img.img[i==img.HEIGHT-1?img.HEIGHT-1:i+1][j==img.WIDTH-1?img.WIDTH-1:j+1];

				res->img[i][j] = TransformGreyArea(area, filter);

				if ( !diff ) if ( res->img[i][j]-img.img[i][j]) diff = T;
			}
		}
		if ( numOfIter > 0 )diff = F;
		iter += 1;
	}
	TRACE_OUT;
	return __SUCCESS__;
}

