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
	char describe[100];
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
		//char start[13] = {};
		//char end[13] = {};
		char start_y[5] = {};
		char start_m[3] = {};
		char start_d[3] = {};
		char end_y[5] = {};
		char end_m[3] = {};
		char end_d[3] = {};
		int flag = 0;
		int flag2 = 0;
		int i = 0;
		int j = 0;
		
		char* temp = strstr(lenstr,"start");
		temp += 6;
		//puts(temp);
		while(1)
		{
			if(temp[i] == ',' || temp[i] == '\0' || temp[i] == '\n')
			{
				break;
			}
			if(temp[i] == '-')
			{
				flag++;
				i++;
				j = 0;
				continue;
			}
			if(flag == 0)
			{
				start_y[j] = temp[i];
				i++;
				j++;
			}
			else if(flag == 1)
			{
				if(temp[i] == '0' && j == 0 && flag2 == 0)
				{
					//printf("temp:%c,j:%d,flag2:%d ",temp[i],j,flag2);
					flag2 = 1;
					i++;
				}
				else
				{
					//printf("temp:%c,j:%d,flag2:%d ",temp[i],j,flag2);
					start_m[j] = temp[i];
					i++;
					j++;
					flag2 = 0;
				}
			}
			else if(flag == 2)
			{
				if(temp[i] == '0' && j == 0 && flag2 == 0)
				{
					flag2 = 1;
					i++;
				}
				else
				{
					start_d[j] = temp[i];
					i++;
					j++;
					flag2 = 0;
				}
			}
			else
			{
				break;
			}
		}
		i = 0;
		j = 0;
		flag = 0;
		
		temp = strstr(lenstr,"end");
		temp += 4;
		while(1)
		{
			if(temp[i] == ',' || temp[i] == '\0' || temp[i] == '\n')
			{
				break;
			}
			if(temp[i] == '-')
			{
				flag++;
				j = 0;
				i++;
				continue;
			}
			if(flag == 0)
			{
				end_y[j] = temp[i];
				i++;
				j++;
			}
			else if(flag == 1)
			{
				if(temp[i] == '0' && j == 0 && flag2 == 0)
				{
					flag2 = 1;
					i++;
				}
				else
				{
					end_m[j] = temp[i];
					i++;
					j++;
					flag2 = 0;
				}
			}
			else if(flag == 2)
			{
				if(temp[i] == '0' && j == 0 && flag2 == 0)
				{
					flag2 = 1;
					i++;
				}
				else
				{
					end_d[j] = temp[i];
					i++;
					j++;
				}
			}
			else
			{
				break;
			}
		}
		i = 0;
		j = 0;
		flag = 0;
		
		//puts(start_y);
		//puts(start_m);
		//puts(start_d);
		//puts(end_y);
		//puts(end_m);
		//puts(end_d);
	
		LogInfo *LI;
		LI = calloc(MAX_NUM,sizeof(LogInfo));
		FILE* fsp = fopen("../file/log.log","r");
		int log_num = 0;
		i = 0;
		j = 0;
		
		int m = 0,n = 0;
		for(i=0; i<MAX_NUM; i++)
		{
			char y[5] = {};
			char month[3] = {};
			char d[3] = {};
			int num = 0;
			num = fscanf(fsp,"%s %s %s",LI[i].time,LI[i].page,LI[i].describe);
			if(num == -1) break;
			//puts(LI[i].time);
			
			// 提取年月日
			temp = LI[i].time;
			while(1)
			{
				//printf("temp[%d]:%c\n",m,temp[m]);
				if(temp[m] == '_' || temp[m] == '\0' || temp[m] == '\n')
				{
					break;
				}
				if(temp[m] == '-')
				{
					flag++;
					n = 0;
					m++;
					continue;
				}
				if(flag == 0)
				{
					y[n] = temp[m];
					m++;
					n++;
				}
				else if(flag == 1)
				{
					month[n] = temp[m];
					m++;
					n++;
				}
				else if(flag == 2)
				{
					d[n] = temp[m];
					m++;
					n++;
				}
				else
				{
					break;
				}
			}
			m = 0;
			n = 0;
			flag = 0;
			temp = NULL;
			
			//puts(y);
			//puts(month);
			//puts(d);
			
			
			if(strcmp(start_y,y) > 0 || strcmp(end_y,y) < 0)
			{
				memset(&LI[i],0,sizeof(LogInfo));
				i--;
				continue;
			}
			if(strcmp(start_y,y) == 0 && strlen(start_m) > strlen(month) || strcmp(end_y,y) == 0 && strlen(end_m) < strlen(month))
			{
				memset(&LI[i],0,sizeof(LogInfo));
				i--;
				continue;
			}
			if(strcmp(start_y,y) == 0 && strcmp(start_m,month) > 0 || strcmp(end_y,y) == 0 && strcmp(end_m,month) < 0)
			{
				//printf("end_m:%s,month:%s\n",end_m,month);
				memset(&LI[i],0,sizeof(LogInfo));
				i--;
				continue;
			}
			if(strcmp(start_y,y) == 0 && strcmp(start_m,month) == 0 && strlen(start_d) > strlen(d) || strcmp(end_y,y) == 0 && strcmp(end_m,month) == 0 && strlen(end_d) < strlen(d))
			{
				memset(&LI[i],0,sizeof(LogInfo));
				i--;
				continue;
			}
			if(strcmp(start_y,y) == 0 && strcmp(start_m,month) == 0 && strcmp(start_d,d) > 0 || strcmp(end_y,y) == 0 && strcmp(end_m,month) == 0 && strcmp(end_d,d) < 0)
			{
				memset(&LI[i],0,sizeof(LogInfo));
				i--;
				continue;
			}

			
			log_num++;
		}
	
		//printf("log_num:%d\n",log_num);
	
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
