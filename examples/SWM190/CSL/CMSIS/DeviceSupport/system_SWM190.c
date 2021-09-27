/****************************************************************************************************************************************** 
* �ļ�����:	system_SWM190.c
* ����˵��:	SWM190��Ƭ����ʱ������
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
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
#include <stdint.h>
#include "SWM190.h"


/******************************************************************************************************************************************
 * ϵͳʱ���趨
 *****************************************************************************************************************************************/
#define SYS_CLK_24MHz		0	 	//0 �ڲ���Ƶ24MHz RC����
#define SYS_CLK_3MHz		1		//1 �ڲ���Ƶ 3MHz RC����
#define SYS_CLK_48MHz		2		//2 �ڲ���Ƶ48MHz RC����
#define SYS_CLK_6MHz		3		//3 �ڲ���Ƶ 6MHz RC����
#define SYS_CLK_XTAL		4		//4 �ⲿ����������2-30MHz��
#define SYS_CLK_XTAL_DIV8	5		//5 �ⲿ����������2-30MHz�� 8��Ƶ
#define SYS_CLK_PLL			6		//6 ���໷���
#define SYS_CLK_PLL_DIV8	7		//7 ���໷��� 8��Ƶ
#define SYS_CLK_32KHz		8		//8 �ڲ���Ƶ32KHz RC  ����
#define SYS_CLK_XTAL_32K	9		//9 �ⲿ��Ƶ32KHz ��������

#define SYS_CLK   SYS_CLK_PLL


#define __HSI		(24000000UL)		//�����ڲ�ʱ��
#define __LSI		(   32000UL)		//�����ڲ�ʱ��
#define __HSE		(24000000UL)		//�����ⲿʱ��
#define __LSE		(   32000UL)		//�����ⲿʱ��


/********************************** PLL �趨 **********************************************
 * VCO���Ƶ�� = PLL����ʱ�� / INDIV * 4 * FBDIV
 * PLL���Ƶ�� = PLL����ʱ�� / INDIV * 4 * FBDIV / OUTDIV = VCO���Ƶ�� / OUTDIV         
 *****************************************************************************************/ 
#define SYS_PLL_SRC   	SYS_CLK_24MHz	//��ȡֵSYS_CLK_24MHz��SYS_CLK_48MHz��SYS_CLK_XTAL

#define PLL_IN_DIV		6				//SYS_PLL_SRC = SYS_CLK_24MHz ʱ�� 6�� SYS_PLL_SRC = SYS_CLK_48MHz ʱ�� 12

#define PLL_FB_DIV		30


#define PLL_OUT_DIV8	0
#define PLL_OUT_DIV4	1
#define PLL_OUT_DIV2	2

#define PLL_OUT_DIV		PLL_OUT_DIV8



uint32_t SystemCoreClock  = __HSI;   				//System Clock Frequency (Core Clock)
uint32_t CyclesPerUs      = (__HSI / 1000000); 		//Cycles per micro second


/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: This function is used to update the variable SystemCoreClock and must be called whenever the core clock is changed
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemCoreClockUpdate(void)    
{
	if(SYS->CLKSEL & SYS_CLKSEL_SYS_Msk)			//SYS  <= HRC
	{
		if(SYS->HRCCR & SYS_HRCCR_DBL_Msk)				//HRC = 48MHz
		{
			SystemCoreClock = __HSI*2;
		}
		else											//HRC = 24MHz
		{
			SystemCoreClock = __HSI;
		}
	}
	else											//SYS  <= CLK
	{
		switch((SYS->CLKSEL & SYS_CLKSEL_CLK_Msk) >> SYS_CLKSEL_CLK_Pos)
		{
		case 0:
			SystemCoreClock = __LSI;
			break;
		
		case 1:
			if(SYS->PLLCR & SYS_PLLCR_INSEL_Msk)			//PLL_IN <= HRC
			{
				if(SYS->HRCCR & SYS_HRCCR_DBL_Msk)				//HRC = 48MHz
				{
					SystemCoreClock = __HSI*2;
				}
				else											//HRC = 24MHz
				{
					SystemCoreClock = __HSI;
				}
			}
			else											//PLL_IN <= XTAL
			{
				SystemCoreClock = __HSE;
			}
			
			SystemCoreClock = SystemCoreClock / PLL_IN_DIV * PLL_FB_DIV * 4 / (2 << (2 - PLL_OUT_DIV));
			break;
		
		case 2:
			SystemCoreClock = __LSE;
			break;
		
		case 3:
			SystemCoreClock = __HSE;
			break;
		
		case 4:
			SystemCoreClock = __HSI;
			if(SYS->HRCCR & SYS_HRCCR_DBL_Msk)  SystemCoreClock *= 2;
			break;
		}
		
		if(SYS->CLKSEL & SYS_CLKSEL_CLK_DIVx_Msk)  SystemCoreClock /= 8;
	}
	
	CyclesPerUs = SystemCoreClock / 1000000;
}

