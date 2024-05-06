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
		HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	}
	else {
		//turn off LED and BEE
		HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	}
}
