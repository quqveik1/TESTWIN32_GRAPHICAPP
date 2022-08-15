//#include "DrawBibliothekCopy.h"




void app->setColor (DebugInfo info, COLORREF color, HDC dc /*= txDc ()*/, int thickness)
{
    qassert (dc, info);
	txSetFillColor (color, dc); 
	txSetColor (color, thickness, dc);
}
#define app->setColor(...) app->setColor (getDebugInfo, __VA_ARGS__)

bool drag (DebugInfo info, Vector *objPos, Vector *lastTimePos, bool *dragedLastTime)
{
    qassert (objPos && lastTimePos, info);

    int mx = txMouseX();
    int my = txMouseY();
    if (*dragedLastTime == false && txMouseButtons() == 1)
    {
        lastTimePos->x = mx;
        lastTimePos->y = my;
        *dragedLastTime = true;
        //printf ("START");
    }
    if (*dragedLastTime)
	{
		objPos->x += mx - lastTimePos->x;
		objPos->y += my - lastTimePos->y;
        //printf ("[objpos: {%lf, %lf} | lastTimePos: {%lf, %lf} | delta: {%lf, %lf}]\n", objPos->x, objPos->y, lastTimePos->x, lastTimePos->y, mx - lastTimePos->x,  my - lastTimePos->y);
		lastTimePos->x = mx; 
		lastTimePos->y = my; 

        
	}
	if (txMouseButtons () != 1)
	{
		*dragedLastTime = false;
        return true;//true if finished
	}
    return false;
}
#define drag(...) drag (getDebugInfo, __VA_ARGS__)

 void compressImage (DebugInfo info, HDC &newDC, Vector newSize, HDC oldDC, Vector oldSize, int line)
{
    qassert (oldDC, info);
	char str[10] = {};
	sprintf(str, "%d", line);
		//newSize.print (str);

    if (!newDC) txDeleteDC (newDC);
	newDC = txCreateCompatibleDC (newSize.x, newSize.y);
    qassert (newDC, info);

	qassert (StretchBlt (newDC, 0, 0, newSize.x, newSize.y, oldDC, 0, 0, oldSize.x, oldSize.y, SRCCOPY), info);

 }
#define compressImage(...) compressImage (getDebugInfo, __VA_ARGS__);






void compressDraw (DebugInfo info, HDC finalDC, Vector pos, Vector finalSize, HDC dc, Vector originalSize, int line)
{
    qassert (finalDC && dc, info);
	HDC copyDC = NULL;
	//if (test1)printBlt (dc);
	compressImage (copyDC, finalSize, dc, originalSize, line);
	//printBlt (dc);
	app->bitBlt (finalDC, pos.x, pos.y, finalSize.x, finalSize.y, copyDC);
	
    txDeleteDC (copyDC);
}
#define compressDraw(...) compressDraw (getDebugInfo, __VA_ARGS__);









void selectFont (DebugInfo info, const char *text, int font, HDC dc)
{
    txSelectFont ("Arial", font, -1, FW_DONTCARE, false, false, false, 0, dc);    
}

#define selectFont(...) selectFont (getDebugInfo, __VA_ARGS__)

void standartDraw (DebugInfo info, Window *window)
{
    qassert (window, info);
    $s                                                                                     
	if (window->finalDC) app->setColor (window->color, window->finalDC);                                           
	if (window->finalDC) app->rectangle (0, 0, window->rect.getSize ().x, window->rect.getSize ().y, window->finalDC);        
                                                                                           
                                                                                          
	if (window->finalDC) app->setColor (TextColor, window->finalDC);                                     
	txSetTextAlign (TA_CENTER, window->finalDC);
    selectFont ("Arial", window->font, window->finalDC);
    window->app->drawText(window->sideThickness, window->sideThickness, window->rect.getSize().x, window->rect.getSize().y, window->text, window->finalDC, window->format);
                                                                                           
                                                                                          
	if (window->dc)                                                                                
	{                                                                                           
		compressDraw (window->finalDC, {0, 0}, window->rect.getSize (), window->dc, window->originalRect.getSize ());
	}                                                                                         
}
#define standartDraw(...) standartDraw (getDebugInfo, __VA_ARGS__);


