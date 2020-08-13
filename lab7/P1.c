#include <LPC17xx.h>

unsigned seven_seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int dig_count=0,j,i;
unsigned int dig_value[4]={4,3,2,1};
unsigned int dig_select[] = {0<<23,1<<23,2<<23,3<<23};

void display()
{
	LPC_GPIO1->FIOPIN=dig_select[dig_count];
	LPC_GPIO0->FIOPIN=seven_seg[dig_value[dig_count]]<<4;
}
void delay()
{
	for(j=0;j<=60000;j++);
}

int main()
{
	//LPC_PINCON -> PINSEL0 = 0x0;
	//LPC_PINCON -> PINSEL3 = 0x0;
	LPC_GPIO0->FIODIR = 0xFF<<4;
	LPC_GPIO1->FIODIR = 0xF<<23;
	while(1)
	{
		delay();
		dig_count=(dig_count+1)%4;
		display();
	}
	
}
