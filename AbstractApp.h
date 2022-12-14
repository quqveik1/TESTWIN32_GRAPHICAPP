#pragma once
#include <Windows.h>
#include "Q_Rect.h"
#include "ColorsName.h"
#include "Asserts.h"
#include "M_HDC.h"
#include <time.h>
#include <vector>
using namespace std;


struct AbstractAppData
{
    const char* appVersion = NULL;
    HWND MAINWINDOW = NULL;
    HICON appIcon = NULL;

    bool filesCompability = true;

    struct CSystemSettings* systemSettings = NULL;
    struct CToolManager* toolManager = NULL;
    struct CLoadManager* loadManager = NULL;
    struct CFileSavings* fileSavings = NULL;
    struct CanvasManager* canvasManager = NULL;
    struct CWindowsLibApi* windowsLibApi = NULL;    
    struct CLoadLib* loadLibManager = NULL;
    struct ConsoleOutput* consoleOutput = NULL;
    struct HGDIManager* hgdiManager = NULL;
    struct TimerManager* timerManager = NULL;
    virtual M_HDC* getHDC() = 0;
    virtual M_HGDIOBJ* getHGDIOBJ() = 0;

    COLORREF* currColor = NULL;
    bool isResized = false;
    bool IsRunning = false;
    bool isShowing = true;;
    HCURSOR defaultCursor = NULL;

    M_HDC testDC;

    virtual int makeDir(const char* path) = 0;

    virtual void setColor(COLORREF color, M_HDC& dc, int thickness = 1) = 0;
    virtual int getColorComponent(COLORREF color, COLORREF component) = 0;
    virtual void setDrawColor(COLORREF color) = 0;
    virtual COLORREF getPixel(Vector pos, HDC dc) = 0;
    virtual int setPixel(Vector pos, COLORREF _color, HDC dc) = 0;
    virtual COLORREF HSL2RGB(COLORREF HSL) = 0;
    virtual COLORREF RGB2HSL(COLORREF rgbColor) = 0;

    virtual int updateScreen(struct Window* window) = 0;
    virtual int updateNonClientAreaScreen(struct Window* window) = 0;
    virtual int invalidateRect(struct Window* window, Rect _rect, bool _erase = false) = 0;
    virtual int captureMouse(HWND wnd = NULL) = 0;
    virtual int releaseMouse(HWND wnd = NULL) = 0;

    //+Function to draw figures
    virtual void rectangle(Rect rect, HDC dc) = 0;
    virtual void rectangle(double x1, double y1, double x2, double y2, HDC dc) = 0;
    virtual void rectangle(Vector pos1, Vector pos2, HDC dc) = 0;
    virtual void line(Rect rect, HDC dc) = 0;
    virtual void line(double x1, double y1, double x2, double y2, HDC dc) = 0;
    virtual void line(Vector pos1, Vector pos2, HDC dc) = 0;

    virtual void ellipse(Vector centrPos, Vector halfSize, HDC dc) = 0;
    virtual void ellipse(double x1, double y1, double x2, double y2, HDC dc) = 0;
    //-Function to draw figures

    virtual void drawOnScreen(HDC dc, bool useAlpha = false) = 0;
    virtual void cleanTransparentDC() = 0;
    virtual bool getAsyncKeyState(int symbol) = 0;
    virtual bool getKeyState(int symbol) = 0;
    virtual bool isDoubleClick() = 0;
    virtual void deleteTransparency(RGBQUAD* buf, unsigned int totalSize) = 0;

    virtual int needToLoadOldFiles() = 0;

    //+Functions with dc
    virtual void horizontalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {}) = 0;
    virtual void verticalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {}) = 0;

    virtual int stretchBlt(HDC dest, double destPosx, double destPosy, double destSizex, double destSizey, HDC source, double sourcePosx, double sourcePosy, double sourceSizex, double sourceSizey) = 0;
    virtual int stretchBlt(HDC dest, Vector destPos, Vector destSize, HDC source, Vector sourcePos, Vector sourceSize) = 0;
    virtual int stretchBlt(HDC dest, Rect destRect, HDC source, Rect sourceRecct) = 0;
    virtual void transparentBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0) = 0;
    virtual void transparentBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {}) = 0;
    virtual void transparentBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {}) = 0;
    virtual void bitBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0) = 0;
    virtual void bitBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {}) = 0;
    virtual void bitBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {}) = 0;
    virtual HDC getBufferDC(RGBQUAD** buf) = 0;

    virtual void compressImage(HDC& newDC, Vector newSize, HDC oldDC, Vector oldSize) = 0;

    virtual Vector getHDCSize(HDC _dc) = 0;
    virtual Vector getHBITMAPSize(HBITMAP _dc) = 0;

    virtual HDC createDIBSection(Vector size, RGBQUAD** pixels = NULL) = 0;
    virtual HDC createDIBSection(double sizex, double sizey, RGBQUAD** pixels = NULL) = 0;
    virtual void deleteDC(HDC dc) = 0;
    virtual int smartDeleteDC(HDC dc) = 0;
    //-Functions with dc

    virtual int messageBox(const char  text[] = "", const char  header[] = "", unsigned  flags = MB_ICONINFORMATION | MB_OKCANCEL) = 0;




    virtual void drawText(double x0, double y0, double x1, double y1, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE) = 0;
    virtual void drawText(Rect rect, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE) = 0;
    virtual Vector getTextExtent(const char* text, HDC finalDC) = 0;

    virtual void setAlign(unsigned align, HDC dc) = 0;
    virtual void selectFont(const char* text, int sizey, M_HDC& dc, int sizex = -1) = 0;

    virtual int saveImage(HDC dc, const char* path) = 0;
    virtual int DEBUGsaveImage(HDC dc) = 0;
    virtual HDC loadImage(const char* path, Vector _size = {}) = 0;

    virtual void drawCadre(Rect rect, M_HDC dc, COLORREF color, int thickness) = 0;
    virtual void drawCadre(Vector pos1, Vector pos2, M_HDC dc, COLORREF color, int thickness) = 0;
    virtual void drawCadre(int x1, int y1, int x2, int y2, M_HDC dc, COLORREF color, int thickness) = 0;

    virtual int isHDCValid(HDC _dc) = 0;

    virtual int setViewPort(HDC _dc, Vector newPos) = 0;
    virtual int getViewPort(HDC _dc, Vector* pos) = 0;

    

    virtual void changeWindow(Vector size = {}, Vector pos = {}) = 0;
    virtual int moveWindowTo(Vector _pos, HWND _wnd = 0) = 0;
    virtual int moveWindow(Vector _delta, HWND _wnd = 0) = 0;
    virtual Rect getWindowRect(HWND _wnd = 0) = 0;
    virtual void setCursor(HCURSOR cursor = NULL) = 0;
    virtual Vector getCursorPos() = 0;

    virtual void setResized(bool state = true) = 0;
    virtual bool wasResized() = 0;
    virtual bool isFullScreen() = 0;


    virtual long lround(double num) = 0;

    virtual Vector getCentrizedPos(Vector localSize, Vector globalSize) = 0;
    virtual void shiftArrBack(char* arr, int oneItemSize, int firstPosOfShifting, int finishPosOfShifting) = 0;

    virtual char* getSaveFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "") = 0;
    virtual char* getOpenFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "") = 0;


    virtual int declareReactionOnMSG(int reaction = 0) = 0;//reaction = 0 on default
    virtual int getReactionOnMSG() = 0;

    virtual Rect getUserRect() = 0;
};