#include <REGX52.H>

unsigned char NixieTable[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F, 0xFF, 0x00};	// 零 一 二 三 四 五 六 七 八 九 亮 灭
//								 0 		1	  2		3	  4		5	  6		7	  8		9	  10	11		
unsigned char Nixie_Buf[9];

// 共阴数码管
void Nixie (unsigned char Local, Num)
{
	P0 = 0x00;
	switch(Local)
	{
		// 位选 74HC138译码器	P2的2、3、4位选择数码管8个位置
		case 1:
			P2_4 = 1; P2_3 = 1; P2_2 = 1; break;	//Y7
		case 2:
			P2_4 = 1; P2_3 = 1; P2_2 = 0; break;	
		case 3:
			P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4:
			P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5:
			P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6:
			P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7:
			P2_4 = 0; P2_3 = 0; P2_2 = 1; break;	//Y1
		case 8:
			P2_4 = 0; P2_3 = 0; P2_2 = 0; break;	//Y0
	}
	// 阳码
	P0 = NixieTable[Num];
}

// 写入缓冲区
void Nixie_Set_Buf(unsigned char Local, Num)
{
	Nixie_Buf[Local] = Num;
}

// 循环扫描
void Nixie_Loop()
{
	static unsigned char i = 1;
	Nixie(i, Nixie_Buf[i]);
	i++;
	if(i >= 9) i = 1;
}