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

## 功能说明
应用资源管理系统 当时设计的主要功能对云服务器的应用资源（mysql、apache、gateone等）进行管理（开/关/重启）；还能上传下载文件，当个简易云盘；当然基本的系统状态查看得有；然后就是基础的登录登出；日志管理；用户管理的功能。

# 效果参考
## 登录页
![在这里插入图片描述](https://img-blog.csdnimg.cn/077fe9f5c06a44edb901917c9cc6c27e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_20,color_FFFFFF,t_70,g_se,x_16)
## 功能页-系统状态
![在这里插入图片描述](https://img-blog.csdnimg.cn/7697757bdd1f43f3a43dc82aad73c76c.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBATG92ZeS4tuS8iuWNoea0m-aWrw==,size_20,color_FFFFFF,t_70,g_se,x_16)
## 整体概览
![在这里插入图片描述](https://img-blog.csdnimg.cn/5d83a4bcb548459bbe29a3029293bc53.gif#pic_center)

