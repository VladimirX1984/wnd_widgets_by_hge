#include "stdafx.h"
#include "WidgetContainer.h"

#include <algorithm>

WidgetContainer::WidgetContainer(const std::string& id) : Widget(id) {
}

WidgetContainer::~WidgetContainer(void) {
  auto it = widgetMap.begin(), end = widgetMap.end();
  for (; it != end; ++it) {
    it->second.reset();
  }
  widgetMap.clear();
  auto vit = widgets.begin(), vend = widgets.end();
  for (; vit != vend; ++vit) {
    vit->reset();
  }
  widgets.clear();
}

WidgetRef WidgetContainer::GetWidget(const std::string& id, bool bChild /*= false*/) {
  auto wIt = widgetMap.find(id);
  if (wIt == widgetMap.end()) {
    if (bChild) {
      auto it = widgets.begin(), end = widgets.end();
      for (; it != end; ++it) {
        auto widget = *it;
        if (!widget->IsContainer()) {
          continue;
        }
        auto derived = dynamic_pointer_cast<WidgetContainer>(widget);
        if (derived != nullptr) {
          auto foundedWidget = derived->GetWidget(id, true);
          if (foundedWidget) {
            return foundedWidget;
          }
        }
      }
    }
    return WidgetRef();
  }
  return wIt->second;
}

bool WidgetContainer::AddWidget(WidgetRef& widget) {
  std::string id = widget->GetId();
  return AddWidget(id, widget);
}

bool WidgetContainer::AddWidget(const std::string& id, WidgetRef& widget) {
  auto widgetIt = widgetMap.find(id);
  if (widgetIt != widgetMap.end()) {
    return false;
  }
  widgetMap[id] = widget;
  auto container = widget->GetWidgetContainer();
  if (container) {
    container->RemoveWidget(widget);
  }
  auto derived = reinterpret_pointer_cast<WidgetContainer>(shared_from_this());
  if (derived != nullptr) {
    widget->widgetContainer = derived;
  }
  OnWidgetAdded(widgetMap[id]);
  return true;
}

void WidgetContainer::RemoveWidget(const std::string& id) {
  auto widgetIt = widgetMap.find(id);
  if (widgetIt != widgetMap.end()) {
    OnWidgetRemoved(widgetIt->second);
    widgetMap.erase(widgetIt);
  }
}

void WidgetContainer::RemoveWidget(WidgetRef& widget) {
  std::string id = widget->GetId();
  RemoveWidget(id);
}

WidgetRef WidgetContainer::FindWidget(float x, float y) {
  auto it = widgets.rbegin(), end = widgets.rend();
  for (; it != end; ++it) {
    auto widget = *it;
    if (!widget->IsVisible()) {
      continue;
    }
    if (widget->IsContainer()) {
      auto derived = dynamic_pointer_cast<WidgetContainer>(widget);
      if (derived != nullptr) {
        auto foundWidget = derived->FindWidget(x - pos.x, y - pos.y);
        if (foundWidget) {
          return foundWidget;
        }
      }
    }
    if (widget->GetBoundingBox().TestPoint(x - pos.x, y - pos.y)) {
      return widget;
    }
  }
  return WidgetRef();
}

void WidgetContainer::UpdateMe(float dt) {
  auto it = widgets.begin(), end = widgets.end();
  for (; it != end; ++it) {
    auto widget = *it;
    widget->Update(dt);
  }
}

void WidgetContainer::RenderMe(void) {
  auto it = widgets.begin(), end = widgets.end();
  for (; it != end; ++it) {
    auto widget = *it;
    float x = widget->GetPosX();
    float y = widget->GetPosY();
    widget->SetPos(pos.x + x, pos.y + y);
    widget->Render();
    widget->SetPos(x, y);
  }
}

void WidgetContainer::OnWidgetAdded(WidgetRef& widget) {
  widgets.push_back(widget);
  std::sort(widgets.begin(), widgets.end(), MemberLess());
}

void WidgetContainer::OnWidgetRemoved(WidgetRef& widget) {
  auto it = std::find(widgets.begin(), widgets.end(), widget);
  if (it != widgets.end()) {
    widgets.erase(it);
    std::sort(widgets.begin(), widgets.end(), MemberLess());
  }
}

void WidgetContainer::OnWidgetUpdated() {
  std::sort(widgets.begin(), widgets.end(), MemberLess());
}
