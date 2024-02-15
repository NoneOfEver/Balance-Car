#include "motor.h"

void moveForward()
{
    HAL_GPIO_WritePin(GPIOA,AIN_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,BIN_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,AIN_2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,BIN_2_Pin,GPIO_PIN_RESET);

}
void moveBack()
{
    HAL_GPIO_WritePin(GPIOA,AIN_1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,BIN_1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,AIN_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,BIN_2_Pin,GPIO_PIN_SET);
  
}
void controlSpeed(uint8_t speed)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, speed); // 设置PWM占空比为speed%
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed); // 设置PWM占空比为speed%

}