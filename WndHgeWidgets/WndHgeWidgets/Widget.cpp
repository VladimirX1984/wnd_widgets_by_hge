#include "stdafx.h"
#include "Widget.h"
#include "WidgetContainer.h"

Widget::Widget(const std::string& id) : id(id) {
  InitMe();
}

void Widget::InitMe() {
  bVisible = true;
  order = 0;
  pos.x = pos.y = 0;
  rect.x1 = rect.x2 = rect.y1 = rect.y2 = 0;
}

void Widget::SetOrder(int order) {
  if (this->order != order) {
    this->order = order;
    auto w = widgetContainer.lock();
    if (w) {
      w->OnWidgetUpdated();
    }
  }
}

void Widget::SetPos(float x, float y) {
  pos.x = x;
  pos.y = y;
  float w = rect.x2 - rect.x1;
  float h = rect.y2 - rect.y1;
  SetSize(w, h);
}

hgeVector Widget::GetGlobalPos() {
  auto glPos = pos;
  auto rootWidget = shared_from_this();
  while (rootWidget->GetWidgetContainer()) {
    rootWidget = rootWidget->GetWidgetContainer();
    glPos.x += rootWidget->GetPosX();
    glPos.y += rootWidget->GetPosY();
  }
  return glPos;
}

void Widget::SetGlobalPos(hgeVector& pos) {
  auto glPos = pos;
  auto rootWidget = shared_from_this();
  while (rootWidget->GetWidgetContainer()) {
    rootWidget = rootWidget->GetWidgetContainer();
    glPos.x -= rootWidget->GetPosX();
    glPos.y -= rootWidget->GetPosY();
  }
  this->pos = glPos;
}

void Widget::SetSize(float w, float h) {
  rect.Set(pos.x, pos.y, pos.x + w, pos.y + h);
}

hgeRect Widget::GetBoundingBox() {
  return rect;
}

void Widget::OnPressLMouseButton(void) {
  CallHandler(MOUSE_PRESS);
}

void Widget::OnReleaseLMouseButton(void) {
  CallHandler(MOUSE_RELEASE);
}

void Widget::OnEnterLMouseButton(void) {
  CallHandler(MOUSE_ENTER);
}

void Widget::OnLeaveLMouseButton(void) {
  CallHandler(MOUSE_LEAVE);
}

void Widget::OnMouseMove(float x, float y) {
  CallHandler(MOUSE_MOVE);
}

void Widget::Update(float dt) {
  if (!bVisible) {
    return;
  }
  UpdateMe(dt);
}

void Widget::Render(void) {
  if (!bVisible) {
    return;
  }
  RenderMe();
}

void Widget::Show(void) {
  bVisible = true;
}

void Widget::Hide(void) {
  bVisible = false;
}

void Widget::AddEventHandler(EVENT_TYPE type, function<void (Widget*)> handler) {
  handlers.insert(std::pair<EVENT_TYPE, function<void (Widget*)>>(type, handler));
}

WidgetContainerRef Widget::GetWidgetContainer() {
  return widgetContainer.lock();
}

WidgetContainerRef Widget::GetRootWidget() {
  auto rootWidget = shared_from_this()->GetWidgetContainer();
  while (true) {
    auto rootWidgetParent = rootWidget->GetWidgetContainer();
    if (!rootWidgetParent) {
      break;
    }
    rootWidget = rootWidgetParent;
  }
  return rootWidget;
}

bool Widget::CallHandler(EVENT_TYPE eventType) {
  auto itLower = handlers.lower_bound(eventType);
  if (itLower == handlers.end()) {
    return false;
  }
  auto itUpper = handlers.upper_bound(eventType);
  for (; itLower != itUpper; ++itLower) {
    itLower->second(this);
  }
  return true;
}