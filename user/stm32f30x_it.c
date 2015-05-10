/**
  ******************************************************************************
  * @file    GPIO_IOToggle/stm32f30x_it.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "delay.h"
#include "TIM_init.h"
#include "MPU6050.h"
#include "motor.h"
#include "usart.h"
#include "cal.h"
#include "extern_variable.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t EndOfTransfer;//DMA������ϱ�־λ
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}



/******************************************************************************/
/*                 STM32F30x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f30x.s).                                            */
/******************************************************************************/




/**
  * @brief  This function handles DMA1_Channel6_IRQ Handler.
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler(void)
{
	/* Test on DMA1 Channel6 Transfer Complete interrupt */
  if(DMA_GetITStatus(DMA1_IT_TC6))
  {
    /* DMA1 finished the transfer of SrcBuffer */
    EndOfTransfer = 1;

    /* Clear DMA1 Channel6 Half Transfer, Transfer Complete and Global interrupt pending bits */
    DMA_ClearITPendingBit(DMA1_IT_GL6);
  }
}

/**
  * @brief  This function handles EXTI1_IRQ Handler.
  * @note	ÿ�����ж�ʹ��ȡ���ݱ�־λ
			ռ��ʽ���ȼ� 1
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET){
		EXTI_ClearITPendingBit(EXTI_Line1);
		ReceiveDataEn = 1;
	}
}

/* 	��Ϊ��ʱ����1us
	ռ��ʽ���ȼ� 0
*/
void TIM2_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) 
    {
		TimingDelay_Decrement();
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);   //����жϱ�־  
	}
}

/* 	����֮��10ms
	ռ��ʽ���ȼ� 2
*/
void TIM3_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET ) 
    {
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);   //����жϱ�־ 
		cal_GyroAngleY();
		cal_AccAngleY();
		KalmanFilter_Y(S_FLOAT_AccAngle.AngleY, S_FLOAT_GyroAngle.AngleX);
	}
}

/* 	΢�ֽǶȵý��ٶ�֮��50ms
	ռ��ʽ���ȼ� 3
*/
extern uint8_t flag_50ms;
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		flag_50ms = 1;
	}
}

/* 	�����ж�
	ռ��ʽ���ȼ� 0
*/
int start_flag = 0;
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET){
		start_flag = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}    
}


/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
