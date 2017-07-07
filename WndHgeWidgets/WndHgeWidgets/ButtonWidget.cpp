#include "stdafx.h"
#include "ButtonWidget.h"
#include "ResourceHub.h"
#include "hgesprite.h"

ButtonWidget::ButtonWidget(const std::string& id) : Widget(id) {
  hge = hgeCreate(HGE_VERSION);
  InitMe();
}

ButtonWidget::~ButtonWidget(void) {
  Clear();
  if (hge) {
    hge->Release();
  }
}

void ButtonWidget::InitMe() {
  bPressed = false;
  color = 0;
}

void ButtonWidget::Clear() {
  sprUp.reset();
  sprDown.reset();
}

bool ButtonWidget::LoadUpSprite(const std::string& resName) {
  auto spr = LoadSprite(resName);
  if (spr) {
    if (sprUp) {
      sprUp.reset();
    }
    sprUp = spr;
    spr.reset();
    return true;
  }
  return false;
}

bool ButtonWidget::LoadUpSprite(const std::string& resName, float x, float y, float w, float h) {
  auto spr = LoadSprite(resName, x, y, w, h);
  if (spr) {
    if (sprUp) {
      sprUp.reset();
    }
    sprUp = spr;
    spr.reset();
    return true;
  }
  return false;
}

bool ButtonWidget::LoadDownSprite(const std::string& resName) {
  auto spr = LoadSprite(resName);
  if (spr) {
    if (sprDown) {
      sprDown.reset();
    }
    sprDown = spr;
    spr.reset();
    return true;
  }
  return false;
}

bool ButtonWidget::LoadDownSprite(const std::string& resName, float x, float y, float w, float h) {
  auto spr = LoadSprite(resName, x, y, w, h);
  if (spr) {
    if (sprDown) {
      sprDown.reset();
    }
    sprDown = spr;
    spr.reset();
    return true;
  }
  return false;
}

void ButtonWidget::SetColor(DWORD col) {
  color = col;
  if (sprUp) {
    sprUp->SetColor(col);
  }
  if (sprDown) {
    sprDown->SetColor(col);
  }
}

void ButtonWidget::OnPressLMouseButton(void) {
  bPressed = true;
  Widget::OnPressLMouseButton();
}

void ButtonWidget::OnReleaseLMouseButton(void) {
  bPressed = false;
  CallHandler(MOUSE_CLICK);
  Widget::OnReleaseLMouseButton();
}

void ButtonWidget::OnEnterLMouseButton(void) {
  Widget::OnEnterLMouseButton();
}

void ButtonWidget::OnLeaveLMouseButton(void) {
  Widget::OnLeaveLMouseButton();
}

void ButtonWidget::RenderMe(void) {
  if (bPressed) {
    if (sprDown) {
      sprDown->Render(GetPosX(), GetPosY());
    }
  }
  else {
    if (sprUp) {
      sprUp->Render(GetPosX(), GetPosY());
    }
  }
}

HgeSpriteRef ButtonWidget::LoadSprite(const std::string& resName) {
  auto res = ResourceHub::Load(resName);
  if (!res) {
    return HgeSpriteRef();
  }
  float w = (float)hge->Texture_GetWidth(res->GetResID());
  float h = (float)hge->Texture_GetHeight(res->GetResID());
  auto spr = make_shared<hgeSprite>(res->GetResID(), 0.f, 0.f, w, h);
  res.reset();
  if (color > 0) {
    spr->SetColor(color);
  }
  SetSize(w, h);
  return spr;
}

HgeSpriteRef ButtonWidget::LoadSprite(const std::string& resName, float x, float y, float w, float h) {
  if (resName.empty()) {
    auto spr = make_shared<hgeSprite>(0, x, y, w, h);
    if (color > 0) {
      spr->SetColor(color);
    }
    SetSize(w, h);
    return spr;
  }
  auto res = ResourceHub::Load(resName);
  if (!res) {
    return HgeSpriteRef();
  }
  auto spr = make_shared<hgeSprite>(res->GetResID(), x, y, w, h);
  res.reset();
  if (color > 0) {
    spr->SetColor(color);
  }
  SetSize(w, h);
  return spr;
}