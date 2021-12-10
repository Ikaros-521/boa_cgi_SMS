#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cgic.h"

#define SESSION_ID_LEN 45

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
	
	if(strstr(lenstr,"check,") != NULL)
	{		
		char session_id[SESSION_ID_LEN] = {};
		char sec[20] = {};

		int i = 0;
		char *temp = lenstr;
		temp = strstr(lenstr, "sec:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 4;
		while(1)
		{
			if(temp[i] != ',')
			{
				sec[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
		
		temp = strstr(lenstr, "session_id:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 11;
		while(1)
		{
			if(temp[i] != ',')
			{
				session_id[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
		
		char path[100] = {};
		sprintf(path, "/var/www/session/%s", session_id);
		FILE* fd_s = fopen(path, "r");
		if(fd_s == NULL)
		{
			printf("<p>failed</p>");
		}
		else
		{
			char sec_local[20] = {};
			fscanf(fd_s, "%s",sec_local);
			fclose(fd_s);
			
			if((atol(sec)-atol(sec_local)) > 3600)
			{
				printf("<p>failed</p>");
			}
			else
			{
				printf("<p>success</p>");
			}
		}
	}
	
    //最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
