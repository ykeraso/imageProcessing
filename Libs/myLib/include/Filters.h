#include "result_codes.h"

typedef float filter_3x3[3][3];

extern filter_3x3 vertical;
extern filter_3x3 horizontal;
extern filter_3x3 diagNE;
extern filter_3x3 diagNW;
extern filter_3x3 def;

#ifndef ___filters_3x3
#define ___filters_3x3


typedef enum{
	VER, HOR, DIA_NE, DIA_NW, DEF
}filter_desc_3x3;

OK Filter_display(filter_desc_3x3 desc);


#endif
