#pragma once
#include "SystemSettings.h"
#include "AbstractApp.h"


CSystemSettings::CSystemSettings(struct AbstractAppData* _app) :
    app(_app)
    //MINSCREENSIZE({300, 100})
{
    setDefaultSettings();
    read("Settings\\FullSettings.settings");
    setDynamicSettings(_app);
    readUserSettings("Settings\\Settings.txt");
}


CSystemSettings::~CSystemSettings()
{
    save("Settings\\FullSettings.settings");
    saveUserSettings("Settings\\Settings.txt");
}

int CSystemSettings::save(const char* path)
{
    FILE* ssFile = fopen(path, "wb");
    if (!ssFile)
    {
        printf("Файл не открылся\n");
        return 1;
    }

    (void)fwrite(this, sizeof(char), byteSize, ssFile);

    fclose(ssFile);
    return 0;
}

int CSystemSettings::saveUserSettings(const char* path)
{
    assert(path);
    FILE* ssFile = fopen(path, "w");
    if (!ssFile)
    {
        printf("Сохранение всех данных не прошло||Errno: %d\n", errno);
        return (int)ssFile;
    }

    saveIntSettings(ssFile, &MainFont, "MainFont");
    saveStringSettings(ssFile, FONTNAME, "FONTNAME");

    saveIntSettings(ssFile, &debugMode, "debugMode");

    saveIntSettings(ssFile, &Thickness, "Thickness");

    saveIntSettings(ssFile, &WindowStyle, "WindowStyle");

    saveDoubleSettings(ssFile, &SizeOfScreen.x, "SizeOfScreen.x");
    saveDoubleSettings(ssFile, &SizeOfScreen.y, "SizeOfScreen.y");

    fclose(ssFile);

    return (int)ssFile;
}



int CSystemSettings::read(const char* path)
{
    //if (access(path, 0) == -1) return 1;
    FILE* ssFile = fopen(path, "rb");

    long fileSize = app->getFileSize(ssFile);

    if (fileSize != byteSize)
    {
        printf("Размеры загружаемой структуры не совпал с нынешней\n");
        return 1;
    }

    
    if (!ssFile || !app->needToLoadOldFiles())
    {
        printf("Файл не открылся\n");
        return 1;
    }

    (void)fread(this, sizeof(char), byteSize, ssFile);

    fclose(ssFile);

    return 0;
}

int CSystemSettings::readUserSettings(const char* path)
{
    assert(path);
    FILE* ssFile = fopen(path, "r");
    if (!ssFile || !app->needToLoadOldFiles())
    {
        printf("Системные настройки не загрузились\n");
        return 1;
    }
    setIntSettings(ssFile, &MainFont, "MainFont");
    setStringSettings(ssFile, FONTNAME, "FONTNAME");

    setIntSettings(ssFile, &debugMode, "debugMode");

    setIntSettings(ssFile, &Thickness, "Thickness");

    setIntSettings(ssFile, &WindowStyle, "WindowStyle");

    setDoubleSettings(ssFile, &SizeOfScreen.x, "SizeOfScreen.x");
    setDoubleSettings(ssFile, &SizeOfScreen.y, "SizeOfScreen.y");

    fclose(ssFile);
    
    return 0;

}


