//
// Created by fibre on 2024/5/7.
//

#include "USER.h"

//BEE for a time
void BEE_Delay(uint8_t time) {
	HAL_GPIO_WritePin(BEE_GPIO_Port, BEE_Pin, GPIO_PIN_RESET);
	HAL_Delay(time);
	HAL_GPIO_WritePin(BEE_GPIO_Port, BEE_Pin, GPIO_PIN_SET);
}

//status 1
void Manual_Signal(void) {
	if (HAL_GPIO_ReadPin(GPIOB, BUT_S_Pin) == GPIO_PIN_RESET) {
		//turn on LED and BEE
		HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	}
	else {
		//turn off LED and BEE
		HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	}
}

void Auto_Morse_Signal(uint8_t* Trans_Msg) {
	//auto send signal
	for (int i = 0; i < 256; ++i) {
		switch (Trans_Msg[i]) {
			case 0: //break
				Morse_Send_Break();
				break;
			case 1: //dot
				Morse_Send_Dot();
				break;
			case 2: //dash
				Morse_Send_Dash();
				break;
			case 3: //space
				Morse_Send_Space();
				break;
			case 4: //end
				break;
		}
	}

}

void Morse_Send_Dot(void) {
	//send dot
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

void Morse_Send_Dash(void) {
	//send dash
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	HAL_Delay(300);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
}

void Morse_Send_Break(void) {
	HAL_Delay(200);
}

void Morse_Send_Space(void) {
	HAL_Delay(600);
}
