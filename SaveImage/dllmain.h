#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "..\AbstractApp.h"
#include "pch.h"
#include "..\Q_Vector.h"
#include <atlimage.h> 



extern "C" __declspec (dllexport) int saveImage(HDC dc, const char* path);
extern "C" __declspec (dllexport) HDC loadImage(const char* path, Vector & size, AbstractAppData* _app);