void CSystemSettings::setDefaultSettings()
{
    if (!this)
    {
        printf("systemSettings не существует дефолтные параметры не установились.\n");
        return;
    }
    setDynamicSettings(app);

    WindowStyle = WS_OVERLAPPEDWINDOW;

    MenuColor = RGB(45, 45, 45);
    SecondMenuColor = RGB(30, 30, 30);
    onMouseColor = RGB(100, 100, 100);
    TextColor = RGB(255, 255, 255);
    BackgroundColor = RGB(255, 255, 255);
    DrawColor = RGB(255, 0, 0);
    TRANSPARENTCOLOR = RGB (57, 57, 57);

    ONELAYTOOLSLIMIT = 100;

    MainFont = 20;
    strcpy(FONTNAME, "Arial");
    TEXTFORMAT = DT_SINGLELINE | DT_VCENTER | DT_CENTER;

    HANDLEHEIGHT = 25.000000;
    BUTTONWIDTH = 50.000000;
    BUTTONHEIGHT = 50.000000;
    MENUBUTTONSWIDTH = 50.000000;
    SIDETHICKNESS = 2.000000;
    SCROLLBARTHICKNESS = 20.000000;
    FrameThickness = 6;

    debugMode = -1;

    SizeOfScreen.x = 1280.000000;
    SizeOfScreen.y = 720.000000;

    WindowStyle = -2146959360;

    DCMAXSIZE = 1000;

    DCVECTORSIZE.x = 1000.000000;
    DCVECTORSIZE.y = 1000.000000;
}

void CSystemSettings::setDynamicSettings(struct AbstractAppData* _app)
{
    FullSizeOfScreen = { .x = (double)GetSystemMetrics(SM_CXSCREEN), .y = (double)GetSystemMetrics(SM_CYSCREEN) };
    app = _app;
    int res = GetSystemMetrics(SM_CYCAPTION);
    HANDLEHEIGHT = GetSystemMetrics(SM_CYCAPTION);
}


void CSystemSettings::setColorSettings(FILE* ssFile, COLORREF* color, const char* name)
{
    char format[MAX_PATH] = {};

    sprintf(format, " %s = %%s ", name);

    char data[MAX_PATH] = {};
    (void)fscanf(ssFile, format, data);

    int resultOfComparision = strcmp(data, "RGB");

    if (resultOfComparision >= 0)
    {
        int red = 0;
        int green = 0;
        int blue = 0;
        (void)fscanf(ssFile, " (%d, %d, %d); ", &red, &green, &blue);
        *color = RGB(red, green, blue);
    }
    else
    {
        COLORREF _color = 0;

        for (int i = 0; ; i++)
        {
            int number = (data[i] - '0');
            if (abs(number) > 9) break;

            _color = _color * 10 + number;
        }

        if (_color)*color = _color;
    }
}

void CSystemSettings::setIntSettings(FILE* ssFile, int* integer, const char* name)
{
    char format[MAX_PATH] = {};
    sprintf(format, " %s = %%d; ", name);

    (void)fscanf(ssFile, format, integer);

}

void CSystemSettings::setDoubleSettings(FILE* ssFile, double* integer, const char* name)
{
    char format[MAX_PATH] = {};
    sprintf(format, " %s = %%lf; ", name);

    (void)fscanf(ssFile, format, integer);

}

void CSystemSettings::setStringSettings(FILE* ssFile, char* str, const char* name)
{
    char format[MAX_PATH] = {};
    sprintf(format, " %s = %%s; ", name);

    char finalStr[MAX_PATH] = {};
    (void)fscanf(ssFile, format, finalStr);

    for (int i = 0; i < MAX_PATH; i++)
    {
        if (finalStr[i] == ';') 
        {
            finalStr[i] = NULL;
            break;
        }
    }
    strcpy (str, finalStr);
}


void CSystemSettings::saveColorSettings(FILE* ssFile, COLORREF* color, const char* name)
{
    int red = GetRValue(*color);
    int green = GetGValue(*color);
    int blue = GetBValue(*color);
    fprintf (ssFile, "%s = RGB (%d, %d, %d);\n", name, red, green, blue);
}

void CSystemSettings::saveIntSettings(FILE* ssFile, int* integer, const char* name)
{
    fprintf(ssFile, "%s = %d;\n", name, *integer);
}

void CSystemSettings::saveDoubleSettings(FILE* ssFile, double* integer, const char* name)
{
    fprintf(ssFile, "%s = %lf;\n", name, *integer);
}

void CSystemSettings::saveStringSettings(FILE* ssFile, char* str, const char* name)
{
    fprintf(ssFile, "%s = %s;\n", name, str);
}