#pragma once
//depricated
#include "Canvas.h"
#include "ZoneSizeControl.cpp"
#include "ImportTool.cpp"
#include "ToolManager.cpp"
#include "Lay.cpp"
#include "CLay.cpp"

Canvas::Canvas(AbstractAppData* _app, Rect _rect, const char* _name) :
    Manager(_app, _rect, 5, true, NULL, { .pos = {0, 0}, .finishPos = {_rect.getSize().x, _app->systemSettings->HANDLEHEIGHT} }),
    canvasCoordinats({}),
    laysSize(_rect.getSize()),
    DrawingModeLastTime(((PowerPoint*)app)->toolManager->getActiveToolNum()),
    zoneSizeControl(this, &rect, &needFrameToWork),
    finalLay()
{
    finalLay.setSize(laysSize, app);
    app->setColor(backgroungColor, finalLay);
    app->rectangle({}, laysSize, finalLay);
    if (_name)strcpy(name, _name);
    createLay();
}

Canvas::~Canvas()
{
    if (finalDC) app->deleteDC(finalDC);
    if (finalLay) app->deleteDC(finalLay);

    int _ll = getCurrentLayLength();
    for (int i = 0; i < _ll; i++)
    {
        delete lay[i];
    }
}

int Canvas::separateWindow(int pos)
{
    if (getCurLen() == 1)
    {
        pointers[getCurLen() - 1] = NULL;
        getCurLen()--; 
        return getCurLen();
    }
    return -1;
}

void Canvas::createLay()
{
    assert(!(currentLayersLength >= LayersNum));
    CLay* newlay = new CLay(app, this, laysSize);
    lay[currentLayersLength] = newlay;
    if (currentLayersLength <= LayersNum) currentLayersLength++;

    activeLayNum = currentLayersLength - 1;
    app->updateScreen(this);    
}

void Canvas::controlImportingImages()
{
    static int lastTimetoolNum = -1;

    if (wasLastTimeImporting && getCurrentlyImportingImage())
    {
        app->deleteDC(getCurrentlyImportingImage());
        getCurrentlyImportingImage() = NULL;
        wasLastTimeImporting = false;
        ((PowerPoint*)app)->toolManager->setActiveToolNum(lastTimetoolNum);
    }

    if (getCurrentlyImportingImage())
    {
        lastTimetoolNum = ((PowerPoint*)app)->toolManager->getActiveToolNum();
    }
}

void Canvas::startTool()
{
    initToolLay();
}

void Canvas::changeTool(Tool2* tool)
{
    setToolToToolLay(getActiveLay()->getActiveToolLay(), getActiveTool());
    getActiveLay()->needRedraw();
}

void Canvas::initToolLay()
{
    addToolLay();

    currentToolLength++;
}

void Canvas::addToolLay()
{
    assert(LayersNum >= currentToolLength);
    CLay* clay = getActiveLay();
    assert(clay);
    clay->isNewToolLayCreated = true;
    ToolLay* toollay = getNewToolLay();
    setToolToToolLay(toollay, getActiveTool());
}


void Canvas::setToolToToolLay(ToolLay* toollay, Tool2* tool)
{
    toollay->addTool(tool);
}

void Canvas::setCurrentData()
{
    currentDate.mousePos = getMousePos();
    currentDate.managerPos = getAbsCoordinats();
    currentDate.color = app->systemSettings->DrawColor;
    currentDate.canvasCoordinats = canvasCoordinats;
    currentDate.backGroundColor = TX_BLACK;
    if (getMBCondition() == 0) currentDate.clickedMB = 0;
}

ToolLay* Canvas::getNewToolLay()
{
    return NULL;
}

bool Canvas::isDrawingModeChanged()
{        
    return false;
    //return DrawingModeLastTime != systemSettings->DrawingMode;
}

Tool2* Canvas::getActiveTool()
{
    return NULL;
    //if (app->systemSettings->DrawingMode <= 0 || app->toolManager->currentLength <= 0) return NULL;
    //return app->toolManager->tools[app->systemSettings->DrawingMode - 1];
}

void Canvas::setActiveToolLayNum(int num)
{
    if (!getActiveLay() || !getActiveLay()->getActiveToolLay()) return;
    getActiveLay()->setActiveToolLayNum(num);
    if (getActiveLay()->getActiveToolLay()->isFinished()) editingMode = 1;
    else editingMode = 0;
};

