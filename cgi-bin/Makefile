# 添加所有的.c文件
SRCS = $(wildcard ./*.c) 

# 指定 头文件目录
#INCLUDES = -I ./inc

# 指定库目录
#LIBS = -L ./lib

# 指定编译器
CC = gcc
# 指定编译选项（可选）
#CCFLAGS = -g -Wall -O0

# 
INPUT1 = login.o
INPUT2 = get_states.o
INPUT3 = set_mysql.o

INPUT8 = get_username.o
INPUT9 = change_username.o
INPUT10 = change_password.o
INPUT11 = get_mysql_state.o
INPUT12 = logout.o
INPUT13 = get_log.o
INPUT14 = get_query_log.o
INPUT15 = check_session.o
INPUT16 = get_cloud_file.o
INPUT17 = upload.o
INPUT18 = del_cloud_file.o
INPUT19 = get_private_ip.o
INPUT20 = get_apache_state.o
INPUT21 = set_apache.o
INPUT22 = get_squid_state.o
INPUT23 = set_squid.o
INPUT24 = set_deny_ping.o
INPUT25 = set_gateone.o
INPUT26 = get_gateone_state.o
INPUT27 = get_log_file.o
INPUT28 = del_log_file.o
INPUT29 = get_frp_state.o
INPUT30 = set_frp.o
INPUT31 = get_wan_ip.o
INPUT32 = get_remote_addr.o

INPUTLIST=$(INPUT1) $(INPUT2) $(INPUT3)  $(INPUT8) $(INPUT9) $(INPUT10) \
$(INPUT11) $(INPUT12) $(INPUT13) $(INPUT14) $(INPUT15) $(INPUT16) $(INPUT17) $(INPUT18) $(INPUT19) $(INPUT20) $(INPUT21) \
$(INPUT22) $(INPUT23) $(INPUT24) $(INPUT25) $(INPUT26) $(INPUT27) $(INPUT28) $(INPUT29) $(INPUT30) $(INPUT31) $(INPUT32)

# 编译目标列表
OUTPUT1 = login.cgi
OUTPUT2 = get_states.cgi
OUTPUT3 = set_mysql.cgi

OUTPUT8 = get_username.cgi
OUTPUT9 = change_username.cgi
OUTPUT10 = change_password.cgi
OUTPUT11 = get_mysql_state.cgi
OUTPUT12 = logout.cgi
OUTPUT13 = get_log.cgi
OUTPUT14 = get_query_log.cgi
OUTPUT15 = check_session.cgi
OUTPUT16 = get_cloud_file.cgi
OUTPUT17 = upload.cgi
OUTPUT18 = del_cloud_file.cgi
OUTPUT19 = get_private_ip.cgi
OUTPUT20 = get_apache_state.cgi
OUTPUT21 = set_apache.cgi
OUTPUT22 = get_squid_state.cgi
OUTPUT23 = set_squid.cgi
OUTPUT24 = set_deny_ping.cgi
OUTPUT25 = set_gateone.cgi
OUTPUT26 = get_gateone_state.cgi
OUTPUT27 = get_log_file.cgi
OUTPUT28 = del_log_file.cgi
OUTPUT29 = get_frp_state.cgi
OUTPUT30 = set_frp.cgi
OUTPUT31 = get_wan_ip.cgi
OUTPUT32 = get_remote_addr.cgi

# ...
OUTPUTLIST=$(OUTPUT1) $(OUTPUT2) $(OUTPUT3)  $(OUTPUT8) $(OUTPUT9) $(OUTPUT10) \
$(OUTPUT11) $(OUTPUT12) $(OUTPUT13) $(OUTPUT14) $(OUTPUT15) $(OUTPUT16) $(OUTPUT17) $(OUTPUT18) $(OUTPUT19) $(OUTPUT20) $(OUTPUT21) \
$(OUTPUT22) $(OUTPUT23) $(OUTPUT24) $(OUTPUT25) $(OUTPUT26) $(OUTPUT27) $(OUTPUT28) $(OUTPUT29) $(OUTPUT30) $(OUTPUT31) $(OUTPUT32)

# 将 所有的目标作为一个列表，便于make clean
all : $(OUTPUTLIST)

# 编译目标1
$(OUTPUT1) : $(INPUT1)
	@$(CC) $^ cgic.c base64.c -o $@ 
$(OUTPUT2) : $(INPUT2)
	@$(CC) $^ cgic.c -o $@ 
$(OUTPUT3) : $(INPUT3)
	@$(CC) $^ cgic.c -o $@ 

$(OUTPUT8) : $(INPUT8)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT9) : $(INPUT9)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT10) : $(INPUT10)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT11) : $(INPUT11)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT12) : $(INPUT12)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT13) : $(INPUT13)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT14) : $(INPUT14)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT15) : $(INPUT15)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT16) : $(INPUT16)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT17) : $(INPUT17)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT18) : $(INPUT18)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT19) : $(INPUT19)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT20) : $(INPUT20)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT21) : $(INPUT21)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT22) : $(INPUT22)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT23) : $(INPUT23)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT24) : $(INPUT24)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT25) : $(INPUT25)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT26) : $(INPUT26)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT27) : $(INPUT27)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT28) : $(INPUT28)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT29) : $(INPUT29)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT30) : $(INPUT30)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT31) : $(INPUT31)
	@$(CC) $^ cgic.c -o $@
$(OUTPUT32) : $(INPUT32)
	@$(CC) $^ cgic.c -o $@

%.o : %.c
	@$(CC) -c $<

clean:
	@rm $(OUTPUTLIST)

rm:
	@rm $(INPUTLIST)

