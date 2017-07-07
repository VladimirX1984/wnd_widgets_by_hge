#include "stdafx.h"
#include "HgeApp.h"

#include "hge.h"
#include "hgefont.h"

#include "ImageWidget.h"
#include "ButtonWidget.h"
#include "EffectWidget.h"
#include "MainWidgetContainer.h"
#include "ResourceHub.h"

const int wndWidth = 1024;
const int wndHeight = 768;

float dx = 0.0f, dy = 0.0f;

const float speed = 50;
const float friction = 0.96f;

HgeAppRef HgeApp::app;

HgeApp::HgeApp(void) {
  hge = nullptr;
  bOrderFlag = false;
  time = 0.f;
}

HgeApp::~HgeApp(void) {

}

int HgeApp::Start() {
  if (!app) {
    MessageBoxA(nullptr, "app is undefined", "Error",
                MB_OK | MB_ICONERROR | MB_APPLMODAL);
    return 1;
  }

  hge = hgeCreate(HGE_VERSION);

  hge->System_SetState(HGE_LOGFILE, "Hge_widgets.log");
  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
  hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
  hge->System_SetState(HGE_TITLE, "Hge widgets - Khovanskiy Vladimir");
  hge->System_SetState(HGE_FPS, 50);
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_SCREENWIDTH, wndWidth);
  hge->System_SetState(HGE_SCREENHEIGHT, wndHeight);
  hge->System_SetState(HGE_SCREENBPP, 32);
  hge->System_SetState(HGE_USESOUND, false);
  hge->System_SetState(HGE_HIDEMOUSE, false);

  if (hge->System_Initiate()) {

    std::string name = "main";
    mainWidget = make_shared<MainWidgetContainer>(hge);
    mainWidget->SetPos(200, 100);

    auto btn1 = make_shared<ButtonWidget>("btn1");
    if (!btn1->LoadUpSprite("image.png", 0, 0, 32, 32) ||
        !btn1->LoadDownSprite("image.png", 96, 64, 32, 32)) {
      Release();
      return 1;
    }
    btn1->SetColor(0xFF2FA0F0);
    btn1->SetPos(100, 100);
    btn1->AddEventHandler(Widget::MOUSE_CLICK, [](Widget * widget) {
      auto container2 = widget->GetRootWidget()->GetWidget("container2");
      if (!container2->IsVisible()) {
        container2->Show();
      }
      else {
        container2->Hide();
      }
    });

    auto img1 = make_shared<ImageWidget>("img1");
    if (!img1->LoadSprite("zazaka.png")) {
      Release();
      return 1;
    }
    img1->SetColor(0xFF2FA0F0);
    img1->SetPos(170, 100);
    img1->SetOrder(1);
    img1->AddEventHandler(Widget::MOUSE_ENTER, [](Widget * widget) {
      widget->GetWidgetContainer()->GetWidget("img2")->Show();
    });
    img1->AddEventHandler(Widget::MOUSE_LEAVE, [](Widget * widget) {
      widget->GetWidgetContainer()->GetWidget("img2")->Hide();
    });

    auto img2 = make_shared<ImageWidget>("img2");
    if (!img2->LoadSprite("image.png")) {
      Release();
      return 1;
    }
    img2->SetColor(0xFFFFA000);
    img2->SetPos(150, 100);
    img2->Hide();

    auto eff1 = make_shared<EffectWidget>("eff1");
    eff1->SetOrder(2);
    eff1->SetPos(wndWidth / 2.f, wndHeight / 2.f);
    eff1->LoadEffect("trail.psi", "image.png", 32, 32, 32, 32);

    auto container1 = make_shared<WidgetContainer>("container1");
    container1->SetOrder(1);

    container1->AddWidget((WidgetRef)btn1);
    container1->AddWidget((WidgetRef)img1);
    container1->AddWidget((WidgetRef)img2);
    container1->AddWidget((WidgetRef)eff1);
    mainWidget->AddWidget((WidgetRef)container1);

    auto container2 = make_shared<WidgetContainer>("container2");
    container2->SetPos(100, 100);
    mainWidget->AddWidget((WidgetRef)container2);

    auto btn2 = make_shared<ButtonWidget>("btn2");
    if (!btn2->LoadUpSprite("", 0, 0, 32, 32) || !btn2->LoadDownSprite("image.png", 96, 64, 32, 32)) {
      Release();
      return 1;
    }
    btn2->SetColor(0xFF2FF010);
    btn2->SetPos(100, 100);

    auto img22 = make_shared<ImageWidget>("img22");
    if (!img22->LoadSprite("zazaka.png")) {
      Release();
      return 1;
    }
    img22->SetColor(0xFFFFA000);
    img22->SetPos(150, 100);
    container2->AddWidget((WidgetRef)btn2);
    container2->AddWidget((WidgetRef)img22);
    container2->Hide();

    fnt = make_shared<hgeFont>("font2.fnt");

    hge->System_Start();

    fnt.reset();
    Release();
  }
  else {
    hge->Release();
  }
  return 0;
}

