#pragma once

#include "StringResources.h"

StringResources::StringResources(AbstractAppData* _app) :
    app(_app)    
{
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
    return resources[Russian];
}

StringResources::CResourcesType& StringResources::getMapCResources()
{
    return cResources[Russian];
}

std::string& StringResources::getResource(const std::string& key)
{
    return getMapResources()[key];
}

int StringResources::setResource(const std::string& region, const std::string& key, const std::string& string)
{
    resources[region][key] = string;
    return 0;
}

const char* StringResources::getCResource(const char* key)
{
    return getMapCResources()[key];
}

int StringResources::setCResource(const std::string& region, const char* key, const char* string)
{
    cResources[region][key] = string;
    return 0;
}