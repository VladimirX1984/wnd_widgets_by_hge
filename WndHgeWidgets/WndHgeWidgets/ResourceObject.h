#pragma once

#include <string>
#include "types.h"

class ResourceManager;

class ResourceObject {
  public:
    ResourceObject(DWORD resId);
    virtual ~ResourceObject(void);

    DWORD GetResID() const;

  private:
    DWORD resId;

    friend ResourceManager;

    static ResRef Load(const std::string& resName);
};

