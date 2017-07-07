#pragma once
#include "widgetcontainer.h"

class MainWidgetContainer : public WidgetContainer {
  public:
    MainWidgetContainer(HGE *hge);
    virtual ~MainWidgetContainer(void);

  protected:
    virtual void UpdateMe(float dt) override;

  private:
    HGE *hge;

    float mx, my;
    bool bLPressed, bLLastPressed;
    WeakWidgetRef ctrlLock;
    WeakWidgetRef ctrlOver;

    void ProcessWidget(WidgetRef& currWidget);
};

