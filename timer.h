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

/* 
* Finds the address of selected timer 
*
* @param timer desired timer
* @return TIM_TypeDef* to the selected timer
*/
TIM_TypeDef* get_timer(char timer);

/* 
* configurates timer to tick each milisecond.
*
* @param timer desired timer
* @param ms desired number of ms
* @return TIM_TypeDef* to the selected timer
* @note prescaler is set considering CPU freq. 72 MHz; otherwise, need to be changed manually
*/
TIM_TypeDef* timer_start_ms(char timer, int ms);

/* 
* configures timer using timer_start_ms(), and enables timer interrupt
*
* @param timer desired timer
* @param ms desired number of ms
* @return none
*/
void timer_interrupt_start_ms(char timer, int ms);

/* 
* Resets the flag of timer interrupt
*
* @param timer interrupted timer
* @return none
*/
void timer_interrupt_flag_reset(char timer);
