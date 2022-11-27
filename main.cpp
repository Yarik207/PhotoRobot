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
    string adress;
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

int get_w(string adress)
{


    FILE *f1 = fopen(adress.c_str(),  "rb");

    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char),54,f1);

    int w = *(int*)&headerinfo[18];

  return w;

}

int get_h(string adress)
{


    FILE *f1 = fopen(adress.c_str(),  "rb");

    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char),54,f1);

    int h = *(int*)&headerinfo[22];

  return h;

}

int main()
{
txCreateWindow (1200, 800);

txDisableAutoPause();

txTextCursor (false);


    int COUNT_BTN = 10;
    int COUNT_PICTURE = 36;
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
    menuPictures[0] = {50, 100,"Pictures/���/nose1.bmp"};
    menuPictures[1] = {50, 150,"Pictures/���/nose2.bmp"};
    menuPictures[2] = {50, 200,"Pictures/���/nose3.bmp"};
    menuPictures[3] = {50, 250,"Pictures/���/nose4.bmp"};
    menuPictures[4] = {50, 300,"Pictures/���/nose5.bmp"};
    menuPictures[5] = {50, 350,"Pictures/���/nose6.bmp"};

    menuPictures[6]  = {50, 100,"Pictures/����/face1M.bmp"};
    menuPictures[7]  = {50, 150,"Pictures/����/face2M.bmp"};
    menuPictures[8]  = {50, 200,"Pictures/����/face3M.bmp"};
    menuPictures[9]  = {50, 250,"Pictures/����/face4M.bmp"};
    menuPictures[10] = {50, 300,"Pictures/����/face5M.bmp"};
    menuPictures[11] = {50, 350,"Pictures/����/face5M.bmp"};

    menuPictures[12] = {50, 100,"Pictures/����/lips1.bmp"};
    menuPictures[13] = {50, 150,"Pictures/����/lips2.bmp"};
    menuPictures[14] = {50, 200,"Pictures/����/lips3.bmp"};
    menuPictures[15] = {50, 250,"Pictures/����/lips4.bmp"};
    menuPictures[16] = {50, 300,"Pictures/����/lips5.bmp"};
    menuPictures[17] = {50, 350,"Pictures/����/lips6.bmp"};
    menuPictures[18] = {50, 400,"Pictures/����/lips7.bmp"};
    menuPictures[19] = {50, 450,"Pictures/����/lips8.bmp"};

    menuPictures[20] = {50, 100,"Pictures/�����/eyes1G.bmp"};
    menuPictures[21] = {50, 150,"Pictures/�����/eyes2G.bmp"};
    menuPictures[22] = {50, 200,"Pictures/�����/eyes3G.bmp"};
    menuPictures[23] = {50, 250,"Pictures/�����/eyes4G.bmp"};
    menuPictures[24] = {50, 300,"Pictures/�����/eyes1M.bmp"};
    menuPictures[25] = {50, 350,"Pictures/�����/eyes2M.bmp"};
    menuPictures[26] = {50, 400,"Pictures/�����/eyes3M.bmp"};
    menuPictures[27] = {50, 450,"Pictures/�����/eyes4M.bmp"};

    menuPictures[28] = {50, 100,"Pictures/������/Hair1G.bmp"};
    menuPictures[29] = {50, 150,"Pictures/������/Hair2G.bmp"};
    menuPictures[30] = {50, 200,"Pictures/������/Hair3G.bmp"};
    menuPictures[31] = {50, 250,"Pictures/������/Hair4G.bmp"};
    menuPictures[32] = {50, 300,"Pictures/������/Hair1M.bmp"};
    menuPictures[33] = {50, 350,"Pictures/������/Hair2M.bmp"};
    menuPictures[34] = {50, 400,"Pictures/������/Hair3M.bmp"};
    menuPictures[35] = {50, 450,"Pictures/������/Hair4M.bmp"};

    //������ ������ �����������
    Pictures CentralPictures[COUNT_PICTURE];
    //���
    CentralPictures[0]   =  {700, 200};
    CentralPictures[1]   =  {700, 200};
    CentralPictures[2]   =  {700, 200};
    CentralPictures[3]   =  {700, 200};
    CentralPictures[4]   =  {700, 200};
    CentralPictures[5]   =  {700, 200};
    //����
    CentralPictures[6]   =  {600, 300};
    CentralPictures[7]   =  {600, 300};
    CentralPictures[8]   =  {600, 300};
    CentralPictures[9]   =  {600, 300};
    CentralPictures[10]  =  {600, 300};
    CentralPictures[11]  =  {600, 300};
    //����
    CentralPictures[12]  =  {700, 300};
    CentralPictures[13]  =  {700, 400};
    CentralPictures[14]  =  {700, 400};
    CentralPictures[15]  =  {700, 400};
    CentralPictures[16]  =  {700, 400};
    CentralPictures[17]  =  {700, 400};
    CentralPictures[18]  =  {700, 400};
    CentralPictures[19]  =  {700, 400};
    //�����
    CentralPictures[20]  =  {700, 465};
    CentralPictures[21]  =  {700, 465};
    CentralPictures[22]  =  {700, 465};
    CentralPictures[23]  =  {700, 465};
    CentralPictures[24]  =  {700, 465};
    CentralPictures[25]  =  {700, 465};
    CentralPictures[26]  =  {700, 465};
    CentralPictures[27]  =  {700, 465};
     //������
    CentralPictures[28]  =  {600, 275};
    CentralPictures[29]  =  {600, 275};
    CentralPictures[30]  =  {600, 275};
    CentralPictures[31]  =  {600, 275};
    CentralPictures[32]  =  {600, 275};
    CentralPictures[33]  =  {600, 275};
    CentralPictures[34]  =  {600, 275};
    CentralPictures[35]  =  {600, 275};



    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
         menuPictures[npic].image = txLoadImage(menuPictures[npic].adress.c_str());

        //menuPictures[npic].image =  txLoadImage(menuPictures[npic].adress.c_str());

        menuPictures[npic].w = get_w(menuPictures[npic].adress);

          menuPictures[npic].h = get_h(menuPictures[npic].adress);


        int pos1 = menuPictures[npic].adress.find("/");
        int pos2 = menuPictures[npic].adress.find("/", pos1+1);
        menuPictures[npic].category = menuPictures[npic].adress.substr(pos1+1, pos2-pos1-1);


        if(menuPictures[npic].category == "���")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "����")
        {
            menuPictures[npic].w_scr = 47;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "����")
        {
            menuPictures[npic].w_scr = 21;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "�����")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 16;
        }

        if(menuPictures[npic].category == "������")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 50;
        }

        menuPictures[npic].visible = false;

    CentralPictures[npic].adress = menuPictures[npic].adress;
    CentralPictures[npic].image = menuPictures[npic].image;
    CentralPictures[npic].w =  menuPictures[npic].w;
    CentralPictures[npic].h = menuPictures[npic].h;
    CentralPictures[npic].w_scr = CentralPictures[npic].w;
    CentralPictures[npic].h_scr = CentralPictures[npic].h;
    CentralPictures[npic].visible = menuPictures[npic].visible;
    CentralPictures[npic].category = menuPictures[npic].category;
    }

     /* if(CentralPictures[npic].category == "���")
        {
            CentralPictures[npic].x = 50;
            CentralPictures[npic].y = 50;
        }

        if(CentralPictures[npic].category == "����")
        {
            CentralPictures[npic].x = 600;
            CentralPictures[npic].y = 300;
        }

        if(CentralPictures[npic].category == "����")
        {
            CentralPictures[npic].x = 53;
            CentralPictures[npic].y = 100;
        }

        if(CentralPictures[npic].category == "�����")
        {
            CentralPictures[npic].x = 100;
            CentralPictures[npic].y = 35;
        }

        if(CentralPictures[npic].category == "������")
        {
            CentralPictures[npic].x = 600;
            CentralPictures[npic].y = 275;
        }       */

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
