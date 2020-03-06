#include <LPC_17xx.h>
#include <stdio.h>
//int i;
//#define delay() while(i<1000)i++;

unsigned int dig1=9,dig2=9,dig=9,dig4=9;
unsigned int a[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

unsigned int dig_count=0,tmp=0,tmp2=0,i=0;

void display():
	
int main(void)
{
		SystemInit();
		SystemCoreClockUpdate();
	
		LPC_PINCON->PINSEL0 = 0x0; // or 0xFF0000FF P0.4 to P0.11 
		LPC_PINCON->PINSEL3 = 0x0; // or P2.23 to P2.26
		LPC_GPIO0->FIODIR=0XFF<<4;
		LPC_GPIO1->FIODIR=0XF<<23;
		while(1)
		{
				display();
		}
		return 0;
}

void display()
{
		dig1--;
	  if(dig1==1)
		{
				dig1=9;
				dig2--;
				if(dig2==-1)
				{
						dig2=9;
					  dig3--;
					  if(dig3==-1)
						{
								dig3=9;
								dig4--;
								if(dig4==-1)
								{
										dig4=9;
								}
						}
				}
		}
		
		LPC_GPIO1->FIOPIN=0x0<<23;
		tmp2=a[dig1];
		LPC_GPIO0->FIOPIN=tmp2<<4;
		for(i=0;i<1000;i++);
		LPC_GPIO1->FIOPIN=0x1<<23;
		tmp2=a[dig2];
		LPC_GPIO0->FIOPIN=tmp2<<4;
		for(i=0;i<1000;i++);
		LPC_GPIO1->FIOPIN=0x2<<23;
		tmp2=a[dig3];
		LPC_GPIO0->FIOPIN=tmp2<<4;
		for(i=0;i<1000;i++);
		LPC_GPIO1->FIOPIN=0x3<<23;
		tmp2=a[dig4];
		LPC_GPIO0->FIOPIN=tmp2<<4;
		for(i=0;i<1000;i++);
}