int standartManagerOnClick (DebugInfo info, Manager *manager)
{
    qassert (manager, info);
    bool missClicked = true;

	int mx = txMouseX ();
	int my = txMouseY ();
    int returnableVal = -1;

    //if (HideIfIsNotActive) unHide ();

	if (manager->advancedMode)
	{
		manager->clickHandle();
		if (manager->handle.getAbsRect().inRect (mx, my))
		{
			manager->startCursorPos.x = mx;
			manager->startCursorPos.y = my;
			manager->handle.isClicked = true;
		}
		for (int i = manager->newButtonNum - 1; i >= 0; i--)
		{
			if (manager->pointers[i]->getAbsRect().inRect(mx, my))
			{
				clickButton (manager->pointers[i], manager);

				missClicked = false;
                returnableVal=  i;
				if (manager->pointers[i]->advancedMode) break;
			}
			else
			{
				manager->pointers[i]->isClicked = false;

				missClicked = true;
			}
		}
	}

	if (missClicked == true) manager->activeWindow = NULL;

    return returnableVal;
}
#define standartManagerOnClick(...) standartManagerOnClick (getDebugInfo, __VA_ARGS__);


void standartManagerDraw (DebugInfo info, Manager *manager)
{
    qassert (manager, info);

    manager->controlHandle ();

    //if (manager->HideIfIsNotActive && manager->activeWindow != this) 
    //{
        //hide ();
    //}

	app->setColor (manager->color, manager->finalDC);
	//app->rectangle (0, 0, DCMAXSIZE, DCMAXSIZE, manager->finalDC);
	if (manager->dc) app->bitBlt (manager->finalDC, 0, 0, 0, 0, manager->dc);


	for (int i = 0; i < manager->newButtonNum; i++)
	{
		if (manager->pointers[i]->advancedMode && manager->pointers[i]->reDraw) manager->pointers[i]->draw (manager);
 		if (manager->pointers[i]->advancedMode) 
		{
			app->bitBlt (manager->finalDC, manager->pointers[i]->rect.pos.x, manager->pointers[i]->rect.pos.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);
			//bitBlt (finalDCArr, pointers[i]->rect.pos.x, pointers[i]->rect.pos.y, pointers[i]->rect.getSize().x, pointers[i]->rect.getSize().y, pointers[i]->finalDCArr, pointers[i]->finalDCSize.x, pointers[i]->finalDCSize.y, finalDCSize.x, finalDCSize.y);	
			//printBlt (pointers[i]->finalDC);
		}
		if (txMouseButtons () != 1)
		{
			manager->pointers[i]->isClicked = false;
		}
	}

	if (manager->getActiveWindow () != manager && manager->manager) 
	{
		manager->activeWindow = NULL;
	
    }
}
#define standartManagerDraw(...) standartManagerDraw (getDebugInfo, __VA_ARGS__);


void Lay::createLay	(Vector _laySize)
{
    //qassert (manager, info);
    laySize = _laySize;
	lay = app->createDIBSection (laySize.x, laySize.y, &layBuf);
	//brightnessHDC = app->createDIBSection (DCMAXSIZE, DCMAXSIZE, &brightnessBuf);


	for (int y = 0; y < laySize.x; y++)
	{
		for (int x = 0; x < laySize.y; x++)
		{
			RGBQUAD* copy = &layBuf[x + y * DCMAXSIZE];
			//copy->rgbRed      = (BYTE) 0;
			//copy->rgbGreen    = (BYTE) 0;
			//copy->rgbBlue     = (BYTE) 0;
			copy->rgbReserved = (BYTE) 0;
		}
	}
}


int Lay::getDownUpCoordinats (int x, int y)
{
    return (int) (x + (laySize.y - y) * laySize.x); 
}


void swap (DebugInfo info, int &x0, int &y0)
{
    assert (&x0 && &y0);
    int copy = x0;
    x0 = y0;
    y0 = copy;
}
#define swap(...) swap (getDebugInfo, __VA_ARGS__)


