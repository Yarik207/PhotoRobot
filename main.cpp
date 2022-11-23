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
    menuPictures[0] = {50, 100,"Pictures/���/nose1.bmp",  txLoadImage("Pictures/���/nose1.bmp")};
    menuPictures[1] = {50, 200,"Pictures/���/nose2.bmp",  txLoadImage("Pictures/���/nose2.bmp")};
    menuPictures[2] = {50, 300,"Pictures/���/nose3.bmp",  txLoadImage("Pictures/���/nose3.bmp")};
    menuPictures[3] = {50, 400,"Pictures/���/nose4.bmp",  txLoadImage(menuPictures[3].adress.c_str())};
    menuPictures[4] = {50, 500,"Pictures/���/nose5.bmp",  txLoadImage(menuPictures[4].adress.c_str())};
    menuPictures[5] = {50, 600,"Pictures/���/nose6.bmp",  txLoadImage(menuPictures[5].adress.c_str())};

    menuPictures[6]  = {50, 100,"Pictures/����/face1M.bmp",  txLoadImage(menuPictures[6].adress.c_str())};
    menuPictures[7]  = {50, 200,"Pictures/����/face2M.bmp",  txLoadImage(menuPictures[7].adress.c_str())};
    menuPictures[8]  = {50, 300,"Pictures/����/face3M.bmp",  txLoadImage(menuPictures[8].adress.c_str())};
    menuPictures[9]  = {50, 400,"Pictures/����/face4M.bmp",  txLoadImage(menuPictures[9].adress.c_str())};
    menuPictures[10] = {50, 500,"Pictures/����/face5M.bmp",  txLoadImage(menuPictures[10].adress.c_str())};
    menuPictures[11] = {50, 600,"Pictures/����/face5M.bmp",  txLoadImage(menuPictures[11].adress.c_str())};

    menuPictures[12] = {50, 100,"Pictures/����/lips1.bmp",  txLoadImage(menuPictures[12].adress.c_str())};
    menuPictures[13] = {50, 200,"Pictures/����/lips2.bmp",  txLoadImage(menuPictures[13].adress.c_str())};
    menuPictures[14] = {50, 300,"Pictures/����/lips3.bmp",  txLoadImage(menuPictures[14].adress.c_str())};
    menuPictures[15] = {50, 400,"Pictures/����/lips4.bmp",  txLoadImage(menuPictures[15].adress.c_str())};
    menuPictures[16] = {50, 500,"Pictures/����/lips5.bmp",  txLoadImage(menuPictures[16].adress.c_str())};
    menuPictures[17] = {50, 600,"Pictures/����/lips6.bmp",  txLoadImage(menuPictures[17].adress.c_str())};
    menuPictures[18] = {50, 700,"Pictures/����/lips7.bmp",  txLoadImage(menuPictures[18].adress.c_str())};
    menuPictures[19] = {150, 100,"Pictures/����/lips8.bmp",  txLoadImage(menuPictures[19].adress.c_str())};

    menuPictures[20] = {50, 100,"Pictures/�����/eyes1G.bmp",  txLoadImage(menuPictures[20].adress.c_str())};
    menuPictures[21] = {50, 200,"Pictures/�����/eyes2G.bmp",  txLoadImage(menuPictures[21].adress.c_str())};
    menuPictures[22] = {50, 300,"Pictures/�����/eyes3G.bmp",  txLoadImage(menuPictures[22].adress.c_str())};
    menuPictures[23] = {50, 400,"Pictures/�����/eyes4G.bmp",  txLoadImage(menuPictures[23].adress.c_str())};

    menuPictures[24] = {50, 500,"Pictures/�����/eyes1M.bmp",  txLoadImage(menuPictures[24].adress.c_str())};
    menuPictures[25] = {50, 600,"Pictures/�����/eyes2M.bmp",  txLoadImage(menuPictures[25].adress.c_str())};
    menuPictures[26] = {50, 700,"Pictures/�����/eyes3M.bmp",  txLoadImage(menuPictures[26].adress.c_str())};
    menuPictures[27] = {150, 100,"Pictures/�����/eyes4M.bmp",  txLoadImage(menuPictures[27].adress.c_str())};

    menuPictures[28] = {50, 100,"Pictures/������/Hair1G.bmp",  txLoadImage(menuPictures[28].adress.c_str())};
    menuPictures[29] = {50, 200,"Pictures/������/Hair2G.bmp",  txLoadImage(menuPictures[29].adress.c_str())};
    menuPictures[30] = {50, 300,"Pictures/������/Hair3G.bmp",  txLoadImage(menuPictures[30].adress.c_str())};
    menuPictures[31] = {50, 400,"Pictures/������/Hair4G.bmp",  txLoadImage(menuPictures[31].adress.c_str())};

    menuPictures[32] = {50, 500,"Pictures/������/Hair1M.bmp",  txLoadImage(menuPictures[32].adress.c_str())};
    menuPictures[33] = {50, 600,"Pictures/������/Hair2M.bmp",  txLoadImage(menuPictures[33].adress.c_str())};
    menuPictures[34] = {50, 700,"Pictures/������/Hair3M.bmp",  txLoadImage(menuPictures[34].adress.c_str())};
    menuPictures[35] = {150, 100,"Pictures/������/Hair4M.bmp",  txLoadImage(menuPictures[35].adress.c_str())};

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



    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
       // menuPictures[npic].image =  txLoadImage(menuPictures[npic].adress.c_str());

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

    CentralPictures[npic].adress = menuPictures[npic].adress;
    CentralPictures[npic].image = menuPictures[npic].image;
    CentralPictures[npic].w =  menuPictures[npic].w;
    CentralPictures[npic].h = menuPictures[npic].h;
    CentralPictures[npic].w_scr = CentralPictures[npic].w;
    CentralPictures[npic].h_scr = CentralPictures[npic].h;
    CentralPictures[npic].visible = menuPictures[npic].visible;
    CentralPictures[npic].category = menuPictures[npic].category;
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
