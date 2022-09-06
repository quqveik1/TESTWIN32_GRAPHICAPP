
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "TXLib.cpp"
#include "Q_Rect.h"
#include "Macroses.h"
#include "SystemSettings.h"
#include "DebugInfo.h"
#include "LoadManager.h"
#include "Tool.h"
#include "ProgrammeDate.h"
#include "commdlg.h"
#include "AbstractApp.h"
#include "WindowsLib.h"
#include "WindowsLibApi.h"




struct CHistoryStep
{
	int toolsNum = 0;
	struct Tool* tools = NULL;
    void* toolsData = NULL;
	int thickness = 1;
};




int standartManagerOnClick$ (struct Manager *manager, Vector mp);
//#define standartManagerOnClick(...) standartManagerOnClick$ (getDebugInfo, __VA_ARGS__);;
void standartDraw$ (struct Window *window);
//#define standartDraw(...) standartDraw$ (getDebugInfo, __VA_ARGS__)
void standartManagerDraw$ (struct Manager *manager);
//#define standartManagerDraw(...) standartManagerDraw$ (getDebugInfo, __VA_ARGS__)
void clickButton (Window *window, Manager *manager, Vector mp);
//#define selectFont(...) selectFont$ (getDebugInfo, __VA_ARGS__)
void swap$ (DebugInfo info, int &x0, int &y0);
//#define swap(...) swap$ (getDebugInfo, __VA_ARGS__)
Vector windowMousePos(bool isThisMainFile = true);
const char* findExtensionStart(const char* text, int extensionPos);
const char* getCustomFilePath(const char* question, const char* fileTypeDescribtion = NULL);
const char* getCustomFilePathForSaving(const char* question, const char* defaultFilename = "", const char* fileTypeDescribtion = NULL);













