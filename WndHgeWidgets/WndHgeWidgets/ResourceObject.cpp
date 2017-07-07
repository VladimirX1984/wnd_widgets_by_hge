#include "stdafx.h"
#include "ResourceObject.h"

ResourceObject::ResourceObject(DWORD resId) : resId(resId) {
}

ResourceObject::~ResourceObject(void) {
}

DWORD ResourceObject::GetResID() const {
  return resId;
}
