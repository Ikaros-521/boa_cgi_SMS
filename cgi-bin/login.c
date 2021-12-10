#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cgic.h"
#include "base64.h"

#define SESSION_ID_LEN 45


int cgiMain(void)
{
	char username[20] = {};
	char password[32] = {};
	//回显信息到HTML网页cgiHeaderContentType("text/html");
	printf("<html>\n\n");
	printf("<head>\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	
	printf("<script src=\"../js/jquery-2.2.3.min.js\"></script>");
	printf("<link type=\"text/css\" href=\"../css/jquery-ui.min.css\" rel=\"stylesheet\">");
	printf("<link href=\"../css/bootstrap.min.css\" rel=\"stylesheet\">");
	printf("<script src=\"../js/bootstrap.min.js\"></script>");
	
	printf("</head>\n\n");
	printf("<body>\n\n");

	if(cgiFormString("username", username, sizeof(username)) != cgiFormSuccess)
	{
		fprintf(stderr, "cgiFormString function username failed");
		//exit(-1);
	}
	// password gateway server_ip dns subnet_mask dhcp error
	if(cgiFormString("password", password, sizeof(password)) != cgiFormSuccess)
	{
		fprintf(stderr, "cgiFormString function password failed");
		//exit(-1);
	}
	//printf("用户名:%s\n\n",username);
	//printf("密码:%s\n\n",password);

	char *buf = malloc(100);
	FILE *fd = fopen("../file/user.bin", "rb");
	if(fd == NULL)
	{
		printf("<script>alert(\"用户信息文件错误\");</script>");
		return 0;
	}
	int size = fread(buf, 100, 1, fd);
	fclose(fd);
	char u[20] = {};
	char p[20] = {};
	int i = 0;
	char *temp = strstr(buf,"username");
	if(temp == NULL)
	{
		printf("<script>alert(\"用户信息文件错误\");</script>");
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
		printf("<script>alert(\"用户信息文件错误\");</script>");
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
	temp = NULL;
	free(buf);
	buf = NULL;
	
	char *remote_host = NULL;
	remote_host = getenv("REMOTE_HOST");
	if(remote_host != NULL)
	{
		printf("<p>remote_host:%s</p>", remote_host);
		return 0;
	}
	else
	{
		//printf("<p>remote_host:NULL</p>");
		//return 0;
	}
	
	char* base_p = malloc(32);
	base_p = (char*)base64_decode((unsigned char*)password);
	if(0 == strcmp(u,username) && 0 == strcmp(p,base_p))
	{
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
			// 写入登陆信息到日志
			int size4 = fprintf(fd2, "%d-%d-%d_%d:%d:%d login username:%s,login\n",(1900+p->tm_year),(1+p->tm_mon), p->tm_mday ,p->tm_hour, p
			->tm_min, p->tm_sec, username);
			
			fclose(fd2);
		}

		// set session_id
		// 字符表
		char table[62] = {'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		char session_id[SESSION_ID_LEN] = {};
		struct timeval tv;
		gettimeofday(&tv, NULL);
		//printf("tv_sec:%d\n",tv.tv_sec);
		//printf("tv_usec:%d\n",tv.tv_usec);

		srand(tv.tv_sec * 1000000 + tv.tv_usec);
		for(i=0; i<SESSION_ID_LEN; i++)
		{
			session_id[i] = table[rand() % 62];
		}
		session_id[SESSION_ID_LEN] = '\0';
		
		char path[100] = {};
		sprintf(path, "/var/www/session/%s", session_id);
		FILE* fd_s = fopen(path, "w");
		if(fd_s == NULL)
		{
			printf("<script>alert(\"打开session失败\");</script>");
			return 0;
		}
		fprintf(fd_s, "%ld",tv.tv_sec);
		fclose(fd_s);

		printf("<script>\
		sessionStorage.setItem('username',\"%s\");\
		sessionStorage.setItem('password',\"true\");\
		sessionStorage.setItem('session_id', \"%s\");\
		sessionStorage.setItem('sec', \"%ld\");\
		</script>\n\n",username, session_id, tv.tv_sec);
		//printf("<script>\
		var storage = window.localStorage;\
		storage.setItem('username',\"%s\");\
		storage.setItem('password',\"true\");\
		</script>\n\n",username);
		printf("<meta http-equiv=Refresh content=1;URL=../SMS.html>\n\n"); 
	}
	else
	{
		printf("<script>\
		alert(\"帐号或密码错误\");\
		</script>\n\n");
		printf("<meta http-equiv=Refresh content=1;URL=../login.html>\n\n"); 
	}
	free(base_p);
	base_p = NULL;
	return 0;
}
