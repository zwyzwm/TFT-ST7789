#include "st7789.h"
#include "data.h"
#include "stdint.h"
#include <unistd.h>
#include <wiringx.h>
#include "stdio.h"
 

#define TFT_COLUMN_NUMBER 170
#define TFT_LINE_NUMBER 320
#define TFT_COLUMN_OFFSET 35
#define TFT_LINE_OFFSET 0

#define SPI_PORT    0


#define     RED          0XF800	 
#define     GREEN        0X07E0	  
#define     BLUE         0X001F	  
#define     WHITE        0XFFFF	  
#define PIC_LEN 120
#define PIC_HIG 120
			


#define SPI_RST_PIN  50
#define SPI_DC_PIN  48
#define SPI_CS_PIN  46 
#define BL_PIN  44


#define SPI_RST_0         digitalWrite(SPI_RST_PIN, LOW)  
#define SPI_RST_1         digitalWrite(SPI_RST_PIN, HIGH)
#define SPI_DC_0          digitalWrite(SPI_DC_PIN, LOW)
#define SPI_DC_1          digitalWrite(SPI_DC_PIN, HIGH)
#define SPI_CS_0          digitalWrite(SPI_CS_PIN, LOW)
#define SPI_CS_1          digitalWrite(SPI_CS_PIN, HIGH)
#define BL_0              digitalWrite(BL_PIN, LOW)
#define BL_1              digitalWrite(BL_PIN, HIGH)

#define TRUE             1
#define FALSE           0




const unsigned char  *point;



int main(void)
{ 
	point= &picture_tab[0];
  wiringx_init();
  DEV_GPIO_Init();
	BL_1;
	
	TFT_init();

	
	while(1)
	{
		
	
	TFT_full(RED);
	delay_ms(5000);
	TFT_full(GREEN);
	delay_ms(5000);
	TFT_full(BLUE);
	delay_ms(5000);
	TFT_clear();
    

		Picture_display(point);
//		Picture_ReverseDisplay(point);
	delay_ms(10000);
		display_char16_16(20,160,BLUE,0);
	display_char16_16(36,160,GREEN,1);
	display_char16_16(60,160,RED,2);
	display_char16_16(76,160,BLUE,3);
	display_char16_16(92,160,GREEN,4);
	display_char16_16(118,160,BLUE,5);
	display_char16_16(134,160,RED,6);
	delay_ms(10000);

	}
}


static void DEV_GPIO_Init(void)
{
    
	
if(wiringXValidGPIO(SPI_RST_PIN) != 0) {
        printf("Invalid GPIO %d\n", SPI_RST_PIN);
    }
	pinMode(SPI_RST_PIN, PINMODE_OUTPUT);


if(wiringXValidGPIO(SPI_DC_PIN) != 0) {
        printf("Invalid GPIO %d\n", SPI_DC_PIN);
    }

	pinMode(SPI_DC_PIN, PINMODE_OUTPUT);

if(wiringXValidGPIO(SPI_CS_PIN) != 0) {
        printf("Invalid GPIO %d\n", SPI_CS_PIN);
    }

	pinMode(SPI_CS_PIN, PINMODE_OUTPUT);

if(wiringXValidGPIO(BL_PIN) != 0) {
        printf("Invalid GPIO %d\n", BL_PIN);
    }

	pinMode(BL_PIN, PINMODE_OUTPUT);

	SPI_CS_1;
	

}
int wiringx_init()
{
    int fd_spi;

    
    if(wiringXSetup("milkv_duos", NULL) == -1) {
        wiringXGC();
        return -1;
    }

    DEV_GPIO_Init();

    if ((fd_spi = wiringXSPISetup(SPI_PORT, 1800000)) <0) {
        printf("SPI Setup failed: %d\n", fd_spi);
        wiringXGC();
        return -1;
    }

}



void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
	  x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;x++;
  }
}
void delay_ms(unsigned int _ms_time)
  {
    unsigned int i,j;
    for(i=0;i<_ms_time;i++)
    {
    for(j=0;j<900;j++)
      {;}
    }
  }


void SPI_SendByte(unsigned char Value)
{
   wiringXSPIDataRW(SPI_PORT, &Value,1);
}

void TFT_SEND_CMD(unsigned char o_command)
  {
    SPI_DC_0;
    SPI_CS_0;
    SPI_SendByte(o_command);
    SPI_CS_1;
	 
    //SPI_DC_1;
  }
void TFT_SEND_DATA(unsigned char o_data)
  { 
    SPI_DC_1;
    SPI_CS_0;
    SPI_SendByte(o_data);
    SPI_CS_1;
	  
   }
void TFT_SET_ADD(unsigned short int x_start,unsigned short int y_start,unsigned short int x_end,unsigned short int y_end)
{
	unsigned short int x = x_start + TFT_COLUMN_OFFSET,y=x_end+ TFT_COLUMN_OFFSET;
    TFT_SEND_CMD(0x2a);     //Column address set
    TFT_SEND_DATA(x>>8);    //start column
    TFT_SEND_DATA(x); 
    TFT_SEND_DATA(y>>8);    //end column
    TFT_SEND_DATA(y);
	x = y_start + TFT_LINE_OFFSET;
	y=y_end+ TFT_LINE_OFFSET;
    TFT_SEND_CMD(0x2b);     //Row address set
    TFT_SEND_DATA(x>>8);    //start row
    TFT_SEND_DATA(x); 
    TFT_SEND_DATA(y>>8);    //end row
    TFT_SEND_DATA(y);
    TFT_SEND_CMD(0x2C);     //Memory write
    
}
void TFT_clear(void)
  {
    unsigned int ROW,column;
    TFT_SET_ADD(0,0,TFT_COLUMN_NUMBER-1,TFT_LINE_NUMBER-1);
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
      { 
    
          for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
            {
              
				TFT_SEND_DATA(0xFF);
				TFT_SEND_DATA(0xFF);
            }
      }
  }

