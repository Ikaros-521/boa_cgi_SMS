#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "cgic.h"

int main(void) 
{
	char *lenstr;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}

    printf("Content-type: text/html\n\n");

	if(strstr(lenstr,"txtIDA")!=NULL)
	{
	    printf("a@b.com\n\n");
	}
	if(strstr(lenstr,"txtIDB")!=NULL)
	{
	    printf("abc\n\n");
	}
	
	return 0; 
} 