void Lay::line(int x0, int y0, int x1, int y1, COLORREF drawColor) 
{
	bool steep = false;
	if (abs (x0 - x1) < abs (y0 - y1)) 
	{
		swap (x0, y0);
		swap (x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		swap (x0, x1);
		swap (y0, y1);
	}
	int dx = x1-x0;
	int dy = y1-y0;
	int derror2 = abs (dy) * 2;
	int error2 = 0;
	int y = y0;

	for (int x = x0; x <= x1; x++)
	{
		if (steep) 
		{
			RGBQUAD* color = &layBuf[getDownUpCoordinats(y, x)];
			color->rgbRed = txExtractColor (drawColor, TX_RED);
			color->rgbGreen = txExtractColor (drawColor, TX_GREEN);
			color->rgbBlue = txExtractColor (drawColor, TX_BLUE);
			color->rgbReserved = 255;
		} 
		else 
		{
			RGBQUAD* color = &layBuf[getDownUpCoordinats(x, y)];
			color->rgbRed = txExtractColor (drawColor, TX_RED);
			color->rgbGreen = txExtractColor (drawColor, TX_GREEN);
			color->rgbBlue = txExtractColor (drawColor, TX_BLUE);
			color->rgbReserved = 255;
		}
		error2 += derror2;

		if (error2 > dx) 
		{
			y += (y1 > y0 ? 1 : -1);

			error2 -= dx * 2;
		}
	}
}


void Lay::rectangle (int x0, int y0, int x1, int y1)
{
    if (x0 > x1) swap (x0, x1);
    if (y0 > y1) swap (y0, y1);
    COLORREF currColor = txGetColor (lay);

    for (int x = x0; x <= x1; x++)
    {
        //line (x, y0, x, y1);
        
        for (int y = y0; y <= y1; y++)
        {
            RGBQUAD *pixel = &layBuf[getDownUpCoordinats(x, y)];
            pixel->rgbRed = txExtractColor (currColor, TX_RED);
            pixel->rgbGreen = txExtractColor (currColor, TX_GREEN);
            pixel->rgbBlue = txExtractColor (currColor, TX_BLUE);
            pixel->rgbReserved = 255;
        }
    }
   // app->setColor (TX_RED, lay);
    //app->rectangle (x0, y0, x1, y1, lay);
    //printBlt (lay);
}


void Lay::circle (int x0, int y0, int r, COLORREF color)
{
    
	for (double t = 0; t <= 1; t += 0.001)
	{
		double x = x0 - r + t * 2 *(r);
		int y1 = sqrt (r * r - (x - x0) * (x - x0)) + y0;
		int y2 = -sqrt (r * r - (x - x0) * (x - x0)) + y0;

		//printf ("x: %lf y = {%lf, %lf}\n", x, y1, y2);
		//app->setColor (TX_RED, lay);
		//txSetColor (TX_RED, 2);
		//app->line (x, y1, x, y2, lay);
		//if (x >= 0 && y1 >= 0 && y2 >= 0)
		line (x, y1, x, y2, color);
	}
}


Window* Manager::getActiveWindow ()
{
	if (this == NULL) return 0;

	return activeWindow;
}


bool Manager::addWindow (Window *window)
{
    assert (window);
	if (newButtonNum >= length) return 0;

	pointers[newButtonNum] = window;
	newButtonNum++;

	window->manager = this;
	
	return 1;
}


void Window::print (HDC DC)
{
    assert (DC);
	draw();
	app->bitBlt (DC, rect.pos.x, rect.pos.y, rect.getSize().x, rect.getSize().y, finalDC);
}

Vector Window::getSize()
{
	return this->rect.finishPos - this->rect.pos;
}

void draw (Window *obj)
{
    assert (obj);   
	standartDraw(obj);
}

void Window::deleteButton ()
{

	//printBlt (dc);
	////if (dc) txDeleteDC (dc);
	///=if (finalDC) txDeleteDC (finalDC);
}

void resize (Window *obj, Rect newRect)
{
    //assert (newRect.isValid());
	if (obj->newRect.getSize().x > 0 && obj->newRect.getSize().y > 0)
	{
		obj->finalDCSize = {obj->newRect.getSize().x, obj->newRect.getSize().y};
		obj->finalDC = app->createDIBSection(obj->finalDCSize.x, obj->finalDCSize.y, &(obj->finalDCArr));
		app->setColor(obj->color, obj->finalDC);
		app->rectangle(0, 0, obj->newRect.getSize().x, obj->newRect.getSize().y, obj->finalDC);
		printBlt(obj->finalDC);
	}
    rect = newRect;
}

void Window::reInit ()
{
    if (rect.getSize().x > 0 && rect.getSize().y > 0)
	{
			finalDCSize = {rect.getSize().x, rect.getSize().y};
			finalDC = app->createDIBSection(finalDCSize.x, finalDCSize.y, &finalDCArr);
			app->setColor(color, finalDC);
			app->rectangle(0, 0, rect.getSize().x, rect.getSize().y, finalDC);
			if (test1) printBlt(finalDC);
	}

	originalRect = rect;
}

/*
void Window::resize (Vector newSize, Vector oldSize)
{
	assert (newSize > 0 && oldSize > 0);
	if (!dc) return;
	//compressImage (dc, newSize, {rect.getSize().x, rect.getSize().y});
	//if (test1) printBlt (dc);
	rect = {.pos = rect.pos * newSize / oldSize, .finishPos = rect.finishPos * newSize / oldSize};
}     */

void Window::setStartRect (Vector pos, Vector finishPos)
{
    assert (pos > 0 && finishPos > 0);
	rect = {pos, finishPos};
	originalRect = rect;
}
Vector Window::getRelativeMousePos (bool coordinatsWithHandle)
{
    return {(double)txMouseX() - getAbsCoordinats(coordinatsWithHandle).x, (double) txMouseY () - getAbsCoordinats(coordinatsWithHandle).y};    
}

Vector Window::getAbsCoordinats (bool coordinatsWithHandle /*=false*/)
{
	Vector coordinats = {};

	Manager *copyOfManager = manager;

	coordinats += rect.pos;

	for (;;)
	{
		if (!copyOfManager) break;

		coordinats = coordinats + copyOfManager->rect.pos;
		if (copyOfManager->coordinatSysFromHandle && !coordinatsWithHandle) coordinats.y += copyOfManager->handle.rect.finishPos.y;
		copyOfManager = copyOfManager->manager;

	}

	return coordinats;
}

Rect Window::getAbsRect (bool coordinatsWithHandle /*=false*/)
{
	Rect coordinats = {};

	Manager *copyOfManager = manager;

	coordinats.pos += rect.pos;

	for (;;)
	{
		if (!copyOfManager) break;

		coordinats.pos += copyOfManager->rect.pos;
		if (copyOfManager->coordinatSysFromHandle && !coordinatsWithHandle)
		{
			coordinats.pos.y += copyOfManager->handle.rect.finishPos.y;
		}
		copyOfManager = copyOfManager->manager;
	}

	coordinats.finishPos = rect.finishPos + (coordinats.pos - rect.pos);

	return coordinats;
}


void Manager::deleteButton ()
{
	if (dc) txDeleteDC (dc);
	if (finalDC) txDeleteDC (finalDC);
	for (int i = 0; i < length; i++)
	{
		if (pointers[i]) pointers[i]->deleteButton ();
	}
}

void Manager::draw ()
{
    standartManagerDraw (this);	
}

void Manager::clickHandle ()
{
	if (handle.getAbsRect(true).inRect (txMouseX (), txMouseY ()))
	{
		startCursorPos.x = txMouseX ();
		startCursorPos.y = txMouseY ();
		handle.isClicked = true;
	}
}

void Manager::controlHandle ()
{
	if (handle.isClicked)
	{
		rect.pos.x += txMouseX () - startCursorPos.x;
		rect.pos.y += txMouseY () - startCursorPos.y;
		rect.finishPos.x += txMouseX () - startCursorPos.x;
		rect.finishPos.y += txMouseY () - startCursorPos.y;
		startCursorPos.x = txMouseX (); 
		startCursorPos.y = txMouseY (); 
	}
	if (txMouseButtons () != 1)
	{
		handle.isClicked = false;
	}
	//drawOnFinalDC (handle);
}


/*
void Manager::replaceWindow (int numOfWindow, int startOfWindows)
{
	Window *copyOfStartWindow = pointers[numOfWindow];
	Window *copyOfWindow = pointers[startOfWindows];

	for (int i = startOfWindows; i < numOfWindow; i++)
	{
		Window* preCopyOfWindow = pointers[i + 1];
		pointers[i + 1] = copyOfWindow;
		copyOfWindow = 	preCopyOfWindow;
	}

	 if (startOfWindows < numOfWindow) pointers[startOfWindows] = copyOfStartWindow;

}
*/


void Manager::hide ()
{
    advancedMode = false;
}
void Manager::unHide ()
{
    advancedMode = true;
}

void Manager::replaceWindow(int numOfWindow)
{
	Window* copyOfStartWindow = pointers[numOfWindow];
	Window* copyOfWindow = pointers[newButtonNum - 1];

	for (int i = newButtonNum - 1; i > numOfWindow; i--)
	{
		Window* preCopyOfWindow = pointers[i - 1];
		pointers[i - 1] = copyOfWindow;
		copyOfWindow = preCopyOfWindow;
	}

	if (numOfWindow < newButtonNum - 1) 
	{
		pointers[newButtonNum - 1] = copyOfStartWindow;
	}

}

void Manager::onClick ()
{
    standartManagerOnClick (this);	
}

void clickButton (Window *window, Manager *manager)
{
    manager->activeWindow = window;
	window->onClick ();
	window->isClicked = true;
}
