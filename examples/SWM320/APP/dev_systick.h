#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

void systick_init(void);
void swm_inctick(void);
uint32_t swm_gettick(void);
void swm_delay_ms(uint32_t ms);
void swm_delay_us(uint32_t us);
#endif //__DEV_SYSTICK_H__
