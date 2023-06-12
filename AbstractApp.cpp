#pragma once
#include "AbstractApp.h"
#include "AppApi.h"
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
#include "TimerManager.cpp"
#include "DLLToolsManager.cpp"
#include "MSGReaction.cpp"
#include "IMREDresource.h"
#include <windowsx.h>
#include <iostream>
#include <sys/stat.h>

#include "IMREDresource.h"

#ifdef _MSC_VER
#pragma comment(lib, "Msimg32")
#endif


AbstractAppData::AbstractAppData(HINSTANCE _instance, std::string _pathToAbstractAppDataApi/* = ""*/) :
    hInstance(_instance),
    pathToAbstractAppDataApi(_pathToAbstractAppDataApi)
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    appData = this;
    appVersion = "v0.2.5.0";
    massert(!makeDir("Settings"), this);

    if (getAsyncKeyState(VK_CONTROL))
    {
        filesCompability = false;
    }

    systemSettings = new CSystemSettings(this);

    loadLibManager = new CLoadLib();

    loadManager = new CLoadManager(this);

    windowsLibApi = new CWindowsLibApi();

    fileSavings = new CFileSavings();

    currColor = &systemSettings->DrawColor;

    dcManager = new DCManager(this);

    hgdiManager = new HGDIManager(this);
    timerManager = new TimerManager();

    HMODULE _saveImagesLib = loadLibManager->loadLib("SaveImage.dll");
    dllsaveImage = (int (*) (HDC dc, const char* path))GetProcAddress(_saveImagesLib, "saveImage");
    dllloadImage = (HDC(*) (const char* path, Vector & _size, AbstractAppData * _app))GetProcAddress(_saveImagesLib, "loadImage");

    msgReaction = new MSGReaction();

    testDC.setSize(systemSettings->SizeOfScreen, this);

    dcout << "Конструтор закончил выполнение" << std::endl;
    //setWindowParameters(hInstance);
}


AbstractAppData::~AbstractAppData()
{
    if (mainManager)
    {
        if (mainManager->mayBeDeletedInDestructor())
        {
            delete mainManager;
        }
    }

    delete loadManager;
    delete windowsLibApi;
    delete systemSettings;
    delete loadLibManager;
    delete dcManager;
    delete hgdiManager;
    delete timerManager;
    delete msgReaction;
}


LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

void AbstractAppData::setWindowParameters(HINSTANCE hInstance)
{
    HWND hwnd = {};
    WNDCLASSEX wndClass = {};

    char handleName[MAX_PATH] = {};
    (void)sprintf(handleName, "%s - %s[AbstractApp/WindowsLibApi]", appName.c_str(), appVersion);

    appIcon = LoadIcon((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IMREDICON2));

    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS);// &~WS_CAPTION;
    wndClass.lpfnWndProc = WinProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIconSm = appIcon;
    wndClass.hIcon = appIcon;
    defaultCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = handleName;

    int registerResult = RegisterClassEx(&wndClass);

    if (!registerResult) massert(!"Главный оконный класс не зарегистрировался:(", this);

    MAINWINDOW = CreateWindow(
        handleName,
        handleName,
        //(WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN),
        WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        lround(systemSettings->SizeOfScreen.x),
        lround(systemSettings->SizeOfScreen.y),
        NULL, NULL,
        hInstance,
        NULL);

    if (!MAINWINDOW) massert(!"Главное окно не создалось:(", this);

    ShowWindow(MAINWINDOW, SW_SHOW);
    updateScreen(NULL);

#ifndef _DEBUG
    hideConsoleWindow();
#else
    showConsoleWindow();
