#include "Encoder.h"
#include "tim.h"
#include "oled.h"
#include "stdio.h"
#include "delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "MPU6050.h"

uint32_t capture_Buf[3]={0};//鐎涙ɑ鏂佺拋鈩冩殶閿燂拷?????
uint8_t RB_Capture_Cnt=0;//閻樿鎷�?閿熻姤鐖ｈ箛妞剧秴
uint8_t RA_Capture_Cnt=0;//閻樿鎷�?閿熻姤鐖ｈ箛妞剧秴
uint32_t high_time;//妤傛鏁搁獮铏閿燂拷?????
char high_time_out[20];//妤傛鏁搁獮铏闂傛潙鐡х粭锔胯
int16_t speed=0;//闁喎瀹�
char speed_out[10];//闁喎瀹崇€涙顑侀敓锟�??
int16_t PulseCnt=0;//閼村鍟块懞鍌滃仯鐠佲剝鏆�
uint8_t CalSpeedCount=0;//TIM1鐠佲剝鏆熺€靛嫬鐡ㄩ崳锟�
uint8_t CalAngleCount=0;
uint8_t RB_HighLowFlag=0;//閸欏磭鏁搁張绡夐惄鎼佺彯娴ｅ海鏁搁獮铏垼韫囷拷
uint8_t RA_HighLowFlag=0;//閸欏磭鏁搁張绡堥惄鎼佺彯娴ｅ海鏁搁獮铏垼韫囷拷
uint8_t LB_HighLowFlag=0;//瀹革妇鏁搁張绡夐惄鎼佺彯娴ｅ海鏁搁獮铏垼韫囷拷
uint8_t LA_HighLowFlag=0;//瀹革妇鏁搁張绡堥惄鎼佺彯娴ｅ海鏁搁獮铏垼韫囷拷
int16_t testint=(0-1);
char test_out[10];

float Pitch,Roll,Yaw;//定义欧拉角
short aacx,aacy,aacz;		//加速度传感器原始数据
short gyrox,gyroy,gyroz;	//陀螺仪原始数据
short temp;					//温度
char Pitch_out[20],Roll_out[20],Yaw_out[20];//转换，供显示

void CapturePulseNods(void)
{
    switch (RB_Capture_Cnt)
    {
      case 0:
        RB_Capture_Cnt++;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);	//閸氼垰濮╂潏鎾冲弳閹规洝骞� 
        //PulseCnt++;
        break;
      case 3:
        high_time = capture_Buf[1]- capture_Buf[0];    //妤傛鏁搁獮铏閿燂拷?????
        RB_Capture_Cnt = 0;  //濞撳懐鈹栭弽鍥х箶閿燂拷?????
        //PulseCnt++;
        break;
      default:
        break;
    }
  
    switch (RA_Capture_Cnt)
    {
      case 0:
        RA_Capture_Cnt++;
        __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING);
        HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);	//閸氼垰濮╂潏鎾冲弳閹规洝骞� 
        //PulseCnt++;
        break;
      case 3:
        
        RA_Capture_Cnt = 0;  //濞撳懐鈹栭弽鍥х箶閿燂拷?????
        //PulseCnt++;
        break;
      default:
        break;
    }
  

}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(TIM2 == htim->Instance)
	{
		switch(RB_Capture_Cnt)
    {
			case 1:
        RB_HighLowFlag=1;//閺嶅洤绻旀担锟� 缂冾喕璐熸锟�
        if(RA_HighLowFlag==0)
        {
          PulseCnt++;
        }
        else if(RA_HighLowFlag==1)
        {
          PulseCnt--;
        }
				capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3);//閼惧嘲褰囪ぐ鎾冲閻ㄥ嫭宕熼懢鍑ゆ嫹??.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);  //鐠佸墽鐤嗘稉杞扮瑓闂勫秵閮ㄩ幑鏇″箯
				RB_Capture_Cnt++;
				break;
			case 2:
        RB_HighLowFlag=0;//閺嶅洤绻旀担锟� 缂冾喕璐熸担锟�
        if(RA_HighLowFlag==1)
        {
          PulseCnt++;
        }
        else if(RA_HighLowFlag==0)
        {
          PulseCnt--;
        }
				capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_3);//閼惧嘲褰囪ぐ鎾冲閻ㄥ嫭宕熼懢鍑ゆ嫹??.
				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_3); //閸嬫粍顒涢幑鏇″箯   閹存牭鎷�??: __HAL_TIM_DISABLE(&htim5);
				RB_Capture_Cnt++;
        break;    
		}
		switch(RA_Capture_Cnt)
    {
			case 1:
        RA_HighLowFlag=1;//閺嶅洤绻旀担锟� 缂冾喕璐熸锟�
        if(RB_HighLowFlag==1)
        {
          PulseCnt++;
        }
        else if(RB_HighLowFlag==0)
        {
          PulseCnt--;
        }
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);  //鐠佸墽鐤嗘稉杞扮瑓闂勫秵閮ㄩ幑鏇″箯
				RA_Capture_Cnt++;
				break;
			case 2:
        RA_HighLowFlag=0;//閺嶅洤绻旀担锟� 缂冾喕璐熸担锟�
        if(RB_HighLowFlag==0)
        {
          PulseCnt++;
        }
        else if(RB_HighLowFlag==1)
        {
          PulseCnt--;
        }

				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_4); //閸嬫粍顒涢幑鏇″箯   閹存牭鎷�??: __HAL_TIM_DISABLE(&htim5);
				RA_Capture_Cnt++;
        break;    
		}

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM1)
  {
    speed=PulseCnt;
    sprintf(speed_out, "%d", speed);
    
    CapturePulseNods();

    CalSpeedCount++;
    
    
    if(CalSpeedCount>=2)//50Hz频率读速度
    {
      CalSpeedCount=0;
      PulseCnt=0;
    }

  }
}

void MyMPU_Init(void)
{
  while(MPU_Init());					//初始化MPU6050
  OLED_NewFrame();
	OLED_PrintASCIIString(1,1,"666",&afont12x6,OLED_COLOR_NORMAL);
  OLED_ShowFrame();
  HAL_Delay(500);
	while(mpu_dmp_init())
	{
		delay_ms(200);
    OLED_NewFrame();
		OLED_PrintASCIIString(1,1,"Init Wrong",&afont12x6,OLED_COLOR_NORMAL);
    OLED_ShowFrame();
	}
  OLED_NewFrame();
	OLED_PrintASCIIString(1,1,"Init OK",&afont12x6,OLED_COLOR_NORMAL);
  OLED_ShowFrame();
  HAL_Delay(200);

}


