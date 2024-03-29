#pragma once
//depricated
#include "EngineAppApi.h"

struct App : EngineAppApi
{

    struct Manager* mainManager = NULL;
    struct DCManager* dcManager = NULL;
    struct Manager* handle = NULL;


    HCURSOR activeCursor = NULL;
    int lastTimeCursorSetTime = NULL;
    Vector sizeHistory[2] = {};

    int lastTimeLButtonClicked = 0;
    bool wasLastTimeLButtonClicked = 0;
    bool dClick = 0;

    virtual M_HDC* getHDC() override;
    virtual M_HGDIOBJ* getHGDIOBJ() override;


    App(HINSTANCE hInstance);
    ~App();

    virtual LRESULT mainProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

    virtual int makeDir(const char* path) override;

    virtual void setColor(COLORREF color, M_HDC& dc, int thickness = 1) override;
    virtual int getColorComponent(COLORREF color, COLORREF component) override;
    virtual void setDrawColor(COLORREF color) override;
    virtual COLORREF getPixel(Vector pos, HDC dc) override;
    virtual int setPixel(Vector pos, COLORREF _color, HDC dc) override;
    virtual COLORREF HSL2RGB(COLORREF HSL) override;
    virtual COLORREF RGB2HSL(COLORREF rgbColor) override;

    virtual int updateScreen(struct Window* window) override;
    virtual int updateNonClientAreaScreen(struct Window* window) override;
    virtual int invalidateRect(struct Window* window, Rect _rect, bool _erase = false) override;
    virtual int captureMouse(HWND wnd = NULL) override;
    virtual int releaseMouse(HWND wnd = NULL) override;

    virtual void rectangle(Rect rect, HDC dc) override;
    virtual void rectangle(double x1, double y1, double x2, double y2, HDC dc) override;
    virtual void rectangle(Vector pos1, Vector pos2, HDC dc) override;

    virtual void drawOnScreen(HDC dc, bool useAlpha = false) override;
    virtual void cleanTransparentDC() override;
    virtual bool getAsyncKeyState(int symbol) override;
    virtual bool getKeyState(int symbol) override;
    virtual bool isDoubleClick() override;
    virtual void deleteTransparency(RGBQUAD* buf, unsigned int totalSize) override;

    virtual int needToLoadOldFiles() override;

    virtual void line(Rect rect, HDC dc) override;
    virtual void line(double x1, double y1, double x2, double y2, HDC dc) override;
    virtual void line(Vector pos1, Vector pos2, HDC dc) override;

    virtual void ellipse(Vector centrPos, Vector halfSize, HDC dc) override;
    virtual void ellipse(double x1, double y1, double x2, double y2, HDC dc) override;

    virtual void horizontalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {}) override;
    virtual void verticalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize = {}) override;

    virtual int stretchBlt(HDC dest, double destPosx, double destPosy, double destSizex, double destSizey, HDC source, double sourcePosx, double sourcePosy, double sourceSizex, double sourceSizey) override;
    virtual int stretchBlt(HDC dest, Vector destPos, Vector destSize, HDC source, Vector sourcePos, Vector sourceSize)  override;
    virtual int stretchBlt(HDC dest, Rect destRect, HDC source, Rect sourceRecct) override;
    virtual void transparentBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0) override;
    virtual void transparentBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {}) override;
    virtual void transparentBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {}) override;
    virtual void bitBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource = 0, double ySource = 0) override;
    virtual void bitBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource = {}) override;
    virtual void bitBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource = {}) override;

    virtual void compressImage(HDC& newDC, Vector newSize, HDC oldDC, Vector oldSize) override;

    virtual HDC getBufferDC(RGBQUAD** buf) override;

    virtual Vector getHDCSize(HDC _dc) override;
    virtual Vector getHBITMAPSize(HBITMAP _bitmap) override;

    virtual HDC createDIBSection(Vector size, RGBQUAD** pixels = NULL) override;
    virtual HDC createDIBSection(double sizex, double sizey, RGBQUAD** pixels = NULL) override;

    virtual void drawText(double x0, double y0, double x1, double y1, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE)  override;
    virtual void drawText(Rect rect, const char text[], HDC dc,
        unsigned format = DT_CENTER | DT_VCENTER | DT_SINGLELINE)  override;
    virtual Vector getTextExtent(const char* text, HDC finalDC) override;

    virtual void selectFont(const char* text, int sizey, M_HDC& dc, int sizex = -1) override;
    virtual void setAlign(unsigned align, HDC dc) override;

    virtual void deleteDC(HDC dc) override;
    virtual int smartDeleteDC(HDC dc) override;
    int (*dllsaveImage) (HDC dc, const char* path) = NULL;
    virtual int saveImage(HDC dc, const char* path) override;
    HDC(*dllloadImage) (const char* path, Vector& _size, AbstractAppData* _app) = NULL;
    virtual HDC loadImage(const char* path, Vector _size = {}) override;
    virtual HDC _loadImage(const char* path);//only bmp
    virtual int DEBUGsaveImage(HDC dc) override;

    virtual int messageBox(const char  text[] = "", const char  header[] = "", unsigned  flags = MB_ICONINFORMATION | MB_OKCANCEL);

    virtual void drawCadre(Rect rect, M_HDC dc, COLORREF color, int thickness) override;
    virtual void drawCadre(Vector pos1, Vector pos2, M_HDC dc, COLORREF color, int thickness) override;
    virtual void drawCadre(int x1, int y1, int x2, int y2, M_HDC dc, COLORREF color, int thickness) override;

    virtual int isHDCValid(HDC _dc) override;


    virtual int setViewPort(HDC _dc, Vector newPos) override;
    virtual int getViewPort(HDC _dc, Vector* pos) override;

    virtual void changeWindow(Vector size = {}, Vector pos = {})  override;
    virtual int moveWindowTo(Vector _pos, HWND _wnd = 0) override;
    virtual int moveWindow(Vector _delta, HWND _wnd = 0) override;
    virtual Rect getWindowRect(HWND _wnd = 0) override;
    virtual void setCursor(HCURSOR cursor = NULL) override;
    virtual Vector getCursorPos() override;

    virtual bool wasResized() override { return isResized; };
    virtual void setResized(bool state = true) override;

    virtual bool isFullScreen() override;
    virtual Rect getUserRect() override;

    virtual long lround(double num) override;

    virtual Vector getCentrizedPos(Vector localSize, Vector globalSize) override;
    void shiftArrBack(char* arr, int oneItemSize, int firstPosOfShifting, int finishPosOfShifting) override;

    virtual char* getSaveFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "") override;
    virtual char* getOpenFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename = "") override;


    //logic part of engine
    struct MSGReaction* msgReaction = NULL;
    virtual int declareReactionOnMSG(int reaction = 0);//reaction = 0 on default
    virtual int getReactionOnMSG();

    virtual int beforeMessage();

    virtual void controlApp();//txver
};