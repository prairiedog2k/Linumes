#include <cstdlib>
#include <iostream>
#include <memory>

#include "LinumesModeManager.h"

#include "boss/Boss.h"

#ifdef MING_ENTRY
#include "Windows.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int iCmdShow)
{
    return main(0, nullptr);
}
#endif
using namespace std;
int main(int argc, char *argv[]) {
    std::cout << "LINUMES developer@mountain 2007" << endl;
#ifdef DEBUG
    std::cout << "(DEBUG MODE ENABLED)" << endl;
#endif

    auto lmm = std::make_unique<LinumesModeManager>("LinumesConfiguration.yaml");
    if (lmm->init()) {
        lmm->run();
    }

    return 0;
}
