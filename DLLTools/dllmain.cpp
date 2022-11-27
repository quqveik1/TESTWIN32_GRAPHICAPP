// dllmain.cpp : Определяет точку входа для приложения DLL.
//#include "pch.h"
#include "dllmain.h"
//#include "CadreResizingTool.cpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}





DLLToolExportData* initDLL(AbstractAppData* data)
{
    DLLToolExportData* dllTools = new DLLToolExportData(1);
    Line* line = new Line(data, NULL, "Линия");
    dllTools->addTool(line);

    return dllTools;
};


void Line::draw()
{
    if (activeToolLay)
    {
        M_HDC* outDC = activeToolLay->getOutputDC();
        app->setColor(TX_RED, *outDC);
        app->rectangle({}, { 100, 100 }, *outDC);
        app->saveImage();
    }
}



int Line::mbDown(Vector pos, int button)
{

    return 0;
}

 int Line::mbUp(Vector pos, int button)
{
    return 0;
}

 int Line::onMouseMove(Vector pos, Vector delta)
{
    return 0;
}




