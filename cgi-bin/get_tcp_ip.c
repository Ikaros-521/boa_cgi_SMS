/*************************************************************************
    > File Name: get_tcp_ip.c
  > Author: hlx
  > Mail: 327209194@qq.com 
  > Created Time: 2020年01月16日 星期四 10时42分29秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

	if(strstr(lenstr,"get_info") != NULL)
	{
		char buf[1024] = {};
		// 网卡配置文件修改为你的路径
		int fd = open("/etc/sysconfig/network-scripts/ifcfg-enp1s0", O_RDONLY);
		if(fd == -1)
		{
			printf("<p>error,网卡文件打开失败</p>");
			return 0;
		}
		int size = read(fd, buf, 1024);
		close(fd);
		//printf("%s",buf);
		
		char dhcp1[20] = {};
		char ip[20] = {};
		char netmask[20] = {};
		char gateway[20] = {};
		char dhcp2[20] = {};
		char dns1[20] = {};
		char dns2[20] = {};
		char network_card[20] = {};
		int flag = 0;
		
		int i = 0;
		int j = 0;
		char *temp = strstr(buf,"BOOTPROTO");
		if(temp == NULL)
		{
			printf("<p>error,网卡文件错误</p>");
			return 0;
		}
		temp += 10;
		while(1)
		{
			if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
			{
				break;
			}
			if(temp[i] != '"')
			{
				dhcp1[j++] = temp[i];
			}
			i++;
		}
		temp = NULL;
		i = 0;
		j = 0;
		
		temp = strstr(buf,"IPADDR");
		if(temp != NULL)
		{
			temp += 7;
			while(1)
			{
				if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
				{
					break;
				}
				if(temp[i] != '"')
				{
					ip[j++] = temp[i];
				}
				i++;
			}
			temp = NULL;
			i = 0;
			j = 0;
		}
		
		temp = strstr(buf,"NETMASK");
		if(temp != NULL)
		{

			temp += 8;
			while(1)
			{
				if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
				{
					break;
				}
				if(temp[i] != '"')
				{
					netmask[j++] = temp[i];
				}
				i++;
			}
			temp = NULL;
			i = 0;
			j = 0;
		}
		
		temp = strstr(buf,"GATEWAY");
		if(temp != NULL)
		{
			temp += 8;
			while(1)
			{
				if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
				{
					break;
				}
				if(temp[i] != '"')
				{
					gateway[j++] = temp[i];
				}
				i++;
			}
			temp = NULL;
			i = 0;
			j = 0;
		}
		
		if(strstr(buf,"DNS1") == NULL && strstr(buf,"DNS2") == NULL)
		{
			sprintf(dhcp2, "dhcp");
		}
		else
		{
			sprintf(dhcp2, "static");
		}
		
		temp = strstr(buf,"DNS1");
		if(temp != NULL)
		{
			temp += 5;
			while(1)
			{
				if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
				{
					break;
				}
				if(temp[i] != '"')
				{
					dns1[j++] = temp[i];
				}
				i++;
			}
			temp = NULL;
			i = 0;
			j = 0;
		}
		
		temp = strstr(buf,"DNS2");
		if(temp != NULL)
		{
			temp += 5;
			while(1)
			{
				if(temp[i] == '\n' || temp[i] == ' ' || temp[i] == '\0')
				{
					break;
				}
				if(temp[i] != '"')
				{
					dns2[j++] = temp[i];
				}
				i++;
			}
			temp = NULL;
			i = 0;
			j = 0;
		}
		
		printf("<p>{\"DHCP1\":\"%s\",\"IP\":\"%s\",\"NETMASK\":\"%s\",\"GATEWAY\":\"%s\",\"DHCP2\":\"%s\",\"DNS1\":\"%s\",\"DNS2\":\"%s\"}</p>", dhcp1, ip, netmask, gateway, dhcp2, dns1, dns2);
	}

	//最后记得关闭文件
	close(fd_webdata);

	return 0; 
} 
