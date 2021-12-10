#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

	if(strstr(lenstr,"get_username") != NULL)
	{
		char *buf = malloc(100);
		FILE *fd = fopen("../file/user.bin", "rb");
		int size = fread(buf, 100, 1, fd);
		fclose(fd);
		//printf("%s",buf);
		char u[20] = {};
		int i = 0;
		char *temp = strstr(buf,"username");
		if(temp == NULL)
		{
			printf("<p>用户信息文件错误</p>");
			return 0;
		}
		temp += 9;
		while(1)
		{
			if(temp[i] != '\n')
			{
				u[i] = temp[i];
				i++;
			}
			else
			{
				i = 0;
				break;
			}
		}
		printf("<p>%s</p>",u);
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
