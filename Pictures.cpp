
#include "TXLib.h"


struct Pictures
{
    int x;
    int y;
    HDC image;
    int w;
    int h;
    int w_scr;
    int h_scr;
};

void drawPicture(Pictures pct)
{
Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0,  pct.w, pct.h, TX_WHITE);
}