#endif

    loadAndSetIcon(IMREDICON1);
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int timeWhenLastTimeRedrawed = 0;
    PAINTSTRUCT ps = {};

    if (appData)
    {
        if (message == WM_CREATE)
        {
            if (appData->getAppCondition())
            {
                appData->MAINWINDOW = window;
                appData->onCreate(window, message, wParam, lParam);
                appData->setAppCondition(true);
            }

        }
        appData->beforeMessage();

        if (message == WM_GETMINMAXINFO)
        {
            LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
            lpMMI->ptMinTrackSize = (POINT)appData->getMinSize();
            dprintf("");
        }

        if (message == WM_SETCURSOR)
        {
            if (appData->activeCursor)
            {
                SetClassLongPtr(window, GCLP_HCURSOR, (LONG_PTR)appData->activeCursor);
            }
        }

        if (message == WM_MOUSEMOVE)
        {
            if (appData->mainManager)
            {
                static Vector lastTimeMp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                Vector mp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                appData->mainManager->onMouseMove(mp, mp - lastTimeMp);
                lastTimeMp = mp;
            }
        }

        if (message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN)
        {
            if (appData->mainManager)
            {
                appData->activeMouseButton = 0;
                if (message == WM_LBUTTONDOWN) appData->activeMouseButton = 1;
                if (message == WM_RBUTTONDOWN) appData->activeMouseButton = 2;
                dprintf("WM_MBDOWN_START\n");
                Vector mp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                appData->mainManager->mbDown(mp, appData->activeMouseButton);
                appData->captureMouse();
                dprintf("WM_MBDOWN_END\n");
                appData->activeMouseButton = 0;
            }
        }

        if (message == WM_LBUTTONUP || message == WM_RBUTTONUP)
        {
            if (appData->mainManager)
            {
                appData->activeMouseButton = 0;
                if (message == WM_LBUTTONUP) appData->activeMouseButton = 1;
                if (message == WM_RBUTTONUP) appData->activeMouseButton = 2;
                dprintf("WM_MBUP_START\n");
                Vector mp = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                appData->mainManager->mbUp(mp, appData->activeMouseButton);
                if (appData->mainManager->hitTest(mp))
                {
                    appData->mainManager->onClick(mp);
                }
                appData->releaseMouse();
                dprintf("WM_MBUP_END\n");
                appData->activeMouseButton = 0;
            }
        }

        if (message == WM_LBUTTONDBLCLK || message == WM_RBUTTONDBLCLK)
        {
            if (appData->mainManager)
            {
                int button = 0;
                if (message == WM_LBUTTONDBLCLK) button = 1;
                if (message == WM_RBUTTONDBLCLK) button = 2;
                Vector mp = { (double)GET_X_LPARAM(lParam), (double)GET_Y_LPARAM(lParam) };
                appData->mainManager->onDoubleClick(mp, button);
            }

        }



        if (message == WM_KEYDOWN)
        {
            if (appData->mainManager)
            {
                int vk = static_cast<int>(wParam);
                appData->mainManager->onKeyboard(vk);
                //appData->captureMouse();
            }
        }

        if (message == WM_CHAR)
        {
            if (appData->mainManager)
            {
                int vk = static_cast<int>(wParam);
                appData->mainManager->onKeyboardChar(vk);
            }
        }

        if (message == WM_TIMER)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onTimer(wParam);
            }
        }

        if (message == WM_SETFOCUS)
        {
            if (appData)
            {
                appData->updateNonClientAreaScreen(NULL);
            }
        }



        if (message == WM_PAINT)
        {
            HDC finalDC = BeginPaint(appData->MAINWINDOW, &ps);
            M_HDC paintDC(appData, finalDC);
            paintDC = finalDC;



            if (appData->mainManager)
            {
                appData->bitBlt(finalDC, {}, {}, appData->mainManager->finalDC);
                appData->mainManager->print(paintDC);
                appData->mainManager->onDrawEnd();
            }
            EndPaint(appData->MAINWINDOW, &ps);
            paintDC.deleteObj();
        }

        if (message == WM_SIZE)
        {
            if (appData->mainManager)
            {
                appData->systemSettings->SizeOfScreen = { (double)LOWORD(lParam), (double)HIWORD(lParam) };
                if (wParam == SIZE_MINIMIZED || wParam == SIZE_MAXIMIZED)
                {
                    appData->windowMovingStatus = true;
                    appData->mainManager->onEnterWindowSizeMove();
                    appData->windowMovingStatus = false;
                    appData->mainManager->onExitWindowSizeMove();

                }
                appData->mainManager->onSize(appData->systemSettings->SizeOfScreen);
            }
            return 0;
        }

        if (message == WM_CLOSE)
        {
            bool canShutProg = true;
            if (appData->mainManager)
            {
                if (appData->mainManager->onClose())
                {
                    canShutProg = false;
                }
            }
            if (!canShutProg)
            {
                return 1;
            }
        }

        if (message == WM_DESTROY)
        {
            if (appData->mainManager)
            {
                appData->mainManager->onDestroy();
            }
            appData->setAppCondition(false);
            PostQuitMessage(0);
        }

        if (message == WM_ENTERSIZEMOVE)
        {
            if (appData->mainManager)
            {
                appData->windowMovingStatus = true;
                appData->mainManager->onEnterWindowSizeMove();
                dcout << "WM_ENTERSIZEMOVE\n";
            }
        }

        if (message == WM_EXITSIZEMOVE)
        {
            if (appData->mainManager)
            {
                appData->windowMovingStatus = false;
                appData->mainManager->onExitWindowSizeMove();
                dcout << "WM_EXITSIZEMOVE\n";
            }
        }
    }

    LRESULT resDefWindowProc = DefWindowProc(window, message, wParam, lParam);
    return resDefWindowProc;
}





HGDIOBJ selectGDIObject(HDC dc, HGDIOBJ obj);