/****************************************************************************************************************************************** 
* ��������: 
* ����˵��: The necessary initializaiton of systerm
* ��    ��: 
* ��    ��: 
* ע������: 
******************************************************************************************************************************************/
void SystemInit(void)
{		
	SYS->CLKEN0 |= (1 << SYS_CLKEN0_ANAC_Pos);
	
	switch(SYS_CLK)
	{
		case SYS_CLK_24MHz:
			switchTo24MHz();
			break;
		
		case SYS_CLK_3MHz:
			switchTo3MHz();
			break;
		
		case SYS_CLK_48MHz:
			switchTo48MHz();
			break;
		
		case SYS_CLK_6MHz:
			switchTo6MHz();
			break;
		
		case SYS_CLK_XTAL:
			switchToXTAL(0);
			break;
		
		case SYS_CLK_XTAL_DIV8:
			switchToXTAL(1);
			break;
		
		case SYS_CLK_PLL:
			switchToPLL(0);
			break;
		
		case SYS_CLK_PLL_DIV8:
			switchToPLL(1);
			break;
		
		case SYS_CLK_32KHz:
			switchTo32KHz();
			break;
		
		case SYS_CLK_XTAL_32K:
			switchToXTAL_32K();
			break;
	}
	
	SystemCoreClockUpdate();
}

void switchTo24MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_ON_Pos) |
				 (0 << SYS_HRCCR_DBL_Pos);			//HRC = 24Hz
	
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);		//SYS <= HRC
}

void switchTo3MHz(void)
{
	switchTo24MHz();
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (4 << SYS_CLKSEL_CLK_Pos);		//CLK <= HRC

	SYS->CLKSEL |= (1 << SYS_CLKSEL_CLK_DIVx_Pos);
	
	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= HRC/8
}

void switchTo48MHz(void)
{
	SYS->HRCCR = (1 << SYS_HRCCR_ON_Pos) |
				 (1 << SYS_HRCCR_DBL_Pos);			//HRC = 48MHz
	
	SYS->CLKSEL |= (1 << SYS_CLKSEL_SYS_Pos);		//SYS <= HRC
}

void switchTo6MHz(void)
{
	switchTo48MHz();
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (4 << SYS_CLKSEL_CLK_Pos);		//CLK <= HRC

	SYS->CLKSEL |= (1 << SYS_CLKSEL_CLK_DIVx_Pos);
	
	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= HRC/8
}

void switchToXTAL(uint32_t div8)
{
	uint32_t i;
	
	switchTo24MHz();
	
	PORT_Init(PORTC, PIN1, PORTC_PIN1_XTAL_IN,  0);
	PORT_Init(PORTC, PIN0, PORTC_PIN0_XTAL_OUT, 0);
	SYS->XTALCR |= (1 << SYS_XTALCR_ON_Pos) | (7 << SYS_XTALCR_DRV_Pos) | (1 << SYS_XTALCR_DET_Pos);
	for(i = 0; i < 1000; i++) __NOP();
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (3 << SYS_CLKSEL_CLK_Pos);		//CLK <= XTAL

	if(div8) SYS->CLKSEL |= (1 << SYS_CLKSEL_CLK_DIVx_Pos);
	else     SYS->CLKSEL &=~(1 << SYS_CLKSEL_CLK_DIVx_Pos);
	
	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= XTAL
}

