#pragma once
#include "widget.h"

class ButtonWidget : public Widget {
  public:
    ButtonWidget(const std::string& id);
    virtual ~ButtonWidget(void);

    bool LoadUpSprite(const std::string& resName);

    bool LoadUpSprite(const std::string& resName, float x, float y, float w, float h);

    bool LoadDownSprite(const std::string& resName);

    bool LoadDownSprite(const std::string& resName, float x, float y, float w, float h);

    void SetColor(DWORD col);

    virtual void OnPressLMouseButton(void) override;

    virtual void OnReleaseLMouseButton(void) override;

    virtual void OnEnterLMouseButton(void) override;

    virtual void OnLeaveLMouseButton(void) override;

  protected:
    virtual void RenderMe(void) override;

  private:
    HgeSpriteRef sprUp;
    HgeSpriteRef sprDown;

    DWORD color;

    HGE* hge;

    bool bPressed;

    void InitMe();
    void Clear();

    HgeSpriteRef LoadSprite(const std::string& resName);
    HgeSpriteRef LoadSprite(const std::string& resName, float x, float y, float w, float h);
};

