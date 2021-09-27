#include "main.h"

#define ST7789_RS_GPIO GPIOC
#define ST7789_RS_PIN PIN2
#define ST7789_CS_GPIO GPIOC
#define ST7789_CS_PIN PIN4
#define ST7789_RST_GPIO GPIOC
#define ST7789_RST_PIN PIN5

#define ST7789_RS_SET GPIO_SetBit(ST7789_RS_GPIO,ST7789_RS_PIN)
#define ST7789_RS_CLR GPIO_ClrBit(ST7789_RS_GPIO,ST7789_RS_PIN)
#define ST7789_CS_SET GPIO_SetBit(ST7789_CS_GPIO,ST7789_CS_PIN)
#define ST7789_CS_CLR GPIO_ClrBit(ST7789_CS_GPIO,ST7789_CS_PIN)
#define ST7789_RST_SET GPIO_SetBit(ST7789_RST_GPIO,ST7789_RST_PIN)
#define ST7789_RST_CLR GPIO_ClrBit(ST7789_RST_GPIO,ST7789_RST_PIN)

static void spi_init(void)
{
    SPI_InitStructure SPI_initStruct;
    
    PORT_Init(PORTC, PIN7, PORTC_PIN7_SPI1_SCLK, 0);
    PORT_Init(PORTC, PIN6, PORTC_PIN6_SPI1_MOSI, 0);

    SPI_initStruct.clkDiv = SPI_CLKDIV_2;
    SPI_initStruct.FrameFormat = SPI_FORMAT_SPI;
    SPI_initStruct.SampleEdge = SPI_FIRST_EDGE;
    SPI_initStruct.IdleLevel = SPI_LOW_LEVEL;
    SPI_initStruct.WordSize = 8;
    SPI_initStruct.Master = 1;
    SPI_initStruct.RXThreshold = 0;
    SPI_initStruct.RXThresholdIEn = 0;
    SPI_initStruct.TXThreshold = 0;
    SPI_initStruct.TXThresholdIEn = 0;
    SPI_initStruct.TXCompleteIEn  = 0;
    SPI_Init(SPI1, &SPI_initStruct);
    SPI_Open(SPI1);
    
    GPIO_Init(ST7789_RS_GPIO, ST7789_RS_PIN, 1, 1, 0, 0);
    GPIO_Init(ST7789_CS_GPIO, ST7789_CS_PIN, 1, 1, 0, 0);
    GPIO_Init(ST7789_RST_GPIO, ST7789_RST_PIN, 1, 1, 0, 0);
    ST7789_RS_SET;
    ST7789_CS_SET;
    ST7789_RST_CLR;
    swm_delay_ms(1);
    ST7789_RST_SET;
}

static void SPI_Write_Cmd(uint8_t data)
{
    //SPI 写命令时序开始
    ST7789_CS_CLR;
    ST7789_RS_CLR;
    SPI_ReadWrite(SPI1, data);
    ST7789_CS_SET;
}

static void SPI_Write_Data(uint8_t data)
{
    //SPI 写数据时序开始
    ST7789_CS_CLR;
    ST7789_RS_SET;
    SPI_ReadWrite(SPI1, data);
    ST7789_CS_SET;
}

