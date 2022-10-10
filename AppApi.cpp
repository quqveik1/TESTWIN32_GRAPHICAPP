#pragma once
#include "AppApi.h"
#include "DrawBibliothek.cpp"
#include "SystemSettings.cpp"
#include "ToolManager.h"
#include "FileSavings.cpp"
#include "LoadLib.cpp"
#include "MainManager.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "WindowsLibApi.cpp"
#include "Loadmanager.cpp"
#include "ToolManager.cpp"
#include "DCManager.cpp"
#include "M_HGDIOBJ.cpp"
#include "M_HDC.cpp"
#include "HGDIManager.cpp"


void setWindowParameters(PowerPoint* app, HINSTANCE hInstance);
bool checkVersionCompability(PowerPoint* app);
void writeVersion(PowerPoint* app);
bool swapDC(HDC dest, int xDest, int yDest, int wDest, int hDest,
    HDC src, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rOp);
LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
HGDIOBJ selectGDIObject(HDC dc, HGDIOBJ obj);

const char* findExtensionStart(const char* text, int extensionPos);


PowerPoint::PowerPoint(HINSTANCE hInstance)
{
    appVersion = "v0.2.3.0";
    if (_mkdir("Settings") == -1)
    {
        if (errno == ENOENT) massert(!"Папка Settings не создалась", this);
    }

    filesCompability = checkVersionCompability(this);

    systemSettings = new CSystemSettings(this);

    loadLibManager = new CLoadLib();

    toolManager = new CToolManager(this);

    loadManager = new CLoadManager(this);

    windowsLibApi = new CWindowsLibApi();

    fileSavings = new CFileSavings();

    currColor = &systemSettings->DrawColor;

    dcManager = new DCManager(this);

    hgdiManager = new HGDIManager(this);

    setWindowParameters(this, hInstance);
}

PowerPoint::~PowerPoint()
{
    writeVersion(appData);

    delete mainManager;

    delete toolManager;
    delete loadManager;
    delete windowsLibApi;
    delete systemSettings;
    delete loadLibManager;
    delete dcManager;
    delete hgdiManager;
}

void writeVersion(PowerPoint* app)
{
    assert(app);
    FILE* versionFile = fopen("Settings\\Version.//txt", "w");

    if (versionFile)
    {
        (void)fprintf(versionFile, "%s", app->appVersion);
    }
    if (versionFile)fclose(versionFile);
}


bool swapDC(HDC dest, int xDest, int yDest, int wDest, int hDest,
    HDC src, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rOp)
{
    return NULL;
}

HGDIOBJ selectGDIObject(HDC dc, HGDIOBJ obj)
{
    HGDIOBJ oldobj = SelectObject(dc, obj);
    if (oldobj)
    {
        DeleteObject(oldobj);
        return obj;
    }
    return oldobj;
}

bool checkVersionCompability(PowerPoint* app)
{
    assert(app);
    bool needLoadSaves = false;
    FILE* versionFile = fopen("Settings\\Version.//txt", "r");

    if (versionFile)
    {
        char versionName[MAX_PATH] = {};
        (void)fscanf(versionFile, "%s", versionName);
        if (app->appVersion)
        {
            int result = strcmp(app->appVersion, versionName);
            if (result == 0) needLoadSaves = true;
        }
    }

    if (app->getAsyncKeyState(VK_CONTROL))
    {
        needLoadSaves = false;
    }

    if (versionFile) fclose(versionFile);
    return needLoadSaves;
}

void setWindowParameters(PowerPoint* app, HINSTANCE hInstance)
{
    HWND hwnd = {};
    WNDCLASSEX wndClass = {};

    char handleName[MAX_PATH] = {};
    (void)sprintf(handleName, "IMRED - %s[TXLib]", app->appVersion);

    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = (CS_VREDRAW | CS_HREDRAW);// &~WS_CAPTION;
    wndClass.lpfnWndProc = WinProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    app->defaultCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = handleName;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    int registerResult = RegisterClassEx(&wndClass);

    if (!registerResult) massert(!"Главный оконный класс не зарегистрировался:(", app);

    appData = app;

    hwnd = CreateWindow(
        handleName,
        handleName,
        (WS_POPUP | WS_BORDER | WS_CAPTION| WS_OVERLAPPEDWINDOW),
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        app->systemSettings->SizeOfScreen.x,
        app->systemSettings->SizeOfScreen.y,
        NULL, NULL,
        hInstance,
        NULL);

    app->MAINWINDOW = hwnd;

    if (!app->MAINWINDOW) massert(!"Главное окно не создалось:(", app);

    ShowWindow(appData->MAINWINDOW, SW_SHOW);
    UpdateWindow(appData->MAINWINDOW);
}

