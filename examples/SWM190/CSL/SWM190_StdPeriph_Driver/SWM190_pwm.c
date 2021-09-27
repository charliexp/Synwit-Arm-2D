/****************************************************************************************************************************************** 
* �ļ�����:	SWM190_pwm.c
* ����˵��:	SWM190��Ƭ����PWM����������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����:	V1.0.0		2016��1��30��
* ������¼: 
*
*
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology 
*******************************************************************************************************************************************/
#include "SWM190.h"
#include "SWM190_pwm.h"


PWM_TypeDef * PWMX[8] = {PWM0, PWM0, PWM1, PWM1, PWM2, PWM2, PWM3, PWM3};


/****************************************************************************************************************************************** 
* ��������:	PWM_Init()
* ����˵��:	PWM��ʼ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
*			PWM_InitStructure * initStruct	����PWM����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_Init(uint32_t pwmx, PWM_InitStructure * initStruct)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
	
	SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_PWM_Pos);
	
	PWMG->CLKDIV = initStruct->clkdiv;
	
	PWM_Stop(pwmx);		//һЩ�ؼ��Ĵ���ֻ����PWMֹͣʱ����
	
	PWMx->MODE = initStruct->PWMnXN ? 5 : 0;
	
	if((pwmx%2) == 0)
	{
		PWMx->PERA = initStruct->cycle;
		PWMx->HIGHA = initStruct->hduty << 1;
		PWMx->DZA = initStruct->deadzone;
		
		if(initStruct->initLevel) PWMx->OUTCR |=  (1 << PWM_OUTCR_INIA_Pos);
		else                      PWMx->OUTCR &= ~(1 << PWM_OUTCR_INIA_Pos);
		
		PWMG->IM = 0x00000000;
		PWMG->HCIM = 0x000000;
		switch((uint32_t)PWMx)
		{
		case((uint32_t)PWM0):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM0A_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM0A_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC0A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC0A_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE0A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE0A_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM0A_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM0A_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM0_IRQn);
			break;

		case((uint32_t)PWM1):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM1A_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM1A_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC1A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC1A_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE1A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE1A_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM1A_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM1A_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM1_GPIOB6_IRQn);
			break;

		case((uint32_t)PWM2):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM2A_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM2A_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC2A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC2A_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE2A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE2A_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM2A_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM2A_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM2_FLASH_IRQn);
			break;
		
		case((uint32_t)PWM3):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM3A_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM3A_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC3A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC3A_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE3A_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE3A_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM3A_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM3A_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM3_CACHE_IRQn);
			break;
		}
	}
	else
	{
		PWMx->PERB = initStruct->cycle;
		PWMx->HIGHB = initStruct->hduty << 1;
		PWMx->DZB = initStruct->deadzone;
		
		if(initStruct->initLevel) PWMx->OUTCR |=  (1 << PWM_OUTCR_INIB_Pos);
		else                      PWMx->OUTCR &= ~(1 << PWM_OUTCR_INIB_Pos);
		
		PWMG->IM = 0x00000000;
		PWMG->HCIM = 0x000000;
		switch((uint32_t)PWMx)
		{
		case((uint32_t)PWM0):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM0B_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM0B_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC0B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC0B_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE0B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE0B_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM0B_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM0B_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM0_IRQn);
			break;

		case((uint32_t)PWM1):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM1B_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM1B_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC1B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC1B_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE1B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE1B_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM1B_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM1B_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM1_GPIOB6_IRQn);
			break;

		case((uint32_t)PWM2):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM2B_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM2B_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC2B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC2B_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE2B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE2B_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM2B_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM2B_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM2_FLASH_IRQn);
			break;
		
		case((uint32_t)PWM3):
			PWMG->NCIRS = (1 << PWMG_NCIRS_PWM3B_Pos);
			PWMG->HEIRS = (1 << PWMG_HEIRS_PWM3B_Pos);
			if(initStruct->NCycleIE) PWMG->IE |=  (1 << PWMG_IE_NC3B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_NC3B_Pos);
			if(initStruct->HEndIE)   PWMG->IE |=  (1 << PWMG_IE_HE3B_Pos);
			else                     PWMG->IE &= ~(1 << PWMG_IE_HE3B_Pos);
			if(initStruct->HCycleIE) PWMG->HCIE |=  (1 << PWMG_HCIE_PWM3B_Pos);
			else                     PWMG->HCIE &= ~(1 << PWMG_HCIE_PWM3B_Pos);
			if(initStruct->HEndIE | initStruct->NCycleIE | initStruct->HCycleIE) NVIC_EnableIRQ(PWM3_CACHE_IRQn);
			break;
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWM_Start()
* ����˵��:	����PWM����ʼPWM���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_Start(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->CHEN |= (1 << PWMG_CHEN_PWM0A_Pos);
		else              PWMG->CHEN |= (1 << PWMG_CHEN_PWM0B_Pos);
		break;

	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->CHEN |= (1 << PWMG_CHEN_PWM1A_Pos);
		else              PWMG->CHEN |= (1 << PWMG_CHEN_PWM1B_Pos);
		break;

	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->CHEN |= (1 << PWMG_CHEN_PWM2A_Pos);
		else              PWMG->CHEN |= (1 << PWMG_CHEN_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->CHEN |= (1 << PWMG_CHEN_PWM3A_Pos);
		else              PWMG->CHEN |= (1 << PWMG_CHEN_PWM3B_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWM_Stop()
* ����˵��:	�ر�PWM��ֹͣPWM���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_Stop(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM0A_Pos);
		else              PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM0B_Pos);
		break;

	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM1A_Pos);
		else              PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM1B_Pos);
		break;

	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM2A_Pos);
		else              PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM3A_Pos);
		else              PWMG->CHEN &= ~(1 << PWMG_CHEN_PWM3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_SetCycle()
* ����˵��:	��������
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
*			uint32_t cycle			Ҫ�趨������ֵ,28λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_SetCycle(uint32_t pwmx, uint32_t cycle)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
	
	if((pwmx%2) == 0) PWMx->PERA = cycle;
	else              PWMx->PERB = cycle;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_GetCycle()
* ����˵��:	��ȡ����
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint32_t				��ȡ��������ֵ
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWM_GetCycle(uint32_t pwmx)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
	
	if((pwmx%2) == 0) return PWMx->PERA;
	else              return PWMx->PERB;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_SetHDuty()
* ����˵��:	���øߵ�ƽʱ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
*			uint32_t hduty			Ҫ�趨�ĸߵ�ƽʱ��,28λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_SetHDuty(uint32_t pwmx, uint32_t hduty)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
	
	if((pwmx%2) == 0) PWMx->HIGHA = hduty << 1;
	else              PWMx->HIGHB = hduty << 1;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_GetHDuty()
* ����˵��: ��ȡ�ߵ�ƽʱ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint32_t				��ȡ���ĸߵ�ƽʱ��
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWM_GetHDuty(uint32_t pwmx)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
		
	if((pwmx%2) == 0) return PWMx->HIGHA >> 1;
	else              return PWMx->HIGHB >> 1;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_SetDeadzone()
* ����˵��:	��������ʱ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
*			uint16_t deadzone		Ҫ�趨������ʱ����ȡֵ��Χ0--1023
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_SetDeadzone(uint32_t pwmx, uint16_t deadzone)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
	
	if((pwmx%2) == 0) PWMx->DZA = deadzone;
	else              PWMx->DZB = deadzone;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_GetDeadzone()
* ����˵��: ��ȡ����ʱ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint16_t					��ȡ��������ʱ��
* ע������: ��
******************************************************************************************************************************************/
uint16_t  PWM_GetDeadzone(uint32_t pwmx)
{
	PWM_TypeDef * PWMx = PWMX[pwmx];
		
	if((pwmx%2) == 0) return PWMx->DZA;
	else              return PWMx->DZB;
}