int AbstractAppData::startApp()
{
    setAppCondition(true);
    setWindowParameters(hInstance);
    WinMain(NULL, NULL, 0, 0);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    MSG message = {};

    for (;;)
    {
        if (!GetMessage(&message, NULL, 0, 0)) break;
        else
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    return 0;
}



struct Manager* AbstractAppData::setMainManager(struct Manager* newManager, MEM_TYPE mt/* = MT_DYNAMIC*/)
{
    Manager* oldManager = mainManager;
    mainManager = newManager;
    if (mainManager) mainManager->memType = mt;
    return oldManager;
}

struct Manager& AbstractAppData::setMainManager(struct Manager& newManager, MEM_TYPE mt/* = MT_STATIC*/)
{
    Manager* oldManager = mainManager;
    mainManager = &newManager;
    mainManager->memType = mt;
    return *oldManager;
}

void AbstractAppData::setMinSize(const Vector& _size)
{
    if (_size != systemSettings->MINSCREENSIZE)
    {
        systemSettings->MINSCREENSIZE = _size;
        //SendMessage(getActiveHWND(),);
    }
}

Vector AbstractAppData::getMinSize()
{
    return systemSettings->MINSCREENSIZE;
}

HWND AbstractAppData::getActiveHWND()
{
    return MAINWINDOW;
}

int AbstractAppData::setIcon(HICON icon/* = NULL*/)
{
    if (!icon)
    {
        icon = appIcon;
    }
    ULONG_PTR res = SetClassLongPtr(getActiveHWND(), GCLP_HICON, (LONG_PTR)icon);

    if (res == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

HICON AbstractAppData::loadIcon(int resourcename)
{
    HICON loadedIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(resourcename));
    if(loadedIcon == 0)
    {
        dcout << "LoadedIcon = 0\n";
    }
    return loadedIcon;
}

int AbstractAppData::loadAndSetIcon(int resource)
{
    appIcon = loadIcon(resource);
    int res = setIcon(appIcon);
    return res;
}

void AbstractAppData::hideConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);
}

void AbstractAppData::showConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_SHOW);
}

int AbstractAppData::getAppCondition()
{
    return IsRunning;
}


void AbstractAppData::setAppCondition(int newCondition)
{
    IsRunning = newCondition;
}

void AbstractAppData::setAppName(const std::string& newName)
{
    appName = newName;
    SetWindowText(getActiveHWND(), appName.c_str());
}


int AbstractAppData::declareReactionOnMSG(int reaction/* = 0*/)
{
    if (msgReaction)
    {
        msgReaction->setReaction(reaction);
        return reaction;
    }
    return 0;
}

int AbstractAppData::getReactionOnMSG()
{
    if (msgReaction)
    {
        int answer = msgReaction->getReaction();
        return answer;
    }
    return 0;

}


int AbstractAppData::beforeMessage()
{
    declareReactionOnMSG(0);//clean reactions
    return 0;
}


HDC AbstractAppData::createDIBSection(Vector size, RGBQUAD** pixels/* = NULL*/)
{
    return createDIBSection(size.x, size.y, pixels);
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

HDC AbstractAppData::createDIBSection(double sizex, double sizey, RGBQUAD** pixels/* = NULL*/)
{
    HDC wndDC = GetDC(MAINWINDOW);
    HDC dc = CreateCompatibleDC(wndDC);
    BITMAPINFO info = { { sizeof(info), lround(sizex), lround(sizey), 1, WORD(sizeof(RGBQUAD) * 8), BI_RGB } };
    HBITMAP bmap = CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void**)pixels, NULL, 0);
    selectGDIObject(dc, bmap);
    PatBlt(dc, 0, 0, lround(sizex), lround(sizey), BLACKNESS);
    SetBkMode(dc, TRANSPARENT);
    ReleaseDC(MAINWINDOW, wndDC);

    dcManager->addDC(dc);
    return dc;
}