void TFT_full(unsigned int color)
  {
    unsigned int ROW,column;
    TFT_SET_ADD(0,0,TFT_COLUMN_NUMBER-1,TFT_LINE_NUMBER-1);
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
    { 
    
        for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop
        {

			TFT_SEND_DATA(color>>8);
			  TFT_SEND_DATA(color);
        }
    }
  }



void TFT_init(void)				////ST7789V2
  {
			//ÌØ±ð×¢Òâ£¡£¡
	SPI_RST_0;
	delay_ms(1000);
	SPI_RST_1;
	delay_ms(1000);
    TFT_SEND_CMD(0x11); 			//Sleep Out
	delay_ms(120);               //DELAY120ms 
	 	  //-----------------------ST7789V Frame rate setting-----------------//
//************************************************
                TFT_SEND_CMD(0x3A);        //65k mode
                TFT_SEND_DATA(0x05);
                TFT_SEND_CMD(0xC5); 		//VCOM
                TFT_SEND_DATA(0x1A);
                TFT_SEND_CMD(0x36);                 // ÆÁÄ»ÏÔÊŸ·œÏòÉèÖÃ
                TFT_SEND_DATA(0x00);
                //-------------ST7789V Frame rate setting-----------//
                TFT_SEND_CMD(0xb2);		//Porch Setting
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x00);
                TFT_SEND_DATA(0x33);
                TFT_SEND_DATA(0x33);

                TFT_SEND_CMD(0xb7);			//Gate Control
                TFT_SEND_DATA(0x05);			//12.2v   -10.43v
                //--------------ST7789V Power setting---------------//
                TFT_SEND_CMD(0xBB);//VCOM
                TFT_SEND_DATA(0x3F);

                TFT_SEND_CMD(0xC0); //Power control
                TFT_SEND_DATA(0x2c);

                TFT_SEND_CMD(0xC2);		//VDV and VRH Command Enable
                TFT_SEND_DATA(0x01);

                TFT_SEND_CMD(0xC3);			//VRH Set
                TFT_SEND_DATA(0x0F);		//4.3+( vcom+vcom offset+vdv)

                TFT_SEND_CMD(0xC4);			//VDV Set
                TFT_SEND_DATA(0x20);				//0v

                TFT_SEND_CMD(0xC6);				//Frame Rate Control in Normal Mode
                TFT_SEND_DATA(0X01);			//111Hz

                TFT_SEND_CMD(0xd0);				//Power Control 1
                TFT_SEND_DATA(0xa4);
                TFT_SEND_DATA(0xa1);

                TFT_SEND_CMD(0xE8);				//Power Control 1
                TFT_SEND_DATA(0x03);

                TFT_SEND_CMD(0xE9);				//Equalize time control
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x08);
                //---------------ST7789V gamma setting-------------//
                TFT_SEND_CMD(0xE0); //Set Gamma
                TFT_SEND_DATA(0xD0);
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x08);
                TFT_SEND_DATA(0x14);
                TFT_SEND_DATA(0x28);
                TFT_SEND_DATA(0x33);
                TFT_SEND_DATA(0x3F);
                TFT_SEND_DATA(0x07);
                TFT_SEND_DATA(0x13);
                TFT_SEND_DATA(0x14);
                TFT_SEND_DATA(0x28);
                TFT_SEND_DATA(0x30);
                 
                TFT_SEND_CMD(0XE1); //Set Gamma
                TFT_SEND_DATA(0xD0);
                TFT_SEND_DATA(0x05);
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x09);
                TFT_SEND_DATA(0x08);
                TFT_SEND_DATA(0x03);
                TFT_SEND_DATA(0x24);
                TFT_SEND_DATA(0x32);
                TFT_SEND_DATA(0x32);
                TFT_SEND_DATA(0x3B);
                TFT_SEND_DATA(0x14);
                TFT_SEND_DATA(0x13);
                TFT_SEND_DATA(0x28);
                TFT_SEND_DATA(0x2F);

                TFT_SEND_CMD(0x21); 		//·ŽÏÔ
               
                TFT_SEND_CMD(0x29);         //¿ªÆôÏÔÊŸ 

  }

void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number)
{
   unsigned int column;
  unsigned char tm=0,temp=0,xxx=0;

  TFT_SET_ADD(x,y,x+15,y+15);
  for(column=0;column<32;column++)  //column loop
          {
        temp=chines_word[  word_serial_number ][xxx];
        for(tm=0;tm<8;tm++)
        {
        if(temp&0x01)
          {
          TFT_SEND_DATA(color>>8);
          TFT_SEND_DATA(color);
          }
        else 
          {
          TFT_SEND_DATA(0XFF);
          TFT_SEND_DATA(0XFF);
          }
          temp>>=1;
        }
        xxx++;
          
      }
}
void Picture_display(const unsigned char *ptr_pic)
{
    unsigned long  number;
	TFT_SET_ADD(0,0,PIC_LEN-1,PIC_HIG-1);
	for(number=0;number<PIC_NUM;number++)	
          {
//            data=*ptr_pic++;
//            data=~data;
            TFT_SEND_DATA(*ptr_pic++);
	
			
          }
  }

