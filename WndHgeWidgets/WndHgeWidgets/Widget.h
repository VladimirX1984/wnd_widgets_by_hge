#pragma once

#include <map>
#include <string>

#include <hgevector.h>
#include <hgerect.h>
#include "types.h"

class WidgetContainer;

class Widget : public enable_shared_from_this<Widget> {
  public:

    enum EVENT_TYPE : unsigned int {
      MOUSE_ENTER = 1,
      MOUSE_LEAVE,
      MOUSE_PRESS,
      MOUSE_RELEASE,
      MOUSE_CLICK,
      MOUSE_MOVE
    };

    Widget(const std::string& id);
    virtual ~Widget(void) { };

    inline const std::string GetId() const { return id; }

    inline int GetOrder() const { return order; }
    void SetOrder(int order);

    inline float GetPosX() { return pos.x; };
    inline float GetPosY() { return pos.y; };

    hgeVector GetGlobalPos();
    void SetGlobalPos(hgeVector& pos);

    void SetPos(float x, float y);

    virtual void SetSize(float w, float h);

    virtual hgeRect GetBoundingBox();

    virtual void OnPressLMouseButton(void);

    virtual void OnReleaseLMouseButton(void);

    virtual void OnEnterLMouseButton(void);

    virtual void OnLeaveLMouseButton(void);

    virtual void OnMouseMove(float x, float y);

    void Update(float dt);

    void Render(void);

    void Show(void);

    void Hide(void);

    inline bool IsVisible(void) { return bVisible; }

    virtual bool IsContainer(void) { return false; }

    void AddEventHandler(EVENT_TYPE type, function<void (Widget*)> handler);

  public:
    WidgetContainerRef GetWidgetContainer();

    WidgetContainerRef GetRootWidget();

  protected:
    virtual void UpdateMe(float dt) { };

    virtual void RenderMe(void) = 0;

    bool CallHandler(EVENT_TYPE eventType);

  private:
    friend WidgetContainer;

    std::string id;

    bool bVisible;

    int order;
    hgeVector pos;
    hgeRect rect;

    WeakWidgetContainerRef widgetContainer;

    std::multimap<EVENT_TYPE, function<void (Widget*)>> handlers;

  private:
    void InitMe();
};