HDC PowerPoint::createDIBSection(Vector size, RGBQUAD** pixels/* = NULL*/)
{
    return createDIBSection(size.x, size.y, pixels);
}

HDC PowerPoint::createDIBSection(double sizex, double sizey, RGBQUAD** pixels/* = NULL*/)
{
    HDC wndDC = GetDC(MAINWINDOW);
    HDC dc = CreateCompatibleDC(wndDC);
    BITMAPINFO info = { { sizeof(info), sizex, sizey, 1, WORD(sizeof(RGBQUAD) * 8), BI_RGB } };
    HBITMAP bmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
    selectGDIObject(dc, bmap);
    PatBlt(dc, 0, 0, sizex, sizey, BLACKNESS);
    SetBkMode(dc, TRANSPARENT);
    ReleaseDC(MAINWINDOW, wndDC);

    dcManager->addDC(dc);
    return dc;
}

HDC PowerPoint::_loadImage(const char* path)
{
    HBITMAP loadedBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC dc = createDIBSection(0, 0);
    selectGDIObject(dc, loadedBitmap);

    return dc;
}



void PowerPoint::rectangle(double x1, double y1, double x2, double y2, HDC dc)
{
    Rectangle(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}


void PowerPoint::rectangle(Vector pos1, Vector pos2, HDC dc)
{
    rectangle(pos1.x, pos1.y, pos2.x, pos2.y, dc);
}

void PowerPoint::rectangle(Rect rect, HDC dc)
{
    rectangle(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, dc);
}

void PowerPoint::drawCadre(Rect rect, M_HDC dc, COLORREF color, int thickness)
{
    $s;
    if (systemSettings->debugMode == 5) printf("Rect: {%lf, %lf}\n", rect.pos.x, rect.pos.y);
    setColor(color, dc, thickness);
    
    int halfThickness = thickness / 2;
    line(rect.pos.x + halfThickness, rect.pos.y + halfThickness - 1, rect.pos.x + halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.pos.x + halfThickness, rect.finishPos.y - halfThickness, rect.finishPos.x - halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.finishPos.x - halfThickness, rect.pos.y + halfThickness, rect.finishPos.x - halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.pos.x + halfThickness, rect.pos.y + halfThickness, rect.finishPos.x - halfThickness, rect.pos.y + halfThickness, dc);
}

void PowerPoint::drawCadre(Vector pos1, Vector pos2, M_HDC dc, COLORREF color, int thickness)
{
    Rect rect = { .pos = pos1, .finishPos = pos2 };

    drawCadre(rect, dc, color, thickness);
}

void PowerPoint::drawCadre(int x1, int y1, int x2, int y2, M_HDC dc, COLORREF color, int thickness)
{
    Vector pos1 = { (double)x1, (double)y1 };
    Vector pos2 = { (double)x2, (double)y2 };

    drawCadre(pos1, pos2, dc, color, thickness);
}

Vector PowerPoint::getCentrizedPos(Vector localSize, Vector globalSize)
{
    return (globalSize - localSize) * 0.5;
}

void PowerPoint::shiftArrBack(char* arr, int oneItemSize, int firstPosOfShifting, int finishPosOfShifting)
{
    for (int i = firstPosOfShifting; i <= finishPosOfShifting; i++)
    {
        if (i - 1 >= 0)
        {
            memcpy(& (arr[(i - 1) * oneItemSize]), &(arr[(i) * oneItemSize]), (size_t)oneItemSize);
        }
    }
}


void PowerPoint::drawText(double x0, double y0, double x1, double y1, const char text[], HDC dc,
    unsigned format /*= DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS*/)
{
    RECT _rect = { x0, y0, x1, y1 };
    DrawText(dc, text, -1, &_rect, format);
}

void PowerPoint::drawText(Rect rect, const char text[], HDC dc,
    unsigned format/* = DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS*/)
{
    drawText(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, text, dc, format);
}



Vector PowerPoint::getTextExtent(const char* text, HDC finalDC)
{
    SIZE resultSize = {};
    size_t len = strlen(text);
    GetTextExtentPoint32(finalDC, text, (int)len, &resultSize);

    Vector result = {};
    result.x = resultSize.cx;
    result.y = resultSize.cy;

    return result;
}

void PowerPoint::setAlign(unsigned align, HDC dc)
{
    SetTextAlign(dc, align);
}

void PowerPoint::selectFont(const char* text, int sizey, M_HDC dc, int sizex/* = -1*/)
{
    HFONT font = CreateFont(sizey,((sizex >= 0) ? sizex : sizey / 3),
        0, 0, FW_DONTCARE, false, false, false,
        RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
       DEFAULT_QUALITY, DEFAULT_PITCH, text);

    if (font)selectGDIObject(dc, font);

}

M_HDC* PowerPoint::getHDC()
{
    return hgdiManager->getHDC();
}  

M_HGDIOBJ* PowerPoint::getHGDIOBJ()
{
    return hgdiManager->getHGDIOBJ();
}


void PowerPoint::setColor(COLORREF color, M_HDC& dc, int thickness)
{
    if (systemSettings->debugMode == 5) printf("SetColor: %d|", color);
    gassert(dc);

    
    HBRUSH newSolidBrush = CreateSolidBrush(color);
    M_HGDIOBJ* solidBrush = hgdiManager->getHGDIOBJ();
    solidBrush->setObj(newSolidBrush);
    dc.selectObj(solidBrush, newSolidBrush);

    HPEN newPen = CreatePen(PS_SOLID, thickness, color); 
    M_HGDIOBJ* pen = hgdiManager->getHGDIOBJ();
    pen->setObj(newPen);
    dc.selectObj(pen, newPen);

    SetTextColor(dc, color);
}

int PowerPoint::getColorComponent(COLORREF color, COLORREF component)
{
    return 0;
}

void PowerPoint::setDrawColor(COLORREF color)
{
    systemSettings->DrawColor = color;
}

COLORREF PowerPoint::getPixel(Vector pos, HDC dc)
{
    return GetPixel(dc, std::lround (pos.x), std::lround(pos.y));
}

int PowerPoint::updateScreen()
{
    return InvalidateRect(MAINWINDOW, NULL, FALSE);
}

void PowerPoint::line(Rect rect, HDC dc)
{
    line(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, dc);
}


void PowerPoint::line(double x1, double y1, double x2, double y2, HDC dc)
{
    bool result = MoveToEx(dc, std::lround(x1), std::lround(y1), NULL);
    result *= LineTo(dc, std::lround(x2), std::lround(y2));
}

void PowerPoint::line(Vector pos1, Vector pos2, HDC dc)
{
    line(pos1.x, pos1.y, pos2.x, pos2.y, dc);
}


void PowerPoint::ellipse(Vector centrePos, Vector halfSize, HDC dc)
{
    ellipse(centrePos.x - halfSize.x, centrePos.y - halfSize.y, centrePos.x + halfSize.x, centrePos.y + halfSize.y, dc);
}

void PowerPoint::ellipse(double x1, double y1, double x2, double y2, HDC dc)
{
    Ellipse(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}

void PowerPoint::horizontalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize/* = {}*/)
{
    if (fullDCSize == fullDCSize.getNullVector()) fullDCSize = size;
    double posy = fullDCSize.y - size.y;

    RGBQUAD* tempBuf = {};
    HDC tempDC = createDIBSection(size, &tempBuf);


    for (int x = 0; x < size.x; x++)
    {
        for (int y = std::lround (posy); y < std::lround(fullDCSize.y); y++)
        {
            int tempY = std::lround(y - posy);
            int newY = std::lround(size.y - tempY - 1);
            tempBuf[x + (int)(newY * size.x)] = buf[x + (int)(y * fullDCSize.x)];
        }
    }
    bitBlt(dc, {}, size, tempDC);

    deleteDC(tempDC);
}

void PowerPoint::verticalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize/* = {}*/)
{
    if (fullDCSize == fullDCSize.getNullVector()) fullDCSize = size;
    double posy = fullDCSize.y - size.y;
   
    RGBQUAD* tempBuf = {};
    HDC tempDC = createDIBSection(size, &tempBuf);
    


    for (int x = 0; x < size.x; x++)
    {
        for (int y = std::lround(posy); y < std::lround(fullDCSize.y); y++)
        {
            int newX = std::lround(size.x - x - 1);
            int tempY = std::lround(y - posy);
            tempBuf[newX + (int)(tempY * size.x)] = buf[x + (int)(y * fullDCSize.x)];
        }
    }
    bitBlt(dc, {}, size, tempDC);

    deleteDC(tempDC);

}


