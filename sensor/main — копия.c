#include <stm32f10x.h>


void delay(uint32_t time){
	while(time!=0){
		time--;
	}
}


void Sensor_InPullUp (void)
{
	GPIOC->CRL &=~ GPIO_CRL_MODE0;
	GPIOC->CRL |= GPIO_CRL_CNF0_1;
	GPIOC->CRL &=~ GPIO_CRL_CNF0_0;
	GPIOC->BSRR |= GPIO_BSRR_BS0;
}

void Sensor_Ground (void)
{
	GPIOC->CRL |= GPIO_CRL_MODE0_0;
	GPIOC->CRL &=~ GPIO_CRL_MODE0_1;
	GPIOC->CRL &=~ GPIO_CRL_CNF0;
	GPIOC->BRR |= GPIO_BRR_BR0;
}




int main(){
	uint16_t count;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE8;
	GPIOC->CRH &=~ GPIO_CRH_CNF8;
	while(1==1){
		Sensor_Ground();
		delay(0xFF);    //простой пустой счётчик
		count = 0;
		Sensor_InPullUp();
		while(!(GPIOC->IDR & GPIO_IDR_IDR0))
    {
    	count++;
			if(count==256){
				break;
			}
    }
		if(count>1){
			GPIOC->BSRR |= GPIO_BSRR_BS8;
			delay(1000000);
			GPIOC->BSRR |= GPIO_BSRR_BR8;
			delay(1000000);
		}
	}
}