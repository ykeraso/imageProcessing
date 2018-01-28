#include <stdio.h>
#include <stdlib.h>

#include "Filters.h"
#include "shared.h"
#include "log.h"

typedef char rgb_pixel_area[3][3][3];
typedef char grey_pixel_area[3][3];

void Print_grey_pixel_area(grey_pixel_area area){
	printf("+---------+---------+---------+\n");
	printf("| 0x%x | 0x%x | 0x%x |\n", area[0][0], area[0][1], area[0][2]);
	printf("+---------+---------+---------+\n");
	printf("| 0x%x | 0x%x | 0x%x |\n", area[1][0], area[1][1], area[1][2]);
	printf("+---------+---------+---------+\n");
	printf("| 0x%x | 0x%x | 0x%x |\n", area[2][0], area[2][1], area[2][2]);
	printf("+---------+---------+---------+\n");
}

OK SimpleApplyFilter_3x3_Grey(GREY img, GREY *res, filter_3x3 filter, int numOfIter){
	TRACE_IN;
	*res = GREY_cpy(img);
	int i, j;
	grey_pixel_area area;
	for ( i = 0; i < img.HEIGHT; i++){
		for ( j = 0; j < img.WIDTH; j++){

			area[0][0] = img.img[i==0?0:i-1][j==0?0:j-1];
			area[0][1] = img.img[i==0?0:i-1][j];
			area[0][2] = img.img[i==0?0:i-1][j==img.WIDTH?img.WIDTH:j+1];

			area[1][0] = img.img[i][j==0?0:j-1];
			area[1][1] = img.img[i][j];
			area[1][2] = img.img[i][j==img.WIDTH? img.WIDTH:j+1];

			area[2][0] = img.img[i==img.HEIGHT?img.HEIGHT:i+1][j==0?0:j-1];
			area[2][1] = img.img[i==img.HEIGHT?img.HEIGHT:i+1][j];
			area[2][2] = img.img[i==img.HEIGHT?img.HEIGHT:i+1][j==img.WIDTH];

			if ( i==0 && j==0){
				Print_grey_pixel_area(area);
			}else if ( i==0 && j==img.WIDTH){
				Print_grey_pixel_area(area);
			}else if ( i==img.HEIGHT && j==0){
				Print_grey_pixel_area(area);
			}else if ( i==img.HEIGHT && j==img.WIDTH){
				Print_grey_pixel_area(area);
			}
		}
	}
	TRACE_OUT;
	return __SUCCESS__;
}

