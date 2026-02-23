#ifndef __ADC0809_H_
#define __ADC0809_H_

#include<reg51.h>
//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--定义使用的IO口--// P1数据口
sbit adc0809_clk  =P3^7;
sbit adc0809_start=P3^6;
sbit adc0809_eoc  =P3^5;
sbit adc0809_oe	  =P3^4;

//--声明全局函数--//
void adc0809_init();//初始化
uchar adc0809_read();//读取

#endif
