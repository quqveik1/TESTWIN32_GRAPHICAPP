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
#ifdef _DEBUG
    auto keyit = getMapResources().find(key);
    if(keyit == getMapResources().end())
    {
        throw runtime_error("Try to get uncreated string");
    }
    return getMapResources()[key];
#else
    return getMapResources()[key];
#endif
}

int StringResources::addResource(const std::string& region, const std::string& key, const std::string& string)
{

#ifdef _DEBUG
    auto keyit = resources[region].find(key);
    if (keyit != resources[region].end())
    {
        throw runtime_error("Try to dublicate string");
    }
    resources[region][key] = string;
#else
    resources[region][key] = string;
#endif
    return 0;
}

const char* StringResources::getCResource(const std::string& key)
{
#ifdef _DEBUG
    auto keyit = getMapCResources().find(key);
    if (keyit == getMapCResources().end())
    {
        throw runtime_error("Try to get uncreated string");
    }
    return getMapCResources()[key];
#else
    return getMapCResources()[key];
#endif
}

int StringResources::addCResource(const std::string& region, const std::string& key, const char* string)
{
#ifdef _DEBUG
    auto keyit = cResources[region].find(key);
    if (keyit != cResources[region].end())
    {
        throw runtime_error("Try to dublicate string");
    }
    cResources[region][key] = string;
#else
    cResources[region][key] = string;
#endif
    return 0;
}

std::string& StringResources::getActiveLang()
{
    return activeLang;
}

void StringResources::setActiveLang(const std::string& str)
{
    activeLang = str;
}