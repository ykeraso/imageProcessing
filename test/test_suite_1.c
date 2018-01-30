/**
 * Standard libs
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Unit test definitions
 */
#include "unimacros.h"
#include "testsuitedef.h"
#include "result_codes.h"
#include "shared.h"
#include "log.h"
#include "../Libs/myLib/include/IORaw.h"

/**
 *  Definition files for function to be tested
 */

int testnum;
GREY grey;
RGB  rgb;



void init_test_suite_1(){
	LOGO("test_suite_1 : Check basic functionalities in image structs");
	testnum = 0;
	grey = GREY_Init();
	rgb  = RGB_Init();
}

Boolean test_suite_1_TEST_1(){
	TRACE_IN;
	RGB rgb_img = RGB_Init();
	return rgb_img.HEIGHT == 0 && rgb_img.WIDTH == 0 && IS_NULL(rgb_img.img) && rgb_img.init == F;
}

Boolean test_suite_1_TEST_2(){
	TRACE_IN;
	GREY grey_img = GREY_Init();
	return grey_img.HEIGHT == 0 && grey_img.WIDTH == 0 && IS_NULL(grey_img.img) && grey_img.init == F;
}

Boolean test_suite_1_TEST_3(){
	TRACE_IN;
	RGB rgb_img = RGB_Init();
	if ( RAW_Input_RGB_FromFile("dummy", NULL) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Input_RGB_FromFile(NULL, &rgb_img) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Input_RGB_FromFile("dummy", &rgb_img) != Unable_to_open_file ){
		ERROR("Fail");
		return F;
	}
	return T;
}

Boolean test_suite_1_TEST_4(){
	TRACE_IN;
	GREY grey_img = GREY_Init();
	if ( RAW_Input_GREY_FromFile("dummy", NULL) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Input_GREY_FromFile(NULL, &grey_img) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Input_GREY_FromFile("dummy", &grey_img) != Unable_to_open_file ){
		ERROR("Fail");
		return F;
	}
	return T;
}

Boolean test_suite_1_TEST_5(){
	TRACE_IN;
	if ( RAW_Input_RGB_FromFile("../../../waterfall_1920_2520.raw", &rgb) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	return IS_NOT_NULL(rgb.img) && rgb.init == T;
}

Boolean test_suite_1_TEST_6(){
	TRACE_IN;
	if ( RAW_Input_GREY_FromFile("../../../waterfall_grey_1920_2520.raw", &grey) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	return IS_NOT_NULL(grey.img);
}

Boolean test_suite_1_TEST_7(){
	TRACE_IN;
	if ( RAW_Output_RGB_ToFile( NULL, 3, NULL) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_RGB_ToFile(&rgb, 3, NULL) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_RGB_ToFile(&rgb, bmpImage, NULL) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_RGB_ToFile(&rgb, rawImage, NULL) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	return T;
}

Boolean test_suite_1_TEST_8(){
	TRACE_IN;
	if ( RAW_Output_GREY_ToFile( NULL, 4, NULL ) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_GREY_ToFile( &grey, 4, NULL ) != Bad_input ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_GREY_ToFile( &grey, bmpImage, NULL) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	if ( RAW_Output_GREY_ToFile( &grey, rawImage, NULL) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	return T;
}

void clear_test_suite_1(){
	GREY_Destroy(&grey);
	RGB_Destroy(&rgb);
}

int test_suite_1(){
	init_test_suite_1();
	TEST(++testnum, "Test RGB_Init function",  test_suite_1_TEST_1() );
	TEST(++testnum, "Test GREY_Init function", test_suite_1_TEST_2() );
	TEST(++testnum, "Test wrong input arguments for RAW_Input_RGB_FromFile", test_suite_1_TEST_3() );
	TEST(++testnum, "Test wrong input arguments for RAW_Input_GREY_FromFile", test_suite_1_TEST_4() );
	TEST(++testnum, "Test RAW_Input_RGB_FromFile", test_suite_1_TEST_5() );
	TEST(++testnum, "Test RAW_Input_GREY_FromFile", test_suite_1_TEST_6() );
	TEST(++testnum, "Test RAW_Output_RGB_ToFile", test_suite_1_TEST_7() );
	TEST(++testnum, "Test RAW_Output_GREY_ToFile", test_suite_1_TEST_8() );

	clear_test_suite_1();
	return suite_eval();
 }
