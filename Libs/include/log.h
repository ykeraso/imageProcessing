#ifndef __log_LIB__
#define __log_LIB__

#define LOG_BUFF 300

/**
 * Debug levels
 * 0: Fatal
 * 1: Error logs
 * 2: Error & trace logs
 * 3: All logs
 */
#define FATAL_ERR 0
#define ERROR_LOG 1
#define TRACE_LOG 2
#define EVERY_LOG 3

#include <string.h>
#include "result_codes.h"

typedef enum{
	ERROR, INFO, TRACE, TEST_LOG
}log_level_t;

extern OK assert_error;
extern log_level_t log_level;

#define FATAL(...) \
	do{ \
		char log_buff[LOG_BUFF]; \
		sprintf(log_buff, __VA_ARGS__); \
		fprintf(stderr, "FATAL ERROR (%s & %s): %s\n", __DATE__, __TIME__, log_buff ); \
	}while(0)

#define CHECK(msg, eval) \
	do{ \
		if ( !(eval) ) { \
			FATAL("CHECK FAILED at File:%s, Line:%d [%s]) : %s\n", __FILE__, __LINE__, __func__, (msg) ); \
			assert_error = Assert_Failure; \
		}else{ \
			assert_error = __SUCCESS__; \
		} \
	}while(0)

#define ASSERT(eval) \
	do{ \
		if ( !(eval) ) { \
			FATAL("CHECK FAILED at File:%s, Line:%d [%s])\n", __FILE__, __LINE__, __func__ ); \
			return Assert_Failure; \
		} \
	}while(0)


#	define ERROR(...) \
	do{ \
		if ( log_level >= ERROR ){ \
			char log_buff[LOG_BUFF]; \
			sprintf(log_buff, __VA_ARGS__); \
			fprintf(stderr, "ERROR (File:%s, Line:%d [%s]) : %s\n",  __FILE__, __LINE__, __func__, log_buff ); \
		} \
	}while(0)


#	define LOG(...) \
		do{\
			if ( log_level >= INFO ){ \
				char log_buff[LOG_BUFF]; \
				sprintf(log_buff, __VA_ARGS__); \
				fprintf(stderr, "LOG (%s & %s) : (File:%s, Line:%d [%s]) : %s\n",  __DATE__, __TIME__, __FILE__, __LINE__, __func__, (log_buff) ); \
			} \
		}while(0)

#	define TRACE_IN \
	do{ \
		if ( log_level >= TRACE ){ \
			fprintf(stderr, "TRACE In function: %s [%s]: %d\n", __func__, __FILE__, __LINE__ ); \
		} \
	}while(0)

#	define TRACE_OUT \
	do{ \
		if ( log_level >= TRACE ){ \
			fprintf(stderr, "TRACE OUT at %s [%s]: %d\n", __func__, __FILE__, __LINE__ ); \
		} \
	}while(0)


#	define TESTLOG(...) \
		do{\
			if ( log_level >= TEST_LOG ){ \
				char log_buff[LOG_BUFF]; \
				sprintf(log_buff, __VA_ARGS__); \
				fprintf(stderr, "TEST (%s & %s) : (File:%s, Line:%d [%s]) : %s\n",  __DATE__, __TIME__, __FILE__, __LINE__, __func__, (log_buff) ); \
			} \
		}while(0)

#endif