int Canvas::getLastNotStartedToolNum()
{
    return getCurrentToolLengthOnActiveLay();
}

void Canvas::onClick(Vector mp)
{
    setActiveWindow(this);
    mp = getMousePos();

    if (getMBCondition() == 1)
    {
        if (zoneSizeControl.clickFrame()) return;
    }

    //independet scenery block++++++++++++++++++++++++++++++++++++++++++++++++++++
    if (getActiveLay())
    {
        currentDate.clickedMB = getMBCondition();
    }
    //independet scenery block----------------------------------------------------

    setMbLastTime();
}

int Canvas::mbDown(Vector mp, int button)
{
    if (rect.inRect(mp + rect.pos))
    {
        CLay* _clay = getActiveLay();
        int _reaction = app->getReactionOnMSG();
        if (_clay && _reaction == 0)
        {
            Vector laymp = convertMousePosForLay(mp);
            _clay->mbDown(laymp, button);
            app->declareReactionOnMSG(1);
        }
    }
    return 0;
}

int Canvas::mbUp(Vector mp, int button)
{
    CLay* _clay = getActiveLay();
    if (_clay)
    {
        Vector laymp = convertMousePosForLay(mp);
        _clay->mbUp(laymp, button);
    }
    return 0;
}

int Canvas::onMouseMove(Vector mp, Vector delta)
{
    CLay* _clay = getActiveLay();
    if (_clay)
    {
        Vector laymp = convertMousePosForLay(mp);
        _clay->onMouseMove(laymp, delta);
    }

    return 0;
}

Vector Canvas::getMousePos()
{
    Vector mp = manager->getMousePos() - rect.pos;
    if (!isEqual(rect.getSize().x, 0)) mp.x *= laysSize.x / rect.getSize().x;
    else mp.x = 0;
    if (!isEqual(rect.getSize().y, 0)) mp.y *= laysSize.y / rect.getSize().y;
    else mp.y = 0;
    return mp;

}

Vector Canvas::convertMousePosForLay(Vector mp)
{
    Vector _laySize = getLaySize();
    Vector _size = rect.getSize();
    if (!isEqual(_size.x, 0)) mp.x *= _laySize.x / _size.x;
    else mp.x = 0;
    if (!isEqual(_size.y, 0)) mp.y *= _laySize.y / _size.y;
    else mp.y = 0;
    return mp;

}

void Canvas::draw()
{
    if (app->systemSettings->debugMode >= 3) printf("Canvas clicked: %d\n", getMBCondition());
    if (app->systemSettings->debugMode >= 3) printf(" Canvasrect.pos: {%lf, %lf}\n", rect.pos.x, rect.pos.y);

    CLay* activeLay = getActiveLay();
    if (activeLay)
    {
        controlLay();
        drawLays();
    }
    
    if (posLastTime != rect.pos) reDraw = true;
    copyFinalLayOnFinalDC();


    DrawingModeLastTime = ((PowerPoint*)app)->toolManager->getActiveToolNum();

    setMbLastTime();

    posLastTime = rect.pos;
}

void Canvas::controlStretching()
{
    if (getSize() != laysSize * scale)
    {
        if (isBigger(scale, 0))
        {
            setNewCanvasSize(laysSize * scale);
        }
        else
        {
            rect.pos = {};
            rect.finishPos = laysSize * scale;
        }

        reDraw = true;
    }
}

void Canvas::resize(Vector newSize)
{
    if (isBigger (newSize.x, 0) && isBigger (newSize.y, 0))
    {
        rect = { .pos = rect.pos, .finishPos = rect.pos + newSize };
        if (isBigger(newSize.x, app->systemSettings->SizeOfScreen.x)) newSize.x = app->systemSettings->SizeOfScreen.x;
        if (isBigger(newSize.y, app->systemSettings->SizeOfScreen.y)) newSize.y = app->systemSettings->SizeOfScreen.y;
        finalDCSize = newSize;

        finalDC.setSize(finalDCSize, app, &finalDCArr);
        Vector _s = finalDC.getSize();

        app->setColor(color, finalDC);
        app->rectangle(0, 0, finalDCSize.x, finalDCSize.y, finalDC);
    }
}

