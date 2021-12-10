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

    int ret = 0;
	if(strstr(lenstr,"start") != NULL)
	{	
		ret = system("systemctl start frp");
        if(ret == 0)
        {
            printf("<p>success</p>");
        }
        else
        {
            printf("<p>failed</p>");
        }
	}
    else if(strstr(lenstr,"stop") != NULL)
	{	
		ret = system("systemctl stop frp");
        if(ret == 0)
        {
            printf("<p>success</p>");
        }
        else
        {
            printf("<p>failed</p>");
        }
	}
    else if(strstr(lenstr,"restart") != NULL)
	{	
		ret = system("systemctl restart frp");
        if(ret == 0)
        {
            printf("<p>success</p>");
        }
        else
        {
            printf("<p>failed</p>");
        }
	}
    else if(strstr(lenstr,"enable") != NULL)
	{	
		ret = system("systemctl enable frp");
        if(ret == 0)
        {
            printf("<p>success</p>");
        }
        else
        {
            printf("<p>failed</p>");
        }
	}
    else if(strstr(lenstr,"disable") != NULL)
	{	
		ret = system("systemctl disable frp");
        if(ret == 0)
        {
            printf("<p>success</p>");
        }
        else
        {
            printf("<p>failed</p>");
        }
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