bool HgeApp::Update() {
  float dt = hge->Timer_GetDelta();

  if (hge->Input_GetKeyState(HGEK_ESCAPE)) {
    return true;
  }

  time += dt;

  if (hge->Input_GetKeyState(HGEK_LEFT)) {
    dx -= speed * dt;
  }
  if (hge->Input_GetKeyState(HGEK_RIGHT)) {
    dx += speed * dt;
  }
  if (hge->Input_GetKeyState(HGEK_UP)) {
    dy -= speed * dt;
  }
  if (hge->Input_GetKeyState(HGEK_DOWN)) {
    dy += speed * dt;
  }

  auto obj = mainWidget->GetWidget("eff1", true);
  if (obj != nullptr) {
    auto eff1 = dynamic_pointer_cast<EffectWidget>(obj);
    if (eff1 != nullptr) {
      auto pos = eff1->GetGlobalPos();
      float x = pos.x;
      float y = pos.y;
      auto rect = eff1->GetBoundingBox();
      float w = (rect.x2 - rect.x1) / 2.f;
      float h = (rect.y2 - rect.y1) / 2.f;
      dx *= friction;
      dy *= friction;
      pos.x += dx;
      pos.y += dy;
      if (pos.x > wndWidth) {
        pos.x = (wndWidth - w) - (pos.x - (wndWidth - w));
        dx = -dx;
      }
      if (pos.x < w) {
        pos.x = w - pos.x;
        dx = -dx;
      }
      if (pos.y > wndHeight - h) {
        pos.y = (wndHeight - h) - (pos.y - (wndHeight - h));
        dy = -dy;
      }
      if (pos.y < h) {
        pos.y = h - pos.y;
        dy = -dy;
      }

      eff1->SetEmission((int)(dx * dx + dy * dy) * 2 + (int)(100.f * dt));
      eff1->SetGlobalPos(pos);
    }
  }

  mainWidget->Update(dt);

  if (time >= 5.0f) {
    auto container1 = mainWidget->GetWidget("container1");
    container1->SetOrder(bOrderFlag ? 1 : -1);
    bOrderFlag = !bOrderFlag;
    time = 0.f;
  }

  //Test(dt);
  return false;
}

void HgeApp::Render() {
  hge->Gfx_BeginScene();
  hge->Gfx_Clear(0);
  mainWidget->Render();
  fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
  hge->Gfx_EndScene();
}

void HgeApp::Release() {
  mainWidget.reset();
  ResourceHub::Release();
  hge->System_Shutdown();
  hge->Release();
}

bool HgeApp::FrameFunc() {
  if (app) {
    return app->Update();
  }
  return true;
}

bool HgeApp::RenderFunc() {
  if (app) {
    app->Render();
    return false;
  }
  return true;
}

void HgeApp::Test(float dt) {
  // грубый тест на память
  for (int i = 33; i < 256; ++i) {
    mainWidget->RemoveWidget(std::string("container_test") + (char)i);
    auto container_test = make_shared<WidgetContainer>((std::string("container_test") + (char)i).c_str());
    container_test->SetOrder(1);
    container_test->Hide();

    auto btn1 = make_shared<ButtonWidget>("btn1");
    btn1->LoadUpSprite("image.png", 0, 0, 32, 32);
    btn1->LoadDownSprite("image.png", 96, 64, 32, 32);
    btn1->LoadDownSprite("image.png", 96, 64, 32, 32);
    btn1->LoadDownSprite("image.png", 96, 64, 32, 32);
    btn1->SetColor(0xFF2FA0F0);
    btn1->SetPos(100, 100);
    btn1->AddEventHandler(Widget::MOUSE_CLICK, [](Widget * widget) { });

    auto img1 = make_shared<ImageWidget>("img1");
    img1->LoadSprite("zazaka.png");
    img1->SetColor(0xFF2FA0F0);
    img1->SetPos(170, 100);
    img1->SetOrder(1);
    img1->AddEventHandler(Widget::MOUSE_ENTER, [](Widget * widget) {
      widget->GetWidgetContainer()->GetWidget("img2")->Show();
    });
    img1->AddEventHandler(Widget::MOUSE_LEAVE, [](Widget * widget) {
      widget->GetWidgetContainer()->GetWidget("img2")->Hide();
    });

    auto img2 = make_shared<ImageWidget>("img2");
    img2->LoadSprite("image.png");

    container_test->AddWidget((WidgetRef)btn1);
    container_test->AddWidget((WidgetRef)img1);
    container_test->AddWidget((WidgetRef)img2);
    mainWidget->AddWidget((WidgetRef)container_test);
  }
}