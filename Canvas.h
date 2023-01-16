#pragma once

#include "WindowsLib.cpp"
#include "CLay.h"
#include "ToolLay.h"
#include "ZoneSizeControl.h"

struct Canvas : Manager
{
    char name[MAX_PATH] = {};
    bool clearBackground = true;
    Vector canvasCoordinats = {};

    const int LayersNum = 100;
    int currentLayersLength = 0;
    int activeLayNum = 0;
    Vector laysSize = {};
    M_HDC finalLay;
    bool needToRedrawBackground = false;
    COLORREF backgroungColor = TX_WHITE;
    CLay** lay = new CLay*[LayersNum]{};
    int currentToolLength = 0;
    bool editingMode = false;
    int DrawingModeLastTime = 0;

    ProgrammeDate currentDate;

    ZoneSizeControl zoneSizeControl;
    bool needFrameToWork = true;

    double scale = 1;
    double scaleLastTime = 0;
    Vector outputDCSize = {};
    Vector posLastTime = {};
    double deltaScale = 0.1;
    int lastTimeButtonClicked = 0;
    int deltaBetween2Clicks = 300;
    Vector deltaPos = {};

    HDC currentlyImportingImage = NULL;
    bool wasLastTimeImporting = false;

    Canvas(AbstractAppData* _app, Rect _rect, const char* _name);
    virtual ~Canvas();

    virtual int separateWindow(int pos) override;

	void controlSize();
    void controlStretching();
    virtual Vector setNewCanvasSize(Vector newSize);

    void drawCadre();

	virtual void createLay ();
	int controlLay ();
	int setActiveLay (int pos);
	int setActiveLay (CLay* _lay);
    void controlEditLay();
	void drawLays();
    void cleanOutputLay();

    void copyFinalLayOnFinalDC();

    void finishTool();
    void controlTool();
    void startTool();
    void changeTool(Tool2* tool);
    void initToolLay();
    void addToolLay();
    void setToolToToolLay(ToolLay* toollay, Tool2* tool);
    void setCurrentData();

    void controlImportingImages();
   

    virtual HDC getImageForSaving();
    virtual int importImage(HDC dc);
    virtual HDC& getCurrentlyImportingImage();
    virtual CLay* getActiveLay();
    virtual int getEditingMode();
    virtual Vector getLaySize();
    virtual int getCurrentLayLength();
    virtual int getCurrentToolLengthOnActiveLay();
    virtual const char* getName();
    virtual double& getScale();

    virtual void stretchCanvas(double percantageFromOriginal);

    int getActiveLayNum();
    ToolLay* getNewToolLay();
    bool isDrawingModeChanged();
    Tool2* getActiveTool();
    void setActiveToolLayNum(int num);
    int getLastNotStartedToolNum();

    Vector convertMousePosForLay(Vector m);
    virtual Vector getMousePos() override;
    

    virtual void MoveWindow(Vector delta) override;
    virtual void MoveWindowTo(Vector pos) override;

    virtual void print(M_HDC& _dc) override;
    virtual void resize(Vector newSize) override;

	virtual void draw () override;
	virtual void onClick (Vector mp) override;
    virtual int mbDown(Vector mp, int button) override;
    virtual int mbUp(Vector mp, int button) override;
    virtual int onMouseMove(Vector mp, Vector delta) override;
	virtual void deleteButton () override;
};