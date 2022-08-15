#pragma once


void RECTangle(const Rect rect, HDC dc = txDC());
void shiftArrBack(char arr[], int length);
void shiftArrForward(char arr[], int length);

/*
struct TimeButton : Window
{
    int font;
    TimeButton (AbstractAppData* _app, Rect _rect, COLORREF _color = TX_RED, int _font = NULL)	:
        Window (_app, _rect, _color),
        font (_font)
    {
        if (!font) font = _app->systemSettings->MainFont;
    }

    virtual void draw () override;
};





*/





void RECTangle(const Rect rect, HDC dc /* = txDc ()*/)
{
    assert(dc);
    //app->rectangle (rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, dc);
}

/*
void TimeButton::draw ()
{
    if (manager)app->setColor (manager->color, finalDC);
    app->rectangle(0, 0, getSize().x, getSize().y, finalDC);
    time_t t = time (NULL);
    t = t % (24 * 3600);

    char newStr[50] = {};
    int hours =	t / 3600;
    int minutes = t / 60 - hours * 60;
    int second  = t - hours * 3600 - minutes * 60;

    sprintf (newStr, "%d:%02d:%02d", hours + 3, minutes, second);

    app->setAlign (TA_LEFT, finalDC);
    app->setColor (color, finalDC);
    app->selectFont("Arial", font, finalDC);
    app->drawText (0, 0, getSize().x, getSize().y, newStr, finalDC);
    //app->drawOnScreen(finalDC);

}
*/



int min(int a, int b)
{
    if (a > b) return b;
    else return a;
}

void bitBlt(RGBQUAD* dest, int x, int y, int sizeX, int sizeY, RGBQUAD* source, int originalSizeX, int originalSizeY, int sourceSizeX, int sourceSizeY)
{
    for (int i = 0; i < min(sizeX, sourceSizeX); i++)
    {
        for (int j = 0; j < min(sizeY, sourceSizeY); j++)
        {
            if (j + y < originalSizeY && i + x < originalSizeX && j + y >= 0 && i + x >= 0)
            {
                //if ( j == 249) _getch ();
                RGBQUAD* destCopy = &dest[i + (originalSizeY - (j + y) - 1) * originalSizeX + x];
                RGBQUAD* sourceCopy = &source[i + (sourceSizeY - j - 1) * sourceSizeX];

                sourceCopy->rgbReserved = 255;

                //if (sourceCopy->rgbReserved != 255) _getch ();

                destCopy->rgbRed = sourceCopy->rgbRed * ((float)sourceCopy->rgbReserved / 255.0);
                destCopy->rgbGreen = sourceCopy->rgbGreen * ((float)sourceCopy->rgbReserved / 255.0);
                destCopy->rgbBlue = sourceCopy->rgbBlue * ((float)sourceCopy->rgbReserved / 255.0);
                destCopy->rgbReserved = 255;

                //txSetPixel (i, j, RGB (sourceCopy->rgbRed, sourceCopy->rgbGreen, sourceCopy->rgbBlue));
                //txSetPixel (i, j, RGB (dest[i + (sizeY - (j + y) - 1) * sizeX + x].rgbRed, dest[i + (sizeY - (j + y) - 1) * sizeX + x].rgbGreen, dest[i + (sizeY - (j + y) - 1) * sizeX + x].rgbBlue));

                continue;
            }

        }
    }
}


void shiftArrForward(char arr[], int length)
{
    assert(arr);
    char copyChar = arr[0];

    for (int i = 1; i < length; i++)
    {
        char rememberArr = arr[i];
        arr[i] = copyChar;
        copyChar = rememberArr;
    }
}

void shiftArrBack(char arr[], int length)
{

    assert(arr);
    char copyChar = '\0';

    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            arr[i] = '\0';
        }
        else
        {
            arr[i] = arr[i + 1];
        }

    }
}

