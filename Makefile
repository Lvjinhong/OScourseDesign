# 定义编译器
CC = gcc

# 定义编译器标志
# CFLAGS = -Wall

# 定义目标可执行文件
TARGET = main

# 定义对象文件
OBJS = build/main.o build/priority.o   build/HRRN.o build/SRT.o build/FCFS.o build/SJF.o build/RR.o
# 定义 build 目录
BUILD_DIR = build

# 默认目标
all: $(BUILD_DIR) $(TARGET)

# 创建 build 目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 构建目标可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 依赖规则
build/main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o build/main.o
	
build/priority.o: priority.c main.h
	$(CC) $(CFLAGS) -c priority.c -o build/priority.o
# 编译规则
build/RR.o: RR.c
	$(CC) $(CFLAGS) -c RR.c -o build/RR.o

build/HRRN.o: HRRN.c
	$(CC) $(CFLAGS) -c HRRN.c -o build/HRRN.o

build/SRT.o: SRT.c
	$(CC) $(CFLAGS) -c SRT.c -o build/SRT.o

build/FCFS.o: FCFS.c
	$(CC) $(CFLAGS) -c FCFS.c -o build/FCFS.o

build/SJF.o: SJF.c
	$(CC) $(CFLAGS) -c SJF.c -o build/SJF.o


# 清理编译生成的文件
clean:
	rm -rf $(TARGET) $(BUILD_DIR)

# 伪目标
.PHONY: all clean