void PowerPoint::bitBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource/* = 0*/, double ySource/* = 0*/)
{
    Vector size = getHDCSize(dc2);
    if (!sizex) sizex = size.x;
    if (!sizey) sizey = size.y;

    BitBlt(dc1, std::lround (x0), std::lround(y0), std::lround(sizex), std::lround(sizey), dc2, std::lround(xSource), std::lround(ySource), SRCCOPY);
    return;
}

void PowerPoint::bitBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource/* = {}*/)
{
    bitBlt(dc1, pos.x, pos.y, size.x, size.y, dc2, posSource.x, posSource.y);
}

void PowerPoint::transparentBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource/* = 0*/, double ySource/* = 0*/)
{
    assert(dc2);

    Vector size = getHDCSize(dc2);
    if (!sizex) sizex = size.x;
    if (!sizey) sizey = size.y;

    TransparentBlt(dc1, std::lround(x0), std::lround(y0), std::lround(sizex), std::lround(sizey), dc2, std::lround(xSource), std::lround(ySource), std::lround(sizex), std::lround(sizey), systemSettings->TRANSPARENTCOLOR);
}

void PowerPoint::transparentBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource/* = {}*/)
{
    transparentBlt(dc1, pos.x, pos.y, size.x, size.y, dc2, posSource.x, posSource.y);
}

