unsigned char __buzzer_en=0;
unsigned char *T_BuzzerEn=&__buzzer_en;

#if (DevPlatform==DevPlatform_Keil_C51)
void buzzer_in_isr(void)
#else
inline void buzzer_in_isr(void)
#endif
{
	if((*T_BuzzerEn)!=0) Buzzer_IO_Channel=!Buzzer_IO_Channel;// else Buzzer_IO_Input;
	//Buzzer_IO_Output;
	//Buzzer_IO_Channel=!Buzzer_IO_Channel;
}