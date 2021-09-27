#ifndef __SWM190_PWM_H__
#define	__SWM190_PWM_H__


typedef struct {
	uint8_t  PWMnXN;		//�Ƿ���PWMnXN��������������Σ������PWM0A��������PWM0AN���������������
							//ע�⣺PWMnXN = 1ʱ�����Ƶ�ʽ��͵�һ��
	uint8_t  clkdiv;		//PWM_CLKDIV_1��PWM_CLKDIV_2��... ...

	uint32_t cycle;			//���ڣ�28λ
	uint32_t hduty;			//ռ�ձȣ��ߵ�ƽʱ����28λ
	uint16_t deadzone;		//����ʱ����ȡֵ0--1023
	uint8_t  initLevel;		//��ʼ�����ƽ��0 �͵�ƽ    1 �ߵ�ƽ
	
	uint8_t  HEndIE;		//�ߵ�ƽ�����ж�ʹ��
	uint8_t  NCycleIE;		//�����ڿ�ʼ�ж�ʹ��
	uint8_t  HCycleIE;		//������    �ж�ʹ��
} PWM_InitStructure;


#define PWM0A	0
#define PWM0B	1
#define PWM1A	2
#define PWM1B	3
#define PWM2A	4
#define PWM2B	5
#define PWM3A	6
#define PWM3B	7


#define PWM_CLKDIV_1	0
#define PWM_CLKDIV_2	1
#define PWM_CLKDIV_4	2
#define PWM_CLKDIV_8	3
#define PWM_CLKDIV_16	4
#define PWM_CLKDIV_32	5
#define PWM_CLKDIV_64	6
#define PWM_CLKDIV_128	7



void PWM_Init(uint32_t pwmx, PWM_InitStructure * initStruct);	//PWM��ʼ��
void PWM_Start(uint32_t pwmx);									//����PWM����ʼPWM���
void PWM_Stop(uint32_t pwmx);									//�ر�PWM��ֹͣPWM���

void PWM_SetCycle(uint32_t pwmx, uint32_t cycle);				//��������
uint32_t PWM_GetCycle(uint32_t pwmx);	   						//��ȡ����
void PWM_SetHDuty(uint32_t pwmx, uint32_t hduty);				//���øߵ�ƽʱ��
uint32_t PWM_GetHDuty(uint32_t pwmx);							//��ȡ�ߵ�ƽʱ��
void PWM_SetDeadzone(uint32_t pwmx, uint16_t deadzone);			//��������ʱ��
uint16_t  PWM_GetDeadzone(uint32_t pwmx);		 				//��ȡ����ʱ��

void PWM_IntNCycleEn(uint32_t pwmx);   							//�����ڿ�ʼ�ж�ʹ��
void PWM_IntNCycleDis(uint32_t pwmx);  							//�����ڿ�ʼ�жϽ���
void PWM_IntNCycleClr(uint32_t pwmx);  							//�����ڿ�ʼ�жϱ�־���
uint32_t PWM_IntNCycleStat(uint32_t pwmx); 						//�����ڿ�ʼ�ж��Ƿ���

void PWM_IntHEndEn(uint32_t pwmx); 								//�ߵ�ƽ�����ж�ʹ��
void PWM_IntHEndDis(uint32_t pwmx);								//�ߵ�ƽ�����жϽ���
void PWM_IntHEndClr(uint32_t pwmx);	 							//�ߵ�ƽ�����жϱ�־���
uint32_t PWM_IntHEndStat(uint32_t pwmx);						//�ߵ�ƽ�����ж��Ƿ���

void PWM_IntHCycleEn(uint32_t pwmx);							//�������ж�ʹ��
void PWM_IntHCycleDis(uint32_t pwmx);							//�������жϽ���
void PWM_IntHCycleClr(uint32_t pwmx);							//�������жϱ�־���
uint32_t PWM_IntHCycleStat(uint32_t pwmx);						//�������ж��Ƿ���

#endif //__SWM190_PWM_H__
