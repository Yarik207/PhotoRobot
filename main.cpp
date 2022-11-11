#include "TXLib.h"

//Структура Кнопки
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

//Функция рисования кнопки
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

    int COUNT_BTN = 5;
    int COUNT_PICTURE = 36;
    int select = -1;
    bool mouse_free = false;
    char str[100];

    //Массив кнопок
    Button btn[COUNT_BTN];
    btn[0] = {100, 50,"Овал лица", "Лицо"};
    btn[1] = {260, 50,"Стрижка", "Волосы"};
    btn[2] = {420, 50,"Разрез Глаз", "Глаза"};
    btn[3] = {580, 50,"Нос", "Нос"};
    btn[4] = {740, 50,"Губы", "Губы"};

    //Массив иконок-меню левых
    Pictures menuPictures[COUNT_PICTURE];
    menuPictures[0] = {50, 100, txLoadImage ("Pictures/Нос/nose1.bmp"), 100, 100, 50, 50, "Нос", false};
    menuPictures[1] = {50, 200, txLoadImage ("Pictures/Нос/nose2.bmp"), 100, 100, 50, 50, "Нос", false};
    menuPictures[2] = {50, 300, txLoadImage ("Pictures/Нос/nose3.bmp"), 100, 125, 50, 50, "Нос", false};
    menuPictures[3] = {50, 400, txLoadImage ("Pictures/Нос/nose4.bmp"), 59, 100, 50, 50,  "Нос", false};
    menuPictures[4] = {50, 500, txLoadImage ("Pictures/Нос/nose5.bmp"), 100, 116, 50, 50, "Нос", false};
    menuPictures[5] = {50, 600, txLoadImage ("Pictures/Нос/nose6.bmp"), 62, 100, 50, 50,  "Нос", false};

    menuPictures[6]  = {50, 100, txLoadImage ("Pictures/Овал лица/face1M.bmp"), 94, 100, 94, 100,  "Лицо", false};
    menuPictures[7]  = {50, 200, txLoadImage ("Pictures/Овал лица/face2M.bmp"), 97, 100, 94, 100,  "Лицо", false};
    menuPictures[8]  = {50, 300, txLoadImage ("Pictures/Овал лица/face3M.bmp"), 70, 100, 94, 100,  "Лицо", false};
    menuPictures[9]  = {50, 400, txLoadImage ("Pictures/Овал лица/face4M.bmp"), 100, 136, 94, 100, "Лицо", false};
    menuPictures[10] = {50, 500, txLoadImage ("Pictures/Овал лица/face5M.bmp"), 100, 115, 94, 100, "Лицо", false};
    menuPictures[11] = {50, 600, txLoadImage ("Pictures/Овал лица/face6M.bmp"), 100, 131, 94, 100, "Лицо", false};

    menuPictures[12] = {50, 100, txLoadImage ("Pictures/Губы/lips1.bmp"), 100, 57, 100, 100, "Губы", false};
    menuPictures[13] = {50, 200, txLoadImage ("Pictures/Губы/lips2.bmp"), 100, 54, 100, 100, "Губы", false};
    menuPictures[14] = {50, 300, txLoadImage ("Pictures/Губы/lips3.bmp"), 100, 51, 100, 100, "Губы", false};
    menuPictures[15] = {50, 400, txLoadImage ("Pictures/Губы/lips4.bmp"), 100, 50, 100, 100, "Губы", false};
    menuPictures[16] = {50, 500, txLoadImage ("Pictures/Губы/lips5.bmp"), 100, 51, 100, 100, "Губы", false};
    menuPictures[17] = {50, 600, txLoadImage ("Pictures/Губы/lips6.bmp"), 100, 51, 100, 100, "Губы", false};
    menuPictures[18] = {50, 700, txLoadImage ("Pictures/Губы/lips7.bmp"), 100, 33, 100, 100, "Губы", false};
    menuPictures[19] = {150, 100, txLoadImage ("Pictures/Губы/lips8.bmp"), 100, 46, 100, 100, "Губы", false};

    menuPictures[20] = {50, 100, txLoadImage ("Pictures/Женский/Глаза/eyes1G.bmp"), 100, 35, 100, 35, "Глаза", false};
    menuPictures[21] = {50, 200, txLoadImage ("Pictures/Женский/Глаза/eyes2G.bmp"), 100, 39, 100, 39, "Глаза", false};
    menuPictures[22] = {50, 300, txLoadImage ("Pictures/Женский/Глаза/eyes3G.bmp"), 100, 37, 100, 37, "Глаза", false};
    menuPictures[23] = {50, 400, txLoadImage ("Pictures/Женский/Глаза/eyes4G.bmp"), 100, 27, 100, 27, "Глаза", false};
    menuPictures[24] = {50, 500, txLoadImage ("Pictures/Мужской/Глаза/eyes1M.bmp"), 100, 46, 100, 46, "Глаза", false};
    menuPictures[25] = {50, 600, txLoadImage ("Pictures/Мужской/Глаза/eyes2M.bmp"), 100, 38, 100, 38, "Глаза", false};
    menuPictures[26] = {50, 700, txLoadImage ("Pictures/Мужской/Глаза/eyes3M.bmp"), 100, 33, 100, 33, "Глаза", false};
    menuPictures[27] = {150, 100, txLoadImage ("Pictures/Мужской/Глаза/eyes4M.bmp"), 100, 32, 100, 32, "Глаза", false};

    menuPictures[28] = {50, 100, txLoadImage ("Pictures/Женский/Челка/Hair1G.bmp"), 100, 108, 100, 108, "Волосы", false};
    menuPictures[29] = {50, 200, txLoadImage ("Pictures/Женский/Челка/Hair2G.bmp"), 100, 102, 100, 102, "Волосы", false};
    menuPictures[30] = {50, 300, txLoadImage ("Pictures/Женский/Челка/Hair3G.bmp"), 100, 105, 100, 105, "Волосы", false};
    menuPictures[31] = {50, 400, txLoadImage ("Pictures/Женский/Челка/Hair4G.bmp"), 100, 123, 100, 123, "Волосы", false};
    menuPictures[32] = {50, 500, txLoadImage ("Pictures/Мужской/Челка/Hair1M.bmp"), 100, 82,  100, 82, "Волосы", false};
    menuPictures[33] = {50, 600, txLoadImage ("Pictures/Мужской/Челка/Hair2M.bmp"), 100, 90,  100, 90, "Волосы", false};
    menuPictures[34] = {50, 700, txLoadImage ("Pictures/Мужской/Челка/Hair3M.bmp"), 100, 91,  100, 91, "Волосы", false};
    menuPictures[35] = {150, 100, txLoadImage ("Pictures/Мужской/Челка/Hair4M.bmp"), 100, 86,  100, 86, "Волосы", false};

    //Массив иконок центральных
    Pictures CentralPictures[COUNT_PICTURE];
    CentralPictures[0]  =  {600, 200, menuPictures[0].image , menuPictures[0].w, menuPictures[0].h, menuPictures[0].w_scr, menuPictures[0].h_scr, menuPictures[0].category, menuPictures[0].visible};
    CentralPictures[1]  =  {600, 200, menuPictures[1].image , menuPictures[1].w, menuPictures[1].h, menuPictures[1].w_scr, menuPictures[1].h_scr, menuPictures[1].category, menuPictures[1].visible};
    CentralPictures[2]  =  {600, 200, menuPictures[2].image , menuPictures[2].w, menuPictures[2].h, menuPictures[2].w_scr, menuPictures[2].h_scr, menuPictures[2].category, menuPictures[2].visible};
    CentralPictures[3]  =  {600, 200, menuPictures[3].image , menuPictures[3].w, menuPictures[3].h, menuPictures[3].w_scr, menuPictures[3].h_scr, menuPictures[3].category, menuPictures[3].visible};
    CentralPictures[4]  =  {600, 200, menuPictures[4].image , menuPictures[4].w, menuPictures[4].h, menuPictures[4].w_scr, menuPictures[4].h_scr, menuPictures[4].category, menuPictures[4].visible};
    CentralPictures[5]  =  {600, 200, menuPictures[5].image , menuPictures[5].w, menuPictures[5].h, menuPictures[5].w_scr, menuPictures[5].h_scr, menuPictures[5].category, menuPictures[5].visible};

    CentralPictures[6]  =  {600, 300, menuPictures[6].image , menuPictures[6].w, menuPictures[6].h, menuPictures[6].w_scr, menuPictures[6].h_scr, menuPictures[6].category, menuPictures[5].visible};
    CentralPictures[7]  =  {600, 300, menuPictures[7].image , menuPictures[7].w, menuPictures[7].h, menuPictures[7].w_scr, menuPictures[7].h_scr, menuPictures[7].category, menuPictures[6].visible};
    CentralPictures[8]  =  {600, 300, menuPictures[8].image , menuPictures[8].w, menuPictures[8].h, menuPictures[8].w_scr, menuPictures[8].h_scr, menuPictures[8].category, menuPictures[7].visible};
    CentralPictures[9]  =  {600, 300, menuPictures[9].image , menuPictures[9].w, menuPictures[9].h, menuPictures[9].w_scr, menuPictures[9].h_scr, menuPictures[9].category, menuPictures[8].visible};
    CentralPictures[10] = {600, 300, menuPictures[10].image , menuPictures[10].w, menuPictures[10].h, menuPictures[10].w_scr, menuPictures[10].h_scr, menuPictures[10].category, menuPictures[10].visible};
    CentralPictures[11] = {600, 300, menuPictures[11].image , menuPictures[11].w, menuPictures[11].h, menuPictures[11].w_scr, menuPictures[11].h_scr, menuPictures[11].category, menuPictures[11].visible};

    CentralPictures[12] = {600, 400, menuPictures[12].image , menuPictures[12].w, menuPictures[12].h, menuPictures[12].w_scr, menuPictures[12].h_scr, menuPictures[12].category, menuPictures[12].visible};
    CentralPictures[13] = {600, 400, menuPictures[13].image , menuPictures[13].w, menuPictures[13].h, menuPictures[13].w_scr, menuPictures[13].h_scr, menuPictures[13].category, menuPictures[13].visible};
    CentralPictures[14] = {600, 400, menuPictures[14].image , menuPictures[14].w, menuPictures[14].h, menuPictures[14].w_scr, menuPictures[14].h_scr, menuPictures[14].category, menuPictures[14].visible};
    CentralPictures[15] = {600, 400, menuPictures[15].image , menuPictures[15].w, menuPictures[15].h, menuPictures[15].w_scr, menuPictures[15].h_scr, menuPictures[15].category, menuPictures[15].visible};
    CentralPictures[16] = {600, 400, menuPictures[16].image , menuPictures[16].w, menuPictures[16].h, menuPictures[16].w_scr, menuPictures[16].h_scr, menuPictures[16].category, menuPictures[16].visible};
    CentralPictures[17] = {600, 400, menuPictures[17].image , menuPictures[17].w, menuPictures[17].h, menuPictures[17].w_scr, menuPictures[17].h_scr, menuPictures[17].category, menuPictures[17].visible};
    CentralPictures[18] = {600, 400, menuPictures[18].image , menuPictures[18].w, menuPictures[18].h, menuPictures[18].w_scr, menuPictures[18].h_scr, menuPictures[18].category, menuPictures[18].visible};
    CentralPictures[19] = {600, 400, menuPictures[19].image , menuPictures[19].w, menuPictures[19].h, menuPictures[19].w_scr, menuPictures[19].h_scr, menuPictures[19].category, menuPictures[19].visible};

    CentralPictures[20] = {600, 500, menuPictures[20].image , menuPictures[20].w, menuPictures[20].h, menuPictures[20].w_scr, menuPictures[20].h_scr, menuPictures[20].category, menuPictures[20].visible};
    CentralPictures[21] = {600, 500, menuPictures[21].image , menuPictures[21].w, menuPictures[21].h, menuPictures[21].w_scr, menuPictures[21].h_scr, menuPictures[21].category, menuPictures[21].visible};
    CentralPictures[22] = {600, 500, menuPictures[22].image , menuPictures[22].w, menuPictures[22].h, menuPictures[22].w_scr, menuPictures[22].h_scr, menuPictures[22].category, menuPictures[22].visible};
    CentralPictures[23] = {600, 500, menuPictures[23].image , menuPictures[23].w, menuPictures[23].h, menuPictures[23].w_scr, menuPictures[23].h_scr, menuPictures[23].category, menuPictures[23].visible};
    CentralPictures[24] = {600, 500, menuPictures[24].image , menuPictures[24].w, menuPictures[24].h, menuPictures[24].w_scr, menuPictures[24].h_scr, menuPictures[24].category, menuPictures[24].visible};
    CentralPictures[25] = {600, 500, menuPictures[25].image , menuPictures[25].w, menuPictures[25].h, menuPictures[25].w_scr, menuPictures[25].h_scr, menuPictures[25].category, menuPictures[25].visible};
    CentralPictures[26] = {600, 500, menuPictures[26].image , menuPictures[26].w, menuPictures[26].h, menuPictures[26].w_scr, menuPictures[26].h_scr, menuPictures[26].category, menuPictures[26].visible};
    CentralPictures[27] = {600, 500, menuPictures[27].image , menuPictures[27].w, menuPictures[27].h, menuPictures[27].w_scr, menuPictures[27].h_scr, menuPictures[27].category, menuPictures[27].visible};

    CentralPictures[28] = {600, 600, menuPictures[28].image , menuPictures[28].w, menuPictures[28].h, menuPictures[28].w_scr, menuPictures[28].h_scr, menuPictures[28].category, menuPictures[28].visible};
    CentralPictures[29] = {600, 600, menuPictures[29].image , menuPictures[29].w, menuPictures[29].h, menuPictures[29].w_scr, menuPictures[29].h_scr, menuPictures[29].category, menuPictures[29].visible};
    CentralPictures[30] = {600, 600, menuPictures[30].image , menuPictures[30].w, menuPictures[30].h, menuPictures[30].w_scr, menuPictures[30].h_scr, menuPictures[30].category, menuPictures[30].visible};
    CentralPictures[31] = {600, 600, menuPictures[31].image , menuPictures[31].w, menuPictures[31].h, menuPictures[31].w_scr, menuPictures[31].h_scr, menuPictures[31].category, menuPictures[31].visible};
    CentralPictures[32] = {600, 600, menuPictures[32].image , menuPictures[32].w, menuPictures[32].h, menuPictures[32].w_scr, menuPictures[32].h_scr, menuPictures[32].category, menuPictures[32].visible};
    CentralPictures[33] = {600, 600, menuPictures[33].image , menuPictures[33].w, menuPictures[33].h, menuPictures[33].w_scr, menuPictures[33].h_scr, menuPictures[33].category, menuPictures[33].visible};
    CentralPictures[34] = {600, 600, menuPictures[34].image , menuPictures[34].w, menuPictures[34].h, menuPictures[34].w_scr, menuPictures[34].h_scr, menuPictures[34].category, menuPictures[34].visible};
    CentralPictures[35] = {600, 600, menuPictures[35].image , menuPictures[35].w, menuPictures[35].h, menuPictures[35].w_scr, menuPictures[35].h_scr, menuPictures[35].category, menuPictures[35].visible};



while(!GetAsyncKeyState(VK_ESCAPE))
{
    txBegin();
    txSetColor (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txClear();


  //Левых картинок рисование
    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(menuPictures[npic]);
    }

    //Центральных картинок рисование
    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        drawPicture(CentralPictures[npic]);
    }

    //Центральных картинок рисование
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

    //Рисование кнопок
    for(int nk=0; nk<5; nk++)
    {
        drawButton(btn[nk]);
    }

   //Видимость левых по категориям кнопок
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

     //выбор центральной картинки
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

    //Передвижение центральной картинки выбранной клавишами
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

        //Передвижение центральной картинки выбранной  мыщкой
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

    //Удаление левых
    for(int npic=0;npic <COUNT_PICTURE; npic++)
   {
        txDeleteDC(menuPictures[npic].image);
   }

    //Удаление центральных
    for(int npic=0;npic <COUNT_PICTURE; npic++)
   {
        txDeleteDC(CentralPictures[npic].image);
   }

return 0;
}
