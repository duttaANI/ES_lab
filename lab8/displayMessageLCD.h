
#include<LPC17xx.h>

#define DATA 0xF<<23
#define RS 1<<27
#define EN 1<<28

int i=0,j=0;

void initializeLCD(void);
void writeData(int data, int rs);
void pulsate(void);
void initializeTimer(void);
void delay(int ms);

void initializeTimer()
{
  LPC_TIM0->CTCR=0x0;
  LPC_TIM0->PR=2;
  LPC_TIM0->MR0=999;
  LPC_TIM0->MCR=0x02;
  LPC_TIM0->EMR=0x02<<4;
  LPC_TIM0->TCR=0x02;
  LPC_TIM0->TCR=0x01;
}

void delay(int ms)
{
	initializeTimer();
  for(j=0; j<ms; j++)
    while(!(LPC_TIM0->EMR & 1));
}

void initializeLCD()
{
  LPC_GPIO0->FIODIR|=(DATA|RS|EN);
  writeData(0x33,0);
  writeData(0x32,0);
  writeData(0x28,0);
  writeData(0x0C,0);
  writeData(0x06,0);
  writeData(0x01,0);
}

void writeData(int data, int rs)
{
  LPC_GPIO0->FIOCLR|=(DATA|RS|EN);
  if(rs==1)
    LPC_GPIO0->FIOPIN|=RS;
  LPC_GPIO0->FIOPIN|=(data&0xF0)<<19;
  pulsate();
	LPC_GPIO0->FIOCLR|=DATA;
  LPC_GPIO0->FIOPIN|=(data&0x0F)<<23;
  pulsate();
}

void pulsate()
{
  LPC_GPIO0->FIOPIN|=EN;
  delay(1);
  LPC_GPIO0->FIOCLR|=EN;
  delay(2);
}
