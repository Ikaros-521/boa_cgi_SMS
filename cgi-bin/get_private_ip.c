#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
	
	system("sudo ifconfig | grep eth0 -C 1 > ifconfig.txt");
	system("sudo chmod 777 ifconfig.txt");
	int fd = 0; 
	fd = open("ifconfig.txt", O_RDONLY);
	if(fd == -1)
	{
		printf("<p>文件打开失败 error</p>");
		return 0;
	}
    
	char ip[20] = {};
	char netmask[20] = {};
	char *buf = malloc(1024);
	int count = 0;
	int i = 0;
	count = read(fd, buf, 1024);
	close(fd);

	char *temp = NULL;
	temp = strstr(buf, "eth0:");
	if(temp == NULL)
	{
		strcpy(ip,"--");
		strcpy(netmask,"--");
	}
	else
	{
		temp = strstr(temp, "inet");
		temp += 5;
		while(1)
		{
			if(temp[i] == ' ')
			{
				break;
			}
			ip[i] = temp[i];
			i++;
		}
		i = 0;
		
		temp = strstr(temp, "netmask");
		temp += 8;
		while(1)
		{
			if(temp[i] == ' ')
			{
				break;
			}
			netmask[i] = temp[i];
			i++;
		}
		i = 0;
		temp = NULL;

	}

	if(strstr(lenstr,"get") != NULL)
	{
		printf("<p>%s</p>",ip);
	}

	// 最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
