#pragma once

#include "../Kernel/Kernel.h"
#include "../View/View.h"

class App {
public:
    App();
    void Run();

private:
    // Kernel k;
    View view_;
    // Controller c;
};