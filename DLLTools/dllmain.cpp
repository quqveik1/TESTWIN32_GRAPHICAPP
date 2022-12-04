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


int Line::createNewToolCopy(ToolLay* toollay)
{
    activeToolLay = toollay;
    LineData* _data = new LineData();
    if (activeToolLay)
    {
        activeToolLay->getToolsData() = (char*)_data;
        return 1;
    }
    return 0;
}


void Line::draw()
{
    if (activeToolLay)
    {
        M_HDC* outDC = activeToolLay->getOutputDC();
        LineData* _data = (LineData*)activeToolLay->getToolsData();
        if (_data && outDC)
        {
        
            if (_data->rect.finishPos != 0)
            {

                app->setColor(_data->color, *outDC, _data->thickness);
                app->line(_data->rect, *outDC);
                //app->DEBUGsaveImage(*outDC);
            }
        }
        //app->rectangle({}, { 100, 100 }, *outDC);
        //app->DEBUGsaveImage(*outDC);
    }
}



int Line::mbDown(Vector pos, int button)
{
    if (activeToolLay)
    {
        if (button == 1)
        {
            LineData* _data = (LineData*)activeToolLay->getToolsData();
            if (_data)
            {
                _data->rect.pos = pos;
                _data->status = 1;
                _data->color = app->systemSettings->DrawColor;
                _data->thickness = app->lround(app->systemSettings->Thickness);
            }
            
        }
    }
    return 0;
}

 int Line::mbUp(Vector pos, int button)
{
     if (activeToolLay)
     {
         if (button == 1)
         {
            LineData* _data = (LineData*)activeToolLay->getToolsData();
             if (_data)
             {
                 if (_data->status == 1)
                 {
                     _data->rect.finishPos = pos;
                     _data->status = 2;
                     activeToolLay->finishThisTool();
                 }
             }

         }
     }
    return 0;
}

 int Line::onMouseMove(Vector pos, Vector delta)
{
     if (activeToolLay)
     {
         LineData* _data = (LineData*)activeToolLay->getToolsData();
         if (_data)
         {
             if (_data->status == 1/*!(_data->rect.pos  0)*/)
             {
                 if (delta != 0)
                 {
                     _data->rect.finishPos = pos;
                     //_data->rect.finishPos.print("_data->rect.finishPos:");
                     //printf("_data->rect.finishPos:{%lf, %lf}\n", ;
                     app->updateScreen(this);
                 }

             }
         }
     }
    return 0;
}




