//
// Created by Anson
//
#include "main.h"
#include "DCmotor.h"
#include "stdio.h"

float speed;
Speed_Pid_Def Speed_PID;
float Read_Encoder(void){
    float encoder;
    if (TIM2->CNT > 0x7fff){
        encoder = (float)TIM2->CNT - 0xffff;
    } else{
        encoder = TIM2->CNT;
    }
    return encoder;
}

void MotorRun(uint16_t Speed, enum Direction direction){
    if (direction == Clockwise){
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, Speed);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MAX_PWM);
    } else{
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, MAX_PWM);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, Speed);
    }
}

void MotorInit(void){
    printf("Speed PID Init...\n");
    Speed_PID.Speed_Ref = 0.0f;
    Speed_PID.Speed_Meas = 0.0f;
    Speed_PID.error = 0.0f;
    Speed_PID.PWM = 0;
    Speed_PID.Kp = 15.0f;
    Speed_PID.Ki = 1.5f;
    Speed_PID.Kd = 0.2f;
    Speed_PID.Kb = 10.0f;
    Speed_PID.PWM_Max = 1000;
    Speed_PID.PWM_Min = 0;
    printf("Speed PID End!");
}

uint16_t MotorPID(float Speed){
    float temp;
    static uint8_t index;
    Speed_PID.Speed_Ref = Speed;
    Speed_PID.error = Speed_PID.Speed_Ref - Speed_PID.Speed_Meas;
    temp = (Speed_PID.error + Speed_PID.Integral)*Speed_PID.Kp;
//    printf("temp=%f, Speep", temp);
    if (temp > (float)Speed_PID.PWM_Max){
        Speed_PID.PWM = Speed_PID.PWM_Max;
    } else if (temp < (float)Speed_PID.PWM_Min){
        Speed_PID.PWM = Speed_PID.PWM_Min;
    } else{
        Speed_PID.PWM = (uint16_t) temp;
    }
    Speed_PID.Integral += ((float)(Speed_PID.PWM - (uint16_t)temp)*Speed_PID.Kb + Speed_PID.Ki * Speed_PID.error)*0.01f;
    return Speed_PID.PWM;
}


