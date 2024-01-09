#pragma once

#include "../Kernel/Kernel.h"
#include "../View/PixelScreen.h"
#include "../View/View.h"

class App {
    static const int kWidth = 800;
    static const int kHeight = 600;

public:
    App();
    void Run();

private:
    // Kernel k;
    View view_;
};