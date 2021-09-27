#ifndef __GT9X_H__
#define __GT9X_H__

#define TP_PRES_DOWN 0x80 //触屏被按下
#define TP_MAX_TOUCH 5    //电容屏支持的点数,固定为5点

//触摸屏控制器
typedef struct
{
    uint16_t x[TP_MAX_TOUCH]; //当前坐标
    uint16_t y[TP_MAX_TOUCH]; //电容屏有最多5组坐标
    uint8_t status;           //笔的状态
                              //b7:按下1/松开0;
                              //b6~b5:保留
                              //b4~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
} tp_dev_t;

extern tp_dev_t tp_dev;

void gt9x_init(void);

#endif //__GT9X_H__
