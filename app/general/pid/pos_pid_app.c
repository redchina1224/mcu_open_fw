#include "..\..\com_include_app.h"

//PID参数移到项目中的app_cfg.h中进行配置,此处保留以方便将此代码单独移作它用
//#define PID_KP 0.04 //PID比例系数

//#define PID_T 1000 //采样与控制周期ms (控制输出改变后反馈信号响应的延时周期)
//#define PID_TI 1000 //积分周期ms
//#define PID_TD 1000 //微分周期ms


//#define PID_INTEGRAL_DISABLE_VALUE 300 // //积分分离值-误差大于多少时不使能积分作用，(每摄氏度AD值差为30-44)
//#define PID_INTEGRAL_LIMIT_VALUE 30  // //积分限幅值-积分值最大限值(每摄氏度AD值差为30-44)
//#define PID_OUT_LIMIT_MAXVALUE 80  //输出限幅值-输出值最大限值(用于输出信号的最大值限制)
//#define PID_OUT_LIMIT_MINVALUE 0  //输出限幅值-输出值最大限值(用于输出信号的最大值限制)

//#define PID_KI ((PID_T/(PID_TI))*PID_KP)  //PID积分系数//KI=(T/Ti)*KP
//#define PID_KD ((PID_TD)/PID_T)*PID_KP)	  //PID微分系数//KD=(Td/T)*KP


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

void zd_pospid_run(struct zd_pospid_t *pid)
{

	pid->error = pid->target - pid->current;
	
	//积分分离
	if((pid->error<PID_INTEGRAL_DISABLE_VALUE_Max&&pid->error>(-PID_INTEGRAL_DISABLE_VALUE_Max))\
		&&(pid->error<PID_INTEGRAL_DISABLE_VALUE_Min&&pid->error>(-PID_INTEGRAL_DISABLE_VALUE_Min))) //每摄氏度预估差25
	{
		//积分限幅封顶一次后清零(以免连续过调)
		if(pid->integral==PID_INTEGRAL_LIMIT_VALUE||pid->integral==(-PID_INTEGRAL_LIMIT_VALUE)) pid->integral=0;
		
		pid->integral+=pid->error;
		
		//积分限幅
		if(pid->integral>PID_INTEGRAL_LIMIT_VALUE) pid->integral=PID_INTEGRAL_LIMIT_VALUE;
		else if(pid->integral<(-PID_INTEGRAL_LIMIT_VALUE)) pid->integral=(-PID_INTEGRAL_LIMIT_VALUE);
	}
	else pid->integral=0;
	
	pid->derivative=pid->error-pid->error_prev;
	
	pid->error_prev=pid->error;
	
	pid->out = ((PID_KP * pid->error) + (PID_KI * pid->integral) + (PID_KD * pid->derivative));
	
	//输出限幅
	if(pid->out>PID_OUT_LIMIT_MAXVALUE) pid->out=PID_OUT_LIMIT_MAXVALUE;
	else if(pid->out<PID_OUT_LIMIT_MINVALUE) pid->out=PID_OUT_LIMIT_MINVALUE;
}
