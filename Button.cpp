
#include "TXLib.h"


struct Button
{
    int x;
    int y;
    const char* text;
};

void  drawButton(Button btn)
{

      txSetColor(TX_BLACK);
      txSetFillColor(TX_BLACK);
      Win32::RoundRect (txDC(),btn.x+3 ,btn.y+3 ,btn.x+153 ,btn.y+43, 30, 30);

      txSetColor(TX_BLACK);
      txSetFillColor(TX_WHITE);
      Win32::RoundRect (txDC(), btn.x, btn.y, btn.x+150, btn.y+40, 30, 30);

      txSetFillColor(TX_WHITE);
      txSetColor(TX_BLACK);
      txSelectFont("Times New Roman", 32);
      txDrawText(btn.x , btn.y,btn.x+150 ,btn.y+40, btn.text);
}

bool Click(Button btn)
{
return(txMouseX() >= btn.x &&
       txMouseY() >= btn.y &&
       txMouseX() <= btn.x + 150 &&
       txMouseY() <= btn.y + 40 &&
       txMouseButtons() == 1 );
}

