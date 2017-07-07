#include "stdafx.h"
#include "HgeResourceObject.h"
#include "hge.h"

HgeResourceObject::HgeResourceObject(HGE *hge, DWORD id) : ResourceObject(id) {
  this->hge = hge;
}

HgeResourceObject::~HgeResourceObject(void) {
  hge->Texture_Free(GetResID());
  hge->Release();
}

ResRef ResourceObject::Load(const std::string& resName) {
  auto hge = hgeCreate(HGE_VERSION);
  HTEXTURE tex = hge->Texture_Load(resName.c_str());
  if (!tex) {
    hge->Release();
    MessageBoxA(nullptr, (std::string("Can't load file: ") + resName).c_str(), "Error",
                MB_OK | MB_ICONERROR | MB_APPLMODAL);
    return ResRef();
  }
  return make_shared<HgeResourceObject>(hge, tex);
}