void AbstractAppData::rectangle(double x1, double y1, double x2, double y2, HDC dc)
{
    Rectangle(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}


void AbstractAppData::rectangle(Vector pos1, Vector pos2, HDC dc)
{
    rectangle(pos1.x, pos1.y, pos2.x, pos2.y, dc);
}

void AbstractAppData::rectangle(Rect rect, HDC dc)
{
    rectangle(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, dc);
}

void AbstractAppData::drawCadre(Rect rect, M_HDC& dc, COLORREF color, int thickness)
{
    $s;
    if (systemSettings->debugMode == 5) dprintf("Rect: {%lf, %lf}\n", rect.pos.x, rect.pos.y);
    setColor(color, dc, thickness);

    int halfThickness = thickness / 2;
    line(rect.pos.x + halfThickness, rect.pos.y + halfThickness - 1, rect.pos.x + halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.pos.x + halfThickness, rect.finishPos.y - halfThickness, rect.finishPos.x - halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.finishPos.x - halfThickness, rect.pos.y + halfThickness, rect.finishPos.x - halfThickness, rect.finishPos.y - halfThickness, dc);
    line(rect.pos.x + halfThickness, rect.pos.y + halfThickness, rect.finishPos.x - halfThickness, rect.pos.y + halfThickness, dc);
}

void AbstractAppData::drawCadre(Vector pos1, Vector pos2, M_HDC& dc, COLORREF color, int thickness)
{
    Rect rect = { .pos = pos1, .finishPos = pos2 };

    drawCadre(rect, dc, color, thickness);
}


void AbstractAppData::drawCadre(int x1, int y1, int x2, int y2, M_HDC& dc, COLORREF color, int thickness)
{
    Vector pos1 = { (double)x1, (double)y1 };
    Vector pos2 = { (double)x2, (double)y2 };

    drawCadre(pos1, pos2, dc, color, thickness);
}


int AbstractAppData::isHDCValid(HDC _dc)
{
    COLORREF _color = getPixel({ 1, 1 }, _dc);
    if (_color == CLR_INVALID)
    {
        return 0;
    }
    return 1;
}


int AbstractAppData::setViewPort(HDC _dc, Vector newPos)
{
    return SetViewportOrgEx(_dc, newPos.getIntX(), newPos.getIntY(), NULL);
}

int AbstractAppData::getViewPort(HDC _dc, Vector* pos)
{
    POINT point = {};
    int operationRes = GetViewportOrgEx(_dc, &point);

    Vector answer = {};
    answer = Vector::toVector(point);
    *pos = answer;
    return operationRes;
}

Vector AbstractAppData::getCentrizedPos(Vector localSize, Vector globalSize)
{
    return (globalSize - localSize) * 0.5;
}

void AbstractAppData::shiftArrBack(char* arr, int oneItemSize, int firstPosOfShifting, int finishPosOfShifting)
{
    for (int i = firstPosOfShifting; i <= finishPosOfShifting; i++)
    {
        if (i - 1 >= 0)
        {
            memcpy(&(arr[(i - 1) * oneItemSize]), &(arr[(i)*oneItemSize]), (size_t)oneItemSize);
        }
    }
}


void AbstractAppData::drawText(double x0, double y0, double x1, double y1, const char text[], HDC dc,
    unsigned format /*= DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS*/)
{
    RECT _rect = { lround(x0), lround(y0), lround(x1), lround(y1) };
    DrawText(dc, text, -1, &_rect, format);
}

void AbstractAppData::drawText(Rect rect, const char text[], HDC dc,
    unsigned format/* = DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS*/)
{
    drawText(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, text, dc, format);
}



Vector AbstractAppData::getTextExtent(const char* text, HDC finalDC)
{
    if (text)
    {
        SIZE resultSize = {};
        size_t len = strlen(text);
        GetTextExtentPoint32(finalDC, text, (int)len, &resultSize);

        Vector result = Vector::toVector(resultSize);

        return result;
    }
    return {};
}


Vector AbstractAppData::getTextExtent(const char* text, int _font, const char* _fontName)
{
    testDC.clear();
    selectFont(_fontName, _font, testDC);
    return getTextExtent(text, testDC);
}

void AbstractAppData::setAlign(unsigned align, HDC dc)
{
    SetTextAlign(dc, align);
}

void AbstractAppData::selectFont(const char* text, int sizey, M_HDC& dc, int sizex/* = -1*/)
{
    HFONT font = CreateFont(sizey, ((sizex >= 0) ? sizex : sizey / 3),
        0, 0, FW_DONTCARE, false, false, false,
        RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH, text);

    if (font) dc.selectObj(font);
    else dprintf("Шрифт[""%s""] не существует!", text);

}

M_HDC* AbstractAppData::getHDC()
{
    return hgdiManager->getHDC();
}

M_HGDIOBJ* AbstractAppData::getHGDIOBJ()
{
    return hgdiManager->getHGDIOBJ();
}

int AbstractAppData::makeDir(const char* path)
{
    if (_mkdir(path) == -1)
    {
        if (errno == ENOENT)
        {
            dprintf("[%s] не создалась и не существует", path);
            return ENOENT;
        }
    }
    return 0;
}

long AbstractAppData::getFileSize(FILE* _file)
{
    if (_file)
    {               
        struct stat buff = {};
        buff.st_size = -1;

        fstat(_fileno(_file), &buff);

        return buff.st_size;
    }
    return -1;
}

char* AbstractAppData::readText(FILE* _file)
{
    if (_file)
    {
        int fileSize = getFileSize(_file);
        char* fileBits = new char[fileSize];

        size_t creadchar = fread(fileBits, sizeof(char), fileSize, _file);

        if (creadchar < 0)
        {
            dprintf("Файл считался %s\n", __FUNCTION__);
            return NULL;
        }

        fileBits[creadchar] = 0;

        return fileBits;
    }
    else
    {
        dprintf("Передан пустой файл для %s\n", __FUNCTION__);
        return NULL;
    }
}


char* AbstractAppData::readText(const char* path)
{
    if (path)
    {
        FILE* pathFile = fopen(path, "r");
        int fileSize = getFileSize(pathFile);
        char* fileBits = new char[fileSize];

        size_t creadchar = fread(fileBits, sizeof(char), fileSize, pathFile);
        fclose(pathFile);

        if (creadchar < 0)
        {
            dprintf("Файл считался %s\n", __FUNCTION__);
            return NULL;
        }

        fileBits[creadchar] = 0;

        return fileBits;
    }
    else
    {
        dprintf("Передан пустой путь для %s\n", __FUNCTION__);
        return NULL;
    }
}

void AbstractAppData::setColor(COLORREF color, M_HDC& dc, int thickness)
{
    if (systemSettings->debugMode == 5) dprintf("SetColor: %d|", color);
    gassert(dc);

    COLORREF oldColor = GetDCBrushColor(dc);
    if (oldColor != color)
    {
        HBRUSH newSolidBrush = CreateSolidBrush(color);
        dc.selectObj(newSolidBrush);
    }

    HPEN newPen = CreatePen(PS_SOLID, thickness, color);
    dc.selectObj(newPen);

    SetTextColor(dc, color);
}

int AbstractAppData::getColorComponent(COLORREF color, COLORREF component)
{
    return 0;
}

void AbstractAppData::setDrawColor(COLORREF color)
{
    systemSettings->DrawColor = color;
}

COLORREF AbstractAppData::HSL2RGB(COLORREF HSL)
{

    struct xRGB
    {
        static double calc(double h, double m1, double m2)
        {
            while (h < 0)   h += 360;
            while (h > 360) h -= 360;

            return (h < 60) ? m1 + (m2 - m1) * h / 60 :
                (h < 180) ? m2 :
                (h < 240) ? m1 + (m2 - m1) * (240 - h) / 60 :
                m1;
        }
    };

    int    si = GetGValue(HSL);

    double h = GetRValue(HSL) / 256.0 * 360,
        s = GetGValue(HSL) / 255.0,
        l = GetBValue(HSL) / 255.0,

        m2 = (l <= 0.5) ? l * (1 + s) : l + s - l * s,
        m1 = 2 * l - m2,

        r = (si) ? xRGB::calc(h + 120, m1, m2) : l,
        g = (si) ? xRGB::calc(h, m1, m2) : l,
        b = (si) ? xRGB::calc(h - 120, m1, m2) : l;

    COLORREF rgbColor = RGB(std::lround(r * 255), std::lround(g * 255), std::lround(b * 255));

    return rgbColor;
}


COLORREF AbstractAppData::RGB2HSL(COLORREF rgbColor)
{
    struct xRGB
    {
        static bool zero(double val)
        {
            const double prec = 0.001;

            return (fabs(val) < prec);
        }
    };

    double r = GetRValue(rgbColor) / 255.0,  //-V2551
        g = GetGValue(rgbColor) / 255.0,  //-V2551
        b = GetBValue(rgbColor) / 255.0,  //-V2551

        m1 = max(max(r, g), b),
        m2 = min(min(r, g), b),
        dm = m1 - m2,
        sm = m1 + m2,

        h = 0,
        s = 0,
        l = sm / 2;

    if (!xRGB::zero(dm))
    {
        sm = (sm <= 1) ? sm : (2 - sm);
        s = (!xRGB::zero(sm)) ? dm / sm : 0;

        double cr = (!xRGB::zero(dm)) ? (m1 - r) / dm : 0,
            cg = (!xRGB::zero(dm)) ? (m1 - g) / dm : 0,
            cb = (!xRGB::zero(dm)) ? (m1 - b) / dm : 0;

        if (xRGB::zero(r - m1)) h = cb - cg;
        if (xRGB::zero(g - m1)) h = 2 + cr - cb;
        if (xRGB::zero(b - m1)) h = 4 + cg - cr;
    }

    h = (h >= 0) ? h * 60 : h * 60 + 360;

    return RGB(std::lround(h / 360.0 * 256), std::lround(s * 255), std::lround(l * 255));
}

int AbstractAppData::setPixel(Vector pos, COLORREF _color, HDC dc)
{
    return SetPixel(dc, lround(pos.x), lround(pos.y), _color);
}

COLORREF AbstractAppData::getPixel(Vector pos, HDC dc)
{
    return GetPixel(dc, std::lround(pos.x), std::lround(pos.y));
}

int AbstractAppData::updateScreen(Window* window)
{
    if (window)
    {
        //int isVisible = window->isVisible();
        if (true)
        {
            InvalidateRect(MAINWINDOW, NULL, FALSE);
            //dprintf("[%p] InvalidetedRect\n", window);
        }
    }
    return 0;
}

int AbstractAppData::updateNonClientAreaScreen(struct Window* window)
{
    HWND _wnd = MAINWINDOW;
    if (window)
    {
        //_wnd = window->hwnd;
    }
    SendMessage(_wnd, WM_NCPAINT, 0, 0);
    //int lasterr = GetLastError();
    return 0;
}

int AbstractAppData::invalidateRect(struct Window* window, Rect _rect, bool _erase /*= false*/)
{
    if (window)
    {
        int isVisible = window->isVisible();
        if (isVisible)
        {
            InvalidateRect(MAINWINDOW, NULL, FALSE);
            //dprintf("[%p] InvalidetedRect\n", window);
        }
    }
    return 0;
}

int AbstractAppData::captureMouse(HWND wnd/*= NULL*/)
{
    if (wnd == NULL) wnd = MAINWINDOW;
    dprintf("Mouse was captured\n");
    HWND captureWnd = SetCapture(wnd);

    if (captureWnd)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int AbstractAppData::releaseMouse(HWND wnd/*= NULL*/)
{
    if (wnd == NULL) wnd = MAINWINDOW;
    dprintf("Mouse was released\n");

    return (int)ReleaseCapture();
}

void AbstractAppData::line(Rect rect, HDC dc)
{
    line(rect.pos.x, rect.pos.y, rect.finishPos.x, rect.finishPos.y, dc);
}


void AbstractAppData::line(double x1, double y1, double x2, double y2, HDC dc)
{
    int result = MoveToEx(dc, std::lround(x1), std::lround(y1), NULL);
    result += LineTo(dc, std::lround(x2), std::lround(y2));
}

void AbstractAppData::line(Vector pos1, Vector pos2, HDC dc)
{
    line(pos1.x, pos1.y, pos2.x, pos2.y, dc);
}


void AbstractAppData::ellipse(Vector centrePos, Vector halfSize, HDC dc)
{
    ellipse(centrePos.x - halfSize.x, centrePos.y - halfSize.y, centrePos.x + halfSize.x, centrePos.y + halfSize.y, dc);
}

void AbstractAppData::ellipse(double x1, double y1, double x2, double y2, HDC dc)
{
    Ellipse(dc, std::lround(x1), std::lround(y1), std::lround(x2), std::lround(y2));
}

void AbstractAppData::circle(double x1, double y1, double r, HDC dc)
{
    ellipse({ x1, y1 }, { r, r }, dc);
}

void AbstractAppData::circle(Vector pos, double r, HDC dc)
{
    circle(pos.x, pos.y, r, dc);
}

void AbstractAppData::horizontalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize/* = {}*/)
{
    if (fullDCSize == fullDCSize.getNullVector()) fullDCSize = size;
    double posy = fullDCSize.y - size.y;

    RGBQUAD* tempBuf = {};
    HDC tempDC = createDIBSection(size, &tempBuf);


    for (int x = 0; x < size.x; x++)
    {
        for (int y = std::lround(posy); y < std::lround(fullDCSize.y); y++)
        {
            int tempY = std::lround(y - posy);
            int newY = std::lround(size.y - tempY - 1);
            tempBuf[x + (int)(newY * size.x)] = buf[x + (int)(y * fullDCSize.x)];
        }
    }
    bitBlt(dc, {}, size, tempDC);

    deleteDC(tempDC);
}

void AbstractAppData::verticalReflect(HDC dc, RGBQUAD* buf, Vector size, Vector fullDCSize/* = {}*/)
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


void AbstractAppData::bitBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource/* = 0*/, double ySource/* = 0*/)
{
    Vector size = getHDCSize(dc2);
    if (!sizex) sizex = size.x;
    if (!sizey) sizey = size.y;

    BitBlt(dc1, std::lround(x0), std::lround(y0), std::lround(sizex), std::lround(sizey), dc2, std::lround(xSource), std::lround(ySource), SRCCOPY);
    return;
}

