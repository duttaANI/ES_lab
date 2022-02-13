
#include<stdlib.h>
#include "displayMessageLCD.h"

int main()
{
  initializeLCD();
  writeData(0x80,0);

  LPC_GPIO2->FIODIR&=~(1<<12);
  while(1)
  {
    if(!(LPC_GPIO2->FIOPIN & 1<<12))
    {
      writeData(0x01,0);
      writeData(0x80,0);
      writeData(rand()%6+1+48,1);
    }
  }
}