int PowerPoint::stretchBlt(HDC dest, double destPosx, double destPosy, double destSizex, double destSizey, HDC source, double sourcePosx, double sourcePosy, double sourceSizex, double sourceSizey)
{
    return StretchBlt(dest, std::lround(destPosx), std::lround(destPosy), std::lround(destSizex), std::lround(destSizey), source, std::lround(sourcePosx), std::lround(sourcePosy), std::lround(sourceSizex), std::lround(sourceSizey), SRCCOPY);
}

int PowerPoint::stretchBlt(HDC dest, Vector destPos, Vector destSize, HDC source, Vector sourcePos, Vector sourceSize)
{
    return stretchBlt(dest, destPos.x, destPos.y, destSize.x, destSize.y, source, sourcePos.x, sourcePos.y, sourceSize.x, sourceSize.y);
}


void PowerPoint::compressImage(HDC& newDC, Vector newSize, HDC oldDC, Vector oldSize)
{   
    assert(oldDC);

    if (!newDC) deleteDC (newDC);
    newDC = createDIBSection(newSize.x, newSize.y);
    assert(newDC);

    assert (stretchBlt(newDC, 0, 0, newSize.x, newSize.y, oldDC, 0, 0, oldSize.x, oldSize.y));
}

HDC PowerPoint::getBufferDC(RGBQUAD** buf)
{
    HDC answer = NULL;
    if (OpenClipboard(MAINWINDOW))
    {
        HBITMAP bitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
        HBITMAP hBmpCopy = (HBITMAP)CopyImage(bitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
        if (bitmap)
        {
            Vector bitmapSize = getHBITMAPSize(hBmpCopy);
            if (bitmapSize > 0)
            {
                answer = createDIBSection(bitmapSize, buf);
                HGDIOBJ result = SelectObject(answer, hBmpCopy);
            } 
        }


        CloseClipboard();
    }

    return answer;
}

Vector PowerPoint::getHDCSize(HDC _dc)
{
    if (!_dc)
    {
        return { -1, -1 };
    }
    HBITMAP _bitmap = (HBITMAP)GetCurrentObject(_dc, OBJ_BITMAP);
    return getHBITMAPSize(_bitmap);
} 

Vector PowerPoint::getHBITMAPSize(HBITMAP _bitmap)
{
    BITMAP bm;
    GetObject(_bitmap, sizeof(bm), (LPVOID)&bm);
    Vector answer = {};
    answer.x = bm.bmWidth;
    answer.y = bm.bmHeight;
    return answer;
}


void PowerPoint::drawOnScreen(HDC dc, bool useAlpha /*=false*/)
{
    //if (!useAlpha)//txBitBlt(0, 0, dc);
    //if (useAlpha)transparentBlt(//txDC(), 0, 0, 0, 0, dc);
    //txSleep(0);
}

void PowerPoint::cleanTransparentDC()
{
    //setColor(SystemSettings.TRANSPARENTCOLOR, transparentLay.lay);
   // rectangle(0, 0, transparentLay.laySize.x, transparentLay.laySize.y, transparentLay.lay);
    ////txClear(transparentLay.lay);
    //deleteTransparency(transparentLay.layBuf, transparentLay.laySize.x * transparentLay.laySize.y);
}

bool PowerPoint::getAsyncKeyState(int symbol)
{
    return GetAsyncKeyState(symbol);
}

bool PowerPoint::getKeyState(int symbol)
{
    return GetKeyState(symbol);
}

bool PowerPoint::isDoubleClick()
{
    return dClick;
}

void PowerPoint::deleteTransparency(RGBQUAD* buf, unsigned int totalSize)
{
    for (int i = 0; i < (int)totalSize; i++)
    {
        buf[i].rgbReserved = 255;
    }
}


int PowerPoint::needToLoadOldFiles()
{
    return filesCompability;
}


void PowerPoint::deleteDC(HDC dc)
{
    if (dc)
    {
        selectGDIObject(dc, GetStockObject(NULL_PEN));
        selectGDIObject(dc, GetStockObject(NULL_BRUSH));
        selectGDIObject(dc, GetStockObject(SYSTEM_FONT));
        HBITMAP defaultBitmap = NULL;
        selectGDIObject(dc, defaultBitmap);
        DeleteObject(GetCurrentObject(dc, OBJ_BITMAP));

        DeleteDC(dc);
    }
    else printf("DC[%d], которые вы хотите удалить не существует\n", (int)dc);
}

int PowerPoint::smartDeleteDC(HDC dc)
{
    return DeleteDC(dc);
}

int PowerPoint::saveImage(HDC dc, const char* path)
{
    return 0;
    //return //txSaveImage(path, dc);
}


int PowerPoint::messageBox(const char  text[]/* = ""*/, const char  header[]/* = ""*/, unsigned  flags/* = MB_ICONINFORMATION | MB_OKCANCEL*/)
{
    return MessageBox(MAINWINDOW, text, header, flags);
}
void PowerPoint::changeWindow(Vector size/* = {}*/, Vector pos/* = {}*/)
{
    /*
    bool wasSizeChanged = true;
    if (pos == pos.getNullVector())
    {
        pos = { .x = abs((size.x - systemSettings->FullSizeOfScreen.x) / 2), .y = abs( (size.y - systemSettings->FullSizeOfScreen.y) / 2) };
    }
    if (size == size.getNullVector())
    {
        size = systemSettings->SizeOfScreen;
        wasSizeChanged = false;
    }

    
    systemSettings->ScreenPos = pos;

    MoveWindow(MAINWINDOW, std::lround (pos.x), std::lround(pos.y), std::lround(size.x), std::lround(size.y), TRUE);

    //SetWindowLong(MAINWINDOW, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0,0,0)));

    if (sizeHistory[1] != size)
    {
        HDC outDC = //txCreateDIBSection(size.x, size.y);
        deleteDC(//txDC());
        //txDC() = outDC;
        sizeHistory[0] = sizeHistory[1];
        sizeHistory[1] = size;
        systemSettings->lastTimeSizeOfScreen = sizeHistory[0];
    }

    

    systemSettings->SizeOfScreen = size;
    if (wasSizeChanged) isResized = true;
    */
}


void PowerPoint::setCursor(HCURSOR cursor)
{
    activeCursor = cursor;
    lastTimeCursorSetTime = clock();
}

Vector PowerPoint::getCursorPos()
{
    Vector vector = {};
    POINT point = {};
    GetCursorPos(&point);
    vector.x = point.x;
    vector.y = point.y;
    return vector;
}


bool PowerPoint::isFullScreen()
{
    RECT fullScreenRect = {};

    SystemParametersInfo(SPI_GETWORKAREA, NULL, &fullScreenRect, NULL);
    RECT _rect = {};
    GetWindowRect(MAINWINDOW, &_rect);

    if (_rect.bottom >= fullScreenRect.bottom && _rect.top <= fullScreenRect.top && _rect.left <= fullScreenRect.left && _rect.right >= fullScreenRect.right)
    {
        return true;
    }
    return false;

}

Rect PowerPoint::getUserRect()
{
    if (isFullScreen())
    {
        return { .pos = {0, systemSettings->HANDLEHEIGHT}, .finishPos = systemSettings->SizeOfScreen };
    }
    else
    {
        return { .pos = {systemSettings->FrameThickness, systemSettings->HANDLEHEIGHT}, .finishPos = {systemSettings->SizeOfScreen.x - systemSettings->FrameThickness, systemSettings->SizeOfScreen.y - (systemSettings->FrameThickness - 1)} };
    }
}


void PowerPoint::setResized(bool state/* = true*/)
{
    isResized = state;
}


void PowerPoint::controlApp()
{
    int time = clock();
    if (time - lastTimeCursorSetTime > 60)
    {
        setCursor(defaultCursor);
    }



    if (dClick)
    {
        dClick = false;
    }

    if (getAsyncKeyState(VK_LBUTTON))
    {
        if (!wasLastTimeLButtonClicked && time - lastTimeLButtonClicked < 300)
        {
            dClick = true;
        }
        wasLastTimeLButtonClicked = true;
        lastTimeLButtonClicked = time;
    }
    else
    {
        wasLastTimeLButtonClicked = false;
    }

    //txClearConsole();
}


char* PowerPoint::getOpenFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename)
{
    int fileNameLength = MAX_PATH;
    char fileName[MAX_PATH] = "";

    sprintf(fileName, "%s", defaultFilename);

    OPENFILENAME ofn = { sizeof(OPENFILENAME)};

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST;

    //bool oldPSW = _//txProcessSystemWarnings;
    //_txProcessSystemWarnings = false;//отключает всякие системные проверки тхлибом иначе возникает ошибка 298

    if ((GetOpenFileNameA))
        (GetOpenFileNameA(&ofn));
    //_//txProcessSystemWarnings = oldPSW;

    if (ofn.nFileOffset <= 0)
    {
        return NULL;
    }

    return fileName;
}



