//
// Created by Anson
//

#ifndef DEMO_DCMOTOR_H
#define DEMO_DCMOTOR_H

#define MAX_PWM    1000

enum Direction {
    Clockwise,
    Anticlockwise
};

typedef struct {
    float Speed_Ref;
    float Speed_Meas;
    float error;
    float Kp;
    float Ki;
    float Kd;
    float Kb;
    uint16_t PWM;
    float Integral;
    uint16_t PWM_Max;
    uint16_t PWM_Min;
}Speed_Pid_Def;

void MotorInit(void);
float Read_Encoder(void);
void MotorRun(uint16_t Speed, enum Direction direction);
uint16_t MotorPID(float Speed);
#endif //DEMO_DCMOTOR_H
