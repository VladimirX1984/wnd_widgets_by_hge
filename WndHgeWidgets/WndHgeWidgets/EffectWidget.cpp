#include "stdafx.h"
#include "EffectWidget.h"
#include "ResourceHub.h"
#include "hgeparticle.h"

EffectWidget::EffectWidget(const std::string& id) : Widget(id) {
  InitMe();
}

EffectWidget::~EffectWidget(void) {
  Clear();
}

void EffectWidget::InitMe() {

}

void EffectWidget::Clear() {
  par.reset();
  spr.reset();
}

void EffectWidget::LoadEffect(const std::string& psFileName, const std::string& sprFileName, float x, float y,
                              float w, float h) {
  Clear();
  auto res = ResourceHub::Get(sprFileName);
  spr = make_shared<hgeSprite>(res ? res->GetResID() : 0, x, y, w, h);
  spr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
  res.reset();
  par = make_shared<hgeParticleSystem>(psFileName.c_str(), spr.get());
  par->Fire();
  SetSize(w, h);
}

void EffectWidget::SetEmission(int emission) {
  this->emission = emission;
}

void EffectWidget::UpdateMe(float dt) {
  if (par) {
    par->info.nEmission = emission;
    par->Update(dt);
  }
}

void EffectWidget::RenderMe(void) {
  if (par) {
    par->MoveTo(GetPosX(), GetPosY());
    par->Render();
  }
}
