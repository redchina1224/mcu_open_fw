
//检测通道设定,为C_KCHS0至C_KCHS25其中之一
const unsigned char _CMS_Table_KeyChannel[] = {
#if(C_KEY_TOTAL>0)
	Touch_Key1_Channel,			//Key1
#endif

#if(C_KEY_TOTAL>1)
	Touch_Key2_Channel,			//Key2
#endif

#if(C_KEY_TOTAL>2)
	Touch_Key3_Channel,			//Key3
#endif

#if(C_KEY_TOTAL>3)
	Touch_Key4_Channel,			//Key4
#endif

#if(C_KEY_TOTAL>4)
	Touch_Key5_Channel,			//Key5
#endif

#if(C_KEY_TOTAL>5)
	Touch_Key6_Channel,			//Key6
#endif

#if(C_KEY_TOTAL>6)
	Touch_Key7_Channel,			//Key7
#endif

#if(C_KEY_TOTAL>7)
	Touch_Key8_Channel,			//Key8
#endif

#if(C_KEY_TOTAL>8)
	Touch_Key9_Channel,			//Key9
#endif

#if(C_KEY_TOTAL>9)
	Touch_Key10_Channel,			//Key10
#endif

#if(C_KEY_TOTAL>10)
	Touch_Key11_Channel,			//Key11
#endif

#if(C_KEY_TOTAL>11)
	Touch_Key12_Channel,			//Key12
#endif

#if(C_KEY_TOTAL>12)
	Touch_Key13_Channel,			//Key13
#endif

#if(C_KEY_TOTAL>13)
	Touch_Key14_Channel,			//Key14
#endif

#if(C_KEY_TOTAL>14)
	Touch_Key15_Channel,			//Key15
#endif

#if(C_KEY_TOTAL>15)
	Touch_Key16_Channel,			//Key16
#endif


};

//灵敏度阈值,设定值不可低于20,不能大于1023
//灵敏度阈值设定必须大于噪声阈值VOL_VALUE
const unsigned int _CMS_Table_KeyDown[] = {
#if(C_KEY_TOTAL>0)
	50,//Key1
#endif

#if(C_KEY_TOTAL>1)
	50,//Key2
#endif

#if(C_KEY_TOTAL>2)
	50,//Key3
#endif

#if(C_KEY_TOTAL>3)
	50,//Key4
#endif

#if(C_KEY_TOTAL>4)
	50,//Key5
#endif

#if(C_KEY_TOTAL>5)
	50,//Key6
#endif

#if(C_KEY_TOTAL>6)
	50,//Key7
#endif

#if(C_KEY_TOTAL>7)
	50,//Key8
#endif

#if(C_KEY_TOTAL>8)
	50,//Key9
#endif

#if(C_KEY_TOTAL>9)
	50,//Key10
#endif

#if(C_KEY_TOTAL>10)
	50,//Key11
#endif

#if(C_KEY_TOTAL>11)
	50,//Key12
#endif

#if(C_KEY_TOTAL>12)
	50,//Key13
#endif

#if(C_KEY_TOTAL>13)
	50,//Key14
#endif

#if(C_KEY_TOTAL>14)
	50,//Key15
#endif

#if(C_KEY_TOTAL>15)
	50,//Key16
#endif
};


/***********************************************************
下面的内容请勿修改
***********************************************************/
const unsigned char _CMS_KeyTNumber = C_KEY_TOTAL;
const unsigned char _CMS_KeyShakeC = C_KEY_SHAKE;
const unsigned char _CMS_KeyOffC = C_KEY_OFFSHAKE;
const unsigned char _CMS_VolValue = VOL_VALUE;
const unsigned char _CMS_SluValue = SLU_VALUE;
const unsigned char _CMS_CmBase = CM_BASE;
const unsigned char _CMS_KeyValidC = C_VALID_KEY;
const unsigned int  _CMS_KeyValidT = C_VALID_TIME;
//-------------------------------------------------------
const unsigned char _CMS_UnNolCheck = UNNOL_CHECK;
const unsigned char _CMS_UnNolTimes = UNNOL_TIMES;
const unsigned char _CMS_LMDValue = LMDVALUE;
const unsigned char _CMS_KeyLDOSel = KEY_LDOSEL;
const unsigned char _CMS_KeyEn1kres = KEY_EN1KRES;

unsigned int _CMS_DispKeyDown[C_KEY_TOTAL];
unsigned int _CMS_NoiseDat[C_KEY_TOTAL];
unsigned int _CMS_FactorRawDat[C_KEY_TOTAL];
//--------------------------------------------------






