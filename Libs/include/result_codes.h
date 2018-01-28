#ifndef __result_codes__
#define __result_codes__

typedef enum{
	F,
	T
}Boolean;

typedef enum{
	__SUCCESS__,
	Unknown_Failure,
	Assert_Failure,
	Memory_Failure,
	Bad_input,
	Unable_to_open_file,
	Unable_to_create_file,
	Max_Error_Num
}Result;

typedef Result OK;

extern Result assert_error;

#define OK_Success return __SUCCESS__

#endif
