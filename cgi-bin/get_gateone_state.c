#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/vfs.h>
#include "cgic.h"

int cgiMain(void) 
{
	char *lenstr;
	int fd_webdata=-1;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}

	printf("Content_type: text/html\n\n");

	if(strstr(lenstr,"get") != NULL)
	{	
		system("sudo systemctl status gateone | grep Active | cut -b 12- > gateone_state.txt");
		system("sudo chmod 777 gateone_state.txt");
		FILE * fp;
		fp = fopen ("gateone_state.txt", "r");
		if(fp == NULL)
		{
			printf("<p>open file:gateone_state.txt error</p>");
			return 0;
		}
		char state[20] = {};
		fscanf(fp, "%s", state);
		fclose(fp);
		fp = NULL;

		printf("<p>%s</p>", state);		
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
