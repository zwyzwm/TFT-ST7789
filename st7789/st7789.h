#ifndef __ST7789_H
#define __ST7789_H



static void DEV_GPIO_Init(void);
int wiringx_init();
void delay_us(unsigned int _us_time);
void delay_ms(unsigned int _ms_time);
void SPI_SendByte(unsigned char Value);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned char o_data);
void TFT_SET_ADD(unsigned short int x_start,unsigned short int y_start,unsigned short int x_end,unsigned short int y_end);
void TFT_clear(void);
void TFT_full(unsigned int color);
void TFT_init(void);
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number);
void Picture_display(const unsigned char *ptr_pic);

#endif


