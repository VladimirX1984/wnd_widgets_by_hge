#pragma once

#include "ResourceObject.h"

class HGE;

class HgeResourceObject : public ResourceObject {
  public:
    HgeResourceObject(HGE *hge, DWORD id);
    virtual ~HgeResourceObject(void);

  private:
    HGE* hge;
};