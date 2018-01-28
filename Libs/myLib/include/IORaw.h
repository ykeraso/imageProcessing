#ifndef __IO_RAW__
#define __IO_RAW__

#include "result_codes.h"
#include "shared.h"

typedef enum{
	rawImage, bmpImage
}ImageType;

OK RAW_Input_RGB_FromFile(char *raw_image_fn, RGB *rgb);
OK RAW_Input_GREY_FromFile(char *raw_image_fn, GREY *grey);
OK RAW_Output_RGB_ToFile(RGB *rgb, ImageType itype);
OK RAW_Output_GREY_ToFile(GREY *grey, ImageType itype);

#endif // __IO_RAW__
