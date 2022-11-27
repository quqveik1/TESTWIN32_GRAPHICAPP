// SaveImage.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SaveImage.h"


// This is an example of an exported variable
SAVEIMAGE_API int nSaveImage=0;

// This is an example of an exported function.
SAVEIMAGE_API int fnSaveImage(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CSaveImage::CSaveImage()
{
    return;
}
