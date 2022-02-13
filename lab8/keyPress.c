
#include "displayMessageLCD.h"

char msg[]={"Key Pressed: "};
int row,column,col,i;
int keyarr[4][4]={{'0','1','2','3'},{'4','5','6','7'},{'8','9','A','B'},{'C','D','E','F'}};

int main()
{
  LPC_GPIO2->FIODIR|=0xF<<10;
  LPC_GPIO1->FIODIR&=~(0xF<<23);

  initializeLCD();
  writeData(0x80,0);

  for(i=0; msg[i]; i++)
    writeData(msg[i],1);

  for(row=0; ; row=(row+1)%4)
  {
    LPC_GPIO2->FIOCLR|=0xF<<10;
    LPC_GPIO2->FIOPIN|=1<<(10+row);
    column=(LPC_GPIO1->FIOPIN >> 23) & 0xF;
    if(column)
    {
      col=-1;
      while(column)
      {
        column/=2;
        col++;
      }
      writeData(0xC0,0);
      writeData(keyarr[row][col],1);
    }
  }
}
