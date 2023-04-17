#include <REGX52.H>

sbit RCK = P3^5;	// 发送标志位
sbit SER = P3^4;	// 位移寄存器
sbit SCK = P3^6;	// 位移标志位

void _74C595_SendData(unsigned char Data)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SER = (Data<<i)&0x80;
		SCK = 1; SCK = 0;
	}
	RCK = 1; RCK = 0;
}

// 某列显示某数据
void Lattice_Show_Column(unsigned char Column, Data)
{
	_74C595_SendData(Data);
	P0 = ~(0x80>>Column);	// 1000 0000 取反 0111 1111
}