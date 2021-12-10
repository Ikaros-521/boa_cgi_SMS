#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
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

	int i = 0;

	if(strstr(lenstr,"del_file") != NULL)
	{
		//printf("%s",lenstr);


		char file_name[100] = {};

		char *temp = lenstr;
		temp = strstr(lenstr, "del_file:");
		if(temp == NULL)
		{
			printf("<p>前端发送的字符串有误</p>");
			return 0;
		}
		temp += 9;
		while(1)
		{
			if(temp[i] != '|')
			{
				file_name[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		temp = NULL;

		if(strlen(file_name) == 0)
		{
			printf("<p>获取文件名失败</p>");
			close(fd_webdata);
			return 0;
		}

		//printf("file_name:%s\n\n",file_name);

		char buf[160] = {};
		sprintf(buf, "sudo rm -f /var/www/log/%s > /dev/null 2>&1", file_name);
		system(buf);

		printf("<p>%s已删除</p>", file_name);
		
		// 获取系统时间
		char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
		time_t timep;
		struct tm *ptr;
		time(&timep);
		ptr=localtime(&timep); /*取得当地时间*/
		
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
		FILE *fd2 = fopen(log_name, "a");
		if(fd2 == NULL)
		{
			printf("<script>alert(\"写入日志失败\");</script>");
		}
		else
		{
			int size2 = fprintf(fd2, "%d-%d-%d_%d:%d:%d cloud_resources delete_a_file_named:%s\n",
			(1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday ,ptr->tm_hour, ptr->tm_min, ptr->tm_sec, file_name);
			fclose(fd2);
		}

	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
