/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bravoINV.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	qClock_SysTick ();
  /* USER CODE END SysTick_IRQn 0 */
  
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles PVD interrupt through EXTI line 16.
  */
void PVD_IRQHandler(void)
{
  /* USER CODE BEGIN PVD_IRQn 0 */

  /* USER CODE END PVD_IRQn 0 */
  
  /* USER CODE BEGIN PVD_IRQn 1 */

  /* USER CODE END PVD_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
  * @brief This function handles ADC1 and ADC2 interrupts.
  */
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

  /* USER CODE END ADC1_2_IRQn 0 */
  
  /* USER CODE BEGIN ADC1_2_IRQn 1 */

  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

	 if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12) != RESET)
	  {
		 	 bravoCheckPerek();
		 	 LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
	  }

  /* USER CODE END EXTI15_10_IRQn 0 */
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_12) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);
    /* USER CODE BEGIN LL_EXTI_LINE_12 */
    
    /* USER CODE END LL_EXTI_LINE_12 */
  }
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles COMP2 global interrupt through EXTI line 22.
  */
void COMP2_IRQHandler(void)
{
  /* USER CODE BEGIN COMP2_IRQn 0 */

  /* USER CODE END COMP2_IRQn 0 */
  /* USER CODE BEGIN COMP2_IRQn 1 */

  /* USER CODE END COMP2_IRQn 1 */
}

/**
  * @brief This function handles COMP4 and COMP6 interrupts through EXTI lines 30 and 32.
  */
void COMP4_6_IRQHandler(void)
{
  /* USER CODE BEGIN COMP4_6_IRQn 0 */

  /* USER CODE END COMP4_6_IRQn 0 */
  
  /* USER CODE BEGIN COMP4_6_IRQn 1 */

  /* USER CODE END COMP4_6_IRQn 1 */
}

/**
  * @brief This function handles HRTIM master timer global interrupt.
  */
void HRTIM1_Master_IRQHandler(void)
{
  /* USER CODE BEGIN HRTIM1_Master_IRQn 0 */

	//if (LL_HRTIM_IsActiveFlag_REP(HRTIM1,LL_HRTIM_TIMER_MASTER)==1) {
		bravoMainTimerRep();
		LL_HRTIM_ClearFlag_REP(HRTIM1,LL_HRTIM_TIMER_MASTER);
	//}

	/*if (LL_HRTIM_IsActiveFlag_CMP4(HRTIM1,LL_HRTIM_TIMER_MASTER)==1) {
		LL_HRTIM_ClearFlag_CMP4(HRTIM1,LL_HRTIM_TIMER_MASTER);
		bravoSinTableRep();
	}*/

  /* USER CODE END HRTIM1_Master_IRQn 0 */
  
  /* USER CODE BEGIN HRTIM1_Master_IRQn 1 */

  /* USER CODE END HRTIM1_Master_IRQn 1 */
}

/**
  * @brief This function handles HRTIM timer E global interrupt.
  */
void HRTIM1_TIME_IRQHandler(void)
{
  /* USER CODE BEGIN HRTIM1_TIME_IRQn 0 */

	if (LL_HRTIM_IsActiveFlag_REP(HRTIM1,LL_HRTIM_TIMER_E)==1) {
		bravoSinTableRep();
		LL_HRTIM_ClearFlag_REP(HRTIM1,LL_HRTIM_TIMER_E);
	}

	if (LL_HRTIM_IsActiveFlag_CMP2(HRTIM1,LL_HRTIM_TIMER_E)==1) {
		bravoRetrigVDac();
		LL_HRTIM_ClearFlag_CMP2(HRTIM1,LL_HRTIM_TIMER_E);
	}

	if (LL_HRTIM_IsActiveFlag_CMP1(HRTIM1,LL_HRTIM_TIMER_E)==1) {
		bravoRestoreIDac();
		LL_HRTIM_ClearFlag_CMP1(HRTIM1,LL_HRTIM_TIMER_E);
	}

	if (LL_HRTIM_IsActiveFlag_CMP3(HRTIM1,LL_HRTIM_TIMER_E)==1) {
		bravoRestoreIDac();
		LL_HRTIM_ClearFlag_CMP3(HRTIM1,LL_HRTIM_TIMER_E);
	}

  /* USER CODE END HRTIM1_TIME_IRQn 0 */
  
  /* USER CODE BEGIN HRTIM1_TIME_IRQn 1 */

  /* USER CODE END HRTIM1_TIME_IRQn 1 */
}

/**
  * @brief This function handles HRTIM fault global interrupt.
  */
void HRTIM1_FLT_IRQHandler(void)
{
  /* USER CODE BEGIN HRTIM1_FLT_IRQn 0 */

	if ( (LL_HRTIM_IsActiveFlag_FLT2(HRTIM1)==1)
			|| (LL_HRTIM_IsActiveFlag_SYSFLT(HRTIM1)==1)  ) {
		bravoFltStopTask();

		bravoSTATE=FLT;
		qTask_Set_Time(&FirstRunTask,10.0);
		qTask_Resume(&FirstRunTask);

		LL_HRTIM_ClearFlag_FLT2(HRTIM1);
		LL_HRTIM_ClearFlag_SYSFLT(HRTIM1);
	}

  /* USER CODE END HRTIM1_FLT_IRQn 0 */
  
  /* USER CODE BEGIN HRTIM1_FLT_IRQn 1 */

  /* USER CODE END HRTIM1_FLT_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
