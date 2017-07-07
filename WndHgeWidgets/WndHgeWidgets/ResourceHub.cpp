#include "stdafx.h"
#include "ResourceHub.h"

class ResourceManager {
  public:
    ResourceManager(void) { };
    ~ResourceManager(void);

    void Add(const std::string& resName, ResRef& res);

    ResRef Load(const std::string& resName);

    ResRef Get(const std::string& resName);

  private:
    std::map<std::string, ResRef> resMap;
};

ResourceManager::~ResourceManager(void) {
  auto it = resMap.begin(), end = resMap.end();
  for (; it != end; ++it) {
    it->second.reset();
  }
  resMap.clear();
}

void ResourceManager::Add(const std::string& resName, ResRef& res) {
  if (resName.empty()) {
    return;
  }
  resMap[resName] = res;
}

ResRef ResourceManager::Load(const std::string& resName) {
  if (resName.empty()) {
    return ResRef();
  }
  auto it = resMap.find(resName);
  if (it == resMap.end()) {
    ResRef res = ResourceObject::Load(resName);
    if (!res) {
      return ResRef();
    }
    Add(resName, res);
    return resMap[resName];
  }
  return it->second;
}

ResRef ResourceManager::Get(const std::string& resName) {
  if (resName.empty()) {
    return ResRef();
  }
  auto it = resMap.find(resName);
  if (it == resMap.end()) {
    return ResRef();
  }
  return it->second;
}

ResourceManagerRef ResourceHub::resMan = make_shared<ResourceManager>();

void ResourceHub::Add(const std::string& resName, ResRef& res) {
  if (resMan) {
    resMan->Add(resName, res);
  }
}

ResRef ResourceHub::Load(const std::string& resName) {
  if (!resMan) {
    return ResRef();
  }
  return resMan->Load(resName);
}

ResRef ResourceHub::Get(const std::string& resName) {
  if (!resMan) {
    return ResRef();
  }
  return resMan->Get(resName);
}

void ResourceHub::Create() {
  resMan = make_shared<ResourceManager>();
}

void ResourceHub::Release() {
  resMan.reset();
}