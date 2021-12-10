#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "cgic.h"

#define BURSIZE 1024

// 16转10
int hex2dec(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    else if ('a' <= c && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else if ('A' <= c && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else
    {
        return -1;
    }
}

// 10转16
char dec2hex(short int c)
{
    if (0 <= c && c <= 9)
    {
        return c + '0';
    }
    else if (10 <= c && c <= 15)
    {
        return c + 'A' - 10;
    }
    else
    {
        return -1;
    }
}
 
 
//编码一个url 
void urlencode(char url[])
{
    int i = 0;
    int len = strlen(url);
    int res_len = 0;
    char res[BURSIZE];
    for (i = 0; i < len; ++i)
    {
        char c = url[i];
        if (    ('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z') ||
                c == '/' || c == '.')
        {
            res[res_len++] = c;
        }
        else
        {
            int j = (short int)c;
            if (j < 0)
                j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1 * 16;
            res[res_len++] = '%';
            res[res_len++] = dec2hex(i1);
            res[res_len++] = dec2hex(i0);
        }
    }
    res[res_len] = '\0';
    strcpy(url, res);
}
 
// 解码url
void urldecode(char url[])
{
    int i = 0;
    int len = strlen(url);
    int res_len = 0;
    char res[BURSIZE];
    for (i = 0; i < len; ++i)
    {
        char c = url[i];
        if (c != '%')
        {
            res[res_len++] = c;
        }
        else
        {
            char c1 = url[++i];
            char c0 = url[++i];
            int num = 0;
            num = hex2dec(c1) * 16 + hex2dec(c0);
            res[res_len++] = num;
        }
    }
    res[res_len] = '\0';
    strcpy(url, res);
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

	printf("Content_type: text/html\n\n");

	int i = 0;

	if(strstr(lenstr,"del_file") != NULL)
	{
		//printf("%s",lenstr);


		char file_name[1024] = {};

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

		//printf("file_name:%s\n\n", file_name);
		urldecode(file_name);
		//printf("file_name:%c\n\n", file_name);

		char buf[1024] = {};
		sprintf(buf, "sudo rm -f /var/www/cloud/%s > /dev/null 2>&1", file_name);
		system(buf);

		printf("<p>%s已删除</p>", file_name);
		
		// 获取系统时间
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
		FILE *fd2 = fopen(log_name, "a");
		if(fd2 == NULL)
		{
			printf("<script>alert(\"写入日志失败\");</script>");
		}
		else
		{
			int size2 = fprintf(fd2, "%d-%d-%d_%d:%d:%d cloud_resources delete_a_file_named:%s\n",(1900+p->tm_year),(1+p->tm_mon), p->tm_mday ,p->tm_hour, p->tm_min, p->tm_sec, file_name);
			fclose(fd2);
		}

	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
