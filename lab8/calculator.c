
#include "displayMessageLCD.h"

int count,row,column,col;

int main()
{
  LPC_GPIO2->FIODIR|=0xF<<10;
  LPC_GPIO1->FIODIR&=~(0xF<<23);

  initializeLCD();
  writeData(0x80,0);

  int keyarr[4][4]={{'0','1','2','3'},{'4','5','6','7'},{'8','9','A','B'},{'+','-','*','/'}};

  int a=0,b=0,res=0;

  for(count=0; count<3; count++)
  {
    for(row=0; ; row=(row+1)%4)
    {
      LPC_GPIO2->FIOCLR|=0xF<<10;
      LPC_GPIO2->FIOPIN|=1<<(10+row);
      column=(LPC_GPIO1->FIOPIN >> 10) & 0xF;
      if(column)
      {
        col=-1;
        while(column)
        {
          column/=2;
          col++;
        }
        switch(count)
        {
          case 0: a=keyarr[row][col]-'0';
                  break;
          case 1: op=keyarr[row][col];
                  break;
          case 2: b=keyarr[row][col]-'0';
                  switch(op)
                  {
                    case '+': res=a+b; break;
                    case '-': res=a-b; break;
                    case '*': res=a*b; break;
                    case '/': res=a/b; break;
                  }
                  writeData(0xC0,0);
                  writeData(res/10+48,1);
                  writeData(res%10+48,1);
                  break;
        }
        break;
      }
    }
  }
}
