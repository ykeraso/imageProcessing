#ifndef __apply_filters_simple
#define __apply_filters_simple

#include "result_codes.h"
#include "shared.h"
#include "Filters.h"

OK SimpleApplyFilter_3x3_Grey(GREY img, GREY *res,  filter_3x3 filter, int iter);
OK SimpleApplyFilter_3x3_RPG(RGB_PIXEL **img, RGB_PIXEL ***res,  filter_3x3 filter, int iter);


#endif
