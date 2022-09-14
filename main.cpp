
#include "TXLib.h"

/*

 txBitBlt(txDC(), 50, 100, 50, 65, nos);
*/
void drawButton(int x, int y, const char* text)
{

      txSetColor(TX_BLACK);
      txSetFillColor(TX_BLACK);
      Win32::RoundRect (txDC(),x+3 ,y+3 ,x+153 ,y+43, 30, 30);

      txSetColor(TX_BLACK);
      txSetFillColor(TX_WHITE);
      Win32::RoundRect (txDC(), x, y, x+150, y+40, 30, 30);

      txSetFillColor(TX_WHITE);
      txSetColor(TX_BLACK);
      txSelectFont("Times New Roman", 32);
      txDrawText(x , y,x+150 ,y+40, text);
}




int main()
    {
    txCreateWindow (1200, 800);

     txDisableAutoPause();

     txTextCursor (false);

     HDC nose = txLoadImage("Pictures/nose.bmp");

     while(!GetAsyncKeyState(VK_ESCAPE))
     {
      txBegin();
      txSetColor (TX_WHITE);
      txSetFillColor (TX_YELLOW);
      txClear();

        drawButton( 100, 50,"Овал лица");//кнопка "Овал лица"

        drawButton( 260, 50,"Стрижка");//кнопка "Стрижка"

        drawButton( 420, 50,"Разрез Глаз");//кнопка "Разрез Глаз"

        drawButton( 580, 50,"Нос");//кнопка "Нос"



        txTransparentBlt(txDC(), 100, 100, 100, 100, nose, 0, 0, TX_WHITE);


      txSleep(50);
       txEnd();
     }



    txDeleteDC(nose);

    return 0;
    }