void Canvas::copyFinalLayOnFinalDC()
{
    if (reDraw)
    {
        if (laysSize == getSize())
        {
            COLORREF pixCol = GetPixel(finalLay, 0, 0);
            app->setColor(TX_WHITE, finalDC);
            app->rectangle({}, { 1000, 1000 }, finalDC);
            app->bitBlt(finalDC, {}, laysSize, finalLay);
        }
        else
        {
            
            Vector layStartPos = {};
            if (isSmaller(rect.pos.x, 0))
            {
                if (!isEqual(getSize().x, 0)) layStartPos.x = ((0 - rect.pos.x) / getSize().x) * laysSize.x;
            }

            if (isSmaller(rect.pos.y, 0))
            {
                if (!isEqual(getSize().y, 0)) layStartPos.y = ((0 - rect.pos.y) / getSize().y) * laysSize.y;
            }

            Vector necessaryLaySize = {};
            if (getSize() > 0) necessaryLaySize = (finalDCSize / getSize()) * laysSize;
            
            app->stretchBlt(finalDC, {}, finalDCSize, finalLay, layStartPos, necessaryLaySize);
            //app->bitBlt(finalDC, {}, laysSize, finalLay);
        }
        reDraw = false;
    }

    if (app->systemSettings->debugMode >= 3 && getSize() > 0) printf("Canvas: (finalDCSize) / getSize()): {%lf, %lf}\n", (finalDCSize.x) / getSize().x, (finalDCSize.y) / getSize().y);
}

void Canvas::print(M_HDC& _dc)
{
    draw();
    Vector outputPos = rect.pos;
    if (isSmaller(outputPos.x, 0) && finalDCSize.x != getSize().x) outputPos.x = 0;
    if (isSmaller(outputPos.y, 0) && finalDCSize.y != getSize().y) outputPos.y = 0;

    app->bitBlt(_dc, outputPos, finalDCSize, finalDC);
}

Vector Canvas::setNewCanvasSize(Vector newSize)
{
    if (newSize > 0)
    {
        assert(manager);
        scale = newSize.x / laysSize.x;

        resize(newSize);
        app->updateScreen(this);

        reDraw = true;
    }
    else
    {
        rect.pos = {};
        rect.finishPos = newSize;
        reDraw = true;
    }

    return getSize();

}

void Canvas::stretchCanvas(double percantageFromOriginal)
{
    Vector newSize = getSize();
    if (newSize > 0)newSize += laysSize * percantageFromOriginal;
    setNewCanvasSize(newSize);
}

HDC Canvas::getImageForSaving()
{
    /*
    if (!getActiveLay()) return NULL;
    HDC notClearedDC = getActiveLay()->lay.lay;

    M_HDC clearedMDC;
    clearedMDC.setSize(getActiveLay()->lay.laySize, app);

    app->setColor(backgroungColor, clearedMDC);
    app->rectangle({}, getActiveLay()->lay.laySize, clearedMDC);

    app->transparentBlt(clearedMDC, 0, 0, 0, 0, notClearedDC);

    HDC clearedDC = (HDC)clearedMDC.obj;
    //������ M_HDC
    return clearedDC;
    */
    return NULL;
    //�������� HDC ������� ������� ����� �������������
}

int Canvas::importImage(HDC dc)
{
    if (!getActiveLay()) createLay();
    currentlyImportingImage = dc;
    editingMode = 0;
    getActiveLay()->setActiveLastToolLay();
    return 1;
}

HDC& Canvas::getCurrentlyImportingImage()
{
    return currentlyImportingImage;
}

int Canvas::getActiveLayNum()
{
    return activeLayNum;
}

int Canvas::getCurrentLayLength()
{
    return  currentLayersLength;
}

CLay* Canvas::getActiveLay()
{
    if (activeLayNum < 0 /*|| !lay[activeLayNum]->toolLays*/) return NULL;
    return (lay[activeLayNum]);
}

Vector Canvas::getLaySize()
{
    CLay* _lay = getActiveLay();
    if (_lay)
    {
        return _lay->getSize();
    }
    return {};
}

int Canvas::getEditingMode()
{
    return editingMode;
}

int Canvas::getCurrentToolLengthOnActiveLay()
{
    if (!getActiveLay()) return 0;
    if (!getActiveLay()->getActiveToolLay()) return 0;
    int length = getActiveLay()->getCurrentSize() - 1;
    return length;
}

const char* Canvas::getName()
{
    return name;
}

double& Canvas::getScale()
{
    return scale;
}

void Canvas::deleteButton()
{
    if (dc) app->deleteDC(dc);
    if (finalDC) app->deleteDC(finalDC);
}

