#pragma once

#include "StringResources.h"

StringResources::StringResources(AbstractAppData* _app) :
    app(_app)    
{
    activeLang = getApp()->getUserLangCode();
    if(activeLang != Russian)
    {
        activeLang = English;
    }

    resources[Russian] = CPPResourcesType();
    resources[English] = CPPResourcesType();
    cResources[Russian] = CResourcesType();
    cResources[English] = CResourcesType();
}

AbstractAppData* StringResources::getApp()
{
    return app;
}

StringResources::CPPResourcesType& StringResources::getMapResources()
{
    return resources[getActiveLang()];
}

StringResources::CResourcesType& StringResources::getMapCResources()
{
    return cResources[getActiveLang()];
}

std::string& StringResources::getResource(const std::string& key)
{
    return getMapResources()[key];
}

std::string& StringResources::getResource(const char* key)
{
    return getMapResources()[key];
}

int StringResources::addResource(const std::string& region, const std::string& key, const std::string& string)
{
    resources[region][key] = string;
    return 0;
}

const char* StringResources::getCResource(const std::string& key)
{
    return getMapCResources()[key];
}

const char* StringResources::getCResource(const char* key)
{
    return getMapCResources()[key];
}

int StringResources::addCResource(const std::string& region, const char* key, const char* string)
{
    cResources[region][key] = string;
    return 0;
}

int StringResources::addCResource(const std::string& region, const std::string& key, const char* string)
{
    cResources[region][key] = string;
    return 0;
}

std::string& StringResources::getActiveLang()
{
    return activeLang;
}