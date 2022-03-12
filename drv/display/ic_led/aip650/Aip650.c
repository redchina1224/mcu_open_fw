
#include "..\Core\core.h"
#include "..\Bsp\bsp.h"


 unsigned char *Led_WriteBuffer;



void Aip650_SendStart(void)
{
  	//发送START命令
    Aip650_CLK_OUT; Aip650_DIO_OUT;
	Aip650_CLK_H;  Aip650_Delay(5); Aip650_DIO_H; Aip650_Delay(10); 
	Aip650_DIO_L;  Aip650_Delay(5); Aip650_CLK_L; Aip650_Delay(10);
}

void Aip650_SendEnd(void)
{
    //发END命令
	Aip650_Delay(10); Aip650_DIO_L; Aip650_CLK_L; Aip650_Delay(10); 
	Aip650_CLK_H;  Aip650_Delay(5); Aip650_DIO_H; Aip650_Delay(10);
}



bit Aip650_SendByte(unsigned char dat)	
{
    static bit ackbit=0;
	unsigned char j;
    

	//发送一个字节+接收1位ACK
	for(j=0;j<9;j++)
	{
		Aip650_CLK_L;//拉低时钟信号

        if(j<8)
        {
            Aip650_Delay(5);
			if((dat&0x80)==0X80)
				{Aip650_DIO_H;}
			else
				{Aip650_DIO_L;}	
			dat<<=1; 
		}
        else
        {
          Aip650_DIO_IN;
          Aip650_DIO_H;
          Aip650_Delay(5);
          ackbit=Aip650_DIO; //获取ACK
          Aip650_DIO_OUT;
		  Aip650_DIO_L;
		}

		Aip650_Delay(5);
		Aip650_CLK_H;//拉高时钟信号
		Aip650_Delay(5);
        Aip650_CLK_L;//拉低时钟信号
		Aip650_Delay(5);
	}
 
	return ackbit; //返回ACK
}




//在bsp_run中调用，每200ms调用一次
void Aip650_SendDisBuffer(void)	
{
    unsigned char i;

		for(i=0;i<5;i++)
        {
            //发送START命令
			Aip650_SendStart();
			//发送DIG0位数据
			Aip650_SendByte(cmd_data[i]);
			Aip650_SendByte(Aip650_WriteBuffer[i]);
			//发END命令
			Aip650_SendEnd();
        }
		
}


void Aip650_Init(void)
{
	Aip650_CLK_OUT;
	Aip650_DIO_OUT;
//    Aip650_SendDisBuffer();
//	Aip650_SendStart();
//	Aip650_Delay(10);
//	Aip650_SendEnd();
}

