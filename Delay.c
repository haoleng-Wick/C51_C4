void Delay(unsigned int nms)
{
	unsigned char i, j;
	while(nms--)
	{	
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}