#pragma once
#include <Windows.h>
#include <wingdi.h>
#include "Q_Rect.h"
#include "ColorsName.h"
#include "Asserts.h"
#include "M_HDC.h"
#include <time.h>
#include <vector>
using namespace std;


struct AbstractAppData* appData = NULL;

struct AbstractAppData
{
    const char* appVersion = NULL;
    HWND MAINWINDOW = NULL;
    HICON appIcon = NULL;
    HCURSOR activeCursor = NULL;
    int lastTimeCursorSetTime = NULL;
    struct Manager* mainManager = NULL;

    
    bool filesCompability = true;
    struct CSystemSettings* systemSettings = NULL;
    struct CLoadManager* loadManager = NULL;
    struct CFileSavings* fileSavings = NULL;
    struct DCManager* dcManager = NULL;
    
    struct CWindowsLibApi* windowsLibApi = NULL;    
    struct CLoadLib* loadLibManager = NULL;
    struct HGDIManager* hgdiManager = NULL;
    struct TimerManager* timerManager = NULL;
    struct MSGReaction* msgReaction = NULL;
    virtual M_HDC* getHDC();
    virtual M_HGDIOBJ* getHGDIOBJ();

    COLORREF* currColor = NULL;
    bool isResized = false;
    int IsRunning = false;
    bool isShowing = true;
    HCURSOR defaultCursor = NULL;
    HINSTANCE hInstance;

    M_HDC testDC;

    AbstractAppData(HINSTANCE _instance);
    ~AbstractAppData();

    virtual int startApp();

    virtual void setWindowParameters(HINSTANCE hInstance);
    virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {};
    virtual int needToLoadOldFiles();

    virtual struct Manager* setMainManager(struct Manager* newManager);

    virtual int getAppCondition();
    virtual void setAppCondition(int newCondition);

    virtual int makeDir(const char* path);

    virtual void setColor(COLORREF color, M_HDC& dc, int thickness = 1);
    virtual int getColorComponent(COLORREF color, COLORREF component);
    virtual void setDrawColor(COLORREF color);
    virtual COLORREF getPixel(Vector pos, HDC dc);
    virtual int setPixel(Vector pos, COLORREF _color, HDC dc);
    virtual COLORREF HSL2RGB(COLORREF HSL);
    virtual COLORREF RGB2HSL(COLORREF rgbColor);

    virtual int updateScreen(struct Window* window);
    virtual int updateNonClientAreaScreen(struct Window* window);
    virtual int invalidateRect(struct Window* window, Rect _rect, bool _erase = false);
    virtual int captureMouse(HWND wnd = NULL);
    virtual int releaseMouse(HWND wnd = NULL);

    //+Function to draw figures
    virtual void rectangle(Rect rect, HDC dc);
    virtual void rectangle(double x1, double y1, double x2, double y2, HDC dc);
    virtual void rectangle(Vector pos1, Vector pos2, HDC dc);
    virtual void line(Rect rect, HDC dc);
    virtual void line(double x1, double y1, double x2, double y2, HDC dc);
    virtual void line(Vector pos1, Vector pos2, HDC dc);

    virtual void ellipse(Vector centrPos, Vector halfSize, HDC dc);
    virtual void ellipse(double x1, double y1, double x2, double y2, HDC dc);
    //-Function to draw figures

    virtual void drawOnScreen(HDC dc, bool useAlpha = false);
    virtual void cleanTransparentDC();
    virtual bool getAsyncKeyState(int symbol);
    virtual bool getKeyState(int symbol);
    virtual void deleteTransparency(RGBQUAD* buf, unsigned int totalSize);

    //+Functions with dc
    virtual void horizontalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {});
    virtual void verticalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {});

    virtual int stretchBlt(HDC dest, double destPosx, double destPosy, double destSizex, double destSizey, HDC source, double sourcePosx, double sourcePosy, double sourceSizex, double sourceSizey);
    virtual int stretchBlt(HDC dest, Vector destPos, Vector destSize, HDC source, Vector sourcePos, Vector sourceSize);
    virtual int stretchBlt(HDC dest, Rect destRect, HDC source, Rect sourceRecct);
    virtual void transparentBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0);
    virtual void transparentBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {});
    virtual void transparentBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {});
    virtual void bitBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0);
    virtual void bitBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {});
    virtual void bitBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {});
    virtual HDC getBufferDC(RGBQUAD** buf);

    virtual void compressImage(HDC& newDC, Vector newSize, HDC oldDC, Vector oldSize);

    virtual Vector getHDCSize(HDC _dc);
    virtual Vector getHBITMAPSize(HBITMAP _dc);

    virtual HDC createDIBSection(Vector size, RGBQUAD** pixels = NULL);
    virtual HDC createDIBSection(double sizex, double sizey, RGBQUAD** pixels = NULL);
    virtual void deleteDC(HDC dc);
    virtual int smartDeleteDC(HDC dc);
    //-Functions with dc

    virtual int messageBox(const char  text[] = "", const char  header[] = "", unsigned  flags = MB_ICONINFORMATION | MB_OKCANCEL);




    virtual void drawText(double x0, double y0, double x1, double y1, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    virtual void drawText(Rect rect, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    virtual Vector getTextExtent(const char* text, HDC finalDC);

    virtual void setAlign(unsigned align, HDC dc);
    virtual void selectFont(const char* text, int sizey, M_HDC& dc, int sizex = -1);

    virtual int saveImage(HDC dc, const char* path);
    int (*dllsaveImage) (HDC dc, const char* path) = NULL;
    HDC(*dllloadImage) (const char* path, Vector& _size, AbstractAppData* _app) = NULL;
    virtual int DEBUGsaveImage(HDC dc);
    virtual HDC loadImage(const char* path, Vector _size = {});

    virtual void drawCadre(Rect rect, M_HDC dc, COLORREF color, int thickness);
    virtual void drawCadre(Vector pos1, Vector pos2, M_HDC dc, COLORREF color, int thickness);
    virtual void drawCadre(int x1, int y1, int x2, int y2, M_HDC dc, COLORREF color, int thickness);

    virtual int isHDCValid(HDC _dc);

    virtual int setViewPort(HDC _dc, Vector newPos);
    virtual int getViewPort(HDC _dc, Vector* pos);

    

    virtual void changeWindow(Vector size = {}, Vector pos = {});
    virtual int moveWindowTo(Vector _pos, HWND _wnd);
    virtual int moveWindow(Vector _delta, HWND _wnd = 0);
    virtual Rect getWindowRect(HWND _wnd = 0);
    virtual void setCursor(HCURSOR cursor = NULL);
    virtual Vector getCursorPos();

    virtual void setResized(bool state = true);
    virtual bool isFullScreen();


    virtual long lround(double num);

    virtual Vector getCentrizedPos(Vector localSize, Vector globalSize);
    virtual void shiftArrBack(char* arr, int oneItemSize, int firstPosOfShifting, int finishPosOfShifting);

    virtual char* getSaveFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "");
    virtual char* getOpenFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "");

    //logic part of engine
    virtual int declareReactionOnMSG(int reaction = 0);//reaction = 0 on default
    virtual int getReactionOnMSG();
    virtual int beforeMessage();


    virtual Rect getUserRect();
};