void AbstractAppData::bitBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource/* = {}*/)
{
    bitBlt(dc1, pos.x, pos.y, size.x, size.y, dc2, posSource.x, posSource.y);
}

void AbstractAppData::bitBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource/* = {}*/)
{
    bitBlt(dc1, destRect.pos, destRect.getSize(), dc2, posSource);
}

void AbstractAppData::transparentBlt(HDC dc1, double x0, double y0, double sizex, double sizey, HDC dc2, double xSource/* = 0*/, double ySource/* = 0*/)
{
    assert(dc2);

    Vector size = getHDCSize(dc2);
    if (!sizex) sizex = size.x;
    if (!sizey) sizey = size.y;

    if(dc2)TransparentBlt(dc1, std::lround(x0), std::lround(y0), std::lround(sizex), std::lround(sizey), dc2, std::lround(xSource), std::lround(ySource), std::lround(sizex), std::lround(sizey), systemSettings->TRANSPARENTCOLOR);
}

void AbstractAppData::transparentBlt(HDC dc1, Vector pos, Vector size, HDC dc2, Vector posSource/* = {}*/)
{
    transparentBlt(dc1, pos.x, pos.y, size.x, size.y, dc2, posSource.x, posSource.y);
}

void AbstractAppData::transparentBlt(HDC dc1, Rect destRect, HDC dc2, Vector posSource/* = {}*/)
{
    transparentBlt(dc1, destRect.pos, destRect.getSize(), dc2, posSource);
}