void spilcd_init(void)
{
    spi_init();
    
    SPI_Write_Cmd(0xEF);

    SPI_Write_Cmd(0xEB);
    SPI_Write_Data(0x14);

    SPI_Write_Cmd(0xFE);
    SPI_Write_Cmd(0xEF);

    SPI_Write_Cmd(0xEB);
    SPI_Write_Data(0x14);

    SPI_Write_Cmd(0x84);
    SPI_Write_Data(0x40);

    SPI_Write_Cmd(0x85);
    SPI_Write_Data(0xFF);

    SPI_Write_Cmd(0x86);
    SPI_Write_Data(0xFF);

    SPI_Write_Cmd(0x87);
    SPI_Write_Data(0xFF);

    SPI_Write_Cmd(0x88);
    SPI_Write_Data(0x0A);

    SPI_Write_Cmd(0x89);
    SPI_Write_Data(0x21);

    SPI_Write_Cmd(0x8A);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0x8B);
    SPI_Write_Data(0x80);

    SPI_Write_Cmd(0x8C);
    SPI_Write_Data(0x01);

    SPI_Write_Cmd(0x8D);
    SPI_Write_Data(0x01);

    SPI_Write_Cmd(0x8E);
    SPI_Write_Data(0xFF);

    SPI_Write_Cmd(0x8F);
    SPI_Write_Data(0xFF);

    SPI_Write_Cmd(0xB6);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0x36);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0x3A);
    SPI_Write_Data(0x55);

    SPI_Write_Cmd(0x90);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x08);

    SPI_Write_Cmd(0xBD);
    SPI_Write_Data(0x06);

    SPI_Write_Cmd(0xBC);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0xFF);
    SPI_Write_Data(0x60);
    SPI_Write_Data(0x01);
    SPI_Write_Data(0x04);

    SPI_Write_Cmd(0xC3);
    SPI_Write_Data(0x13);
    SPI_Write_Cmd(0xC4);
    SPI_Write_Data(0x13);

    SPI_Write_Cmd(0xC9);
    SPI_Write_Data(0x22);

    SPI_Write_Cmd(0xBE);
    SPI_Write_Data(0x11);

    SPI_Write_Cmd(0xE1);
    SPI_Write_Data(0x10);
    SPI_Write_Data(0x0E);

    SPI_Write_Cmd(0xDF);
    SPI_Write_Data(0x21);
    SPI_Write_Data(0x0c);
    SPI_Write_Data(0x02);

    SPI_Write_Cmd(0xF0);
    SPI_Write_Data(0x45);
    SPI_Write_Data(0x09);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x26);
    SPI_Write_Data(0x2A);

    SPI_Write_Cmd(0xF1);
    SPI_Write_Data(0x43);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x72);
    SPI_Write_Data(0x36);
    SPI_Write_Data(0x37);
    SPI_Write_Data(0x6F);

    SPI_Write_Cmd(0xF2);
    SPI_Write_Data(0x45);
    SPI_Write_Data(0x09);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x26);
    SPI_Write_Data(0x2A);

    SPI_Write_Cmd(0xF3);
    SPI_Write_Data(0x43);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x72);
    SPI_Write_Data(0x36);
    SPI_Write_Data(0x37);
    SPI_Write_Data(0x6F);

    SPI_Write_Cmd(0xED);
    SPI_Write_Data(0x1B);
    SPI_Write_Data(0x0B);

    SPI_Write_Cmd(0xAE);
    SPI_Write_Data(0x77);

    SPI_Write_Cmd(0xCD);
    SPI_Write_Data(0x63);

    SPI_Write_Cmd(0x70);
    SPI_Write_Data(0x07);
    SPI_Write_Data(0x07);
    SPI_Write_Data(0x04);
    SPI_Write_Data(0x0E);
    SPI_Write_Data(0x0F);
    SPI_Write_Data(0x09);
    SPI_Write_Data(0x07);
    SPI_Write_Data(0x08);
    SPI_Write_Data(0x03);

    SPI_Write_Cmd(0xE8);
    SPI_Write_Data(0x04);

    SPI_Write_Cmd(0xE9);
    SPI_Write_Data(0x0A);

    SPI_Write_Cmd(0x62);
    SPI_Write_Data(0x18);
    SPI_Write_Data(0x0D);
    SPI_Write_Data(0x71);
    SPI_Write_Data(0xED);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x18);
    SPI_Write_Data(0x0F);
    SPI_Write_Data(0x71);
    SPI_Write_Data(0xEF);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x70);

    SPI_Write_Cmd(0x63);
    SPI_Write_Data(0x18);
    SPI_Write_Data(0x11);
    SPI_Write_Data(0x71);
    SPI_Write_Data(0xF1);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x18);
    SPI_Write_Data(0x13);
    SPI_Write_Data(0x71);
    SPI_Write_Data(0xF3);
    SPI_Write_Data(0x70);
    SPI_Write_Data(0x70);

    SPI_Write_Cmd(0x64);
    SPI_Write_Data(0x28);
    SPI_Write_Data(0x29);
    SPI_Write_Data(0xF1);
    SPI_Write_Data(0x01);
    SPI_Write_Data(0xF1);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x07);

    SPI_Write_Cmd(0x66);
    SPI_Write_Data(0x3C);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0xCD);
    SPI_Write_Data(0x67);
    SPI_Write_Data(0x45);
    SPI_Write_Data(0x45);
    SPI_Write_Data(0x10);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0x67);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x3C);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x01);
    SPI_Write_Data(0x54);
    SPI_Write_Data(0x10);
    SPI_Write_Data(0x32);
    SPI_Write_Data(0x98);

    SPI_Write_Cmd(0x74);
    SPI_Write_Data(0x10);
    SPI_Write_Data(0x85);
    SPI_Write_Data(0x80);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x00);
    SPI_Write_Data(0x4E);
    SPI_Write_Data(0x00);

    SPI_Write_Cmd(0x98);
    SPI_Write_Data(0x3e);
    SPI_Write_Data(0x07);

    SPI_Write_Cmd(0x35);
    SPI_Write_Cmd(0x21);

    SPI_Write_Cmd(0x11);
    swm_delay_ms(1);
    SPI_Write_Cmd(0x29);
    swm_delay_ms(1);
}

static void adderset(int xs, int xe, int ys, int ye)
{
    SPI_Write_Cmd(0x2A);
    ST7789_CS_CLR;
    ST7789_RS_SET;
    SPI1->DATA = xs >> 8;
    SPI1->DATA = xs & 0xFF;
    SPI1->DATA = xe >> 8;
    SPI1->DATA = xe & 0xFF;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    ST7789_CS_SET;
    

    SPI_Write_Cmd(0x2B);
    ST7789_CS_CLR;
    ST7789_RS_SET;
    SPI1->DATA = ys >> 8;
    SPI1->DATA = ys & 0xFF;
    SPI1->DATA = ye >> 8;
    SPI1->DATA = ye & 0xFF;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
        ;
    SPI1->DATA;
    ST7789_CS_SET;
    
    SPI_Write_Cmd(0x2C); //display on
}

int32_t GLCD_DrawBitmap (uint32_t x, 
                         uint32_t y, 
                         uint32_t width, 
                         uint32_t height, 
                         const uint8_t *bitmap) 
{
    
    uint32_t i,j;
    const uint16_t *phwSrc = (const uint16_t *)bitmap;
    adderset(x, x+width-1, y, y+height-1);
    ST7789_CS_CLR;
    ST7789_RS_SET;

    SPI1->CTRL |= 0x0F << SPI_CTRL_SIZE_Pos;
    for(j = y; j < y+height; j++) {
        for(i = x; i < x+width; i++) {
            
            SPI1->DATA = *phwSrc++;
            while (!(SPI1->STAT & SPI_STAT_RFNE_Msk))
                ;
            SPI1->DATA;
        }
    }
    SPI1->CTRL &= ~(0x0F << SPI_CTRL_SIZE_Pos);
    SPI1->CTRL |= 0x07 << SPI_CTRL_SIZE_Pos;
    ST7789_CS_SET;

    return 0;
}
