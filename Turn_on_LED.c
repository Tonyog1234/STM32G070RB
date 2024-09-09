#include "stm32g0xx.h"


int main(){
	
	RCC->IOPENR |= 0b1;  //enable GPIOA
	
	GPIOA->MODER &= ~(0b11) ;// Reset the last two bits
	GPIOA->MODER |= (0b01); //Set up Pin 0 as output
	
	GPIOA->OTYPER &= ~(0b1); // Set up the pin as push pull
	
	GPIOA->ODR |= (0b1); //Set Pin 0 high or on
}


