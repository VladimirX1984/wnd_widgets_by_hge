// WndHgeWidgets.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WndHgeWidgets.h"

#include "HgeApp.h"
#include "types.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  HgeApp::app = make_shared<HgeApp>();
  return HgeApp::app->Start();
}