#include "stdafx.h"
#include "MainWidgetContainer.h"

MainWidgetContainer::MainWidgetContainer(HGE *hge) : WidgetContainer(std::string("main")) {
  this->hge = hge;

  bLPressed = bLLastPressed = false;
  mx = my = 0.0f;
}

MainWidgetContainer::~MainWidgetContainer(void) {
  ctrlLock.reset();
  ctrlOver.reset();
}

void MainWidgetContainer::UpdateMe(float dt) {
  hge->Input_GetMousePos(&mx, &my);
  bLLastPressed = bLPressed;
  bLPressed = hge->Input_GetKeyState(VK_LBUTTON);

  WidgetContainer::UpdateMe(dt);

  if (!ctrlLock.expired()) {
    if (auto widget = ctrlLock.lock()) {
      if (!bLPressed) {
        ctrlLock.reset();
      }
      ProcessWidget(widget);
    }
    return;
  }

  auto widget = FindWidget(mx, my);
  if (widget) {
    auto ref = ctrlOver.lock();
    if (!ref || ref != widget) {
      if (ref) {
        ref->OnLeaveLMouseButton();
      }
      widget->OnEnterLMouseButton();
      ctrlOver = WeakWidgetRef(widget);
      return;
    }
    ProcessWidget(widget);
    return;
  }

  if (!ctrlOver.expired()) {
    if (auto ref = ctrlOver.lock()) {
      ref->OnLeaveLMouseButton();
    }
    ctrlOver.reset();
  }
}

void MainWidgetContainer::ProcessWidget(WidgetRef& currWidget) {
  if (!bLLastPressed && bLPressed) {
    ctrlLock = WeakWidgetRef(currWidget);
    currWidget->OnPressLMouseButton();
  }
  if (bLLastPressed && !bLPressed) {
    currWidget->OnReleaseLMouseButton();
  }
  currWidget->OnMouseMove(mx - currWidget->GetPosX(), my - currWidget->GetPosY());
}
