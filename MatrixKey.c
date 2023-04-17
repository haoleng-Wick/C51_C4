#include <REGX52.H>

unsigned char Key_KeyNumber;

unsigned char MatrixKey()
{
	unsigned char Temp = 0;
	Temp = Key_KeyNumber;
	Key_KeyNumber = 0;
	return Temp;
}

unsigned char Key_Status()
{
	unsigned char key_number = 0;
	// 第1列
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7 == 0){key_number = 1;}
	if(P1_6 == 0){key_number = 5;}
	if(P1_5 == 0){key_number = 9;}
	if(P1_4 == 0){key_number = 13;}
	
	// 第2列
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0){key_number = 2;}
	if(P1_6 == 0){key_number = 6;}
	if(P1_5 == 0){key_number = 10;}
	if(P1_4 == 0){key_number = 14;}
	
	// 第3列
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0){key_number = 3;}
	if(P1_6 == 0){key_number = 7;}
	if(P1_5 == 0){key_number = 11;}
	if(P1_4 == 0){key_number = 15;}
	
	// 第4列
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0){key_number = 4;}
	if(P1_6 == 0){key_number = 8;}
	if(P1_5 == 0){key_number = 12;}
	if(P1_4 == 0){key_number = 16;}
	
	return key_number;
}

void MatrixKey_Loop()
{
	// 通过此时刻与上次扫描时刻的对比得到按键位置
	static unsigned char NowStatus, LastStatus;
	LastStatus = NowStatus;
	NowStatus = Key_Status();
	if(LastStatus == 1 && NowStatus == 0){Key_KeyNumber = 1;}
	if(LastStatus == 2 && NowStatus == 0){Key_KeyNumber = 2;}
	if(LastStatus == 3 && NowStatus == 0){Key_KeyNumber = 3;}
	if(LastStatus == 4 && NowStatus == 0){Key_KeyNumber = 4;}
	
	if(LastStatus == 5 && NowStatus == 0){Key_KeyNumber = 5;}
	if(LastStatus == 6 && NowStatus == 0){Key_KeyNumber = 6;}
	if(LastStatus == 7 && NowStatus == 0){Key_KeyNumber = 7;}
	if(LastStatus == 8 && NowStatus == 0){Key_KeyNumber = 8;}
	
	if(LastStatus == 9 && NowStatus == 0){Key_KeyNumber = 9;}
	if(LastStatus == 10 && NowStatus == 0){Key_KeyNumber = 10;}
	if(LastStatus == 11 && NowStatus == 0){Key_KeyNumber = 11;}
	if(LastStatus == 12 && NowStatus == 0){Key_KeyNumber = 12;}
	
	if(LastStatus == 13 && NowStatus == 0){Key_KeyNumber = 13;}
	if(LastStatus == 14 && NowStatus == 0){Key_KeyNumber = 14;}
	if(LastStatus == 15 && NowStatus == 0){Key_KeyNumber = 15;}
	if(LastStatus == 16 && NowStatus == 0){Key_KeyNumber = 16;}
}