#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgic.h"

int cgiMain(void)
{
	// 用于接收环境变量QUERY_STRING
	char *lenstr = NULL;

	// 搜索环境变量 QUERY_STRING,并返回相关的值给字符串lenster。
	lenstr = getenv("QUERY_STRING");
	// 若没有找到环境变量 QUERY_STRING,直接return
	if (lenstr == NULL)
	{
		return -1;
	}

	// 使用MIME头信息″Content-type: text/html\n\n″来输出HTML源代码给Web服务器。
	// 请注意任何MIME头信息后必须有一个空行。一旦发送这个MIME头信息给Web服务器后,Web浏览器将认为随后的文本输出为HTML源代码
	printf("Content-type: text/html\n\n");
	
	printf("<p>汝之IP乃%s，莫慌，吾已敲汝门！</p>", cgiRemoteAddr);
	return 0;
}