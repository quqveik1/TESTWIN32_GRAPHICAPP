#pragma once

#include <map>
#include <string>

#include "AbstractApp.h"

struct StringResources
{
    static inline const std::string Russian = "ru";
    static inline const std::string English = "en";

private:
    using CPPResourcesType = std::map<std::string, std::string>;
    using CResourcesType = std::map<std::string, const char*>;

    std::map<std::string, CPPResourcesType> resources;
    std::map<std::string, CResourcesType> cResources;

    AbstractAppData* app;

public:
    StringResources(AbstractAppData* _app);

    std::string& getResource(const std::string& key);
    int setResource(const std::string& region, const std::string& key, const std::string& string);

    const char* getCResource(const char* key);
    int setCResource(const std::string& region, const char* key, const char* string);

private:
    AbstractAppData* getApp();

    CPPResourcesType& getMapResources();
    CResourcesType& getMapCResources();

};