#include "TXLib.h"
#include "dirent.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

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
    string adress;
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
       txMouseX() <= btn.x + 150  &&
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

int readFromDir(string adress, Pictures menuPictures[], int COUNT_PICTURE)
{
    DIR  * dir;
    struct dirent *ent;
    int lastY = 100;
     if((dir = opendir (adress.c_str())) != NULL)
     {
         while ((ent = readdir (dir))!= NULL)
         {
             if((string)ent->d_name != "." && (string)ent->d_name != "..")
             {
                 menuPictures[COUNT_PICTURE].y  = lastY;
                 menuPictures[COUNT_PICTURE].adress = adress + (string)ent->d_name;
                 COUNT_PICTURE++;
                 lastY +=50;
             }
         }
         closedir (dir);
     }
     return COUNT_PICTURE ;
}

string runFileDialog(bool isSave)
{
    string filename = "";
    OPENFILENAME ofn;
    TCHAR szFile[260] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = txWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = ("Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST |OFN_FILEMUSTEXIST;

    if (isSave)
    {
        if (GetSaveFileName(&ofn) == TRUE)
        {
            filename = ofn.lpstrFile;

            if (filename.find(".txt") > 1000)
            {
                filename = filename + ".txt";
            }
        }
    }
 else
 {
    if (GetOpenFileName(&ofn) == TRUE)
    {
        filename = ofn.lpstrFile;
    }
 }
    return filename;
}





const int COUNT_BTN = 7;
const int BTN_SAVE = COUNT_BTN - 2;
const int BTN_LOAD = COUNT_BTN - 1;


int main()
{
txCreateWindow (1200, 800);

txDisableAutoPause();

txTextCursor (false);

    int COUNT_PICTURE = 0;
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
    btn[5] = {1000, 50, "Сохранить" , ""};
    btn[6] = {1000, 100, "Загрузить" , ""};

    //Массив иконок-меню левых
    Pictures menuPictures[100];

    //Массив иконок центральных
    Pictures CentralPictures[100];

    COUNT_PICTURE = readFromDir("Pictures/Лицо/",  menuPictures, COUNT_PICTURE) ;
    COUNT_PICTURE = readFromDir("Pictures/Волосы/",  menuPictures, COUNT_PICTURE) ;
    COUNT_PICTURE = readFromDir("Pictures/Глаза/",  menuPictures, COUNT_PICTURE) ;
    COUNT_PICTURE = readFromDir("Pictures/Нос/",  menuPictures, COUNT_PICTURE) ;
    COUNT_PICTURE = readFromDir("Pictures/Губы/",  menuPictures, COUNT_PICTURE) ;


    for(int npic = 0; npic < COUNT_PICTURE; npic++)
    {
        menuPictures[npic].x = 50;
        menuPictures[npic].image = txLoadImage(menuPictures[npic].adress.c_str());

        menuPictures[npic].w = get_w(menuPictures[npic].adress);

        menuPictures[npic].h = get_h(menuPictures[npic].adress);


        int pos1 = menuPictures[npic].adress.find("/");
        int pos2 = menuPictures[npic].adress.find("/", pos1+1);
        menuPictures[npic].category = menuPictures[npic].adress.substr(pos1+1, pos2-pos1-1);


        if(menuPictures[npic].category == "Нос")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "Лицо")
        {
            menuPictures[npic].w_scr = 47;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "Губы")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 50;
        }

        if(menuPictures[npic].category == "Глаза")
        {
            menuPictures[npic].w_scr = 50;
            menuPictures[npic].h_scr = 16;
        }

        if(menuPictures[npic].category == "Волосы")
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

        if(CentralPictures[npic].category == "Лицо")
            {
                CentralPictures[npic].x = 600;
                CentralPictures[npic].y = 300;
            }

        if(CentralPictures[npic].category == "Нос")
            {
                CentralPictures[npic].x = 755;
                CentralPictures[npic].y = 500;
            }

        if(CentralPictures[npic].category == "Губы")
            {
                CentralPictures[npic].x = 755;
                CentralPictures[npic].y = 600;
            }

        if(CentralPictures[npic].category == "Глаза")
            {
                CentralPictures[npic].x = 700;
                CentralPictures[npic].y = 465;
            }

        if(CentralPictures[npic].category == "Волосы")
            {
                CentralPictures[npic].x = 600;
                CentralPictures[npic].y = 275;
               // CentralPictures[npic].w_scr = 755;
               // CentralPictures[npic].h_scr = 500;
            }
    }

while(!GetAsyncKeyState(VK_ESCAPE))
{
    txBegin();
    txSetColor (TX_WHITE);
    txSetFillColor (TX_WHITE);
    txClear();

    //Рисование кнопок
    for(int nk=0; nk<COUNT_BTN; nk++)
    {
        drawButton(btn[nk]);
    }

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

    sprintf(str, "count= %d; vybor= %d ", COUNT_PICTURE, select);
    //txTextOut(0,0,str);

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

    if(Click(btn[BTN_SAVE]))
    {
        string filename  = runFileDialog(true);
        if (filename != "")
            {
            ofstream fout;

            fout.open(filename);

            for (int npic = 0; npic < COUNT_PICTURE; npic++)
            {
                if (CentralPictures[npic].visible)
                {
                    fout << CentralPictures[npic].x << endl;
                    fout << CentralPictures[npic].y << endl;
                    fout << CentralPictures[npic].adress << endl;
                }
            }
            fout.close();

            txMessageBox ("Сохранено", "Спасибо" , MB_ICONINFORMATION);
        }
    }



    if(Click(btn[BTN_LOAD]))
    {
    string filename  = runFileDialog(true);
        if (filename != "")
        {
            for (int npic = 0; npic < COUNT_PICTURE; npic++)
            {
                CentralPictures[npic].visible = false;
            }

        char buff[50];
        ifstream fin(filename);
            while (fin.good())
            {
                fin.getline(buff , 50);
                int x = atoi(buff);
                fin.getline(buff , 50);
                int y = atoi(buff);
                fin.getline(buff , 50);
                string adress = (buff);

                for (int npic = 0; npic < COUNT_PICTURE; npic++)
                {
                    if (CentralPictures[npic].adress == adress)
                    {
                        CentralPictures[npic].x = x;
                        CentralPictures[npic].y = y;
                        CentralPictures[npic].visible = true;
                    }
                }
            }
            fin.close();
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
