
#define _CONSOLE 1
#define _WINDOWS 0

#if _WINDOWS

#include "Book/Chapter4/InitDirect3DApp.h"
 int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE prevInstance,
    PSTR cmdLine,
    int showCmd) {
  // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  try {
    InitDirect3DApp theApp(hInstance);
    if (!theApp.Initialize())
      return 0;

    return theApp.Run();
  } catch (const DxException& e) {
    MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
    return 0;
  }
}

#elif _CONSOLE
#include "Book/Chapter2/Exercise.h"

int main() {

  Exercise::Matrix A = {{-1, 5, 5}, {3, 2, 5}};
  Exercise::Matrix B = {{2, 1, 0}, {0, -2, 1}, {-1, 2, 3}};

  auto m =
      Exercise::MatrixTimes(A, B);
  if (m.has_value()) {
    auto invertM = Exercise::InvertMatrix(m.value());
    Exercise::PrintMatrix(m.value());
    Exercise::PrintMatrix(invertM.value());
  }
  return 0;
}

#endif// 

