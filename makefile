CC=gcc
CPPFLAGS= -I./inc -I /usr/local/include/hiredis/
CFLAGS=-Wall -std=c99
LIBS= -lhiredis

#找到当前目录下所有的.c文件
src = $(wildcard ./src/*.c)

#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))

#目标
redis_api_test=./src/redis_api_test
redis_op_test=./src/redis_op_test
target=$(redis_api_test) $(redis_op_test)

ALL:$(target)

#生成所有的.o文件
$(obj):%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 


$(redis_api_test):./src/redis_api_test.o
	$(CC) $^ -o $@ $(LIBS)

$(redis_op_test):./src/redis_op_test.o ./src/redis_op.o ./src/make_log.o
	$(CC) $^ -o $@ $(LIBS)

#clean指令
clean:
	-rm -rf $(obj)  

distclean:
	-rm -rf $(obj)  

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
