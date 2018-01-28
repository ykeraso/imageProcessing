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
#include "../Libs/myLib/include/Filters.h"
#include "../Libs/myLib/include/IORaw.h"
#include "../Libs/myLib/include/ApplyFiltersSimple.h"



/**
 *  Definition files for function to be tested
 */

int testnum;


void init_test_suite_2(){
	LOGO("test_suite_2 : Apply filters");
	testnum = 0;
}
void clear_test_suite_2(){
	TRACE_IN;
}

Boolean test_suite_2_TEST_1(){
	TRACE_IN;
	if ( Filter_display(VER) != __SUCCESS__){
		TRACE_OUT;
		return F;
	}
	if ( Filter_display(HOR) != __SUCCESS__){
		TRACE_OUT;
		return F;
	}
	if ( Filter_display(DIA_NE) != __SUCCESS__){
		TRACE_OUT;
		return F;
	}
	if ( Filter_display(DIA_NW) != __SUCCESS__){
		TRACE_OUT;
		return F;
	}
	if ( Filter_display(DEF) != __SUCCESS__){
		TRACE_OUT;
		return F;
	}
	if ( Filter_display(8) != Assert_Failure){
		TRACE_OUT;
		return F;
	}
	return T;
}

Boolean test_suite_2_TEST_2(){
	TRACE_IN;
	GREY grey = GREY_Init();
	if ( RAW_Input_GREY_FromFile("../../../waterfall_grey_1920_2520.raw", &grey) != __SUCCESS__ ){
		ERROR("Fail");
		return F;
	}
	if IS_NULL(grey.img){
		ERROR("grey picture is not read from file");
	}
	GREY res = GREY_Init();
	OK ret = SimpleApplyFilter_3x3_Grey(grey, &res, vertical, 0);
	GREY_Destroy(&grey);
	return ret == __SUCCESS__ && grey.init == 0;
}

int test_suite_2(){
	init_test_suite_2();
	TEST(++testnum, "Print out filters:",  test_suite_2_TEST_1() );
	TEST(++testnum, "Apply VER filter once in a GREY image", test_suite_2_TEST_2() );
	clear_test_suite_2();
	return suite_eval();
 }
