#include<LPC17xx.h>

//<======================================FOR  LCD ==========================================================> 
#define LcdDataBusPort LPC_GPIO1->FIOPIN    // for P1.24 , 25 , 26 , 27
#define LcdControlBusPort LPC_GPIO2->FIOPIN // for P2.0  , 1  , 2

#define LcdDataBusDirnReg LPC_GPIO1->FIODIR
#define LcdCtrlBusDirnReg LPC_GPIO2->FIODIR

#define LCD_D4 24
#define LCD_D5 25
#define LCD_D6 26
#define LCD_D7 27

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

/* Masks for configuring the DataBus and Control Bus direction */
#define LCD_ctrlBusMask ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))
#define LCD_dataBusMask ((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))

//<==================================== END LCD ============================================================>





//<===================================== FOR KEYBOARD ======================================================>
unsigned char SCAN_CODE[16] = {0x11,0x21,0x41,0x81,
0x12,0x22,0x42,0x82,
0x14,0x24,0x44,0x84,
0x18,0x28,0x48,0x88};

unsigned char ASCII_CODE[16] = {'0','1','2','3',
'4','5','6','7',
'8','9','A','B',
'C','D','E','F'};

unsigned char row, var,flag,key;
unsigned long int i,var1,temp, temp1, temp2, temp3;

unsigned char Msg1[13] = "KEY PRESSED=";

//======================================== END KEYBOARD =====================================================>





//<===================================== LCD functions =====================================================>

void delay(int cnt)
{
	int i;
	for(i=0;i<cnt;i++);
}


/* Function send the a nibble on the Data bus (LCD_D4 to LCD_D7) */
void sendNibble(char nibble)
{
	LcdDataBusPort&=~(LCD_dataBusMask); // Clear previous data
	
/*LcdDataBusPort|= (((nibble >>0x00) & 0x01) << LCD_D4);
  LcdDataBusPort|= (((nibble >>0x01) & 0x01) << LCD_D5);
  LcdDataBusPort|= (((nibble >>0x02) & 0x01) << LCD_D6);
  LcdDataBusPort|= (((nibble >>0x03) & 0x01) << LCD_D7);*/
	
	LcdDataBusPort |= nibble << LCD_D4; 	
}

void Lcd_CmdWrite(char cmd)
{
	sendNibble((cmd >> 0x04) & 0x0F);      //Send higher nibble
	LcdControlBusPort &= ~(1<<LCD_RS);    // Send LOW pulse on RS pin for selecting Command register
	//LcdControlBusPort &= ~(1<<LCD_RW);  // Send LOW pulse on RW pin for Write operation
	LcdControlBusPort |= (1<<LCD_EN);     // Generate a High-to-low pulse on EN pin
	delay(1000);
	LcdControlBusPort &= ~(1<<LCD_EN);

	delay(10000);

	sendNibble(cmd & 0x0F);               //Send Lower nibble
	LcdControlBusPort &= ~(1<<LCD_RS);   // Send LOW pulse on RS pin for selecting Command register
	//LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
	LcdControlBusPort |= (1<<LCD_EN);    // Generate a High-to-low pulse on EN pin
	delay(1000);
	LcdControlBusPort &= ~(1<<LCD_EN);

	delay(10000);
}

void Lcd_DataWrite(char dat)
{
sendNibble((dat >> 0x04) & 0x0F); //Send higher nibble
LcdControlBusPort |= (1<<LCD_RS); // Send HIGH pulse on RS pin for selecting data register
//LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
LcdControlBusPort |= (1<<LCD_EN); // Generate a High-to-low pulse on EN pin
delay(1000);
LcdControlBusPort &= ~(1<<LCD_EN);
	
delay(10000);

sendNibble(dat & 0x0F); //Send higher nibble
LcdControlBusPort |= (1<<LCD_RS); // Send HIGH pulse on RS pin for selecting data register
//LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
LcdControlBusPort |= (1<<LCD_EN); // Generate a High-to-low pulse on EN pin
delay(1000);
LcdControlBusPort &= ~(1<<LCD_EN);

delay(10000);
}

void lcd_init()
{
Lcd_CmdWrite(0x02); // Initialize Lcd in 4-bit mode
Lcd_CmdWrite(0x28); // enable 5x7 mode for chars
Lcd_CmdWrite(0x0E); // Display OFF, Cursor ON
Lcd_CmdWrite(0x01); // Clear Display
Lcd_CmdWrite(0x80); // Move the cursor to beginning of first line

}

//<=================================== END LCD functions ===================================================>






//<==================================  KEYBOARD FUNCTIONS ==================================================>
void scan(void)
{
temp3 = LPC_GPIO1->FIOPIN;    //get P1.23 to P1.26(cols) 
temp3 &= 0x07800000;         //check if any key[P1.23 to P1.26] pressed in the enabled row
if(temp3 != 0x00000000)
{

flag = 1;
temp3 >>= 19; //Shifted to come at HN of byte
temp >>= 10; //shifted to come at LN of byte
key = temp3|temp; //get SCAN_CODE

}//if(temp3 != 0x00000000)
}//end scan
//<========================================= END KEYBOARD FUNCTIONS ========================================>

int main()
{
int p=0;
	
SystemInit(); //Clock and PLL configuration
SystemCoreClockUpdate();

//<--------------FOR LCD --------------------->
LcdDataBusDirnReg |= LCD_dataBusMask; // Configure all the LCD pins as output
LcdCtrlBusDirnReg |= LCD_ctrlBusMask;
	
	
//<-------------- FOR KEYBOARD --------------->	
LPC_GPIO2->FIODIR |= 0x00003C00; //made output P2.10 to P2.13 (rows)
LPC_GPIO1->FIODIR &= 0xF87FFFFF; //made input P1.23 to P1.26(cols) 
	

lcd_init();
	
for(p=0; Msg1[p]!=0 ; p++)
{
		Lcd_DataWrite(Msg1[p]);
}

Lcd_CmdWrite(0xC0);             // get cursor to second line

while(1)
{
while(1)
{
for(row=1;row<5;row++)
{
if(row == 1)
var1 = 0x00000400;   // for P2.10
else if(row == 2)
var1 = 0x00000800;   // for P2.11
else if(row == 3)
var1 = 0x00001000;   // for P2.12
else if(row == 4)
var1 = 0x00002000;   // for P2.13

temp = var1;

LPC_GPIO2->FIOCLR = 0x00003C00; //first clear the port and send appropriate value for

LPC_GPIO2->FIOPIN |= var1; //enabling the row

flag = 0;
scan(); //scan if any key pressed in the enabled row

if(flag == 1)
break;
} //end for(row=1;row<5;row++)
if(flag == 1)
break;
} // end 2nd while(1)
	
for( p=0; p<16 ; p++)
{
		if(key==SCAN_CODE[p])
		{
				key = ASCII_CODE[p];
				break;
		}
}



}//end while 1
	
while(1);
return 0;
}// end main
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	