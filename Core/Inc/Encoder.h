#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
extern char speed_out[10];
extern char Pitch_out[20];
extern char Roll_out[20];
extern char Yaw_out[20];
extern float Pitch,Roll,Yaw;//定义欧拉角
extern short aacx,aacy,aacz;		//加速度传感器原始数据
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据
extern short temp;					//温度
extern uint8_t CalAngleCount;


void CapturePulseNods(void);
void MyMPU_Init(void);


#endif
