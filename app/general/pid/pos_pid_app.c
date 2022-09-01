#include "..\..\com_include_app.h"

//PID�����Ƶ���Ŀ�е�app_cfg.h�н�������,�˴������Է��㽫�˴��뵥����������
//#define PID_KP 0.04 //PID����ϵ��

//#define PID_T 1000 //�������������ms (��������ı�����ź���Ӧ����ʱ����)
//#define PID_TI 1000 //��������ms
//#define PID_TD 1000 //΢������ms


//#define PID_INTEGRAL_DISABLE_VALUE 300 // //���ַ���ֵ-�����ڶ���ʱ��ʹ�ܻ������ã�(ÿ���϶�ADֵ��Ϊ30-44)
//#define PID_INTEGRAL_LIMIT_VALUE 30  // //�����޷�ֵ-����ֵ�����ֵ(ÿ���϶�ADֵ��Ϊ30-44)
//#define PID_OUT_LIMIT_MAXVALUE 80  //����޷�ֵ-���ֵ�����ֵ(��������źŵ����ֵ����)
//#define PID_OUT_LIMIT_MINVALUE 0  //����޷�ֵ-���ֵ�����ֵ(��������źŵ����ֵ����)

//#define PID_KI ((PID_T/(PID_TI))*PID_KP)  //PID����ϵ��//KI=(T/Ti)*KP
//#define PID_KD ((PID_TD)/PID_T)*PID_KP)	  //PID΢��ϵ��//KD=(Td/T)*KP


void zd_pospid_init(struct zd_pospid_t *pid)
{
	pid->error=0;
	pid->error_last=0;
	pid->error_prev=0;
	pid->target=0;
	pid->current=0;
	pid->integral=0;
	pid->derivative=0;
	pid->out=0;
}

#ifdef PID_KP_DIV
	#define PID_P_VALUE (pid->error/PID_KP_DIV)
#else
	#define PID_P_VALUE (pid->error*PID_KP_MUL)
#endif

#ifdef PID_KI_DIV
	#define PID_I_VALUE (pid->integral/PID_KI_DIV)
#else
	#define PID_I_VALUE (pid->integral*PID_KI_MUL)
#endif

#ifdef PID_KD_DIV
	#define PID_D_VALUE (pid->derivative/PID_KD_DIV)
#else
	#define PID_D_VALUE (pid->derivative*PID_KD_MUL)
#endif

void zd_pospid_run(struct zd_pospid_t *pid)
{

	pid->error = pid->target - pid->current;
	
	//���ַ���
	if((pid->error<PID_INTEGRAL_DISABLE_VALUE_Max&&pid->error>(-PID_INTEGRAL_DISABLE_VALUE_Max))\
		&&(pid->error<PID_INTEGRAL_DISABLE_VALUE_Min&&pid->error>(-PID_INTEGRAL_DISABLE_VALUE_Min))) //ÿ���϶�Ԥ����25
	{
		//�����޷��ⶥһ�κ�����(������������)
		if(pid->integral==PID_INTEGRAL_LIMIT_VALUE||pid->integral==(-PID_INTEGRAL_LIMIT_VALUE)) pid->integral=0;
		
		pid->integral+=pid->error;
		
		//�����޷�
		if(pid->integral>PID_INTEGRAL_LIMIT_VALUE) pid->integral=PID_INTEGRAL_LIMIT_VALUE;
		else if(pid->integral<(-PID_INTEGRAL_LIMIT_VALUE)) pid->integral=(-PID_INTEGRAL_LIMIT_VALUE);
	}
	else pid->integral=0;
	
	pid->derivative=pid->error-pid->error_prev;
	
	pid->error_prev=pid->error;

	//��������	
	#ifdef PID_PROPORTION_DISABLE_VALUE

	if((pid->error<PID_PROPORTION_DISABLE_VALUE&&pid->error>(-PID_PROPORTION_DISABLE_VALUE))) //
	{
		pid->error=0;
	}
	#endif

	//΢�ַ���	
	#ifdef PID_DERIVATIVE_DISABLE_VALUE

	if((pid->derivative<PID_DERIVATIVE_DISABLE_VALUE&&pid->derivative>(-PID_DERIVATIVE_DISABLE_VALUE))) //
	{
		pid->derivative=0;
	}
	#endif	
	

	pid->out = (PID_P_VALUE+PID_I_VALUE+PID_D_VALUE);
	
	//����޷�
	if(pid->out>PID_OUT_LIMIT_MAXVALUE) pid->out=PID_OUT_LIMIT_MAXVALUE;
	else if(pid->out<PID_OUT_LIMIT_MINVALUE) pid->out=PID_OUT_LIMIT_MINVALUE;
}
