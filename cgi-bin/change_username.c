#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include "cgic.h"

int cgiMain(void)
{
	char new_username[20] = {};

	char *lenstr;
	int fd_webdata=-1;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}

	printf("Content_type: text/html\n\n");

	if(strstr(lenstr,"set_username") != NULL)
	{
		//printf("%s",lenstr);
		int i = 0;
		char new_username[20] = {};
		char *temp = lenstr;
		temp = strstr(lenstr, "new:");
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
				new_username[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
	
		char *buf = malloc(100);
		FILE *fd = fopen("../file/user.bin", "rb");
		int size = fread(buf, 100, 1, fd);
		fclose(fd);
		//printf("%s",buf);
		char u[20] = {};
		char p[20] = {};
		
		temp = strstr(buf,"username");
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
		temp = strstr(buf,"password");
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
				p[i] = temp[i];
				i++;
			}
			else
			{
				i = 0;
				break;
			}
		}
		bzero(buf,sizeof(buf));

		sprintf(buf,"username:%s\npassword:%s\n",new_username,p);
		FILE *fd2 = fopen("../file/user.bin", "wb");
		size = fwrite(buf, strlen(buf), 1, fd);
		fclose(fd2);
		
		// 获取系统时间
		char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
		time_t timep;
		struct tm *ptr;
		time(&timep);
		ptr = localtime(&timep); /*取得当地时间*/
		
		// 写入日志 log.log
		char log_name[30] = {};
		if((1+ptr->tm_mon) < 10)
		{
			if(ptr->tm_mday < 10)
				sprintf(log_name, "../log/log%d-0%d-0%d.log", (1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday);
			else
				sprintf(log_name, "../log/log%d-0%d-%d.log", (1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday);
		}
		else
		{
			if(ptr->tm_mday < 10)
				sprintf(log_name, "../log/log%d-%d-0%d.log", (1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday);
			else
				sprintf(log_name, "../log/log%d-%d-%d.log", (1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday);
		}
		FILE *fd3 = fopen(log_name, "a");
		if(fd3 == NULL)
		{
			printf("<p>error,写入日志失败</p>");
		}
		else
		{
			int size3 = fprintf(fd3, "%d-%d-%d_%d:%d:%d user_management-change_username old_username:%s,new_username:%s\n",(1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday ,ptr->tm_hour, ptr->tm_min, ptr->tm_sec, u, new_username);
			fclose(fd3);
		}
		
		printf("<p>success</p>");

		temp = NULL;
		free(buf);
		buf = NULL;
		
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
}
