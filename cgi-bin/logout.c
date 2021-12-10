#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
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
	
	if(strstr(lenstr,"logout,") != NULL)
	{		
		char username[20] = {};
		char session_id[SESSION_ID_LEN] = {};
		int i = 0;
		char *temp = lenstr;
		temp = strstr(lenstr, "username:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 9;
		while(1)
		{
			if(temp[i] != ',')
			{
				username[i] = temp[i];
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
	
		char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
		time_t timep;
		struct tm *p;
		time(&timep);
		p=localtime(&timep); /*取得当地时间*/

		// 写入日志 log.log
		char log_name[30] = {};
		if((1+p->tm_mon) < 10)
		{
			if(p->tm_mday < 10)
				sprintf(log_name, "../log/log%d-0%d-0%d.log", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
			else
				sprintf(log_name, "../log/log%d-0%d-%d.log", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
		}
		else
		{
			if(p->tm_mday < 10)
				sprintf(log_name, "../log/log%d-%d-0%d.log", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
			else
				sprintf(log_name, "../log/log%d-%d-%d.log", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
		}
		FILE *fd = fopen(log_name, "a");
		if(fd == NULL)
		{
			printf("<p>error</p>");
			close(fd_webdata);
			return 0;
		}
		else
		{
			int size = fprintf(fd, "%d-%d-%d_%d:%d:%d logout username:%s,logout\n",(1900+p->tm_year),(1+p->tm_mon), p->tm_mday ,p->tm_hour, p
			->tm_min, p->tm_sec, username);
			fclose(fd);
		}
		
		char shell_str[200] = {};
		sprintf(shell_str, "sudo rm -rf /var/www/session/%s", session_id);
		int ret = system(shell_str);
		if(ret == 0)
		{
			// 把结果发送回去
			printf("<p>success</p>");
		}
		else
		{
			printf("<p>error,删除session失败</p>");
		}
	}
	
    //最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
