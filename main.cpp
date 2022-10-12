#include "TXLib.h"

//��������� ������
struct Button
{
    int x;
    int y;
    const char* text;
    string category;
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
    string category;
    bool visible;
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
    if(pct.visible)
    {
        Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0,  pct.w, pct.h, TX_WHITE);
    }
}

int main()
{
txCreateWindow (1200, 800);

txDisableAutoPause();

txTextCursor (false);

    int COUNT_BTN = 4;
    int COUNT_PICTURE = 12;

    //������ ������
    Button btn[COUNT_BTN];
    btn[0] = {100, 50,"���� ����", "����"};
    btn[1] = {260, 50,"�������", "������"};
    btn[2] = {420, 50,"������ ����", "�����"};
    btn[3] = {580, 50,"���", "���"};

    //������ ������-���� �����
    Pictures menuPictures[COUNT_PICTURE];
     menuPictures[0] = {50, 100, txLoadImage ("Pictures/���/nose.bmp"), 100, 100, 100, 100, "���", false};
    menuPictures[1] = {50, 200, txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 100, 100, "���", false};
    menuPictures[2] = {50, 300, txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 100, 100, "���", false};
    menuPictures[3] = {50, 100, txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 100, 35, "�����", false};
    menuPictures[4] = {50, 200, txLoadImage ("Pictures/�����/eyes2.bmp"), 100, 42, 100, 42, "�����", false};
    menuPictures[5] = {50, 300, txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 100, 35, "�����", false};
    menuPictures[6] = {50, 100, txLoadImage ("Pictures/���� ����/face1M.bmp"), 94, 100, 94, 100, "����", false};
    menuPictures[7] = {50, 200, txLoadImage ("Pictures/���� ����/face2M.bmp"), 97, 100, 97, 100, "����", false};
    menuPictures[8] = {50, 300, txLoadImage ("Pictures/���� ����/face3M.bmp"), 70, 100, 70, 100, "����", false};
    menuPictures[9] = {50, 100, txLoadImage ("Pictures/�����/Volosi1M.bmp"), 80, 100, 80, 100, "������", false};
    menuPictures[10] ={50, 200, txLoadImage ("Pictures/�����/Volosi2M.bmp"), 87, 100, 87, 100, "������", false};
    menuPictures[11] ={50, 300, txLoadImage ("Pictures/�����/Volosi3M.bmp"), 100, 97, 100, 97, "������", false};

    //������ ������-���� �����������
    Pictures CentralPictures[COUNT_PICTURE];
    CentralPictures[0] = {250, 200, txLoadImage ("Pictures/���/nose.bmp"), 100, 100, 100, 100, "���", false};
    CentralPictures[1] = {250, 300, txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 100, 100, "���", false};
    CentralPictures[2] = {250, 400, txLoadImage ("Pictures/���/Nooose.bmp"), 100, 100, 100, 100, "���", false};
    CentralPictures[3] = {250, 200, txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 100, 35, "�����", false};
    CentralPictures[4] = {250, 300, txLoadImage ("Pictures/�����/eyes2.bmp"), 100, 42, 100, 42, "�����", false};
    CentralPictures[5] = {250, 400, txLoadImage ("Pictures/�����/eyes1.bmp"), 100, 35, 100, 35, "�����", false};
    CentralPictures[6] = {250, 200, txLoadImage ("Pictures/���� ����/face1M.bmp"), 94, 100, 94, 100, "����", false};
    CentralPictures[7] = {250, 300, txLoadImage ("Pictures/���� ����/face2M.bmp"), 97, 100, 97, 100, "����", false};
    CentralPictures[8] = {250, 400, txLoadImage ("Pictures/���� ����/face3M.bmp"), 70, 100, 70, 100, "����", false};
    CentralPictures[9] = {250, 200, txLoadImage ("Pictures/�����/Volosi1M.bmp"), 80, 100, 80, 100, "������", false};
    CentralPictures[10] ={250, 300, txLoadImage ("Pictures/�����/Volosi2M.bmp"), 87, 100, 87, 100, "������", false};
    CentralPictures[11] ={250, 400, txLoadImage ("Pictures/�����/Volosi3M.bmp"), 100, 97, 100, 97, "������", false};




while(!GetAsyncKeyState(VK_ESCAPE))
{
    txBegin();
    txSetColor (TX_WHITE);
    txSetFillColor (TX_YELLOW);
    txClear();

    //�����������

    //����������� �������� ���������
     for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(CentralPictures[npic]);
    }

    //����������� �������� ���������
    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(CentralPictures[npic]);
    }


    //����������� �������� ���������
for(int npic = 0; npic < COUNT_PICTURE; npic++)
{
    if(txMouseX() >= menuPictures[npic].x &&
    txMouseY() >= menuPictures[npic].y &&
    txMouseX() <= menuPictures[npic].x + menuPictures[npic].w_scr &&
    txMouseY() <= menuPictures[npic].y + menuPictures[npic].h_scr &&
    menuPictures[npic].visible &&
    txMouseButtons() == 1)
    {
        for(int npic1 = 0; npic < COUNT_PICTURE; npic1++)
        {
            if(CentralPictures[npic1].category == CentralPictures[npic1].category)
            {
                CentralPictures[npic1].visible = false;
            }
        }
        CentralPictures[npic].visible = !CentralPictures[npic].visible;
        txSleep(100);
    }
}

       //�����

    //��������� ������
    for(int nk=0; nk<4; nk++)
    {
        drawButton(btn[nk]);
    }

    //����� �������� ���������
    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(menuPictures[npic]);
    }



   //��������� ����� �� ���������� ������
    for(int nk=0; nk<COUNT_BTN; nk++)
    {
        if (Click(btn[nk]))
        {
            for(int npic = 0; npic < COUNT_PICTURE; npic++)
            {
                menuPictures[npic].visible = false;
                if (menuPictures[npic].category == btn[nk].category)
                {
                    menuPictures[npic].visible = true;
                }
            }
        }
    }


    txSleep(50);
    txEnd();
}


    //�������� �����
    for(int npic=0;npic <COUNT_PICTURE; npic++)
   {
        txDeleteDC(menuPictures[npic].image);
   }

    //�������� �����������
    for(int npic=0;npic <COUNT_PICTURE; npic++)
   {
        txDeleteDC(CentralPictures[npic].image);
   }

return 0;
}
