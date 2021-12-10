#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cgic.h"

// 专用获取特定信息函数
void get_info(char* src,char* dest,char* search)
{
	int i = 0;
	char *buf1 = malloc(1024);
	strcpy(buf1,src);
	char *temp1 = strstr(buf1,search);
	if(NULL == temp1)
	{
		strcpy(dest, "error");
	}
	else
	{
		temp1 += strlen(search)+1;
		while(1)
		{
			if(temp1[i] == '\n' || temp1[i] == '\0' || temp1[i] == ' ')
			{
				break;
			}
			dest[i] = temp1[i];
			i++;
		}
		i = 0;
		temp1 = NULL;
	}
}

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

	printf("Content type: text/html\n\n");

	if(strstr(lenstr,"get") != NULL)
	{
		char ip[20] = {};
		char netmask[20] = {};
		char gateway[20] = {};
		char dns1[20] = {};
		char dns2[20] = {};
		char *buf = malloc(1024);
		int count = 0;
		int i = 0;
		system("sudo w | grep \"pts/1\" > w.txt");
		system("sudo chmod 777 w.txt"); 
		FILE* fp = fopen("w.txt", "r");
		if(fp == NULL)
		{
			printf("<p>文件打开失败 error</p>");
			return 0;
		}
		
		char user[20] = {};
		char tty[20] = {};
		fscanf(fp, "%s %s %s", user, tty, ip);
		fclose(fp);
		
		printf("<p>%s</p>", ip);
	}

	// 最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 