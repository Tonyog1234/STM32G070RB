#include "stm32g0xx.h"


int main(){
	// PB1 : LED ,  PA0: USART4_Tx  ,  PA1: USART4_Rx
	volatile char msg =0; // store the data from receive data register
	RCC->IOPENR |= 0b11;  //enable GPIOA & GPIOB
	
	//********GPIOA Alternate function**********
	GPIOA->MODER &= ~(0xF) ;// Reset the last four bits which is pin 0 and pin 1
	GPIOA->MODER |= (0xA); //Set up Pin 0 and Pin 1 as alternate function
	
	GPIOA->AFR[0] &= (0b0100) ; //set up PA0 as  AF4 (USART4)              
	GPIOA->AFR[0] &= (0b0100<<4) ; // set up PA1 as AF4 (USART4) 
	
	
	//******Enable PB1 for LED**************
	GPIOB->MODER &= ~(0b11<<1*2) ;// Reset the last two bits
	GPIOB->MODER |= (0b01<<1*2); //Set up Pin 1 as output
	
	GPIOB->OTYPER &= ~(0b1<<1); // Set up  pin 1 as push pull
	
	//**********Initialize USART4**************
	
	//*******Enable USART 4(RCC)************
	RCC->APBENR1 |= (1<<19); 
	
	//*******Set up baud rate for 9600bps************
	USART4->BRR =(16000000/9600); //       from reference manual                                      
	
	//******Disable FIFO(First in first out) mode for USART4**********
	USART4->CR1 &= ~(1<<29);
	
	// Enable USART 4 Transmit(TE)
	USART4->CR1 |= 0b1000;
	
	// Enable USART 4 Recive(RE)
	USART4->CR1 |= 0b0100;
	
	// Enable USART 4(UE)
	USART4->CR1 |= 0x0001;
	
	
	while(1){
		
		while(!(USART4->ISR & USART_ISR_RXNE_RXFNE)){ //RXNE : data is ready to be read
			
		}
		msg = USART4->RDR ;//read from recieve data register
		
		if(msg == '1'){
			GPIOB->ODR |=(0b1<<1); //PB1 become high => turn on LED 
		}
		else if(msg == '0'){
			GPIOB->ODR &=~(0b1<<1); //PB1 become low => turn off LED 
		}
	}
	}


