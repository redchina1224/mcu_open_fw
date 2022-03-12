
#include "..\Core\core.h"
#include "..\Bsp\bsp.h"


 unsigned char *Led_WriteBuffer;



void Aip650_SendStart(void)
{
  	//����START����
    Aip650_CLK_OUT; Aip650_DIO_OUT;
	Aip650_CLK_H;  Aip650_Delay(5); Aip650_DIO_H; Aip650_Delay(10); 
	Aip650_DIO_L;  Aip650_Delay(5); Aip650_CLK_L; Aip650_Delay(10);
}

void Aip650_SendEnd(void)
{
    //��END����
	Aip650_Delay(10); Aip650_DIO_L; Aip650_CLK_L; Aip650_Delay(10); 
	Aip650_CLK_H;  Aip650_Delay(5); Aip650_DIO_H; Aip650_Delay(10);
}



bit Aip650_SendByte(unsigned char dat)	
{
    static bit ackbit=0;
	unsigned char j;
    

	//����һ���ֽ�+����1λACK
	for(j=0;j<9;j++)
	{
		Aip650_CLK_L;//����ʱ���ź�

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
          ackbit=Aip650_DIO; //��ȡACK
          Aip650_DIO_OUT;
		  Aip650_DIO_L;
		}

		Aip650_Delay(5);
		Aip650_CLK_H;//����ʱ���ź�
		Aip650_Delay(5);
        Aip650_CLK_L;//����ʱ���ź�
		Aip650_Delay(5);
	}
 
	return ackbit; //����ACK
}




//��bsp_run�е��ã�ÿ200ms����һ��
void Aip650_SendDisBuffer(void)	
{
    unsigned char i;

		for(i=0;i<5;i++)
        {
            //����START����
			Aip650_SendStart();
			//����DIG0λ����
			Aip650_SendByte(cmd_data[i]);
			Aip650_SendByte(Aip650_WriteBuffer[i]);
			//��END����
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

