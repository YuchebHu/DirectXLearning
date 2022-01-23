#include "InitDirect3DApp.h"

#include <DirectXColors.h>

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance) : D3DApp(hInstance) {}

InitDirect3DApp::~InitDirect3DApp() {}

bool InitDirect3DApp::Initialize() {
  if (!D3DApp::Initialize()) {
    return false;
  }
  return true;
}

void InitDirect3DApp::OnResize() { D3DApp::OnResize(); }

void InitDirect3DApp::Update(const GameTimer& gt) {}

void InitDirect3DApp::Draw(const GameTimer& gt) {
  ThrowIfFailed(mDirectCmdListAlloc->Reset());

  ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

  {
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        CurrentBackBuffer(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET);
    mCommandList->ResourceBarrier(1, &barrier);
  }

  mCommandList->RSSetViewports(1, &mScreenViewport);
  mCommandList->RSSetScissorRects(1, &mScissorRect);

  mCommandList->ClearRenderTargetView(
      CurrentBackBufferView(),
      DirectX::Colors::LightSteelBlue,
      0,
      nullptr);
  mCommandList->ClearDepthStencilView(
      DepthStencilView(),
      D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
      1.0f,
      0,
      0,
      nullptr);

  {
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        CurrentBackBuffer(),
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT);
    mCommandList->ResourceBarrier(1, &barrier);
  }

  ThrowIfFailed(mCommandList->Close());

  ID3D12CommandList* cmdsLists[] = {mCommandList.Get()};
  mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

  ThrowIfFailed(mSwapChain->Present(0, 0));
  mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

  FlushCommandQueue();
}
