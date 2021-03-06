#pragma once

#include "Common/d3dApp.h"

#include <DirectXColors.h>

class InitDirect3DApp : public D3DApp {
public:
  InitDirect3DApp(HINSTANCE hInstance);
  ~InitDirect3DApp();

  virtual bool Initialize() override;

private:
  virtual void OnResize() override;
  virtual void Update(const GameTimer& gt) override;
  virtual void Draw(const GameTimer& gt) override;
};
