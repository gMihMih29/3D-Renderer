#pragma once

#include "../Observer/Observer.h"
#include "../View/PixelScreen.h"

namespace ThreeDRenderer {

class Kernel {
public:
    Kernel();
    void SubscribeToCameraUpdates(CObserver<PixelScreen>*);
    // метод для генерации данных для подсписчиков?

private:
    CObservable<PixelScreen> observable_;
};

}  // namespace ThreeDRenderer
