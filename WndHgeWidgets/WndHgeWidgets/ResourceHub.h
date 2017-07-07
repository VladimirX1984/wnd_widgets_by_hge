#pragma once

#include <map>
#include <memory>
#include <string>

#include "ResourceObject.h"

#if BOOST
typedef boost::shared_ptr<ResourceManager> ResourceManagerRef;
#else
typedef std::shared_ptr<ResourceManager> ResourceManagerRef;
#endif

class ResourceHub final {
  public:
    static void Add(const std::string& resName, ResRef& res);

    static ResRef Load(const std::string& resName);

    static ResRef Get(const std::string& resName);

    static void Create();
    static void Release();

  private:
    static ResourceManagerRef resMan;
};

