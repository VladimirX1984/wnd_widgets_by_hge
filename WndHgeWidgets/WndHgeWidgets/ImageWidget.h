#pragma once
#include "widget.h"

class ImageWidget : public Widget {
  public:
    ImageWidget(const std::string& id);
    virtual ~ImageWidget(void);

    bool LoadSprite(const std::string& resName);

    bool LoadSprite(const std::string& resName, float x, float y, float w, float h);

    void SetColor(DWORD col);

  protected:
    virtual void RenderMe(void) override;

  private:
    HgeSpriteRef spr;

    DWORD color;

    HGE* hge;

    void InitMe();
    void Clear();
};

