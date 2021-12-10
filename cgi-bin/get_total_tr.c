#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cgic.h"

#define MAX_NUM 10000

typedef struct LogInfo
{
	char time[40];
	char page[40];
	char describe[140];
}LogInfo;

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

	if(strstr(lenstr,"get") != NULL)
	{
		/* 解析lenstr */
		char start[20] = {};
		char end[20] = {};
		
		char *temp = lenstr;
		int i = 0, j = 0;
		temp = strstr(lenstr, "start:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 6;
		while(1)
		{
			/*
			if(temp[i] == '-' && temp[i+1] == '0')
			{
				start[j] = temp[i];
				j++;
				i += 2;
				continue;
			}
			*/
			if(temp[i] != ',')
			{
				start[j] = temp[i];
				i++;
				j++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		j = 0;
		
		temp = strstr(temp, "end:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 4;
		while(1)
		{
			/*
			if(temp[i] == '-' && temp[i+1] == '0')
			{
				end[j] = temp[i];
				j++;
				i += 2;
				continue;
			}
			*/
			if(temp[i] != ',')
			{
				end[j] = temp[i];
				i++;
				j++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
		
		//printf("start:%s,end:%s\n", start, end);
		
		/* 整合日志 */
		DIR *dirptr = NULL;         
		struct dirent *dir = NULL;         
		if((dirptr = opendir("/var/www/log")) == NULL)         
		{         
			printf("<p>error,opendir failed!</p>");
			return 1;         
		}         
		
		// 清空日志文件
		system("cat /dev/null > /var/www/file/log.log");
		
		int file_num = -2;
		char file_name[30] = {};
		while(dir = readdir(dirptr))         
		{
			if(strcmp(dir->d_name,".") == 0)
			{
				continue;
			}
			if(strcmp(dir->d_name,"..") == 0)
			{
				continue;
			}
			//printf("filename = %s\n", dir->d_name);
			
			// 筛选
			if(strcmp(dir->d_name, start) >= 0 && strcmp(dir->d_name, end) <= 0)
			{
				//sudo cat ../log/log2020-2-18.log >> /var/www/file/log.log
				// 追加入日志文件
				char cmd[256] = {};
				//sprintf(cmd, "sudo cat ../log/%s >> /var/www/file/log.log", dir->d_name);
				sprintf(cmd, "sudo cat ../log/%s /var/www/file/log.log > /var/www/file/log_temp.log", dir->d_name);
				int ret = system(cmd);
				sprintf(cmd, "sudo cat /var/www/file/log_temp.log > /var/www/file/log.log");
				ret = system(cmd);
			}
			else
			{
				//printf("d_name:%s,%d\n", dir->d_name, strcmp(dir->d_name, start));
			}
			file_num++;
		}
		closedir(dirptr);
			
		/* 读取日志行数 */
		FILE * fp = NULL; //文件指针。
		int c, lc=0; //c为文件当前字符，lc为上一个字符，供结尾判断用。
		int line = 0; //行数统计
		fp = fopen("/var/www/file/log.log", "r");//以只读方式打开文件。
		while((c = fgetc(fp)) != EOF) //逐个读入字符直到文件结尾
		{
		    if(c == '\n') line++; //统计行数。
		    lc = c; //保存上一字符。
		}
		fclose(fp); //关闭文件
		if(lc != '\n') line++;//处理末行

		printf("<p>%d</p>", line);
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
