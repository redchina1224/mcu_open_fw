

const uint8_t FWHEELSILERB[4]  = {0,0,0,0};	//第一组滑条滚轮按键
const uint8_t SWHEELSILERB[4]  = {0,0,0,0};	//第二组滑条滚轮按键


const uint8_t ACTIVE_SENSOR_DELTA[9]   = 
{
KEY0_ACTIVE_SENSOR_DELTA1,	
KEY1_ACTIVE_SENSOR_DELTA1,	
KEY2_ACTIVE_SENSOR_DELTA1,	
KEY3_ACTIVE_SENSOR_DELTA1,	
KEY4_ACTIVE_SENSOR_DELTA1,	
KEY5_ACTIVE_SENSOR_DELTA1,	
KEY6_ACTIVE_SENSOR_DELTA1,	
KEY7_ACTIVE_SENSOR_DELTA1,	
KEY8_ACTIVE_SENSOR_DELTA1,	
};
//----------------------------------------------------------

const uint8_t INACTIVE_SENSOR_DELTA[9]  =
{
KEY0_INACTIVE_SENSOR_DELTA1,	
KEY1_INACTIVE_SENSOR_DELTA1,	
KEY2_INACTIVE_SENSOR_DELTA1,	
KEY3_INACTIVE_SENSOR_DELTA1,	
KEY4_INACTIVE_SENSOR_DELTA1,	
KEY5_INACTIVE_SENSOR_DELTA1,	
KEY6_INACTIVE_SENSOR_DELTA1,	
KEY7_INACTIVE_SENSOR_DELTA1,	
KEY8_INACTIVE_SENSOR_DELTA1,	
};
//----------------------------------------------------------

const uint8_t     IO_TOUCH_ATTR1   = IO_TOUCH_ATTR;
const uint8_t     LONGKEYPROTECT1 = LONGKEYPROTECT;
const uint8_t     ANTISHAKETIMES1   = ANTISHAKETIMES;
const uint8_t     TouchCount1           = TouchCount;
const uint8_t   	 MAXIMUMNUMBEROFKEYS11 	=MAXIMUMNUMBEROFKEYS1;		//最多返回按键数
const uint8_t     PRIMARYKEY11    			  		=PRIMARYKEY1;							//主键1
const uint8_t     FORBIDDENKEY11    		  		=FORBIDDENKEY1;						//禁止按键1
const uint8_t     SCANNINGTIME1    			  		=SCANNINGTIME;
const uint8_t   	 WHEELADDSILER1 	=	WHEELADDSILER;		//滑轮按键选择


bit      awaken; 
unsigned char GKeyValue=0;	
unsigned int StartTouchTime=0;//开始扫描时间  

void TOUCH_INITIAL(void)
{
	TKCON0=0;
    LVDCON  = 0x17;   //bit2 0: 101/110/111: TOUCH  
								  //bit3 LVDDEB LVD 电平输出是否经过去抖电路 1：经过去抖 0：不经过去抖 
                                  //bit 4 LVDP  1:表示VDD高于所设阀值,0：表示低于所设阀值  					
   PCON	= 0x80;		//bit[7:4]=1xxx 1.2v   低电压选择位     
   TKMODE =0;       //1：选择硬件检测， 0：选择软件检测 
}


void TIMER1_INITIAL(void)  
{
    T2CON0 |= 0B00000001;  		 //bit0-bit1  timer2和timer1共用 的分频比 00: 1:1 01: 1：4  1x:1:16   
	T1CON0 = 0B00010001;//TICKPSA=0; 预分频给TIM1;  T1CKSRC=01;HIRC
    PR1H=0x6;  //0X640=1600
    PR1L=0x40; 
    T1ON=1;
    TMR1IF=0;
    TMR1IE=1;
    PEIE=1;
}