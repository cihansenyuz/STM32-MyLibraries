#include "timer.h"

/* 
* Finds the address of selected timer 
*
* @param timer desired timer
* @return TIM_TypeDef* to the selected timer
*/
TIM_TypeDef * get_timer(char timer){
	TIM_TypeDef * tim;
	switch(timer)
	{
		case 1 : tim = TIM1;break;
		case 2 : tim = TIM2;break;
		case 3 : tim = TIM3;break;
		case 4 : tim = TIM4;break;
	}
	return tim;
}

/* 
* configurates timer to tick each milisecond.
*
* @param timer desired timer
* @param ms desired number of ms
* @return TIM_TypeDef* to the selected timer
* @note prescaler is set considering CPU freq. 72 MHz; otherwise, need to be changed manually
*/
TIM_TypeDef* timer_start_ms(char timer, int ms)
{
	int prescaler = 36000-1; /* (72000)/2 - 1 = 35999 for 0.5 ms */
	TIM_TypeDef * tim;
	
	if(timer == 1)
		RCC->APB2ENR |= 0x800; /* enable timer on bus */
	else
		RCC->APB1ENR |= 1 << (timer-2);
	
	tim = get_timer(timer);
	tim->CNT = 0; /* setup the counter to zero */
	tim->PSC = prescaler; /* setup the prescaler. */
	tim->ARR = (ms*2-1); /* initialize the auto reload register value */
	tim->CR1 |= 0x01; /* enable timer */
	
	return tim;	
}

/* 
* configures timer using timer_start_ms(), and enables timer interrupt
*
* @param timer desired timer
* @param ms desired number of ms
* @return none
*/
void timer_interrupt_start_ms(char timer, int ms)
{
	TIM_TypeDef* tim = timer_start_ms(timer, ms);
	tim->DIER |= 1; /* to enable timer interrupt */
	
	__disable_irq();
	switch(timer)
	{
		case 1 : NVIC_EnableIRQ(TIM1_UP_IRQn);break;
		case 2 : NVIC_EnableIRQ(TIM2_IRQn);break;
		case 3 : NVIC_EnableIRQ(TIM3_IRQn);break;
		case 4 : NVIC_EnableIRQ(TIM4_IRQn);break;
	}
	__enable_irq();
	
}

/* 
* Resets the flag of timer interrupt
*
* @param timer interrupted timer
* @return none
*/
void timer_interrupt_flag_reset(char timer)
{
	TIM_TypeDef* tim = get_timer(timer);
	tim->SR &= 0xFFFE;
}
