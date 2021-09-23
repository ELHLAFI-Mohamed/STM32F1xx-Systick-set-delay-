#include "stm32f1xx.h"
#include "GPIO_drive.h"

void systick_init(void);
void DelayMillis(void);
void DelayMs(unsigned long t);


int signal=0;
int main(void){
	systick_init();

GPIO_init(port_A,0,Input_mode,Input_PP);
GPIO_init(port_C,13,Output_50Mhz,Output_GP_PP);
GPIO_init(port_A,12,Output_50Mhz,Output_GP_PP);
__disable_irq();
AFIO->EXTICR[0]=0X00;
EXTI->IMR |=1;
EXTI->RTSR |=1;
NVIC_EnableIRQ(EXTI0_IRQn);
__enable_irq();

 while(1){
	 GPIO_write(port_A,12,signal);
	 if(signal){
		 DelayMs(1000);

		 GPIO_toggle(port_C,13);

		 DelayMs(1000);

	 }
	 else{
		GPIO_write(port_C,13,0);
	 }
 }


}


void EXTI0_IRQHandler(){

	EXTI->PR|=1;
	if(signal){
		signal=0;
	}
	else signal=1;
}

void systick_init(void){
	SysTick->CTRL=0;
	SysTick->LOAD=0x00FFFFFF;
	SysTick->CTRL=5; // clock processor resource

}

void DelayMillis(void){
	SysTick->LOAD=72000-1; // cpu 72Mhz
	SysTick->VAL=0;
	while((SysTick->CTRL & 0x00010000)==0);
}

void DelayMs(unsigned long t){
	for(;t>0;t--){
		DelayMillis();
	}
}






























