#pragma once

class HGE;
class hgeFont;
class MainWidgetContainer;
class Widget;
class HgeApp;

#if BOOST
#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<MainWidgetContainer> MainWidgetContainerRef;
typedef boost::shared_ptr<HgeApp> HgeAppRef;
typedef boost::shared_ptr<hgeFont> HgeFontRef;
#else
#include<memory>
typedef std::shared_ptr<MainWidgetContainer> MainWidgetContainerRef;
typedef std::shared_ptr<HgeApp> HgeAppRef;
typedef std::shared_ptr<hgeFont> HgeFontRef;
#endif

class HgeApp {
  public:
    HgeApp(void);
    virtual ~HgeApp(void);

    int Start();

    static HgeAppRef app;

  private:
    HGE *hge;
    MainWidgetContainerRef mainWidget;

    HgeFontRef fnt;

    float time;
    bool bOrderFlag;

  private:
    bool ProcessWidget(Widget* currWidget);

    bool Update();
    void Render();

    void Release();

  private:
    static bool FrameFunc();
    static bool RenderFunc();

    void Test(float dt);
};

