#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "cgic.h"

int cgiMain(void) 
{
	char *lenstr;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}

    printf("Content-type: text/html\n\n");

	char ip[20] = "192.168.10.1";
	char prot[6] = "8080";

	if(strstr(lenstr,"get_info") != NULL)
	{
	    printf("%s\n\n",ip);
	    printf("%s\n\n",prot);
	}
	
	return 0; 
} 
