#pragma once           
#include <Window.cpp>
#include <mutex>

struct CoordinatSystemWindow : Window
{
    Vector cCells = {};
    Vector cCellsLines = { 10, 10 };
    Vector cellNull = {};
    Vector pixNullPercantage = { 0.1, 0.1 };
    COLORREF axisColor = RGB(150, 150, 150);
    COLORREF pointsColor = C_LIGHTBLUE;
    int pointsR = 2;
    string axisXName;
    string axisYName;

    mutex pointsMutex;
    vector<Vector> points;

    M_HDC axisSystemDC;

    Window* onClickListener = NULL;

    CoordinatSystemWindow(AbstractAppData* _app) :
        Window(_app),
        axisSystemDC(_app)
    {
    };

    virtual ~CoordinatSystemWindow()
    {
        //axisSystemDC.deleteObj();
    };

    double humanRound(double delta);

    void drawOneXLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc);
    void drawOneYLine(int stepNum, const Vector& cellStep, char* textBuf, M_HDC& destDc);
    virtual void drawPoints();
    void drawAxisName(M_HDC& destDC);

    virtual void invalidateSysConfig();

    void setCCells(Vector _cScreenCells);
    void setCellNull(Vector _cellNull)     { cellNull = _cellNull;           invalidateSysConfig(); };
    void setAxisColor(COLORREF _color)     { axisColor = _color;             invalidateSysConfig(); };
    void setAxisXName(string _axisXName)   { axisXName = _axisXName;         invalidateSysConfig(); };
    void setAxisYName(string _axisYName)   { axisYName = _axisYName;         invalidateSysConfig(); };
    void setPointsColor(COLORREF _color)   { pointsColor = _color;           invalidateSysConfig(); };
    void setPointsR(int _r)                { pointsR = _r;                   invalidateSysConfig(); };
    void setOnClickListener(Window* _wnd)  { onClickListener = _wnd;         invalidateSysConfig(); };

    //-pix per cell
    Vector getDensity();
    Vector getPixNullCoordinats();
    Vector getHumanCellStep();
    Vector getPixCellStep();
    Vector fromCellToPix(Vector cells);
    Vector fromPixToCell(Vector pixs);

    virtual Vector getXCellBound();
    virtual Vector getYCellBound();
    virtual size_t addPoint(Vector point, bool needTOUpdateWindow = true);
    virtual size_t getPointsSize();
    virtual size_t clearSys();

    void draw() override;
    virtual void onClick(Vector mp) override;
    int onSize(Vector managerSize, Rect _newRect = {}) override;
};