void switchToPLL(uint32_t div8)
{
	switchTo24MHz();
	
	PLLInit();
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (1 << SYS_CLKSEL_CLK_Pos);		//CLK <= PLL

	if(div8)  SYS->CLKSEL |= (1 << SYS_CLKSEL_CLK_DIVx_Pos);
	else      SYS->CLKSEL &=~(1 << SYS_CLKSEL_CLK_DIVx_Pos);
	
	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= PLL
}

void switchTo32KHz(void)
{
	switchTo24MHz();
	
	SYS->LRCCR = (1 << SYS_LRCCR_ON_Pos);
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (0 << SYS_CLKSEL_CLK_Pos);		//CLK <= LRC

	SYS->CLKSEL &=~(1 << SYS_CLKSEL_CLK_DIVx_Pos);

	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= LRC
}

void switchToXTAL_32K(void)
{
	uint32_t i;
	
	switchTo24MHz();
	
	SYS->XTALCR |= (1 << SYS_XTALCR_32KON_Pos) | (1 << SYS_XTALCR_32KDRV_Pos) | (1 << SYS_XTALCR_32KDET_Pos);
	for(i = 0; i < 1000; i++) __NOP();
	
	SYS->CLKDIVx_ON = 1;
	
	SYS->CLKSEL &= ~SYS_CLKSEL_CLK_Msk;
	SYS->CLKSEL |= (2 << SYS_CLKSEL_CLK_Pos);		//CLK <= XTAL_32K

	SYS->CLKSEL &=~(1 << SYS_CLKSEL_CLK_DIVx_Pos);

	SYS->CLKSEL &=~(1 << SYS_CLKSEL_SYS_Pos);		//SYS <= XTAL_32K
}

void PLLInit(void)
{
	uint32_t i;
	
	if(SYS_PLL_SRC == SYS_CLK_24MHz)
	{
		SYS->HRCCR = (1 << SYS_HRCCR_ON_Pos) |
					 (0 << SYS_HRCCR_DBL_Pos);		//HRC = 24Hz
		
		SYS->PLLCR |= (1 << SYS_PLLCR_INSEL_Pos);	//PLL_SRC <= HRC
	}
	else if(SYS_PLL_SRC == SYS_CLK_48MHz)
	{
		SYS->HRCCR = (1 << SYS_HRCCR_ON_Pos) |
					 (1 << SYS_HRCCR_DBL_Pos);		//HRC = 48Hz
		
		SYS->PLLCR |= (1 << SYS_PLLCR_INSEL_Pos);	//PLL_SRC <= HRC
	}
	else if(SYS_PLL_SRC == SYS_CLK_XTAL)
	{
		PORT_Init(PORTC, PIN1, PORTC_PIN1_XTAL_IN,  0);
		PORT_Init(PORTC, PIN0, PORTC_PIN0_XTAL_OUT, 0);
		
		SYS->XTALCR |= (1 << SYS_XTALCR_ON_Pos) | (7 << SYS_XTALCR_DRV_Pos) | (1 << SYS_XTALCR_DET_Pos);
		for(i = 0; i < 1000; i++) __NOP();
		
		SYS->PLLCR &= ~(1 << SYS_PLLCR_INSEL_Pos);	//PLL_SRC <= XTAL
	}
	
	SYS->PLLDIV &= ~(SYS_PLLDIV_INDIV_Msk |
					 SYS_PLLDIV_FBDIV_Msk |
					 SYS_PLLDIV_OUTDIV_Msk);
	SYS->PLLDIV |= (PLL_IN_DIV << SYS_PLLDIV_INDIV_Pos) |
				   (PLL_FB_DIV << SYS_PLLDIV_FBDIV_Pos) |
				   (PLL_OUT_DIV<< SYS_PLLDIV_OUTDIV_Pos);
	
	SYS->PLLCR &= ~(1 << SYS_PLLCR_OFF_Pos);
	
	while(SYS->PLLLOCK == 0);		//�ȴ�PLL����
	
	SYS->PLLCR |= (1 << SYS_PLLCR_OUTEN_Pos);
}
