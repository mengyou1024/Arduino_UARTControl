#include "master.h"
#include <Arduino.h>

cmdlist_typedef cmd;
char uart_buf[3][20];
void print_string(char* str, char num)//串口输出字符串
{
  
	int i=0;
	switch(num)
	{
	case 0:
	  for(;;)
	  {
		if(str[i]=='\0') break;
		else
		  Serial.print(str[i]);
		i++;
	  }
	  break;
	  
	case 1:
	  for(;;)
	  {
		if(str[i]=='\0') break;
		else
		  Serial1.print(str[i]);
		i++;
	  }
	  break;
	  
	case 2:
	  for(;;)
	  {
		if(str[i]=='\0') break;
		else
		  Serial2.print(str[i]);
		i++;
	  }
	  break;

	case 3:
	  for(;;)
	  {
		if(str[i]=='\0') break;
		else
		  Serial3.print(str[i]);
		i++;
	  }
	  break;
	}
}

char bit_read(char num)
{
	switch(num)
	{
		case 0:
			while(Serial.available()==0);
			return Serial.read();
		case 1:
			while(Serial1.available()==0);
			return Serial1.read();
		case 2:
			while(Serial2.available()==0);
			return Serial2.read();
		case 3:
			while(Serial3.available()==0);
			return Serial3.read();
		default:
			return ' ';
	}
}

void add_cmd(char* str, void (*func)(void))//添加命令
{
	char i;
	for(i=0;i<20;i++)
	{
	cmd.cmdlist[cmd.num].text[i]=str[i];//将命令文本复制到命令列表
	if(str[i]=='\0')
	  break;
	}
	cmd.cmdlist[cmd.num].len = i;//添加命令的长度
	cmd.cmdlist[cmd.num].func = func;//添加函数指针
	cmd.cmdlist[cmd.num].num = cmd.num;//添加命令序号

	cmd.num++;//命令条数+1
	return;
}

char get_num(char* str)
{
	char i,j ;
	for(i=0;i<cmd.num;i++)
	{
	for(j=0;j<cmd.cmdlist[i].len;j++)
	{
	  if(str[j]!= cmd.cmdlist[i].text[j]) break;
	}
	if(j==cmd.cmdlist[i].len) break;  
	}
	if(i==cmd.num) return 255;
	else return i;  
}

void parse_data(void)
{
	char  data, i, j ;
	data = bit_read();
	if(data=='#')
	{
	for(i=0;i<3;i++)
	{
	  for(j=0;j<20;j++)
	  {
		data = bit_read();
		if(data=='|'||data=='%') break;
		uart_buf[i][j] = data;
	  }
	}
	}
  print_string("从机从串口接受到的数据 \r\n");
  print_string("#");
	print_string(uart_buf[1], 1);//发送给从机，第二个参数是输出到几号串口
  print_string("%");
  print_string("\r\n");
  print_string("#");
	print_string(uart_buf[2], 1);//发送给从机，第二个参数是输出到几号串口
  print_string("%");
  print_string("\r\n--------------------\r\n");
	(*cmd.cmdlist[get_num(uart_buf[0])].func)();//调用命令
	//while(Serial.available()>0)data=Serial.read();
}

void print_cmdlist(void)
{
	char i;
	for(i=0;i<cmd.num;i++)
	{
		print_string(cmd.cmdlist[i].text);
		print_string("\r\n");
	}
}
