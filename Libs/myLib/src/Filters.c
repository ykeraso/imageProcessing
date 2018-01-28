#include "Filters.h"
#include "shared.h"
#include "result_codes.h"
#include "log.h"

filter_3x3 vertical = {{-1, 2, -1}, {-1, 2, -1}, {-1, 2, -1} };
filter_3x3 horizontal = {{-1,-1,-1}, {2,2,2},{-1,-1,-1} };
filter_3x3 diagNE = {{2, -1, -1}, {-1, 2, -1}, {-1, -1, 2}};
filter_3x3 diagNW = {{-1, -1, 2}, {-1, 2, -1}, {2, -1, -1}};

filter_3x3 def = {{0.0625, 0.125, 0.0625},{ 0.125, 0.25, 0.125},{0.0625, 0.125, 0.0625}};
OK Filter_display(filter_desc_3x3 desc){
	TRACE_IN;
	switch(desc){
		case VER:
			printf("VERTICAL filter:\n");
			break;
		case HOR:
			printf("HORIZONTIAL filter:\n");
			break;
		case DIA_NE:
			printf("DIAGONIAL NE filter:\n");
			break;
		case DIA_NW:
			printf("DIAGONIAL NW filter:\n");
			break;
		case DEF:
			printf("DEFAULT filter:\n");
			break;
		default:
			ASSERT(desc >= VER && desc <= DEF);
	}
	int i, j;
	char buff[100];
	buff[100] = '\0';
	for ( i = 0; i < 3; i++){
		memset(buff, ' ', 99);
		sprintf(buff, "|  ");
		for (j = 0; j < 3; j++){
			switch(desc)
			{
			case VER:
				sprintf(buff+ 3 + 7*j, "%.3f ", vertical[i][j]);
				break;
			case HOR:
				sprintf(buff+ 3 + 7*j, "%.3f ", horizontal[i][j]);
				break;
			case DIA_NE:
				sprintf(buff+ 3 + 7*j, "%.3f ", diagNE[i][j]);
				break;
			case DIA_NW:
				sprintf(buff+ 3 + 7*j, "%.3f ", diagNW[i][j]);
				break;
			case DEF:
				sprintf(buff+ 3 + 7*j, "%.3f ", def[i][j]);
				break;
			default:
				break;
			}
		}
		sprintf(buff+ 3 + 7*j, " |");
		printf("%s\n", buff);
	}
	return __SUCCESS__;
}
