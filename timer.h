/**
  ******************************************************************************
  * @file    timer.h
  * @author  Cihan Senyuz
  * @brief   Header for timer.c file.
  *                 This file contains the common defines of the application.
  * 
  * 	interrupt handlers for timer1 to timer4
  * 		void TIM1_UP_IRQHandler(){}
  * 		void TIM2_IRQHandler(){}
  * 		void TIM3_IRQHandler(){}
  * 		void TIM4_IRQHandler(){}
  * 
  * @note   Source code depends on stm32f10x.h library
  ******************************************************************************
  */

#include "stm32f10x.h"

enum timers
{
	timer,timer1,timer2,timer3
};

TIM_TypeDef* get_timer(char timer);
TIM_TypeDef* timer_start_ms(char timer, int ms);
void timer_interrupt_start_ms(char timer, int ms);
void timer_interrupt_flag_reset(char timer);
