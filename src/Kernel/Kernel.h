#pragma once

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

class Kernel : public CObservable<PixelScreen> {
public:
    Kernel();
    const PixelScreen& GetScreen();
};