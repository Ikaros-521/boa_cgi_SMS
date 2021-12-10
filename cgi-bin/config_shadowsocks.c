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

int if_ipv4(const char *str)
{
	struct in_addr addr;
	int ret;
	volatile int local_errno;

	errno = 0;
	ret = inet_pton(AF_INET, str, &addr);
	local_errno = errno;
	/*
	if (ret > 0)
		fprintf(stderr, "\"%s\" is a valid IPv4 address\n", str);
	else if (ret < 0)
		fprintf(stderr, "EAFNOSUPPORT: %s\n", strerror(local_errno));
	else 
		fprintf(stderr, "\"%s\" is not a valid IPv4 address\n", str);
	*/
	return ret;
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

	if(strstr(lenstr,"config_shadowsocks") != NULL)
	{
		//server,server_port,local_address,local_port,password,timeout,method,fast_open,workers
		char server[20] = {};
		char server_port[8] = {};
		char local_address[20] = {};
		char local_port[8] = {};
		char password[20] = {};
		char timeout[10] = {};
		char method[20] = {};
		char fast_open[10] = {};
		char workers[4] = {};
	
		// 对接收到的数据进行解析
		int i = 0;
		char *temp = lenstr;
		temp = strstr(lenstr, "server:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 7;
		while(1)
		{
			if(temp[i] != ',')
			{
				server[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "server_port:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 12;
		while(1)
		{
			if(temp[i] != ',')
			{
				server_port[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "local_address:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 14;
		while(1)
		{
			if(temp[i] != ',')
			{
				local_address[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;

		temp = strstr(lenstr, "local_port:");
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
				local_port[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "password:");
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
				password[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "timeout:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 8;
		while(1)
		{
			if(temp[i] != ',')
			{
				timeout[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "method:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 7;
		while(1)
		{
			if(temp[i] != ',')
			{
				method[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "fast_open:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 10;
		while(1)
		{
			if(temp[i] != ',')
			{
				fast_open[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		
		temp = strstr(temp, "workers:");
		if(temp == NULL)
		{
			printf("<p>error,JS发送数据错误</p>");
			close(fd_webdata);
			return 0;
		}
		temp += 8;
		while(1)
		{
			if(temp[i] != ',')
			{
				workers[i] = temp[i];
				i++;
			}
			else
			{
				break;
			}   
		}
		i = 0;
		temp = NULL;
		
		// 判空
		if(strlen(server) == 0 || strlen(server_port) == 0 || strlen(local_address) == 0 || strlen(local_port) == 0 || strlen(password) == 0 ||
		strlen(timeout) == 0 || strlen(method) == 0 || strlen(fast_open) == 0 || strlen(workers) == 0)
		{
			printf("<p>error 含有空数据</p>");
			close(fd_webdata);
			return 0;
		}
		
		if(if_ipv4(server) <= 0)
		{
			printf("<p>error server</p>");
			close(fd_webdata);
			return 0;
		}
		if(if_ipv4(local_address) <= 0)
		{
			printf("<p>error local_address</p>");
			close(fd_webdata);
			return 0;
		}
		
		//printf("<p>server:%s,server_port:%s,local_address:%s,local_port:%s,password:%s,timeout:%s,method:%s,fast_open:%s,workers:%s</p>",server, server_port, local_address, local_port, password, timeout, method, fast_open, workers);
		
		// 对系统文件进行操作
		system("sudo chmod 777 /etc/shadowsocks.json"); // 修改文件权限
		system("sudo cp /etc/shadowsocks.json /etc/shadowsocks.json.bak"); // 备份
		system("sudo chmod 777 /etc/shadowsocks.json.bak"); // 修改备份文件权限备份
		//system("sudo cat /dev/null > /etc/shadowsocks.json"); // 置空
		
		// 打开配置文件并写入获取到的配置
		FILE *fd = fopen("/etc/shadowsocks.json", "w");
		if(fd == NULL)
		{
			printf("<p>error,打开配置文件失败</p>");
		}
		else
		{
			int size = fprintf(fd, "{\n\"server\":\"%s\",\n\"server_port\":%s,\n\"local_address\":\"%s\",\n\"local_port\":%s,\n\"password\":\"%s\",\n\
\"timeout\":%s,\n\"method\":\"%s\",\n\"fast_open\":%s,\n\"workers\":%s\n}",
			server, server_port, local_address, local_port, password, timeout, method, fast_open, workers);
			fclose(fd);
		}
		
		// 返回执行结果
		printf("<p>success</p>");
		
		
		// 获取系统时间
		char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
		time_t timep;
		struct tm *p;
		time(&timep);
		p=localtime(&timep); //取得当地时间
		
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
			printf("<p>error,写入日志失败</p>");
		}
		else
		{
			int size2 = fprintf(fd2, "%d-%d-%d_%d:%d:%d shadowsocks config_shadowsocks\n"
			,(1900+p->tm_year),(1+p->tm_mon), p->tm_mday ,p->tm_hour, p->tm_min, p->tm_sec);
			fclose(fd2);
		}
	} 
	//最后记得关闭文件
	close(fd_webdata);

	return 0;
}