int AbstractAppData::stretchBlt(HDC dest, double destPosx, double destPosy, double destSizex, double destSizey, HDC source, double sourcePosx, double sourcePosy, double sourceSizex, double sourceSizey)
{
    //dcout << destSizex << "|" << destSizey << "|||" << sourceSizex<<"|" << sourceSizey;
    return StretchBlt(dest, std::lround(destPosx), std::lround(destPosy), std::lround(destSizex), std::lround(destSizey), source, std::lround(sourcePosx), std::lround(sourcePosy), std::lround(sourceSizex), std::lround(sourceSizey), SRCCOPY);
}

int AbstractAppData::stretchBlt(HDC dest, Vector destPos, Vector destSize, HDC source, Vector sourcePos, Vector sourceSize)
{
    return stretchBlt(dest, destPos.x, destPos.y, destSize.x, destSize.y, source, sourcePos.x, sourcePos.y, sourceSize.x, sourceSize.y);
}


int AbstractAppData::stretchBlt(HDC dest, Rect destRect, HDC source, Rect sourceRect)
{
    return stretchBlt(dest, destRect.pos, destRect.getSize(), source, sourceRect.pos, sourceRect.getSize());
}


void AbstractAppData::compressImage(HDC& newDC, Vector newSize, HDC oldDC, Vector oldSize)
{
    assert(oldDC);

    if (!newDC) deleteDC(newDC);
    newDC = createDIBSection(newSize.x, newSize.y);
    assert(newDC);

    assert(stretchBlt(newDC, 0, 0, newSize.x, newSize.y, oldDC, 0, 0, oldSize.x, oldSize.y));
}