char* PowerPoint::getSaveFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename/* = NULL*/)
{
    int fileNameLength = MAX_PATH;
    char fileName[MAX_PATH] = "";

    sprintf(fileName, "%s", defaultFilename);

    OPENFILENAME ofn = { sizeof(OPENFILENAME)};

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;

    //bool oldPSW = _//txProcessSystemWarnings;
    //_//txProcessSystemWarnings = false;//отключает всякие системные проверки тхлибом иначе возникает ошибка 298

    if ((GetSaveFileNameA))
        (GetSaveFileNameA(&ofn));
    //_//txProcessSystemWarnings = oldPSW;

    if (ofn.nFileOffset <= 0)
    {
        return NULL;
    }

    const char* extension = findExtensionStart(fileTypeDescribtion, ofn.nFilterIndex);

    int extensionSize = strlen(extension);
    int realFilenameSize = strlen(fileName);
    if (strcmp(&fileName[realFilenameSize - extensionSize], extension))
    {
        sprintf(fileName, "%s.%s", fileName, extension);
    }

    return fileName;
}


const char* findExtensionStart(const char* text, int extensionPos)
{
    int startPos = 0;
    for (int i = 0; i < extensionPos; i++)
    {
        startPos += strlen(&text[startPos]) + 3;
        if (i < extensionPos - 1)
        {
            startPos += strlen(&text[startPos]) + 2;
        }
    }

    return &text[startPos];
}
