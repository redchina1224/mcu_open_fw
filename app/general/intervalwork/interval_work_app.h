//******************************************************************************
//Copyright(C) 2020-2021 zhejiang zhida dianzikeji Co., Ltd
//�㽭�Ǵ���ӿƼ����޹�˾
//File name:      function.h
//Author:         zzg
//Version:        Ver0.1
//Date:           2021-4-25
//Description:    ����
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



//ʹ��ʾ��
/*

			//��������
			if(��������)
			{
				work.inRunning1=1;
				intervalWorkRun_Start(&work,50,100);//�������,Enableʱ��50x100ms,Disableʱ��100x100ms
			}


			//���ؿ���
			if(work.inRunning1!=0)//�ڹ���״̬
			{
				if(100msִ��һ�α�־)
				{
					intervalWorkRun(&work);

						if(work.intervalWorkEn==1)//��˸ʱ�Ƿ���ʾ��Ϩ���ı�־
						{
							//��������
						}
						else
						{			
							//�رո���
						}

				}


			}
			else//���ڹ���״̬
			{
				//�رո���
			}



*/










/************************ (C) COPYRIGHT zhejiang zhida *****END OF FILE****/