HDC AbstractAppData::getBufferDC(RGBQUAD** buf)
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

Vector AbstractAppData::getHDCSize(HDC _dc)
{
    if (!_dc)
    {
        return { -1, -1 };
    }
    HBITMAP _bitmap = (HBITMAP)GetCurrentObject(_dc, OBJ_BITMAP);
    return getHBITMAPSize(_bitmap);
}

Vector AbstractAppData::getHBITMAPSize(HBITMAP _bitmap)
{
    BITMAP bm;
    GetObject(_bitmap, sizeof(bm), (LPVOID)&bm);
    Vector answer = {};
    answer.x = bm.bmWidth;
    answer.y = bm.bmHeight;
    return answer;
}


void AbstractAppData::drawOnScreen(HDC dc, bool useAlpha /*=false*/)
{
    //if (!useAlpha)//txBitBlt(0, 0, dc);
    //if (useAlpha)transparentBlt(//txDC(), 0, 0, 0, 0, dc);
    //txSleep(0);
}

void AbstractAppData::cleanTransparentDC()
{
    //setColor(SystemSettings.TRANSPARENTCOLOR, transparentLay.lay);
   // rectangle(0, 0, transparentLay.laySize.x, transparentLay.laySize.y, transparentLay.lay);
    ////txClear(transparentLay.lay);
    //deleteTransparency(transparentLay.layBuf, transparentLay.laySize.x * transparentLay.laySize.y);
}

bool AbstractAppData::getAsyncKeyState(int symbol)
{
    return GetAsyncKeyState(symbol);
}

bool AbstractAppData::getKeyState(int symbol)
{
    short res = GetKeyState(symbol);
    int hiword = HIBYTE(res);
    if (hiword == 255) return 1;
    return 0;
}

int AbstractAppData::getMouseButton()
{
    return activeMouseButton;
}

void AbstractAppData::deleteTransparency(RGBQUAD* buf, unsigned int totalSize)
{
    for (int i = 0; i < (int)totalSize; i++)
    {
        buf[i].rgbReserved = 255;
    }
}


int AbstractAppData::needToLoadOldFiles()
{
    return filesCompability;
}


void AbstractAppData::deleteDC(HDC dc)
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
    else dprintf("DC, которые вы хотите удалить не существует\n");
}

int AbstractAppData::smartDeleteDC(HDC dc)
{
    return DeleteDC(dc);
}

int AbstractAppData::saveImage(HDC dc, const char* path)
{
    if (dllsaveImage)
    {
        int res = dllsaveImage(dc, path);
        return res;
    }
    dprintf("dllsaveImage не загрузилось\n");
    return NULL;
}


int AbstractAppData::DEBUGsaveImage(HDC dc, std::string _name/* = "1"*/)
{
    if (dllsaveImage)
    {
        int folderRes = _mkdir(".debug_screenshots");
        std::string finalName = ".debug_screenshots\\dbg_" + _name + ".bmp";
        int res = dllsaveImage(dc, finalName.c_str());
        return res;
    }
    dprintf("dllsaveImage не загрузилось\n");
    return NULL;
};

HDC AbstractAppData::loadImage(const char* path, Vector _size/* = {}*/)
{
    if (dllloadImage)
    {
        HDC _dc = dllloadImage(path, _size, this);
        return _dc;
    }
    dprintf("dllloadImage не загрузилось\n");
    return NULL;
}


int AbstractAppData::messageBox(const char  text[]/* = ""*/, const char  header[]/* = ""*/, unsigned  flags/* = MB_ICONINFORMATION | MB_OKCANCEL*/)
{
    return MessageBox(MAINWINDOW, text, header, flags);
}


bool AbstractAppData::isWindowMoving()
{
    return windowMovingStatus;
}


void AbstractAppData::changeWindow(Vector size/* = {}*/, Vector pos/* = {}*/)
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

int AbstractAppData::moveWindow(Vector _delta, HWND _wnd/* = 0*/)
{
    if (_wnd == 0)
    {
        _wnd = MAINWINDOW;
    }

    Rect _windowRect = getWindowRect(_wnd);
    Vector _pos = _windowRect.pos;
    _pos += _delta;
    return moveWindowTo(_pos, _wnd);


}


int AbstractAppData::moveWindowTo(Vector _pos, HWND _wnd/*=0*/)
{
    if (_wnd == 0)
    {
        _wnd = MAINWINDOW;
    }
    Rect _windowRect = getWindowRect(_wnd);
    Vector _size = _windowRect.getSize();
    //return MoveWindow(MAINWINDOW, std::lround(_pos.x), std::lround(_pos.y), std::lround(_size.x), std::lround(_size.y), TRUE);        r
    return 0;
}