void Canvas::controlTool()
{
    CLay* clay = getActiveLay();
    assert(clay);

    if (!clay->isNewToolLayCreated)
    {
        startTool();
    }

    ToolLay* toollay = clay->getActiveToolLay();
    assert(toollay);
    bool isFinished = toollay->isFinished();


    setCurrentData();
    if (!isFinished)
    {
  
        /*
        if (isDrawingModeChanged())
        {
            changeTool(getActiveTool());
        }
        if (systemSettings->debugMode == 5) printf("Num:%d_IsFinished:%d", clay->getActiveToolLayNum(), isFinished);
        if (toollay->useTool(&currentDate))
        {
            finishTool();
        }
        */
    }
}

int Canvas::controlLay()
{
    setCurrentData();

    CLay* clay = getActiveLay();
    assert(clay);

    controlImportingImages();

    clay->controlTool(&currentDate);

    return 0;
}

int Canvas::setActiveLay(int pos)
{
    if (pos >= 0 && pos < LayersNum)
    {
        CLay* _lay = lay[pos];
        if (_lay)
        {
            return activeLayNum = pos;
        }
    }

    return -1;
}

int Canvas::setActiveLay(CLay* _lay)
{
    if (_lay)
    {
        int _l = getCurrentLayLength();
        for (int i = 0; i < _l; i++)
        {
            if (lay[i] == _lay)
            {
                return setActiveLay(i);
            }
        }
    }

    return -1;
}

void Canvas::finishTool()
{
    CLay* clay = getActiveLay();
    assert(clay);
    clay->isNewToolLayCreated = false;
}

void Canvas::controlSize()
{
    zoneSizeControl.controlFrame();
}

void Canvas::controlEditLay()
{
    if (!getActiveLay()) return;
    ToolLay* activeToolLay = getActiveLay()->getActiveToolLay();
    if (app->getAsyncKeyState('E') && currentToolLength > 0 && activeToolLay->isFinished())
    {
        while (app->getAsyncKeyState('E')) {};
        editingMode = !editingMode;
        activeToolLay->needRedraw();
    }
}


void Canvas::cleanOutputLay()
{
    for (int i = 0; i < currentLayersLength; i++)
    {
        //if (lay[i].redrawStatus ()) app->bitBlt(lay[i].getOutPutDC(), 0, 0, 0, 0, lay[i].getPermanentDC());
        //txAlphaBlend(lay[i].outputLay, 0, 0, 0, 0, lay[i].lay);
        //lay[i].clean(lay[i].outputLay);
        //txTransparentBlt (lay[i].outputLay, 0, 0, 0, 0, lay[i].lay, 0, 0, _app->systemSettings->TRANSPARENTCOLOR);
        //app->bitBlt(0, 0, lay[i].tempLay);
        //while (app->getAsyncKeyState('G')) { txSleep(0); }

    }
}

void Canvas::drawLays()
{
    static int debugMode = 0;

    app->setColor(backgroungColor, finalLay);
    app->rectangle(rect - rect.pos, finalLay);

    for (int lays = 0; lays < currentLayersLength; lays++)
    {
        if (true/*lay[lays]->redrawStatus()*/)
        {
            //app->DEBUGsaveImage(finalLay);
            lay[lays]->print(finalLay);
            //app->DEBUGsaveImage(finalLay);
            //lay[lays]->redraw();
            //lay[lays]->noMoreRedraw();

            reDraw = true;
        }

        if (editingMode && (lays == getActiveLayNum()))
        {
            lay[lays]->editTool(&currentDate);
        }

        //app->transparentBlt(finalLay, lay[lays].lay.layCoordinats.x, lay[lays].lay.layCoordinats.y, 0, 0, lay[lays].lay.outputLay);
    }
}

void Canvas::MoveWindow(Vector delta)
{
    rect.pos.x += delta.x;
    rect.finishPos.x += delta.x;

    rect.pos.y += delta.y;
    rect.finishPos.y += delta.y;
}

void Canvas::MoveWindowTo(Vector pos, bool needToCallOnSize/* = true*/)
{
    Vector size = getSize();
    rect.pos.x = pos.x;
    rect.finishPos.x = rect.pos.x + size.x;

    size = getSize();
    rect.pos.y = pos.y;
    rect.finishPos.y = rect.pos.y + size.y;

    if (app->systemSettings->debugMode >= 3)printf("Canvas pos: {%lf, %lf}\n", rect.pos.x, rect.pos.y);
}

void Canvas::drawCadre()
{
    zoneSizeControl.drawFrame();
}