/****************************************************************************************************************************************** 
* ��������:	PWM_IntNCycleEn()
* ����˵��: �����ڿ�ʼ�ж�ʹ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntNCycleEn(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_NC0A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_NC0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_NC1A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_NC1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_NC2A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_NC2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_NC3A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_NC3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntNCycleDis()
* ����˵��: �����ڿ�ʼ�жϽ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntNCycleDis(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_NC0A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_NC0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_NC1A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_NC1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_NC2A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_NC2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_NC3A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_NC3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntNCycleClr()
* ����˵��: �����ڿ�ʼ�жϱ�־���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntNCycleClr(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM0A_Pos);
		else			  PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM1A_Pos);
		else			  PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM2A_Pos);
		else			  PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM3A_Pos);
		else			  PWMG->NCIRS = (0x01 << PWMG_NCIRS_PWM3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntNCycleStat()
* ����˵��: �����ڿ�ʼ�ж��Ƿ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint32_t				��0 �����ڿ�ʼ�ж��ѷ���    0 �����ڿ�ʼ�ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWM_IntNCycleStat(uint32_t pwmx)
{	
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) return (PWMG->NCIF & PWMG_NCIF_PWM0A_Msk);
		else			  return (PWMG->NCIF & PWMG_NCIF_PWM0B_Msk);

	case((uint32_t)PWM1):
		if((pwmx%2) == 0) return (PWMG->NCIF & PWMG_NCIF_PWM1A_Msk);
		else			  return (PWMG->NCIF & PWMG_NCIF_PWM1B_Msk);

	case((uint32_t)PWM2):
		if((pwmx%2) == 0) return (PWMG->NCIF & PWMG_NCIF_PWM2A_Msk);
		else			  return (PWMG->NCIF & PWMG_NCIF_PWM2B_Msk);
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) return (PWMG->NCIF & PWMG_NCIF_PWM3A_Msk);
		else			  return (PWMG->NCIF & PWMG_NCIF_PWM3B_Msk);
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	PWM_IntHEndEn()
* ����˵��: �ߵ�ƽ�����ж�ʹ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHEndEn(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_HE0A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_HE0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_HE1A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_HE1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_HE2A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_HE2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->IE |= (0x01 << PWMG_IE_HE3A_Pos);
		else			  PWMG->IE |= (0x01 << PWMG_IE_HE3B_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHEndDis()
* ����˵��: �ߵ�ƽ�����жϽ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHEndDis(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_HE0A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_HE0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_HE1A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_HE1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_HE2A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_HE2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->IE &= ~(0x01 << PWMG_IE_HE3A_Pos);
		else			  PWMG->IE &= ~(0x01 << PWMG_IE_HE3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHEndClr()
* ����˵��: �ߵ�ƽ�����жϱ�־���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHEndClr(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM0A_Pos);
		else			  PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM1A_Pos);
		else			  PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM2A_Pos);
		else			  PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM3A_Pos);
		else			  PWMG->HEIRS = (0x01 << PWMG_HEIRS_PWM3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHEndStat()
* ����˵��: �ߵ�ƽ�����ж��Ƿ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint32_t				��0 �ߵ�ƽ�����ж��ѷ���    0 �ߵ�ƽ�����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWM_IntHEndStat(uint32_t pwmx)
{	
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) return (PWMG->HEIF & PWMG_HEIF_PWM0A_Msk);
		else			  return (PWMG->HEIF & PWMG_HEIF_PWM0B_Msk);

	case((uint32_t)PWM1):
		if((pwmx%2) == 0) return (PWMG->HEIF & PWMG_HEIF_PWM1A_Msk);
		else			  return (PWMG->HEIF & PWMG_HEIF_PWM1B_Msk);

	case((uint32_t)PWM2):
		if((pwmx%2) == 0) return (PWMG->HEIF & PWMG_HEIF_PWM2A_Msk);
		else			  return (PWMG->HEIF & PWMG_HEIF_PWM2B_Msk);
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) return (PWMG->HEIF & PWMG_HEIF_PWM3A_Msk);
		else			  return (PWMG->HEIF & PWMG_HEIF_PWM3B_Msk);
	}
	
	return 0;
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHCycleEn()
* ����˵��: �������ж�ʹ��
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHCycleEn(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM0A_Pos);
		else			  PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM1A_Pos);
		else			  PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM2A_Pos);
		else			  PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM3A_Pos);
		else			  PWMG->HCIE |= (0x01 << PWMG_HCIE_PWM3B_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHCycleDis()
* ����˵��: �������жϽ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHCycleDis(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM0A_Pos);
		else			  PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM1A_Pos);
		else			  PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM2A_Pos);
		else			  PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM3A_Pos);
		else			  PWMG->HCIE &= ~(0x01 << PWMG_HCIE_PWM3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHCycleClr()
* ����˵��: �������жϱ�־���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWM_IntHCycleClr(uint32_t pwmx)
{
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM0A_Pos);
		else			  PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM0B_Pos);
		break;
	
	case((uint32_t)PWM1):
		if((pwmx%2) == 0) PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM1A_Pos);
		else			  PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM1B_Pos);
		break;
	
	case((uint32_t)PWM2):
		if((pwmx%2) == 0) PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM2A_Pos);
		else			  PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM2B_Pos);
		break;
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM3A_Pos);
		else			  PWMG->HCIRS = (0x01 << PWMG_HCIRS_PWM3B_Pos);
		break;
	} 
}

/****************************************************************************************************************************************** 
* ��������:	PWM_IntHCycleStat()
* ����˵��: �������ж��Ƿ���
* ��    ��: uint32_t pwmx			ָ��Ҫ�����õ�PWM����Чֵ����PWM0A��PWM0B��PWM1A��PWM1B��PWM2A��PWM2B��PWM3A��PWM3B
* ��    ��: uint32_t				��0 �������ж��ѷ���    0 �������ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWM_IntHCycleStat(uint32_t pwmx)
{	
	switch((uint32_t)PWMX[pwmx])
	{
	case((uint32_t)PWM0):
		if((pwmx%2) == 0) return (PWMG->HCIF & PWMG_HCIF_PWM0A_Msk);
		else			  return (PWMG->HCIF & PWMG_HCIF_PWM0B_Msk);

	case((uint32_t)PWM1):
		if((pwmx%2) == 0) return (PWMG->HCIF & PWMG_HCIF_PWM1A_Msk);
		else			  return (PWMG->HCIF & PWMG_HCIF_PWM1B_Msk);

	case((uint32_t)PWM2):
		if((pwmx%2) == 0) return (PWMG->HCIF & PWMG_HCIF_PWM2A_Msk);
		else			  return (PWMG->HCIF & PWMG_HCIF_PWM2B_Msk);
	
	case((uint32_t)PWM3):
		if((pwmx%2) == 0) return (PWMG->HCIF & PWMG_HCIF_PWM3A_Msk);
		else			  return (PWMG->HCIF & PWMG_HCIF_PWM3B_Msk);
	}
	
	return 0;
}

