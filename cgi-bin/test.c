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
#include <sqlite3.h>
#include "cgic.h"


#define SESSION_ID_LEN 45


int cgiMain(void)
{
	char username[21] = {};
	char password[40] = {};
	//回显信息到HTML网页cgiHeaderContentType("text/html");
	printf("<html>\n\n");
	printf("<head>\n\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\n");
	
	printf("<script src=\"../js/jquery-ui.min.js\"></script>");
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
	
	char u[21] = {};
	char pw[40] = {};
	sqlite3 *db;
	int result;
	char *errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;
	int i, j;
	int index;

	result = sqlite3_open("/var/www/file/sms.db", &db);
	if(result != SQLITE_OK)
	{
		printf("数据库打开失败");
		return -1;
	}

	//数据库操作代码
	//开始查询，传入的 dbResult 已经是 char **，这里又加了一个 & 取地址符，传递进去的就成了 char ***
	char sql_str[400] = {};
	snprintf(sql_str, 400, "select * from user where username='%s' and password='%s'", username, password);
	result = sqlite3_get_table(db, sql_str, &dbResult, &nRow, &nColumn, &errmsg);
	// 查询成功
	if(SQLITE_OK == result)
	{
		if(nRow > 0)
		{
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
			
			snprintf(sql_str, 400, "update user set session_id='%s',sec=%ld where username='%s'", session_id, tv.tv_sec, username);
			result = sqlite3_exec(db, sql_str, 0, 0, &errmsg);
			if(SQLITE_OK != result)
			{
				printf("更新数据失败");
				sqlite3_free_table(dbResult);
				//关闭数据库
				sqlite3_close(db);
				return -1;
			}
		
			char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
			time_t timep;
			struct tm *p;
			time(&timep);
			p = localtime(&timep); /*取得当地时间*/
			

			printf("<script>\
			sessionStorage.setItem('username',\"%s\");\
			sessionStorage.setItem('password',\"true\");\
			sessionStorage.setItem('birth', \"true\");\
			sessionStorage.setItem('session_id', \"%s\");\
			sessionStorage.setItem('sec', \"%ld\");\
			</script>\n\n",username, session_id, tv.tv_sec);
			//printf("<script>\
			var storage = window.localStorage;\
			storage.setItem('username',\"%s\");\
			storage.setItem('password',\"true\");\
			</script>\n\n",username);
			printf("<script>alert('success')</script>"); 
		}
		else
		{
			printf("<script>\
			alert(\"帐号或密码错误\");\
			</script>\n\n");
			printf("<meta http-equiv=Refresh content=1;URL=../test.html>\n\n"); 
		}
	}
	else
	{
		printf("<script>alert(\"查询数据失败\");</script>");
		return -1;
	}

	//到这里，不论数据库查询是否成功，都释放 char** 查询结果，使用 sqlite 提供的功能来释放
	sqlite3_free_table(dbResult);

	//关闭数据库
	sqlite3_close(db);
	
	//free(base64_p);
	//base64_p = NULL;
	return 0;
}
