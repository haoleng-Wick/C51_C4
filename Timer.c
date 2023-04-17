#include <REGX52.H>

void Timer01Init()
{
	TMOD = 0x11;	// 设置定时器模式
	TL0 = 0x18;
	TH0 = 0xFC;
	TL1 = 0x14;
	TH1 = 0xFC;		// 设置定时器初始值,定时1ms
	TR0 = 1;
	TR1 = 1;		// 定时器开始计时
	EA = 1;			// 总中断允许
	ET0 = 1;
	ET1 = 1;		// 定时器中断允许
	PT0 = 0;
	PT1 = 0;		// 定时器中断为低级优先级
}

// 直接注释方便以后复制
//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	TL0 = 0x18;
//	TH0 = 0xFC;
//	T0Count++;
//	if(T0Count >= 1000)	// 1s == 1000ms
//	{
//		T0Count = 0;
//		// 添加需要执行的代码
//		
//	}
//}

//void Timer1_Routine() interrupt 3
//{
//	static unsigned int T1Count;
//	TL1 = 0x15;
//	TH1 = 0xFC;
//	T1Count++;
//	if(T1Count >= 1000)	// 1s == 1000ms
//	{
//		T1Count = 0;
//		// 添加需要执行的代码
//		
//	}
//}