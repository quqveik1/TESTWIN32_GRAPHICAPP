#pragma once
#include "CustomRCoordinatSystemWindow.h"

struct CoordinatLay
{
    COLORREF defaultColor = C_LIGHTBLUE;
    COLORREF defaultR = 5;
    vector<Vector> pointsLay{};
    vector<COLORREF> colorLay{};
    vector<int> rLay{};
    size_t addPoint(Vector pos, COLORREF color, int r);
    size_t size() { return pointsLay.size(); }
    size_t clear();
};

struct MultiLayCoordinatSystemWindow : CustomRCoordinatSystemWindow
{
    vector<CoordinatLay*> lays;
    mutex laysMutex;
    size_t standartLayIndex = 0;
    size_t activeLayIndex = 0;

    MultiLayCoordinatSystemWindow(AbstractAppData* _app);

private:
    void throwLayOutOfRange();

public:

    size_t addLay();
    size_t getActiveLayIndex();
    size_t setActiveLayIndex(size_t index);

    virtual size_t addPoint(Vector point, COLORREF _pointColor = NULL, int _r = 0, size_t layIndex = 0, bool _needToUpdateWindow = true);
    virtual Vector getPoint(size_t index, size_t layIndex = 0);
    virtual COLORREF getPointColor(size_t index, size_t layIndex = 0);
    virtual int getPointR(size_t index, size_t layIndex = 0);
    virtual void setPointsR(int r, size_t layIndex = 0);
    virtual void setPointsColor(COLORREF color, size_t layIndex = 0);
    virtual CoordinatLay* getCoordinatLay(size_t layIndex = 0);

    virtual void drawPoints() override;
    virtual size_t clearSys() override;
    virtual size_t clearLay(size_t layIndex);

};