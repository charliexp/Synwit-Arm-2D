/****************************************************************************************************************************************** 
* �ļ�����:	SWM190_flash.c
* ����˵��:	ʹ��оƬ��IAP���ܽ�Ƭ��Flashģ���EEPROM���������ݣ�����󲻶�ʧ
* ����֧��:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* ע������:
* �汾����: V1.0.0		2016��1��30��
* ������¼: 
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
#include "SWM190_flash.h"


void FLASH_Init(void)
{
	SFC->TIM &= ~(SFC_TIM_WIP_CHK_ITV_Msk | SFC_TIM_WIP_CHK_LMT_Msk);
	SFC->TIM |= (48 << SFC_TIM_WIP_CHK_ITV_Pos) |	// (2000 * 48) / 48MHz = 2ms
				(0xFF << SFC_TIM_WIP_CHK_LMT_Pos);	// 2ms * 255 = 510ms
}


/****************************************************************************************************************************************** 
* ��������:	FLASH_Erase()
* ����˵��:	FLASH����������ÿ������4K�ֽ�
* ��    ��: uint32_t addr		Ҫ���������ĵ�ַ������4K���룬��addr%4096 == 0
* ��    ��: uint32_t			FLASH_RES_OK��FLASH_RES_TO��FLASH_RES_ERR
* ע������: ��
******************************************************************************************************************************************/
uint32_t FLASH_Erase(uint32_t addr)
{
	uint32_t res;
	
	__disable_irq();
	
	SFC->ADDR = addr;
	
	SFC->CFG &= ~SFC_CFG_CMDTYPE_Msk;
	SFC->CFG |= (1 << SFC_CFG_WREN_Pos) |
				(1 << SFC_CFG_CMDWREN_Pos) |
				(7 << SFC_CFG_CMDTYPE_Pos);
	SFC->CMD = FLASH_CMD_ERASE_SECT;
	
	SFC->GO = 1;
	while(SFC->GO);
	SFC->CFG &= ~SFC_CFG_WREN_Msk;
	
	if(SFC->IF & SFC_IF_ERR_Msk)     res = FLASH_RES_ERR;
	else if(SFC->IF & SFC_IF_TO_Msk) res = FLASH_RES_TO;
	else                             res = FLASH_RES_OK;
	
	__enable_irq();
	
	return res;
}

/****************************************************************************************************************************************** 
* ��������:	FLASH_Write()
* ����˵��:	FLASH����д��
* ��    ��: uint32_t addr		����Ҫд�뵽Flash�еĵ�ַ���ֶ���
*			uint32_t buff[]		Ҫд��Flash�е�����
*			uint32_t cnt		Ҫд�����ݵĸ���������Ϊ��λ�����64
* ��    ��: uint32_t			FLASH_RES_OK��FLASH_RES_TO��FLASH_RES_ERR
* ע������: Ҫд������ݱ���ȫ����ͬһҳ�ڣ���addr/256 == (addr+(cnt-1)*4)/256
******************************************************************************************************************************************/
uint32_t FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t cnt)
{	
	uint32_t res, i;
	
	__disable_irq();
	
	SFC->CFG |= (1 << SFC_CFG_WREN_Pos);
	for(i = 0; i < cnt; i++)
		*((volatile unsigned int *)(0x41000000+addr+i*4)) = buff[i];
	
	while(SFC->SR & SFC_SR_BUSY_Msk) __NOP();
	SFC->CFG &= ~SFC_CFG_WREN_Msk;
	
	if(SFC->IF & SFC_IF_ERR_Msk)     res = FLASH_RES_ERR;
	else if(SFC->IF & SFC_IF_TO_Msk) res = FLASH_RES_TO;
	else                             res = FLASH_RES_OK;
	
	__enable_irq();
	
	return res;
}

/****************************************************************************************************************************************** 
* ��������:	FLASH_Read()
* ����˵��:	FLASH���ݶ�ȡ
* ��    ��: uint32_t addr		Ҫ��ȡ��������Flash�еĵ�ַ���ֶ���
*			uint32_t buff[]		��ȡ�������ݴ���buffָ����ڴ�
*			uint32_t cnt		Ҫ��ȡ�����ݵĸ���������Ϊ��λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void FLASH_Read(uint32_t addr, uint32_t buff[], uint32_t cnt)
{	
	uint32_t i;
	
	for(i = 0; i < cnt; i++)
		buff[i] = *((volatile unsigned int *)(0x41000000+addr+i*4));
}
