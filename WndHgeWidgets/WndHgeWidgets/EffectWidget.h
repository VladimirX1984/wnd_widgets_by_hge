#pragma once
#include "widget.h"

class EffectWidget : public Widget {
  public:
    EffectWidget(const std::string& id);
    virtual ~EffectWidget(void);

    void LoadEffect(const std::string& psFileName, const std::string& sprFileName, float x, float y, float w, float h);
    void SetEmission(int emission);

  protected:
    virtual void UpdateMe(float dt) override;

    virtual void RenderMe(void) override;

  private:
    HgeSpriteRef spr;
    HgePsRef par;
    int emission;

    void InitMe();
    void Clear();
};

