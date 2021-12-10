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
	char *lenstr;
	int fd_webdata=-1;

	if(lenstr=getenv("QUERY_STRING"))
	{
	}
	else
	{
	}
	
	printf("Content_type: text/html\n\n");

	if(strstr(lenstr,"set_password") != NULL)
	{
	
		char cur_password[20] = {};
		char new_password[20] = {};
		char new_password2[20] = {};

		char *temp = lenstr;
		int i = 0;
		temp = strstr(lenstr, "cur:");
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
				cur_password[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "new:");
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
				new_password[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "new2:");
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
				new_password2[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
		

		if(strlen(cur_password) == 0)
		{
			printf("<p>error,当前密码为空</p>");
			return 0;
		}
		if(strlen(new_password) == 0)
		{
			//printf("新密码错误\n\n");
			printf("<p>error,新密码为空</p>");
			return 0;
		}
		if(strlen(new_password2) == 0)
		{
			//printf("确认新密码错误\n\n");
			printf("<p>error,确认新密码为空</p>");
			return 0;
		}

		//printf("当前密码:%s,新密码:%s，确认新密码:%s\n\n",cur_password,new_password,new_password2);
		char *buf = malloc(100);
		FILE *fd = fopen("../file/user.bin", "rb");
		int size = fread(buf, 100, 1, fd);
		fclose(fd);
		//printf("%s",buf);
		char u[20] = {};
		char p[20] = {};
		i = 0;
		temp = strstr(buf,"username");
		if(temp == NULL)
		{
			//printf("用户信息文件错误\n\n");
			printf("<p>error,用户信息文件错误</p>");
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
			//printf("用户信息文件错误\n\n");
			printf("<p>error,用户信息文件错误</p>");
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
		if(0 == strcmp(p,cur_password))
		{
			sprintf(buf,"username:%s\npassword:%s\n",u,new_password);
			FILE *fd2 = fopen("../file/user.bin", "wb");
			size = fwrite(buf, strlen(buf), 1, fd2);
			fclose(fd2);
			printf("<p>success</p>");
		}
		else
		{
			printf("<p>error,cur_password</p>");
		}
		temp = NULL;
		free(buf);
		buf = NULL;
		
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
			if(0 == strcmp(p,cur_password))
			{
				int size3 = fprintf(fd3, "%d-%d-%d_%d:%d:%d user_management-change_password username:%s,have_changed_password \n",(1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday ,ptr->tm_hour, ptr->tm_min, ptr->tm_sec, u);
				fclose(fd3);
			}
			else
			{
				int size3 = fprintf(fd3, "%d-%d-%d_%d:%d:%d user_management-change_password username:%s,changed_password_failed\n",(1900+ptr->tm_year),(1+ptr->tm_mon), ptr->tm_mday ,ptr->tm_hour, ptr->tm_min, ptr->tm_sec, u);
				fclose(fd3);
			}
		}

	}
	//最后记得关闭文件
	close(fd_webdata); 

	return 0;
}
