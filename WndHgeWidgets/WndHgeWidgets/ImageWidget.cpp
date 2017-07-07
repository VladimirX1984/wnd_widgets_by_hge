#include "stdafx.h"
#include "ImageWidget.h"
#include "ResourceHub.h"
#include "hgesprite.h"

ImageWidget::ImageWidget(const std::string& id) : Widget(id) {
  InitMe();
}

ImageWidget::~ImageWidget(void) {
  Clear();
  if (hge) {
    hge->Release();
  }
}

void ImageWidget::InitMe() {
  color = 0;
  hge = hgeCreate(HGE_VERSION);
}

void ImageWidget::Clear() {
  spr.reset();
}

bool ImageWidget::LoadSprite(const std::string& resName) {
  auto res = ResourceHub::Load(resName);
  if (!res) {
    return false;
  }
  Clear();
  float w = (float)hge->Texture_GetWidth(res->GetResID());
  float h = (float)hge->Texture_GetHeight(res->GetResID());
  spr = make_shared<hgeSprite>(res->GetResID(), 0.f, 0.f, w, h);
  res.reset();
  if (color > 0) {
    spr->SetColor(color);
  }
  SetSize(w, h);
  return true;
}

bool ImageWidget::LoadSprite(const std::string& resName, float x, float y, float w, float h) {
  if (resName.empty()) {
    Clear();
    spr = make_shared<hgeSprite>(0, x, y, w, h);
    if (color > 0) {
      spr->SetColor(color);
    }
    SetSize(w, h);
    return true;
  }
  auto res = ResourceHub::Load(resName);
  if (!res) {
    return false;
  }
  Clear();
  spr = make_shared<hgeSprite>(res->GetResID(), x, y, w, h);
  res.reset();
  if (color > 0) {
    spr->SetColor(color);
  }
  SetSize(w, h);
  return true;
}

void ImageWidget::SetColor(DWORD col) {
  color = col;
  if (spr) {
    spr->SetColor(col);
  }
}

void ImageWidget::RenderMe(void) {
  if (spr) {
    spr->Render(GetPosX(), GetPosY());
  }
}