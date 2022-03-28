#include "..\com_include_app.h"
  
#define PlateauCheckSet_TempStart 82
#define PlateauCheckSet_TempDiff 2
#define PlateauCheckSet_TimeOutSec 30



/*****************************************************************************
*函数		: void PlateauCheck(void)
*函数功能描述 	: 高原检查（用于检查高原模式），每秒调用一次
*函数参数 	: 无
*函数返回值 	: 无
******************************************************************************/
unsigned char PlateauCheck_PerSecond(unsigned char lucv_real_temp,unsigned char lucv_CheckEn)
{
	static unsigned char lucv_TempCheck_Max
	static unsigned char lucv_TempCheck_TimeSec
	
    //工作时使能检查
    if(lucv_CheckEn!=0)
    {

		//高原检测处理
		if(lucv_real_temp>=lucv_TempCheck_Max||lucv_TempCheck_Max<PlateauCheck_Temp) //水温上升2度或水温低于高原沸点时，复位计时
		{
            		lucv_TempCheck_Max=lucv_real_temp+PlateauCheck_TempDiff;
			lucv_TempCheck_TimeSec=0;
		}
        	else if(++lucv_TempCheck_TimeSec>PlateauCheckSet_TimeOutSec)
        	{
			lucv_TempCheck_TimeSec=PlateauCheckSet_TimeOutSec;
			return 1; //触发高原时返回1
        	}

    }
    else//非工作时复位相关数据
    {
		 lucv_TempCheck_Max=0;//每次加热关闭后，复位高原检测变量
		 lucv_TempCheck_TimeSec=0;//高原检测从加热启动开始计时,非工作模式清零
    }
    

    return 0;

}
