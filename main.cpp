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
    int adress;
    HDC image;
    int w;
    int h;
    int w_scr;
    int h_scr;
    bool visible;
    string category;
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

    int COUNT_BTN = 10;
    int COUNT_PICTURE = 50;
    int select = -1;
    bool mouse_free = false;
    char str[100];

    //������ ������
    Button btn[COUNT_BTN];
    btn[0] = {100, 50,"���� ����", "����"};
    btn[1] = {260, 50,"�������", "������"};
    btn[2] = {420, 50,"������ ����", "�����"};
    btn[3] = {580, 50,"���", "���"};
    btn[4] = {740, 50,"����", "����"};

    //������ ������-���� �����
    Pictures menuPictures[COUNT_PICTURE];
    menuPictures[0] = {50, 100,"Pictures/���/nose1.bmp", NULL, 100, 100, NULL, NULL, "���"};
    menuPictures[1] = {50, 200,"Pictures/���/nose2.bmp", NULL, 100, 100, NULL, NULL, "���"};
    menuPictures[2] = {50, 300,"Pictures/���/nose3.bmp", NULL, 100, 125, NULL, NULL, "���"};
    menuPictures[3] = {50, 400,"Pictures/���/nose4.bmp", NULL, 59, 100, NULL, NULL, "���"};
    menuPictures[4] = {50, 500,"Pictures/���/nose5.bmp", NULL, 100, 116, NULL, NULL, "���"};
    menuPictures[5] = {50, 600,"Pictures/���/nose6.bmp", NULL, 62, 100, NULL, NULL, "���"};

    menuPictures[6]  = {50, 100,"Pictures/����/face1M.bmp", NULL, 94, 100, NULL, NULL, "����"};
    menuPictures[7]  = {50, 200,"Pictures/����/face1M.bmp", NULL, 97, 100, NULL, NULL, "����"};
    menuPictures[8]  = {50, 300,"Pictures/����/face1M.bmp", NULL, 70, 100, NULL, NULL, "����"};
    menuPictures[9]  = {50, 400,"Pictures/����/face1M.bmp", NULL, 100, 136, NULL, NULL, "����"};
    menuPictures[10] = {50, 500,"Pictures/����/face1M.bmp", NULL, 100, 115, NULL, NULL, "����"};
    menuPictures[11] = {50, 600,"Pictures/����/face1M.bmp", NULL, 100, 131, NULL, NULL, "����"};

    menuPictures[12] = {50, 100,"Pictures/����/lips1.bmp", NULL, 100, 57, NULL, NULL, "����"};
    menuPictures[13] = {50, 200,"Pictures/����/lips1.bmp", NULL, 100, 54, NULL, NULL, "����"};
    menuPictures[14] = {50, 300,"Pictures/����/lips1.bmp", NULL, 100, 51, NULL, NULL, "����"};
    menuPictures[15] = {50, 400,"Pictures/����/lips1.bmp", NULL, 100, 50, NULL, NULL, "����"};
    menuPictures[16] = {50, 500,"Pictures/����/lips1.bmp", NULL, 100, 51, NULL, NULL, "����"};
    menuPictures[17] = {50, 600,"Pictures/����/lips1.bmp", NULL, 100, 51, NULL, NULL, "����"};
    menuPictures[18] = {50, 700,"Pictures/����/lips1.bmp", NULL, 100, 33, NULL, NULL, "����"};
    menuPictures[19] = {150, 100,"Pictures/����/lips1.bmp", NULL, 100, 46, NULL, NULL, "����"};

    menuPictures[20] = {50, 100,"Pictures/�������/�����/eyes1G.bmp", NULL, 100, 35, NULL, NULL, "�����"};
    menuPictures[21] = {50, 200,"Pictures/�������/�����/eyes1G.bmp", NULL, 100, 39, NULL, NULL, "�����"};
    menuPictures[22] = {50, 300,"Pictures/�������/�����/eyes1G.bmp", NULL, 100, 37, NULL, NULL, "�����"};
    menuPictures[23] = {50, 400,"Pictures/�������/�����/eyes1G.bmp", NULL, 100, 27, NULL, NULL, "�����"};

    menuPictures[24] = {50, 500,"Pictures/�������/�����/eyes1M.bmp", NULL, 100, 46, NULL, NULL, "�����"};
    menuPictures[25] = {50, 600,"Pictures/�������/�����/eyes1M.bmp", NULL, 100, 38, NULL, NULL, "�����"};
    menuPictures[26] = {50, 700,"Pictures/�������/�����/eyes1M.bmp", NULL, 100, 33, NULL, NULL, "�����"};
    menuPictures[27] = {150, 100,"Pictures/�������/�����/eyes1M.bmp", NULL, 100, 32, NULL, NULL, "�����"};

    menuPictures[28] = {50, 100,"Pictures/�������/������/Hair1G.bmp", NULL, 100, 108, NULL, NULL, "������"};
    menuPictures[29] = {50, 200,"Pictures/�������/������/Hair1G.bmp", NULL, 100, 102, NULL, NULL, "������"};
    menuPictures[30] = {50, 300,"Pictures/�������/������/Hair1G.bmp", NULL, 100, 105, NULL, NULL, "������"};
    menuPictures[31] = {50, 400,"Pictures/�������/������/Hair1G.bmp", NULL, 100, 123, NULL, NULL, "������"};

    menuPictures[32] = {50, 500,"Pictures/�������/������/Hair1M.bmp", NULL, 100, 82,  NULL, NULL, "������"};
    menuPictures[33] = {50, 600,"Pictures/�������/������/Hair1M.bmp", NULL, 100, 90,  NULL, NULL, "������"};
    menuPictures[34] = {50, 700,"Pictures/�������/������/Hair1M.bmp", NULL, 100, 91,  NULL, NULL, "������"};
    menuPictures[35] = {150, 100,"Pictures/�������/������/Hair1M.bmp", txLoadImage (menuPictures[35].adress.c_str()), 100, 86,  NULL, NULL, "������"};

    //������ ������ �����������
    Pictures CentralPictures[COUNT_PICTURE];
    CentralPictures[0]   =  {600, 200};
    CentralPictures[1]   =  {600, 200};
    CentralPictures[2]   =  {600, 200};
    CentralPictures[3]   =  {600, 200};
    CentralPictures[4]   =  {600, 200};
    CentralPictures[5]   =  {600, 200};

    CentralPictures[6]   =  {600, 300};
    CentralPictures[7]   =  {600, 300};
    CentralPictures[8]   =  {600, 300};
    CentralPictures[9]   =  {600, 300};
    CentralPictures[10]  =  {600, 300};
    CentralPictures[11]  =  {600, 300};

    CentralPictures[12]  =  {600, 300};
    CentralPictures[13]  =  {600, 400};
    CentralPictures[14]  =  {600, 400};
    CentralPictures[15]  =  {600, 400};
    CentralPictures[16]  =  {600, 400};
    CentralPictures[17]  =  {600, 400};
    CentralPictures[18]  =  {600, 400};
    CentralPictures[19]  =  {600, 400};
    CentralPictures[20]  =  {600, 400};

    CentralPictures[21]  =  {600, 500};
    CentralPictures[22]  =  {600, 500};
    CentralPictures[23]  =  {600, 500};
    CentralPictures[24]  =  {600, 500};
    CentralPictures[25]  =  {600, 500};
    CentralPictures[26]  =  {600, 500};
    CentralPictures[27]  =  {600, 500};
    CentralPictures[28]  =  {600, 500};

    CentralPictures[29]  =  {600, 600};
    CentralPictures[30]  =  {600, 600};
    CentralPictures[31]  =  {600, 600};
    CentralPictures[32]  =  {600, 600};
    CentralPictures[33]  =  {600, 600};
    CentralPictures[34]  =  {600, 600};
    CentralPictures[35]  =  {600, 600};

 menuPictures[0].adress.c_str();

    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
     menuPictures[npic].image =  txLoadImage (menuPictures[npic].adress.c_str());

   if(menuPictures[npic].category == "���")
     menuPictures[npic].w_scr = 50;
     menuPictures[npic].h_scr = 50;

      if(menuPictures[npic].category == "����")
      {
     menuPictures[npic].w_scr = 94;
     menuPictures[npic].h_scr = 100;
     }

      if(menuPictures[npic].category == "����")
      {
     menuPictures[npic].w_scr = 53;
     menuPictures[npic].h_scr = 100;
       }

      if(menuPictures[npic].category == "�����")
      {
     menuPictures[npic].w_scr = 100;
     menuPictures[npic].h_scr = 38;
      }

      if(menuPictures[npic].category == "������")
      {
     menuPictures[npic].w_scr = 100;
     menuPictures[npic].h_scr = 100;
       }

    menuPictures[npic].visible = false;

    CentralPictures[npic].image = menuPictures[npic].image;
    menuPictures[npic].w =  menuPictures[npic].w;
    menuPictures[npic].h = menuPictures[npic].h;
    menuPictures[npic].w_scr = menuPictures[npic].w_scr;
    menuPictures[npic].h_scr = menuPictures[npic].h_scr;
    menuPictures[npic].visible = menuPictures[npic].visible;
    menuPictures[npic].category = menuPictures[npic].category;
    }

