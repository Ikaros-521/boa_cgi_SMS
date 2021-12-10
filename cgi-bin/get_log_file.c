#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cgic.h"

#define MAX_NUM 100

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
		DIR *dirptr = NULL;
		struct dirent *dir = NULL;         
		if((dirptr = opendir("/var/www/log")) == NULL)         
		{         
			printf("<p>error,opendir failed!</p>");
			return 1;         
		}         
		
		int file_num = 0;
		char file_name[MAX_NUM][100] = {};
		
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
			
			if(dir->d_type == DT_DIR)
			{
				continue;
			}
			else
			{
				strcpy(file_name[file_num], dir->d_name);
				file_num++;
			}
		}
		closedir(dirptr);
		
		printf("<p>[");
		int i = 0;
		for(i=0; i<file_num; i++)
		{
			printf("{\"name\":\"%s\"}", file_name[i]);
			if(i != file_num-1)
			{
				printf(",");
			}
		}
		printf("]</p>");
	}
	
	//最后记得关闭文件
	close(fd_webdata);
	return 0;
}	