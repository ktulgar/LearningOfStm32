
#include "main.h"
#include "stm32f4xx_it.h"

extern TIM_HandleTypeDef htim2;
extern uint8_t period;
uint16_t binaryNumbers[16] = {0x0000,0x1000,0x2000,0x3000,0x4000,0x5000,0x6000,0x7000,0x8000,0x9000,0xA000,0xB000,0xC000,0xD000,0xE000,0xF000};

void NMI_Handler(void)
{

}


void HardFault_Handler(void)
{

  while (1)
  {

  }
}


void MemManage_Handler(void)
{

  while (1)
  {

  }
}


void BusFault_Handler(void)
{

  while (1)
  {

  }
}


void UsageFault_Handler(void)
{

  while (1)
  {

  }
}


void SVC_Handler(void)
{

}


void DebugMon_Handler(void)
{

}


void PendSV_Handler(void)
{

}


void SysTick_Handler(void)
{

  HAL_IncTick();

}


void TIM2_IRQHandler(void)
{

 if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_SET)
	                                  period++;
 else {

	 if(period>15) {
		 GPIOD->ODR = binaryNumbers[15];
		 period = 0;
	 }

	 else if(period<=15 && period > 0) {
		 GPIOD->ODR = binaryNumbers[period];
	     period = 0; }

	 else {
		 period = 0;
	 }


 }

  HAL_TIM_IRQHandler(&htim2);
}