while(!GetAsyncKeyState(VK_ESCAPE))
{
    txBegin();
    txSetColor (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txClear();


  //����� �������� ���������
    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(menuPictures[npic]);
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
            for(int n1 = 0; n1 < COUNT_PICTURE; n1++)
            {
                if(CentralPictures[n1].category == CentralPictures[npic].category)
                {
                    CentralPictures[n1].visible = false;
                }
            }
            CentralPictures[npic].visible = !CentralPictures[npic].visible;
            txSleep(100);
        }
    }

    //��������� ������
    for(int nk=0; nk<5; nk++)
    {
        drawButton(btn[nk]);
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

     //����� ����������� ��������
      for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        if(txMouseX() >= CentralPictures[npic].x &&
        txMouseY() >= CentralPictures[npic].y &&
        txMouseX() <= CentralPictures[npic].x + CentralPictures[npic].w &&
        txMouseY() <= CentralPictures[npic].y + CentralPictures[npic].h &&
        CentralPictures[npic].visible &&
        txMouseButtons() == 1)
        {
           select = npic;
           mouse_free = false;


        }
    }

    //������������ ����������� �������� ��������� ���������
    if(select >= 0)
    {
        if(GetAsyncKeyState(VK_RIGHT)) CentralPictures[select].x += 3;
        if(GetAsyncKeyState(VK_LEFT)) CentralPictures[select].x -= 3;
        if(GetAsyncKeyState(VK_UP)) CentralPictures[select].y -= 3;
        if(GetAsyncKeyState(VK_DOWN)) CentralPictures[select].y += 3;

            if(GetAsyncKeyState(VK_OEM_PLUS))
            {
                CentralPictures[select].w_scr = CentralPictures[select].w_scr * 1.02;
                CentralPictures[select].h_scr = CentralPictures[select].h_scr * 1.02;
            }

            if(GetAsyncKeyState(VK_OEM_MINUS))
            {
                CentralPictures[select].w_scr = CentralPictures[select].w_scr * 0.98;
                CentralPictures[select].h_scr = CentralPictures[select].h_scr * 0.98;
            }

    }

        //������������ ����������� �������� ���������  ������
    if(select >= 0)
    {
        if(txMouseButtons() == 1 && !mouse_free)
        {
            CentralPictures[select].x = txMouseX() - CentralPictures[select].w/2;
            CentralPictures[select].y = txMouseY() - CentralPictures[select].h/2;
        }
            else
            {
                if(txMouseButtons() != 1)
                {
                    mouse_free = true;
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
