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

	if(strstr(lenstr,"get_info") != NULL)
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
			file_num++;
		}
		closedir(dirptr);
			
		/* 读取日志并打印 */
		LogInfo *LI;
		LI = calloc(MAX_NUM,sizeof(LogInfo));
		FILE* fsp = fopen("../file/log.log","r");
		int log_num = 0;
		j = 0;
		i = 0;
		for(i = 0; i < MAX_NUM; i++)
		{
			int num = 0;
			num = fscanf(fsp,"%s %s %s",LI[i].time,LI[i].page,LI[i].describe);
			if(num == -1) break;
			log_num++;
		}
	
		printf("<p>[");
		for(i=0; i<log_num; i++)
		{
			printf("{\"time\":\"%s\",\"page\":\"%s\",\"describe\":\"%s\"}",LI[i].time,LI[i].page,LI[i].describe);
			if(i != log_num-1)
				printf(",");
		}
		printf("]</p>");

	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
