#pragma once
#include "Q_Vector.h"
#include <stdio.h>
#include "ColorsName.h"




struct CSystemSettings
{
    struct AbstractAppData* app = NULL;
    int WindowStyle = NULL;

    COLORREF MenuColor = NULL;
    COLORREF SecondMenuColor = NULL;
    COLORREF TextColor = NULL;
    COLORREF BackgroundColor = NULL;
    COLORREF onMouseColor = NULL;
    COLORREF DrawColor = NULL;
    COLORREF TRANSPARENTCOLOR = C_TRANSPARENT;
    int Thickness = 3;


    int ONELAYTOOLSLIMIT = NULL;


    int MainFont = NULL;
    char FONTNAME[256] = {};
    int TEXTFORMAT = NULL;// = DT_CENTER | DT_VCENTER | DT_SINGLELINE;

    double HANDLEHEIGHT = NULL;
    double BUTTONWIDTH = NULL;
    double BUTTONHEIGHT = NULL;
    double MENUBUTTONSWIDTH = NULL;
    double SIDETHICKNESS = NULL;
    double SCROLLBARTHICKNESS = NULL;
    double FrameThickness = NULL;

    int debugMode = NULL;
    int TOOLSNUM = NULL;

    Vector SizeOfScreen = {};
    Vector MINSCREENSIZE = {};
    Vector FullSizeOfScreen = {};
    Vector lastTimeSizeOfScreen = {};
    Vector ScreenPos = {};
    int DCMAXSIZE = NULL;
    Vector DCVECTORSIZE = {};


    void setColorSettings(FILE* ssFile, COLORREF* color, const char* name);
    void setIntSettings(FILE* ssFile, int* integer, const char* name);
    void setDoubleSettings(FILE* ssFile, double* integer, const char* name);
    void setStringSettings(FILE* ssFile, char* str, const char* name);


    void saveColorSettings(FILE* ssFile, COLORREF* color, const char* name);
    void saveIntSettings(FILE* ssFile, int* integer, const char* name);
    void saveDoubleSettings(FILE* ssFile, double* integer, const char* name);
    void saveStringSettings(FILE* ssFile, char* str, const char* name);

    int read(const char* path);
    int readUserSettings(const char* path);
    void setDynamicSettings(struct AbstractAppData* _app);
    void setDefaultSettings();


    int save(const char* path);
    int saveUserSettings(const char* path);
    
    int byteSize = sizeof(*this);

    CSystemSettings(struct AbstractAppData* _app);
    ~CSystemSettings();
};




