#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "widget.h"

class WidgetContainer : public Widget {
  public:
    WidgetContainer(const std::string& id);
    virtual ~WidgetContainer(void);

    WidgetRef GetWidget(const std::string& id, bool bChild = false);

    bool AddWidget(WidgetRef& widget);
    bool AddWidget(const std::string& id, WidgetRef& widget);

    void RemoveWidget(const std::string& id);
    void RemoveWidget(WidgetRef& widget);

    WidgetRef FindWidget(float x, float y);

  public:
    virtual bool IsContainer(void) override final { return true; }

  protected:
    virtual void UpdateMe(float dt) override;

    virtual void RenderMe(void) override;

    virtual void OnWidgetAdded(WidgetRef& widget);

    virtual void OnWidgetRemoved(WidgetRef& widget);

    virtual void OnWidgetUpdated();

  protected:
    friend Widget;

    std::unordered_map<std::string, WidgetRef> widgetMap;

    std::vector<WidgetRef> widgets;

  private:
    struct MemberLess : public std::binary_function<WidgetRef, WidgetRef, bool> {
      bool operator()(WidgetRef m1, WidgetRef m2) const {
        return m1->GetOrder() < m2->GetOrder();
      };
    };
};