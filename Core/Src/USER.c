//
// Created by fibre on 2024/5/7.
//
#define UNIT_TIME 200
#define FIBRE_TIME 500 //500us

#include "USER.h"

static inline void delayMicroseconds(uint32_t us);

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


/**
 * @brief Auto send morse code
 * 			0: break 1: dot 2: dash 3: space 4: end
 * 			and this part of code is for XS018 and SOS
 * **/
void Auto_Morse_Signal(uint8_t* Trans_Msg) {
	//auto send signal
	//0: break 1: dot 2: dash 3: space 4: end
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
			case 3: //space & end
				Morse_Send_Space();
				break;
			case 4: //end
				return;
		}
	}

}
//morse code send assist
void Morse_Send_Dot(void) {
	//send dot
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	HAL_Delay(UNIT_TIME);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	HAL_Delay(UNIT_TIME);
}
void Morse_Send_Dash(void) {
	//send dash
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_RESET);
	HAL_Delay(UNIT_TIME * 3);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LED_R_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, BEE_Pin, GPIO_PIN_SET);
	HAL_Delay(UNIT_TIME);
}
void Morse_Send_Break(void) {
	HAL_Delay(UNIT_TIME * 4);
}
void Morse_Send_Space(void) {
	HAL_Delay(UNIT_TIME * 6);
}

void FibreTran_Pic(uint8_t *data) {
	FibreTran_Start();
	for (int i = 0; i < 1024; ++i) {
		FibreTran_DATA(data[i]);
	}
	FibreTran_End();
}
void FibreTran_Start(void) {
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	delayMicroseconds(FIBRE_TIME * 50);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
}
void FibreTran_DATA(uint8_t data) {
	for (int i = 0; i < 4; ++i) {
		if (data & 0x80) {
			FibreTran_1();
		}
		else {
			FibreTran_0();
		}
		data <<= 1;
	}
}
void FibreTran_0(void) {
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	delayMicroseconds(FIBRE_TIME * 2);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	delayMicroseconds(FIBRE_TIME * 7);
}
void FibreTran_1(void) {
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	delayMicroseconds(FIBRE_TIME * 7);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	delayMicroseconds(FIBRE_TIME * 2);
}
void FibreTran_End(void) {
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_RESET);
	delayMicroseconds(FIBRE_TIME * 50);
	HAL_GPIO_WritePin(GPIOB, LED_Pin, GPIO_PIN_SET);
	BEE_Delay(255);
}


static inline void delayMicroseconds(uint32_t us) {
	__IO uint32_t currentTicks = SysTick->VAL;
	/* Number of ticks per millisecond */
	const uint32_t tickPerMs = SysTick->LOAD + 1;
	/* Number of ticks to count */
	const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
	/* Number of elapsed ticks */
	uint32_t elapsedTicks = 0;
	__IO uint32_t oldTicks = currentTicks;
	do {
		currentTicks = SysTick->VAL;
		elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
		                oldTicks - currentTicks;
		oldTicks = currentTicks;
	}
	while (nbTicks > elapsedTicks);
}