# 前言
相比大家已经看过我之前写的 [嵌入式web服务器BOA+CGI+HTML+MySQL项目实战——Linux](https://blog.csdn.net/Ikaros_521/article/details/102801453)，因为当时也是刚接触，所以其实里面写的比较乱，现在打算直接上一个清爽点的小系统，以方便学习参考。(*当然，这个小系统还有很多设计不合理，不安全的地方，所以大家就当个学习例程就好*）  
**操作系统**：CentOS7 （ubuntu的话 需要自行适配一下）  
**使用的技术和工具等**：
 - C
 - HTML/CSS/JavaScript
 - Ajax
 - sqlite3
 - CGI
 - jQuery
 - bootstrap
 - echarts.js

## 工程下载
[码云](https://gitee.com/ikaros-521/boa_cgi_SMS) [github](https://github.com/Ikaros-521/boa_cgi_SMS)
## 目录说明
**cgi-bin** 存放 `.c .h`和编译好的 `.cgi`文件  
**cloud**  云端资源功能，存储云文件的文件夹  
**css** 存放 `.css`文件  
**file** 存放 用户账号信息文件，数据库文件等  
**img** 存放图片素材  
**js** 存放 `.js`文件  
**log** 存放系统生成的 日志信息  
**session** 存放用户登录生成的session_id  
**html**文件置于根目录  
![在这里插入图片描述](https://img-blog.csdnimg.cn/46c76079eec54565a5bab17365484e10.png)
## 功能说明
应用资源管理系统 当时设计的主要功能对云服务器的应用资源（mysql、apache、gateone等）进行管理（开/关/重启）；还能上传下载文件，当个简易云盘；当然基本的系统状态查看得有；然后就是基础的登录登出；日志管理；用户管理的功能。  
**默认用户名：admin 默认密码：123456**
# 效果参考
## 登录页
![在这里插入图片描述](https://img-blog.csdnimg.cn/077fe9f5c06a44edb901917c9cc6c27e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_20,color_FFFFFF,t_70,g_se,x_16)
## 功能页-系统状态
![在这里插入图片描述](https://img-blog.csdnimg.cn/7697757bdd1f43f3a43dc82aad73c76c.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_20,color_FFFFFF,t_70,g_se,x_16)
## 整体概览
![在这里插入图片描述](https://img-blog.csdnimg.cn/5d83a4bcb548459bbe29a3029293bc53.gif#pic_center)
# 系统分析
## 系统概述
![在这里插入图片描述](https://img-blog.csdnimg.cn/785fde37c9b44f85a08e81eb53ea4d72.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_18,color_FFFFFF,t_70,g_se,x_16)
## 系统功能需求
![在这里插入图片描述](https://img-blog.csdnimg.cn/9cd8d7c09a654e199434aad4a29bf101.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
# 系统设计
## 系统功能模块设计
![在这里插入图片描述](https://img-blog.csdnimg.cn/52cec9ea8daf491dbf5f94551d560d8c.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_13,color_FFFFFF,t_70,g_se,x_16)
## 系统数据存储设计
### 数据文件的结构设计
![在这里插入图片描述](https://img-blog.csdnimg.cn/f9b9547594f24572aa55f5aef032723f.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
# 系统实现
## 1、登录帐号的设计与实现
登录页面不填写会进行相应的前端提示，成功填写但密码或账号错误会提示相应错误信息。系统默认的初始用户名为admin，密码为123456。登录界面的效果如图5.2所示。登录流程如图5.3所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/b5c0e9060d9e4f21a16aa5527e4e151e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
![在这里插入图片描述](https://img-blog.csdnimg.cn/6678f8d9f05f4ffe97ced9c74723f9a0.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_8,color_FFFFFF,t_70,g_se,x_16)
## 2、系统状态的设计与实现
系统状态页面包含云服务器的基础信息以及CPU、内存、硬盘的占用情况。效果图如图5.4所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/dc31f5a24a64446586e4436ed3dd848e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
## 3、应用管理的设计与实现
应用管理页面包含云服务器的应用，分别为MySQL、Apache等。对这些应用程序的开启/关闭/重启、运行状态、设置或关闭开机自启。此模块用户后期还可以DIY拓展，相应功能的基本代码流程大致类似、拓展十分方便。
![在这里插入图片描述](https://img-blog.csdnimg.cn/25d3ad51522f43e396512062357c90dd.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
## 4、云端资源的设计与实现
云端资源页面进入后就会自动获取指定目录下的文件资源，并以表格的形式展示在页面上，页面提供了下载和删除的功能，另外还可以上传文件和搜索文件，可以算是比较齐全的资源管理模块了。效果图如图5.8所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/b41d31fc36014844a7bcd7979fbffd90.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
这里的文件管理涉及到了Linux命令以及标准C语言的文件操作，文件名以json串的格式发回前端，JavaScript对json串进行相应的解析，为表格增加新的行。以下主要展示后端CGI程序的实现代码。
## 5、系统日志的设计与实现
系统日志页面进入就可以获取所有的系统日志（如登录操作、登出操作、关闭开启重启相关的软件、上传了什么文件、删除了什么文件、修改账号和密码等），可以通过日历控件来检索对应时间的日志，方便相关问题的排查和记录、还能监控是否有不明人员进行了操作。可以在前面的代码中发现，相应的操作过后会对操作的类型、操作执行的时间还有相应的操作描述进行日志记录，这就是日志数据的来源。效果图如图5.9所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/d72d5984d74340eba853237036a2e843.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
这里的日志查询涉及了Linux命令以及标准C语言的文件操作相关知识、当然还有必不可少的CGI，对应字段以json串的格式发回前端，JavaScript对收到的json串进行相应的解析，为前端的表格增加新的行。
## 6、用户管理的设计与实现
用户管理页面进入可以看到修改用户名和修改密码两块内容，相互独立操作。修改用户名模块可以回显当前用户名信息，设计十分人性。取消按钮可以清空输入方便错误修改，效果图如图5.10所示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/0033ec3aa0954c16a49958a0f0ab583c.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_16,color_FFFFFF,t_70,g_se,x_16)
用户信息修改同样也是文件操作，解析前端传来的数据，对数据进行校验后，将修改好的数据写入文件，实现信息的修改。
## 7、退出系统的设计与实现
在之前的图中可以发现，这一版本系统的“退出系统”设置在右上角。实现session的清除和页面的跳转。
![在这里插入图片描述](https://img-blog.csdnimg.cn/e19946ae829f4b7caca13d13b18be1b0.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_20,color_FFFFFF,t_70,g_se,x_16)
# 总结
云服务器管理系统网站是基于Boa嵌入式WEB服务器，配合CGI公共网关接口结合C语言进行编写后端程序，配合jQuery和bootstrap前端框架实现前端优化，常见的B/S架构进行开发的。并结合网上的echarts.js插件制作饼图统计。  
本项目搭建与云服务器，与以往的Boa服务器的常见用途不同，算是开拓新方向。当然本项目并不局限于云服务器，只要是Linux系统，都能够进行相应调整后移植。课题结束之后便会以开源项目的形式发布GitHub和码云上供大家学习和拓展。  
应用管理模块因人而异，需要用户根据个人需求进行DIY设计，本人提供的几个例子也做为简单的参考，主要为了开拓用户的视野，发掘新功能。另外本系统的安全方面做的不是很充足，比如在登录页面的账号密码明文传输，在后续可进行相应的加密，如base64、MD5、RSA等，进一步加强系统安全。

