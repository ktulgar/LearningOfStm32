
#include "main.h"
#include "stdio.h"
#include "string.h"


void SystemClock_Config(void);
static void MX_GPIO_Init(void);

// Prototypes

void initLEDS(void);
void initUART(void);

void receiveMessage(char[] , int);
char receiveChar(void);

void sendMessage(char[] , int);
void sendChar(char);

char txBuffer[50];
char rxBuffer[50];

int main(void)
{
  
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
	initLEDS();
	initUART();
  
 
  while (1)
		
  {
	
		
	  	/*  Receiving Char
		
		char message = receiveChar();
		
		if(message == 'g') 
			   GPIOD->ODR = 0x1000; 
		else if(message == 'o') 
			   GPIOD->ODR = 0x2000; 
		else if(message == 'r') 
			   GPIOD->ODR = 0x4000; 
		else if(message == 'b') 
			   GPIOD->ODR = 0x8000; 
		
	   */
	
		
		
		
		/* Sending Message
		
		sendMessage(txBuffer,sprintf(txBuffer,"Hello World\n"));
		HAL_Delay(100000); 
		
		*/
		
	
  }
 
}

void initLEDS(void) {

	RCC->AHB1ENR |= 0x8; // Enable GPIOD to use user LEDS
	GPIOD->MODER |= 0x55000000; // Set as 12-13-14-15-16 as output
	GPIOD->OSPEEDR |=  0xFF000000; // Set as 12-13-14-15 as High-Speed
	GPIOD->PUPDR = 0 ; // No pull-up pull-down
	
}

void initUART(void) {

	RCC->APB1ENR |= 0x80000; // Enable UART4
	RCC->AHB1ENR |= 0x1;     // Enable GPIOA
	
	GPIOA->MODER |= 0xA;     // Set GPIOA 0-1 as Alternate Function
	GPIOA->OTYPER |= 0x3;    // Set GPIOA 0-1 as Open-Drain
	GPIOA->AFR[0] |= 0x88;   // I specify that GPIOA 0-1 will be Uart rx and tx
	
	UART4->CR1 |= 0x200C;    // Enable TE,RE,USART
	UART4->BRR = 0x1117;     // I adjust the Baud Rate to 9600 . APB1 runs on 42 mhz. 

}

void receiveMessage(char rxBuffer[] , int length) {
	
	for(int i=0 ; i<length ; i++) {
	
		*rxBuffer = receiveChar();
     rxBuffer++;		
	
	}
		
}

char receiveChar(void) {

	char message;
	while(!(UART4->SR & USART_SR_RXNE));		
	message = UART4->DR;
	return message; 

}

void sendMessage(char message[] ,int length) {

  for(int i=0 ; i<length ; i++) {
	
		sendChar(*message);
		message++;
	
	}

}

void sendChar(char myChar) {

	while(!(UART4->SR & USART_SR_TXE));
	UART4->DR = myChar;
	while(!(UART4->SR & USART_SR_TC));

}



void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

 
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
 
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void)
{


  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}


void Error_Handler(void)
{
  
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{ 
  
}
#endif 
