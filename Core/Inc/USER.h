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