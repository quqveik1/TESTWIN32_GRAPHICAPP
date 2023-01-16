// dllmain.cpp : Defines the entry point for the DLL application.  
#include "dllmain.h"

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

int saveImage(HDC dc, const char* path)
{
    HBITMAP bitmap = (HBITMAP)GetCurrentObject(dc, OBJ_BITMAP);

    CImage image;
    image.Attach(bitmap);

    LPCTSTR widePath = path;
    HRESULT hresult = image.Save(widePath);

    if (FAILED(hresult))
    {
        return hresult;
    }

    return 0;
}

HDC loadImage(const char* path, Vector& size, EngineAppApi* _app)
{
    CImage image;
    LPCTSTR widePath = path;
    HRESULT hresult = image.Load(widePath);
    if (FAILED(hresult))
    {
        return 0;
    }
    
    size.x = image.GetWidth();
    size.y = image.GetHeight();
    HDC imageDC = image.GetDC();
    HDC newdc = NULL;
    if (_app)
    {
        newdc = _app->createDIBSection(size);
        _app->bitBlt(newdc, {}, {}, imageDC);
    }
    image.ReleaseDC();
    return newdc;
}

