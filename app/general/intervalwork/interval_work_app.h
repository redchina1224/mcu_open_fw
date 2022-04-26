//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//浙江智达电子科技有限公司
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    功能
//History:
//******************************************************************************
#ifndef __APPSTDLIB_INTERVAL_WORK_APP_H__
#define __APPSTDLIB_INTERVAL_WORK_APP_H__
//******************************************************************

struct  zd_interval_work_t {
	struct {
		unsigned char intervalWorkEn:1;
		unsigned char inRunning1:1;
		unsigned char inRunning2:1;
		unsigned char inRunning3:1;	
		unsigned char inRunning4:1;
		unsigned char inRunning5:1;
		unsigned char inRunning6:1;
		unsigned char inRunning7:1;		
	};
unsigned char intervalTimeOut_x100ms;
unsigned char intervalTimeOut_En_x100ms;
unsigned char intervalTimeOut_Dis_x100ms;
};



void intervalWorkRun(struct  zd_interval_work_t* work);

void intervalWorkRun_Start(struct  zd_interval_work_t* work,unsigned char En_mSec,,unsigned char Dis_mSec);

#endif 



//使用示例
/*

			//触发工作
			if(按键触发)
			{
				work.inRunning1=1;
				intervalWorkRun_Start(&work,50,100);//间隔工作,Enable时间50x100ms,Disable时间100x100ms
			}


			//负载控制
			if(work.inRunning1!=0)//在工作状态
			{
				if(100ms执行一次标志)
				{
					intervalWorkRun(&work);

						if(work.intervalWorkEn==1)//闪烁时是否显示或熄屏的标志
						{
							//开启负载
						}
						else
						{			
							//关闭负载
						}

				}


			}
			else//不在工作状态
			{
				//关闭负载
			}



*/










/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/