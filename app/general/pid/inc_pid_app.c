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


//KP:���ϸ��������ı仯�����������ƣ���ǰ�����ֵ��ȥ���һ�ε����ֵ���������ֵ˵������ڱ������Ǹ�ֵ˵������ڱ�С
//#define PID_KP 0.04 //PID����ϵ��

//KI: ��ǰ�����ֵ
//#define PID_KI ((PID_T/(PID_TI))*PID_KP)  //PID����ϵ��//KI=(T/Ti)*KP

//KD:���ϸ��������ı仯�����������ƣ�- (���ϸ��������ı仯�����������ƣ�,����ֵԽ��˵�����ڵ��ٶ�Խ����Ŀ��ֵ�ӽ����ٶ�Խ��
//#define PID_KD ((PID_TD)/PID_T)*PID_KP)	  //PID΢��ϵ��//KD=(Td/T)*KP

void zd_incpid_init(struct zd_incpid_t *pid)
{
	pid->error=0;
	pid->error_last=0;
	pid->error_prev=0;
	pid->target=0;
	pid->current=0;
	pid->proportion=0;
	pid->derivative=0;
	pid->out=0;
}

void zd_incpid_run(struct zd_incpid_t *pid)
{
	signed int outdelta;
	pid->error_prev = pid->error_last;
	pid->error_last = pid->error;
	pid->error = pid->target - pid->current;
	
	//KP:���ϸ��������ı仯�����������ƣ���ǰ�����ֵ��ȥ���һ�ε����ֵ���������ֵ˵������ڱ������Ǹ�ֵ˵������ڱ�С
	//KI: ��ǰ�����ֵ
	//KD:���ϸ��������ı仯�����������ƣ�- (���ϸ��������ı仯�����������ƣ�,����ֵԽ��˵�����ڵ��ٶ�Խ����Ŀ��ֵ�ӽ����ٶ�Խ��

	pid->proportion=(pid->error-pid->error_last);
	
	pid->derivative=(pid->error-2*pid->error_last+pid->error_prev);

	outdelta=( (PID_KP * pid->proportion) + (PID_KI * pid->error) + (PID_KD * pid->derivative) );
	

	pid->out += outdelta;
	
	//����޷�
	if(pid->out>PID_OUT_LIMIT_MAXVALUE) pid->out=PID_OUT_LIMIT_MAXVALUE;
	else if(pid->out<PID_OUT_LIMIT_MINVALUE) pid->out=PID_OUT_LIMIT_MINVALUE;
}