Rect AbstractAppData::getWindowRect(HWND _wnd/* = 0*/)
{
    if (_wnd == 0)
    {
        _wnd = MAINWINDOW;
    }
    RECT _winAnswer = {};
    BOOL _winAnswerRes = GetWindowRect(_wnd, &_winAnswer);

    if (_winAnswerRes)
    {
        Rect _answer = {};
        _answer = _winAnswer;
        return _answer;
    }

    return {};
}

void AbstractAppData::setCursor(HCURSOR cursor/*= NULL*/)
{
    if (cursor == NULL) cursor = defaultCursor;
    activeCursor = cursor;
    dprintf("Cursor was set\n");
    lastTimeCursorSetTime = clock();
}

Vector AbstractAppData::getCursorPos()
{
    Vector _vector = {};
    POINT point = {};
    GetCursorPos(&point);
    _vector.x = point.x;
    _vector.y = point.y;
    return _vector;
}


long AbstractAppData::lround(double num)
{
    return std::lround(num);
}

double AbstractAppData::generateRandom(double min, double max, size_t precision/* = 0*/)
{
    if (min > max)
    {
        double copy = max;
        max = min;
        min = copy;
    }

    double _10pow = pow(10, precision);
    double _10min = min * _10pow;
    double _10max = max * _10pow;

    int range = (int)round(_10max - _10min);

    double num = rand() % range;

    num /= _10pow;

    num += min;

    return num;
}

double AbstractAppData::generateRandom(Vector range, size_t precision/* = 0*/)
{
    return generateRandom(range.x, range.y, precision);
}

template <typename T>
int AbstractAppData::findElement(const std::vector<T>& arr, const T& val, int startIndex/*=0*/, int finishIndex/*=0*/)
{
    if (finishIndex == 0)
    {
        size_t _size = arr.size();
        if (_size <= 0)
        {
            return -1;
        }
        finishIndex = (int)_size;
    }

    for (int  i = startIndex; i <= finishIndex; i++)
    {
        if (arr[i] == val)
        {
            return i;
        }
    }
    return -1;
}

bool AbstractAppData::isFullScreen()
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

Rect AbstractAppData::getUserRect()
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


void AbstractAppData::setResized(bool state/* = true*/)
{
    isResized = state;
}


UINT_PTR AbstractAppData::setTimer(int mslen)
{
    UINT_PTR idtimerNum = timerManager->getNewTimerNum();
    UINT_PTR timerNum = SetTimer(MAINWINDOW, idtimerNum, mslen, NULL);
    if (timerNum == 0)
    {
        dprintf("Таймер на %d мс с индифекатором %lld не поставился((", mslen, idtimerNum);
        return 0;
    }

    return idtimerNum;
}

int AbstractAppData::deleteTimer(UINT_PTR timer)
{
    return KillTimer(MAINWINDOW, timer);
}

/*   txVer
void AbstractAppData::controlApp()
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
*/

const char* findExtensionStart(const char* text, int extensionPos);


char* AbstractAppData::getOpenFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename)
{
    int fileNameLength = MAX_PATH;
    static char fileName[MAX_PATH] = "";

    sprintf(fileName, "%s", defaultFilename);

    OPENFILENAME ofn = { sizeof(OPENFILENAME) };

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST;

    //bool oldPSW = _//txProcessSystemWarnings;
    //_txProcessSystemWarnings = false;//отключает всякие системные проверки тхлибом иначе возникает ошибка 298

    GetOpenFileNameA(&ofn);
    //_//txProcessSystemWarnings = oldPSW;

    if (ofn.nFileOffset <= 0)
    {
        return NULL;
    }

    return fileName;
}



char* AbstractAppData::getSaveFileName(const char* question, const char* fileTypeDescribtion, const char* defaultFilename/* = NULL*/)
{
    int fileNameLength = MAX_PATH;
    static char fileName[MAX_PATH] = "";

    sprintf(fileName, "%s", defaultFilename);

    OPENFILENAME ofn = { sizeof(OPENFILENAME) };

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;

    //bool oldPSW = _//txProcessSystemWarnings;
    //_//txProcessSystemWarnings = false;//отключает всякие системные проверки тхлибом иначе возникает ошибка 298

    GetSaveFileNameA(&ofn);
    //_//txProcessSystemWarnings = oldPSW;

    if (ofn.nFileOffset <= 0)
    {
        return NULL;
    }

    const char* extension = findExtensionStart(fileTypeDescribtion, ofn.nFilterIndex);

    size_t extensionSize = strlen(extension);
    size_t realFilenameSize = strlen(fileName);
    if (strcmp(&fileName[realFilenameSize - extensionSize], extension))
    {
        sprintf(fileName, "%s.%s", fileName, extension);
    }

    return fileName;
}


const char* findExtensionStart(const char* text, int extensionPos)
{
    size_t startPos = 0;
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



