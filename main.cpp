
#include "TXLib.h"

int main()
    {
    txCreateWindow (1200, 800);

     txDisableAutoPause();

     txTextCursor (false);

     while(!GetAsyncKeyState(VK_ESCAPE))
     {
      txBegin();
      txSetColor (TX_WHITE);
      txSetFillColor (TX_WHITE);
      txClear();

      txSetColor(TX_BLACK);
      txSetFillColor(TX_GRAY);
      Win32::RoundRect (txDC(), 53, 53, 203, 93, 30, 30);


      txSetColor(TX_BLACK);
      txSetFillColor(TX_WHITE);
      Win32::RoundRect (txDC(),50, 50, 200, 90, 30, 30);


      txSetFillColor(TX_WHITE);
      txSetColor(TX_BLACK);
      txSelectFont("Times New Roman", 32);
      txDrawText(50, 50, 200, 90, "Кнопка");


      txSleep(50);
       txEnd();
     }

    return 0;
    }

