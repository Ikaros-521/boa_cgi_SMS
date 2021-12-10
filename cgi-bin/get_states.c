#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/vfs.h>
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

	if(strstr(lenstr,"get_states") != NULL)
	{	
		// memory
		double memory_have = 0;
		system("sudo free -m | grep Mem > memory.txt");
		system("sudo chmod 777 memory.txt");
		FILE * fp;
		fp = fopen ("memory.txt", "r");
		if(fp == NULL)
		{
			printf("<p>open file:memory.txt error</p>");
			return 0;
		}
		char s1[20] = {};
		double total = 0;
		double used = 0;
		fscanf(fp, "%s %f %f", s1, &total, &used);
		fclose(fp);
		fp = NULL;
		memory_have = 100 - ((100 * used) / total);

	
		// disk
		int disk_have = 0;
		struct statfs sfs;
		int ret = statfs("/", &sfs);
		disk_have = (sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks - sfs.f_bfree + sfs.f_bavail) + 1;
		
		// cpu
		system("sudo cat /proc/stat | head -1 > cpu.txt");
		system("sudo chmod 777 cpu.txt");
		fp = fopen ("cpu.txt", "r");
		if(fp == NULL)
		{
			printf("<p>open file:cpu.txt error</p>");
			return 0;
		}
		char str1[20] = {};
		int user, nice, system2, idle;
		fscanf(fp, "%s %d %d %d %d", str1, &user, &nice, &system2, &idle);
		fclose(fp);
		fp = NULL;
		double cpu_have = 100 * (user + nice + system2) / (user + nice + system2 + idle);

		printf("<p>{\"cpu\":\"%.1f\",\"disk\":\"%d\",\"memory\":\"%.1f\"}</p>", cpu_have, disk_have, memory_have);		
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
