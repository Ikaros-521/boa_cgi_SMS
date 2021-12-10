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
		// 调用脚本
		ret = system("echo 1 >/proc/sys/net/ipv4/icmp_echo_ignore_all");
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
		// 调用脚本
		ret = system("echo 0 >/proc/sys/net/ipv4/icmp_echo_ignore_all");
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


