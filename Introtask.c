#include "stm32g0xx.h"


int main(){
	// PB1 : LED ,  PA0: USART4_Tx  ,  PA1: USART4_Rx
	
	RCC->IOPENR |= 0b11;  //enable GPIOA & GPIOB
	
	//********GPIOA Alternate function**********
	GPIOA->MODER &= ~(0xF) ;// Reset the last four bits which is pin 0 and pin 1
	GPIOA->MODER |= (0xA); //Set up Pin 0 and Pin 1 as alternate function
	
	GPIOA->AFR[0] &= (0b0100) ; //set up PA0 as  AF4 (USART4)              ***Need to ask why there is no AFRL***
	GPIOA->AFR[1] &= (0b0100) ; // set up PA1 as AF4 (USART4) 
	
	
	//******Enable PB1 for LED**************
	GPIOB->MODER &= ~(0b11<<1*2) ;// Reset the last two bits
	GPIOB->MODER |= (0b01<<1*2); //Set up Pin 1 as output
	
	GPIOB->OTYPER &= ~(0b1<<1); // Set up  pin 1 as push pull
	
	//**********Initialize USART4**************
	
	//*******Enable USART 4(RCC)************
	RCC->APBENR1 |= (1<<19); 
	
	//*******Set up baud rate for 9600bps************
	USART4->BRR =0x0341; //       from reference manual                                      
	
	//******Enable FIFO(First in first out) mode for USART4**********
	USART4->CR1 |= (1<<29);
	
	// Enable USART 4 Transmit(TE)
	USART4->CR1 |= 0b1000;
	
	// Enable USART 4 Recive(RE)
	USART4->CR1 |= 0b0100;
	
	// Enable USART 4(UE)
	USART4->CR1 |= 0x0001;
	
	
	while(1){
		
		//Android phone sends integer 1 through bluethooth terminal
		if(USART4->RDR == 1){
			GPIOB->ODR |= (0b1<<1); //PB1 becomes high => turn on LED
		}
	
		//Android phone sends integer 0 through bluethooth terminal
		else if(USART4->RDR == 0){
			GPIOB->ODR &= ~(0b1<<1); // PB1 become low => turn off LED
		}
	}
}


