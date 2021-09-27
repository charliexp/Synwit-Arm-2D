/****************************************************************************************************************************************** 
* �ļ�����: SWM190_cache.c
* ����˵��:	SWM190��Ƭ����CACHE������������
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
#include "SWM190_cache.h"


/****************************************************************************************************************************************** 
* ��������:	CACHE_Reset()
* ����˵��:	CHCHE��λ�����CHCHE���б�־������
* ��    ��: ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void CACHE_Reset(void)
{
	while((CACHE->CR & CACHE_CR_IDLE_Msk) == 0) __NOP();
	
	CACHE->CR |= (1 << CACHE_CR_RST_Pos);
}

/****************************************************************************************************************************************** 
* ��������:	CACHE_Prefet()
* ����˵��:	CHCHEԤȡ����
* ��    ��: uint32_t addr		��Flash��addr��ʼ��128�ֽڴ���Ԥȡ��Cache�в�����
* ��    ��: uint32_t			CACHE_RES_OK��CACHE_RES_FAIL
* ע������: ��
******************************************************************************************************************************************/
uint32_t CACHE_Prefet(uint32_t addr)
{
	uint32_t res;
	
	CACHE->IE |= (1 << CACHE_IE_PREFET_Pos);	// ֻ���ж�ʹ��ʱ��Ӧ�ж�״̬��������
	
	while((CACHE->PREFCR & CACHE_PREFCR_RDY_Msk) == 0) __NOP();
	
	CACHE->PREFCR = (1 << CACHE_PREFCR_PREFET_Pos) |
					(addr << CACHE_PREFCR_ADDR_Pos);
	
	while((CACHE->IF & (CACHE_IF_PREOK_Msk | CACHE_IF_PREFAIL_Msk)) == 0) __NOP();
	
	if(CACHE->IF & CACHE_IF_PREOK_Msk) res = CACHE_RES_OK;
	else							   res = CACHE_RES_FAIL;
	
	CACHE->IF = CACHE_IF_PREOK_Msk | CACHE_IF_PREFAIL_Msk;	//�����־
		
	return res;
}

/****************************************************************************************************************************************** 
* ��������:	CACHE_Unlock()
* ����˵��:	�ͷ�������Cache�еĴ���
* ��    ��: uint32_t addr		Ҫ�����ͷŵĴ���ĵ�ַ
* ��    ��: uint32_t			CACHE_RES_OK��CACHE_RES_FAIL
* ע������: ��
******************************************************************************************************************************************/
uint32_t CACHE_Unlock(uint32_t addr)
{
	uint32_t res;
	
	CACHE->IE |= (1 << CACHE_IE_UNLOCK_Pos);	// ֻ���ж�ʹ��ʱ��Ӧ�ж�״̬��������
	
	while((CACHE->PREFCR & CACHE_PREFCR_RDY_Msk) == 0) __NOP();
	
	CACHE->PREFCR = (1 << CACHE_PREFCR_UNLOCK_Pos) |
					(addr << CACHE_PREFCR_ADDR_Pos);
	
	while((CACHE->IF & (CACHE_IF_UNLOK_Msk | CACHE_IF_UNLFAIL_Msk)) == 0) __NOP();
	
	if(CACHE->IF & CACHE_IF_UNLOK_Msk) res = CACHE_RES_OK;
	else 							   res = CACHE_RES_FAIL;
	
	CACHE->IF = CACHE_IF_UNLOK_Msk | CACHE_IF_UNLFAIL_Msk;	//�����־
	
	return res;
}
