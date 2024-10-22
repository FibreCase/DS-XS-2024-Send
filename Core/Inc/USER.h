//
// Created by fibre on 2024/5/7.
//

#ifndef USER_H
#define USER_H

#endif //USER_H

#include "main.h"

void BEE_Delay(uint8_t time);
void Manual_Signal(void);

void Auto_Morse_Signal(uint8_t* Trans_Msg);
void Morse_Send_Dot(void);
void Morse_Send_Dash(void);
void Morse_Send_Break(void);
void Morse_Send_Space(void);

void FibreTran_0(void);
void FibreTran_1(void);
void FibreTran_Start(void);
void FibreTran_End(void);
void FibreTran_DATA(uint8_t data);
void FibreTran_Pic(uint8_t* data);
