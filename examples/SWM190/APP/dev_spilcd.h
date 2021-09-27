#ifndef __DEV_RGBLCD_H__
#define __DEV_RGBLCD_H__

void spilcd_init(void);
int32_t GLCD_DrawBitmap (uint32_t x, 
                         uint32_t y, 
                         uint32_t width, 
                         uint32_t height, 
                         const uint8_t *bitmap);
                         
#endif //__DEV_RGBLCD_H__
