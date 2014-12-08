#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H 
#define TRACE_INFO 1
#define TRACE_WARNING 1
#define INFO 0
#define WARNING 1
#define ERROR 2
#include "stdio.h"
//void ErrorHandler(int iLevel,char *szMsg);
void ErrorHandler(int iLevel,char *szMsg)
{
	if(iLevel==ERROR)
	{

		printf("ERROR:%s\n",szMsg);
		getch();
	}
}
#endif 