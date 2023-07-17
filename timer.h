#include "stm32f10x.h"

/*
interrupt handlers for timer1 to timer4

void TIM1_UP_IRQHandler(){}
void TIM2_IRQHandler(){}
void TIM3_IRQHandler(){}
void TIM4_IRQHandler(){}
*/

enum timers
{
	timer,timer1,timer2,timer3
};

TIM_TypeDef* get_timer(char timer);
TIM_TypeDef* timer_start_ms(char timer, int ms);
void timer_interrupt_start_ms(char timer, int ms);
void timer_interrupt_flag_reset(char timer);
