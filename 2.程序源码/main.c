#include"reg51.h"
#include"ADC0809.h"
#define uchar unsigned char
#define uint unsigned int
sbit out1=P2^0;//电机	
sbit out2=P2^1;
sbit smg1=P2^2;//数码管
sbit smg2=P2^3;
sbit smg3=P2^4;
sbit smg4=P2^5;
sbit led1=P3^1;//LED
sbit led2=P3^2;
sbit led3=P3^3;
//数码管编码
uchar code smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar fang=0;//方向
uchar rain=0;//雨量
uchar pwm=0;//档位
uchar time=0,sec=0;//定时
uchar cishu=0;
/*
提供 毕设咨询、购买实物、毕设指导、论文编写 服务

联系我：
方式一：
	打开下方链接，微信扫描咨询：
	https://docs.qq.com/doc/DVm51bXRXS2FGZHds
方式二：
	添加微信：aerb2022  咨询

更多设计视频请查看b站主页：
https://space.bilibili.com/3537120073353692

*/
//延时
void delay(uint i)
{
	while(i--);
}
//主函数
void main()
{
	uchar i;
	adc0809_init();
	TMOD|=0X01;
	TH0=0X3C;
	TL0=0XB0;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器
	while(1)
	{
		if(cishu<100)
		{
		if(i<4)//pwm计时
			i++;
		else
		{
			i=0;
			if(cishu<100)
				cishu++;
		}
		}
		else
			i=5;
		if(i<pwm)//PWM输出
		{
			if(fang==0)
			{
				out1=0;out2=1;
			}	
			else
			{
				out1=1;out2=0;
			}
		} 
		else
		{
			out1=1;out2=1;
		}
		//LED
		switch(pwm)
		{
			case 0:led1=1;led2=1;led3=1;break;
			case 1:led1=0;led2=1;led3=1;break;
			case 2:led1=1;led2=0;led3=1;break;
			case 3:led1=1;led2=1;led3=0;
		}
		//显示
		P0=smgduan[rain/100];smg1=0;delay(50);smg1=1;
		P0=smgduan[rain%100/10];smg2=0;delay(50);smg2=1;
		P0=smgduan[rain%10];smg3=0;delay(50);smg3=1;
	}
}
//定时器中断
void Timer0() interrupt 1
{
	if(time<10)//0.5s
		time++;
	else
	{
		time=0;
		rain=adc0809_read();//测量
		pwm=rain/64;
	}
	if(pwm==1) //小雨
	{
		if(sec<160)
			sec++;
		else
		{
			sec=0;
			fang=!fang;
			cishu=0;
		}
	}
	if(pwm==2) //中雨
	{
		if(sec<100)
			sec++;
		else
		{
			sec=0;
			fang=!fang;
			cishu=0;
		}
	}
	if(pwm==3) //大雨
	{
		if(sec<60)
			sec++;
		else
		{
			sec=0;
			fang=!fang;
			cishu=0;
		}
	}
	TH0=0X3C;
	TL0=0XB0;
}