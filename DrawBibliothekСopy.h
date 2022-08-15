#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "TXLib.h"
#include "Q_Rect.h"
#include "Macroses.h"
#include "GlobalOptions.h"
#include "GRAPHICAPP\DebugInfo.h"

struct Manager;
struct Window;
struct Lay;

Lay *ActiveLay;




void txSetAllColors(DebugInfo info, COLORREF color, HDC dc = txDC(), int thickness = 1);
void compressDraw (DebugInfo info, HDC finalDC, Vector pos, Vector finalSize, HDC dc, Vector originalSize, int line = NULL);
void compressImage (DebugInfo info, HDC &newDC, Vector newSize, HDC oldDC, Vector oldSize, int line = NULL);
bool drag(DebugInfo info, Vector *objPos, Vector *lastTimePos, bool *dragedLastTime);
int standartManagerOnClick (DebugInfo info, Manager *manager);
void standartDraw (DebugInfo info, Window *window);
void standartManagerDraw (DebugInfo info, Manager *manager);
void clickButton (Window *window, Manager *manager);
void selectFont (DebugInfo info, const char *text, int font, HDC dc);
void swap (DebugInfo info, int &x0, int &y0);
void draw (Window *obj);
void resize (Window *obj, Rect newRect);



struct Lay
{
	HDC lay = {};
	Vector layCoordinats = {}; 
    Vector laySize = {};
	RGBQUAD *layBuf = {};
    HDC brightnessHDC = {};
    RGBQUAD *brightnessBuf = {};
	bool isClicked = false;

    void createLay (Vector size = {DCMAXSIZE, DCMAXSIZE});
    int getDownUpCoordinats (int x, int y);
	void line (int x0, int y0, int x1, int y1, COLORREF drawColor =  DrawColor);
	void circle (int x, int y, int r, COLORREF color = TX_BLACK);
    void rectangle (int x0, int y0, int x1, int y1);
};

struct Window
{
	Rect rect;
	Rect originalRect;
	COLORREF color;

	const char *text;
    int format = DT_CENTER;
    int font = MainFont;
    int sideThickness = SIDETHICKNESS;

	bool isClicked;
	HDC dc;

	HDC finalDC = NULL;
	RGBQUAD *finalDCArr = NULL;
    Vector finalDCSize = {}; 
	Manager *manager;
	bool advancedMode;
	bool reDraw;

    void (*resize) (Window *obj, Rect newSize);
    void (*draw) (Window *obj);

    Window (void (*_resize) (Window *obj, Rect newSize), Rect _rect = {}, COLORREF _color = MenuColor, HDC _dc = NULL, Manager *_manager = NULL, const char *_text = "", bool _advancedMode = true) :
		rect (_rect),
		color(_color),
		manager (_manager),
		text (_text), 
		isClicked (false), 
		dc (_dc),
		advancedMode (_advancedMode),
		reDraw (true),
        resize (_resize)
	{
		resize (this, rect);

		originalRect = rect;
	} 


	Vector getAbsCoordinats (bool coordinatsWithHandle = false);
    Vector getRelativeMousePos (bool coordinatsWithHandle = false);
	Rect getAbsRect (bool coordinatsWithHandle = false);
	
	
	//void resize (Vector newSize, Vector oldSize);
    void reInit ();
	void setStartRect (Vector pos, Vector finishPos);
	void print (HDC finalDC);
    

	Vector getSize();
	
	//virtual void onClick () {};

	//virtual void deleteButton ();
};

/*
struct Manager : Window
{
	int length;
	Window **pointers = NULL;
	int newButtonNum;
	Window *activeWindow;
	Window handle;
	Vector startCursorPos;
	bool coordinatSysFromHandle;
    bool HideIfIsNotActive;

	Manager (Rect _rect,  int _length, bool _advancedMode = true, HDC _dc = NULL, Rect _handle = {}, COLORREF _color = MenuColor, bool _coordinatSysFromHandle = false, bool _HideIfIsNotActive = false) :
		Window (_rect, _color, _dc, NULL, "", _advancedMode),
		length (_length),
		pointers (new Window*[_length]{}),
		newButtonNum (0),
		activeWindow (NULL), 
		handle (_handle),
		startCursorPos({}),
		coordinatSysFromHandle (_coordinatSysFromHandle),
        HideIfIsNotActive (_HideIfIsNotActive) 
	{
		handle.manager = this;
		handle.rect.finishPos.x = DCMAXSIZE * 10;
		handle.color = MenuColor;
	}

	bool addWindow (Window *window);
	Window *getActiveWindow ();
	void controlHandle ();
	void clickHandle ();
	void replaceWindow (int numOfWindow);
    void hide ();
    void unHide ();

	virtual void draw () override;
	virtual void onClick () override;

	virtual void deleteButton () override;
};
*/


