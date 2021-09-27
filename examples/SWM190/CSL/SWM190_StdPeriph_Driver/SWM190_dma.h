#ifndef __SWM190_DMA_H__
#define __SWM190_DMA_H__


typedef struct {
	uint8_t  Mode;			//DMA_MODE_SINGLE��DMA_MODE_CIRCLE
	
	uint8_t  Unit;			//DMA_UNIT_BYTE��DMA_UNIT_HALFWORD��DMA_UNIT_WORD
	
	uint16_t Count;			//���� Unit ���������ȡֵ4096
	
	uint32_t SrcAddr;
	
	uint8_t  SrcAddrInc;	//0 ��ַ�̶�    1 ��ַ����
		
	uint32_t DstAddr;
	
	uint8_t  DstAddrInc;
	
	uint8_t  Trigger;		//���������DMA_TRG_SW    Ӳ��������DMA_CH0_UART0TX��DMA_CH0_SPI0TX��... ...
	
	uint8_t  Priority;		//DMA_PRI_LOW��DMA_PRI_HIGH
	
	uint8_t  DoneIE;		//��������ж�ʹ��
} DMA_InitStructure;


#define DMA_CH0		0
#define DMA_CH1		1
#define DMA_CH2		2
#define DMA_CH3		3

#define DMA_MODE_SINGLE		0		//����ģʽ��������ɺ�ֹͣ
#define DMA_MODE_CIRCLE		1		//����ģʽ��������ɺ��ͷִ����һ�ִ���

#define DMA_UNIT_BYTE		0
#define DMA_UNIT_HALFWORD	1
#define DMA_UNIT_WORD		2

#define DMA_PRI_LOW			0
#define DMA_PRI_HIGH		1


#define DMA_TRG_M0			(0 << 4)
#define DMA_TRG_M1			(1 << 4)
#define DMA_TRG_SW			(2 << 4)
#define DMA_TRG_MSK			(3 << 4)

#define DMA_DIR_TX			(0 << 7)	// M0 --> M1
#define DMA_DIR_RX			(1 << 7)	// M1 --> M0
#define DMA_DIR_MSK			(1 << 7)

// M0 ������
#define DMA_CH0_UART0TX		(0 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH0_SPI0TX		(1 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH0_UART3TX		(3 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH1_UART1TX		(0 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH1_SPI1TX		(1 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH1_UART2TX		(3 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH2_UART2TX		(0 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH2_SPI0TX		(1 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH2_UART1TX		(3 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH3_UART3TX		(0 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH3_SPI1TX		(1 | DMA_TRG_M0 | DMA_DIR_RX)
#define DMA_CH3_UART0TX		(3 | DMA_TRG_M0 | DMA_DIR_RX)

// M1 ������
#define DMA_CH0_UART1RX		(0 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH0_SPI1RX		(1 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH0_ADC0		(2 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH0_UART2RX		(3 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH1_UART0RX		(0 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH1_SPI0RX		(1 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH1_ADC1		(2 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH1_UART3RX		(3 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH2_UART3RX		(0 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH2_SPI1RX		(1 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH2_ADC0		(2 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH2_UART0RX		(3 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH3_UART2RX		(0 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH3_SPI0RX		(1 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH3_ADC1		(2 | DMA_TRG_M1 | DMA_DIR_RX)
#define DMA_CH3_UART1RX		(3 | DMA_TRG_M1 | DMA_DIR_RX)


void DMA_CH_Init(uint32_t chn, DMA_InitStructure * initStruct);	//DMAͨ������
void DMA_CH_Open(uint32_t chn);
void DMA_CH_Close(uint32_t chn);

void DMA_CH_INTEn(uint32_t chn);				//DMA�ж�ʹ�ܣ����ݰ�����ɺ󴥷��ж�
void DMA_CH_INTDis(uint32_t chn);				//DMA�жϽ�ֹ�����ݰ�����ɺ󲻴����ж�
void DMA_CH_INTClr(uint32_t chn);				//DMA�жϱ�־���
uint32_t DMA_CH_INTStat(uint32_t chn);			//DMA�ж�״̬��ѯ��1 ���ݰ������    0 ���ݰ���δ���


#endif //__SWM190_DMA_H__
