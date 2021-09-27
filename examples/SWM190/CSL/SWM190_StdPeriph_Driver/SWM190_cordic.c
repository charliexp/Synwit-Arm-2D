/****************************************************************************************************************************************** 
* �ļ�����: SWM190_cordic.c
* ����˵��:	SWM190��Ƭ����CORDIC����������
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
#include "SWM190_cordic.h"


/****************************************************************************************************************************************** 
* ��������:	CORDIC_Init()
* ����˵��:	CORDIC��ʼ��
* ��    ��: CORDIC_TypeDef * CORDICx	ָ��Ҫ�����õ�CORDIC����Чֵ����CORDIC
* ��    ��: ��
* ע������: CORDICģ������DIVģ�飬��ΪCORDIC_Arctan()Ҫʹ��Ӳ������ģ��������ֵ
******************************************************************************************************************************************/
void CORDIC_Init(CORDIC_TypeDef * CORDICx)
{
	switch((uint32_t)CORDICx)
	{
	case ((uint32_t)CORDIC):
		SYS->CLKEN0 |= (0x01 << SYS_CLKEN0_CORDIC_Pos);
		break;
	}
}


/****************************************************************************************************************************************** 
* ��������:	CORDIC_FullCycleSin()
* ����˵��:	ʹ��CORDICģ�����sin
* ��    ��: double radian		Ҫ����Ļ���ֵ
* ��    ��: double
* ע������: ��
******************************************************************************************************************************************/
double CORDIC_FullCycleSin(double radian)
{
	double res;
	uint32_t negative = 0;
	
	while(radian < 0) radian += 2*CORDIC_PI;
	
	while(radian > 2*CORDIC_PI) radian -= 2*CORDIC_PI;
	
	if(radian > CORDIC_PI)
	{
		negative = 1;
		
		radian -= CORDIC_PI;
	}
	
	if(radian > CORDIC_PI/2)
	{
		radian = CORDIC_PI - radian;
	}
	
	if(radian < 0.01)
	{
		res = 0;
	}
	else if(radian > 1.56)
	{
		res = 1;
	}
	else
	{
		CORDIC_Sin(radian * 16384);
		while(CORDIC_Sin_IsDone() == 0);
		res = CORDIC_Sin_Result()/16384.0;
	}
	
	if(negative) res = 0 - res;
	
	return res;
}

/****************************************************************************************************************************************** 
* ��������:	CORDIC_FullCycleSin_Angle()
* ����˵��:	ʹ��CORDICģ�����sin
* ��    ��: double angle		Ҫ����ĽǶ�ֵ
* ��    ��: double
* ע������: ��
******************************************************************************************************************************************/
double CORDIC_FullCycleSin_Angle(double angle)
{
	double radian = angle / 180 * CORDIC_PI;
	
	return CORDIC_FullCycleSin(radian);
}

/****************************************************************************************************************************************** 
* ��������:	CORDIC_FullCycleCos()
* ����˵��:	ʹ��CORDICģ�����cos
* ��    ��: double radian		Ҫ����Ļ���ֵ
* ��    ��: double
* ע������: ��
******************************************************************************************************************************************/
double CORDIC_FullCycleCos(double radian)
{
	double res;
	uint32_t negative = 0;
	
	while(radian < 0) radian += 2*CORDIC_PI;
	
	while(radian > 2*CORDIC_PI) radian -= 2*CORDIC_PI;
	
	if(radian > CORDIC_PI)
	{
		radian = 2*CORDIC_PI - radian;
	}
	
	if(radian > CORDIC_PI/2)
	{
		negative = 1;
		
		radian = CORDIC_PI - radian;
	}
	
	if(radian < 0.01)
	{
		res = 1;
	}
	else if(radian > 1.56)
	{
		res = 0;
	}
	else
	{
		CORDIC_Cos(radian * 16384);
		while(CORDIC_Cos_IsDone() == 0);
		res = CORDIC_Cos_Result()/16384.0;
	}
	
	if(negative) res = 0 - res;
	
	return res;
}

/****************************************************************************************************************************************** 
* ��������:	CORDIC_FullCycleCos_Angle()
* ����˵��:	ʹ��CORDICģ�����cos
* ��    ��: double angle		Ҫ����ĽǶ�ֵ
* ��    ��: double
* ע������: ��
******************************************************************************************************************************************/
double CORDIC_FullCycleCos_Angle(double angle)
{
	double radian = angle / 180 * CORDIC_PI;
	
	return CORDIC_FullCycleCos(radian);
}
