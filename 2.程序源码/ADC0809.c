#include"ADC0809.h"
#include"intrins.h"

void adc0809_init()//初始化
{
	adc0809_start=0;
	adc0809_oe=0;
}

uchar adc0809_read()//读取
{
	uchar i;
		_nop_();
		adc0809_clk=!adc0809_clk;
		adc0809_start=1;//启动转换
		for(i=0;i<10;i++)//产生脉冲
		{
			_nop_();
			adc0809_clk=!adc0809_clk;
		}
		adc0809_start=0;
		while(!adc0809_eoc)//等待转换结束
		{
			_nop_();
			adc0809_clk=!adc0809_clk;
		}
		adc0809_oe=1;//读取
		_nop_();
		i=P1;
		adc0809_oe=0;
		return i;
}