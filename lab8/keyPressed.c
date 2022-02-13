
#include<LPC17xx.h>
#include "displayMessageLCD.h"

void scan(void);

unsigned char msg1[13]="KEY PRESSED=";
unsigned char row, var, flag, key;

int i, var1, temp, temp1, temp2, temp3;
unsigned char scan_code[16]={ 0x11, 0x21, 0x41, 0x81, 0x12, 0x22, 0x42, 0x82, 0x14, 0x24, 0x44, 0x84, 0x18, 0x28, 0x48, 0x88 };
unsigned char ascii_code[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int ans=0;

int main()
{
	LPC_GPIO2->FIODIR|=0X00003C00;
	LPC_GPIO1->FIODIR&=0XF87FFFFF;
	
	initializeLCD();
	
	writeData(0x80,0);
	for(i=0; msg1[i]; i++)
    writeData(msg1[i],1);
	
	while(1)
	{
			for(row=0; ; row=(row+1)%4)
			{
				var1=1<<(10+row);
				
				temp=var1;
				LPC_GPIO2->FIOCLR=0X00003C00;
				LPC_GPIO2->FIOPIN=var1;
				flag=0;
				temp3=LPC_GPIO1->FIOPIN;
				temp3&=(0xF<<23);
				
				if(temp3)
				{
					flag=1;
					temp3>>=19;
					temp>>=10;
					key=temp3|temp;
					for(i=0;i<10000;i++);
				}
				if(flag==1)
					break;
			}
		
			for(i=0; i<16; i++)
			{
				if(key==scan_code[i])
				{
					key=ascii_code[i];
					break;
				}
			}
			writeData(0xC0,0);
			writeData(key,1);
	} // outer while
}
				
			