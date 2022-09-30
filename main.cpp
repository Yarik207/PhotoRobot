
#include "TXLib.h"

/*

 txBitBlt(txDC(), 50, 100, 50, 65, nos);

        drawButton(btn[1]);
        drawButton(btn[2]);
        drawButton(btn[3]);
        drawButton(btn[4]);


*/
//��������� ������
struct Button
{
    int x;
    int y;
    const char* text;
};

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

//������� ��������� ������
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

void drawPicture(Pictures pct)
{
 Win32::txTransparentBlt(txDC(), pct.x, pct.y, pct.w, pct.h, pct.image, 0, 0, TX_WHITE, pct.w_scr, pct.h_scr);
}


int main()
{
txCreateWindow (1200, 800);

txDisableAutoPause();

txTextCursor (false);

HDC nose = txLoadImage ("Pictures/���/nose.bmp");
HDC Nooose = txLoadImage ("Pictures/���/Nooose.bmp");

HDC eyes = txLoadImage ("Pictures/�����/eyes1.bmp");
HDC eyes2 = txLoadImage ("Pictures/�����/eyes2.bmp");

HDC face1M = txLoadImage ("Pictures/���� ����/face1M.bmp");
HDC face2M = txLoadImage ("Pictures/���� ����/face2M.bmp");
HDC face3M = txLoadImage ("Pictures/���� ����/face3M.bmp");

HDC Hair1M = txLoadImage ("Pictures/�����/Volosi1M.bmp");
HDC Hair2M = txLoadImage ("Pictures/�����/Volosi2M.bmp");
HDC Hair3M = txLoadImage ("Pictures/�����/Volosi3M.bmp");

 //������ ������
    Button btn[10];
    btn[0] = {100, 50,"���� ����"};
    btn[1] = {260, 50,"�������"};
    btn[2] = {420, 50,"������ ����"};
    btn[3] = {580, 50,"���"};

         //������ ������
         Pictures menuPickture[12];
         menuPickture[0] = {600, 400, txLoadImage ("Pictures/���/nose.bmp"), 100, 100, 35, 35};
         menuPickture[1] = {100, 100,txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 35, 35};
         menuPickture[2] = {100, 250, txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 35, 35};

         menuPickture[3] = {600, 400, txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 99, 34};
         menuPickture[4] = {100, 100, txLoadImage ("Pictures/�����/eyes2.bmp"), 100, 42, 99, 43 };
         menuPickture[5] = {100, 250,  txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 99, 34 };

         menuPickture[6] = {600, 400, txLoadImage ("Pictures/���� ����/face1M.bmp"), 94, 100, 93, 99};
         menuPickture[7] = {100, 100, txLoadImage ("Pictures/���� ����/face2M.bmp"), 97, 100, 96, 99};
         menuPickture[8] = {100, 250, txLoadImage ("Pictures/���� ����/face3M.bmp"), 70, 100, 69, 99};

         menuPickture[9] = {600, 400, txLoadImage ("Pictures/�����/Volosi1M.bmp"), 80, 100, 79, 99};
         menuPickture[10] = {100, 100, txLoadImage ("Pictures/�����/Volosi2M.bmp"), 87, 100, 86, 99};
         menuPickture[11] = {100, 250, txLoadImage ("Pictures/�����/Volosi3M.bmp"), 100, 97, 99, 96};


        bool noseVisible = false;
        bool GlasaVisible = false;
        bool FaceVisible = false;
        bool HairVisible = false;

while(!GetAsyncKeyState(VK_ESCAPE))
{
    txBegin();
    txSetColor (TX_WHITE);
    txSetFillColor (TX_YELLOW);
    txClear();

    //��������� ������
        for(int nk=0; nk<4; nk++)
        {
            drawButton(btn[nk]);
        }

        if(Click(btn[0]))
        {
        GlasaVisible = false;
        noseVisible = false;
        FaceVisible = true;
        HairVisible = false;
        }

        if(Click(btn[1]))
        {
        GlasaVisible = false;
        noseVisible = false;
        FaceVisible = false;
        HairVisible = true;
        }

        if(Click(btn[2]))
        {
        GlasaVisible = true;
        noseVisible = false;
        FaceVisible = false;
        HairVisible = false;
        }

        if(Click(btn[3]))
        {
        noseVisible = true;
        GlasaVisible = false;
        FaceVisible = false;
        HairVisible = false;
        }

           if(noseVisible)
        {
           for(int npic=0;npic <=2; npic++)
           {
             drawPicture(menuPickture[npic]);
           }
        }


        if(GlasaVisible)
        {
           for(int npic=3;npic <=5; npic++)
           {
             drawPicture(menuPickture[npic]);
           }
        }

        if(FaceVisible)
        {
            for(int npic=6;npic <=8; npic++)
           {
             drawPicture(menuPickture[npic]);
           }
        }

        if(HairVisible)
        {
           for(int npic = 9;npic <= 11; npic++)
           {
             drawPicture(menuPickture[npic]);
           }
        }

    txSleep(50);
    txEnd();
    }

    for(int npic=0;npic <=2; npic++)
           {
             txDeleteDC(menuPickture[npic].image);
           }

return 0;
}

