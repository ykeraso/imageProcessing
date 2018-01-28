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

/**
 *  Definition files for function to be tested
 */

int testnum;


void init_test_suite_0(){
	LOGO("test_suite_0 : Checking the test framework");
	testnum = 0;
}

void clear_test_suite_0(){
}


int test_suite_0(){
	init_test_suite_0();
	TEST(testnum++, "Dummy test T", T);
	TEST(testnum++, "Dummy test F", F);
	clear_test_suite_0();
	return suite_eval();
 }
