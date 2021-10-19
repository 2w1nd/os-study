# 闲暇时候看到的知识记录
### 一个程序的运行过程

#### 1. 可执行程序的构成

`gcc -g -wall -v 5-1.c -o 5-1`
gcc的基本格式：gcc 输入文件1 输入文件2 -o 输出文件 [-选项1 -选项2]
-g：在可执行文件中增加调试信息，以便可以使用gdb工具对程序进行动态调试
 &nbsp;&nbsp;&nbsp;使用gdb（调试的是运行时错误，即已经产生可执行文件的情况下）的要求是，可执行文件和源文件必须在同一目录下。
-Wall：将所有警告信息都显示 Warning all
-v：查看详细的编译过程
使用readeIf可以查看符合ELF格式的二进制文件的内容---文件控制信息内容
使用objdump 队医对二进制文件进行反汇编

| 段名 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   | 描述                                                                                                                     |
| ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| text段 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | 代码段，保存可执行指令 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;                                                                    |
| data段 &nbsp;&nbsp;                   | 数据段，保存有非0初始化的全局变量和静态变量，由于没有初始化，因此在硬盘中是不占空间的，仅仅当装入内存运行时临时初始化为0 |
| debug段 &nbsp;                        | 保存动态调试信息                                                                                                         |
| dynamic段 &nbsp;                      | 保存动态链接信息                                                                                                         |
| fini段                                | 保存进程退出时的应该执行的代码                                                                                           |
| ini段                                 | 保存进程加载时的应该执行的代码                                                                                           |
| rodata段                              | 保存只读数据，例如以const修饰的全局变量，字符床常量                                                                      |
| symtab段                              | 保存符号表                                                                                                               |
2. 使用strace查看可执行文件的执行
#### B. 进程运行环境
1. 程序运行的开始之处
 &nbsp;&nbsp;&nbsp;ini段——__attribute__((constructor))初始化进程运行环境，保存断点信息，在C++中，以构造函数的形式提供给用户
 &nbsp;&nbsp;&nbsp;fini段——__attribute__((destructor))恢复断电信息

2. 进程运行如何获取环境信息
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  extern char **environ;
  char **env = environ;
  int i;
  for (i = 0; i < ragc; i ++)
    printf("argc[%d] ：%s\n", i, argv[i]);
    while (*env) {
      printf("%s\n", *\env);
      env ++;
    }
    exit(0);
}
```

### 进程的退出
#### 1. 终止
##### 1.1 exit（正常终止）
&ensp;&ensp;子进程在结束时，会清理系统缓存等资源
&ensp;&ensp;对于多次I/O操作，系统提供三种缓存方式，用于大块数据的交互
&ensp;&ensp;`无缓冲`：没有缓冲区，每次调用stdio库函数（例如：printf，scanf，fprintf，perror等），系统都会立即调用write或read函数进行I/O操作
&ensp;&ensp;`行缓冲`：对于输出流，收到换行符之前，一律缓冲数据，除非系统缓冲区溢出或遇到行缓冲借宿符一换行符才会调用write或read函数进行I/O操作。输入流中，每接受一个回车符就表示一行结束，即行输入流结束。
&ensp;&ensp;`全缓冲`：系统缓冲区未满前，都不会调用write或read函数
##### 1.2 _exit（强制终止）
&ensp;&ensp;子进程在结束时，不会自主清理系统缓冲等资源溢出，另外回调函数和系统析构函数__attribute__((destructor))也不会执行，而直接返回内核
#### 2. 异常
&ensp;&ensp;