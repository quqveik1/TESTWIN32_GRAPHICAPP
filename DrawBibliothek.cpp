#pragma once
#include "DrawBibliothek.h"




bool drag$ (DebugInfo info, Vector *objPos, Vector *lastTimePos, bool *dragedLastTime, bool clicked)
{
    qassert (objPos && lastTimePos, info);

    /*
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
	if (clicked != 1)
	{
		*dragedLastTime = false;
        return true;//true if finished
	}
    */
    return false;
}

void standartDraw$ (Window *window)
{
    gassert (window);
    $s

    AbstractAppData* app = window->app;
    assert(app);

    if (window->needToShow)
    {

        if (window->finalDC) app->setColor(window->color, window->finalDC);
        if (window->finalDC) app->rectangle(0, 0, window->rect.getSize().x, window->rect.getSize().y, window->finalDC);

        if (window->text)
        {
            app->setColor(window->systemSettings->TextColor, window->finalDC);
            app->selectFont(window->fontName, window->font, window->finalDC);
            app->drawText(0, 0, window->rect.getSize().x, window->rect.getSize().y, window->text, window->finalDC, window->format);
        }

        if (window->dc)
        {
            app->bitBlt(window->finalDC, 0, 0, window->rect.getSize().x, window->rect.getSize().y, window->dc);
        }
    }
}


const char* getCustomFilePath(const char* question, const char* fileTypeDescribtion)
{
    char fileName[MAX_PATH] = "";

    OPENFILENAME ofn = { sizeof(ofn) }; 

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;

    ofn.Flags = OFN_PATHMUSTEXIST;

    if ((GetOpenFileNameA))
        (GetOpenFileNameA(&ofn));


    return fileName;
}

/*
const char* getCustomFilePathForSaving(const char* question, const char* defaultFilename, const char* fileTypeDescribtion)
{
    int fileNameLength = MAX_PATH;
    char fileName[MAX_PATH] = "";

    sprintf(fileName, "%s", defaultFilename);

    OPENFILENAME ofn = { sizeof(OPENFILENAME), txWindow() };

    ofn.lpstrTitle = question;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = (fileTypeDescribtion);
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;

    bool oldPSW = _txProcessSystemWarnings;
    _txProcessSystemWarnings = false;//отключает всякие системные проверки тхлибом иначе возникает ошибка 298

    if ((GetSaveFileNameA))
        (GetSaveFileNameA(&ofn));
    _txProcessSystemWarnings = oldPSW;

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
*/







int standartManagerOnClick$ (Manager *manager, Vector mp)
{
    gassert (manager);

    bool missClicked = true;

    int returnableVal = -1;

    //if (HideIfIsNotActive) unHide ();

	if (manager->needToShow)
	{
        manager->setActiveWindow(manager);
		manager->clickHandle();
		for (int i = manager->currLen - 1; i >= 0; i--)
		{
			if (manager->pointers[i]->rect.inRect(mp))
			{
				clickButton (manager->pointers[i], manager, mp);

				missClicked = false;
                returnableVal = i;
				if (manager->pointers[i]->needToShow) break;
			}
			else
			{
				missClicked = true;
			}
		}
	}

    return returnableVal;
}



void standartManagerDraw$ (Manager *manager)
{
    gassert (manager);

    manager->controlHandle ();

    AbstractAppData* app = manager->app;
    assert(app);

	if (manager->dc) app->bitBlt (manager->finalDC, 0, 0, 0, 0, manager->dc);

    int test1 = 0;
    if (manager->needToShow)
    {
        for (int i = 0; i < manager->getCurLen(); i++)
        {
            if (manager->pointers[i]->reDraw) manager->pointers[i]->draw();
            if (manager->pointers[i]->needToShow)
            {
                if (manager->pointers[i]->needTransparencyOutput) app->transparentBlt(manager->finalDC, manager->pointers[i]->rect.pos.x, manager->pointers[i]->rect.pos.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);
                else                                              app->bitBlt(manager->finalDC, manager->pointers[i]->rect.pos.x, manager->pointers[i]->rect.pos.y, manager->pointers[i]->rect.getSize().x, manager->pointers[i]->rect.getSize().y, manager->pointers[i]->finalDC);
            }
        }
    }
}


void swap$ (DebugInfo info, int &x0, int &y0)
{
    assert (&x0 && &y0);
    int copy = x0;
    x0 = y0;
    y0 = copy;
}




void clickButton (Window *window, Manager *manager, Vector mp)
{
	window->onClick (mp - window->rect.pos);
}
