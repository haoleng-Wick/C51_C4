#include <REGX52.H>
#include "Timer.h"
#include "MatrixKey.h"
#include "Nixie.h"
#include "Delay.h"

unsigned char Key_Number;
unsigned char Passwd[8] = {11, 7, 3, 5, 5, 6, 0, 8},
				Passwd_Input[8], Passwd_Buff[8];

unsigned char Min, Sec, MSec;

// 输入完成、倒计时结束、数码管闪烁
bit PASS, FLAG, LIGHT;

// 复位
void Reset()
{
	((void (code *) (void)) 0x0000) ();
}

// 欺骗函数
void _Beep()
{
	P2_5 = 0;
	Delay(1);
	P2_5 = 1;
	Delay(1);
}

// 倒计时循环
void Timer_Loop()
{
	static bit stop;
	if(!FLAG)
	{
		MSec--;
		if(MSec == 0 && stop == 0)
		{
			if(Sec != 0) {Sec--; MSec = 99;}
			if(Sec == 0)
			{
				if(Min != 0) {Min--; Sec = 60;}
				// 还有最后99跑秒
				if(Min == 0 && stop == 0) {MSec = 99; stop = 1;}
			}
		}
		// 跑完最后这99跑秒再结束倒计时
		else if(MSec == 0 && stop == 1)
		{
			FLAG = 1;
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned char T0Count, T0Count1, T0Count2;
	static unsigned int Temp;
	TL0 = 0x18;
	TH0 = 0xFC;
	Nixie_Loop();	// 数码管扫描
	if(!PASS)
	{
		T0Count++;
		if(T0Count >= 20)	// 矩阵键盘扫描
		{
			T0Count = 0;
			MatrixKey_Loop();
		}
	} 
	else 
	{
		T0Count1++;
		// 1s == 100跑秒 == 1000ms
		if(T0Count1 >= 10)		// 1跑秒 == 10ms
		{
			T0Count1 = 0;
			Timer_Loop();		// 倒计时循环
		}
		if(FLAG)
		{
			T0Count2++;
			if(T0Count2 >= 128)	// 128ms 数码管闪烁
			{
				T0Count2 = 0;
				// 通过这个标志位实现闪烁-与mian()配合
				LIGHT = !LIGHT;
			}
		}
		if(!FLAG)
		{
			Temp++;
			// 蜂鸣器控制
			if(Sec > 19){
				if(Temp > 500){Temp = 0; _Beep();}}
			else if(Sec > 9 && Sec <=19){
				if(Temp > 300){Temp = 0; TR1 = ~TR1;}}
			else if(Sec > 4 && Sec <= 9){
				if(Temp > 100){Temp = 0; TR1 = ~TR1;}}
			else if(Sec >= 1 && Sec <= 4){
				if(Temp > 80){Temp = 0; TR1 = ~TR1;}}
			else{TR1 = 1;}
		}
	}
}

void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	if(PASS)	// 密码正确
	{
		if(!FLAG)
		{
			T1Count++;
			TL1 = 0x18;
			TH1 = 0xFC;
			P2_5 = ~P2_5;	// 蜂鸣器
			P2_6 = ~P2_6;
			P2_7 = ~P2_7;	// 指示灯
		}
	}
}

// 密码输入完成
void Input_Over()
{
	unsigned char i;
	for(i = 1; i < 8; i++)
	{
		if(Passwd[i] == Passwd_Input[i])
		{
			PASS = 1;
		}
		else // 密码错误直接复位
		{
			Reset();
		}
	}
}

// 开始输入密码
void Key_Input()
{
	unsigned char i, j;
	static unsigned char count;
	Key_Number = MatrixKey();
		if(Key_Number)
		{
			if(Key_Number < 11)	// 1~9 10表示0
			{
				if(count < 7)
				{
					count++; j++;
					if(Key_Number != 10)
						Passwd_Buff[j] = Key_Number;
					else
						Passwd_Buff[j] = 0;
				}
			} else if(Key_Number < 13)	//11 12 删除键
			{
				if(count > 0)
				{
					count--;
					Passwd_Buff[j] = 11;
					j--;
				}
			} else 	// 最后一排为确认按键
			{
				//  缓冲区写入准备判断
				for(i = 0; i < 8; i++)
					Passwd_Input[i] = Passwd_Buff[i];
				Input_Over();
			}
		}
}

int main()
{
	unsigned char i;
	Min = 0; Sec = 44; MSec = 99;
	Timer01Init();
	PASS = 0;
	TR1 = 0;
	for(i = 0; i < 8; i++) 
	{
		Passwd_Buff[i] = 11;	// 数码管先全灭
		Passwd_Input[i] = 11;
	}
	while(1)
	{
		if(!PASS)
		{
			Key_Input();
			for(i = 0; i < 8; i++)
			Nixie_Set_Buf(i+1, Passwd_Buff[i]);	
		}
		else
		{
			if(LIGHT)
			{
				// 全灭
				unsigned char j;
				for(j = 1; j < 9; j++)
					Nixie_Set_Buf(j, 11);
			}
			else
			{
				// 显示时间数据
				Nixie_Set_Buf(1, Min/10);
				Nixie_Set_Buf(2, Min%10);
				Nixie_Set_Buf(3, 11);
				Nixie_Set_Buf(4, Sec/10);
				Nixie_Set_Buf(5, Sec%10);
				Nixie_Set_Buf(6, 11);
				Nixie_Set_Buf(7, MSec/10);
				Nixie_Set_Buf(8, MSec%10);
			}
		}
	}
	return 0;
}