#include <stdio.h>
#include <string.h>

#include "testsuitedef.h"
#include "../utest/unimacros.h"
#include "result_codes.h"

#include "log.h"

#define PRINT_RESULT( ev ) \
	printf("\n... Test suite finished. %d test cases failed\n", (ev));

//OK assert_error;

log_level_t log_level;

/* The suite config.
 * Should returns zero on success, non-zero otherwise.
 */
int main(int argc , char *argv[]){
	/* Configure test */
	log_level = TEST_LOG;
	if ( argc == 1){
		printf("No argument: test for VIRTUAL 0");
		SET_TEST_MODE(1);
	}else if( strncmp(argv[1], "reg", 3) == 0)
		SET_TEST_MODE(0);
	else SET_TEST_MODE(1);

	/* Run test cases */
//	PRINT_RESULT( test_suite_0() )
	PRINT_RESULT( test_suite_1() )
	PRINT_RESULT( test_suite_2() )
	return evaluate();
}
