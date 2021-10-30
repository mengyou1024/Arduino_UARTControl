#ifndef __MASTER__H
#define __MASTER__H
typedef struct
{
  char text[20];
  char num;
  char len;
  void (*func)(void);
}cmd_typedef;//命令类型数据结构

typedef struct
{
  cmd_typedef cmdlist[25];
  char num=0;
}cmdlist_typedef;//命令列表

extern cmdlist_typedef cmd;
extern char uart_buf[3][20];//数据

void print_string(char* str, char num=1);//串口输出字符串
char bit_read(char num=1);//从串口读取一个字符， 阻塞式
void add_cmd(char* str, void (*func)(void));//添加命令， 第一个为命令调用的字符串， 第二个为函数指针
char get_num(char* str);  //获取字符串在命令列表中的序号， 无效则返回255
void parse_data(void);//解析串口数据
void print_cmdlist(void);//输出命令列表
#endif
