#include <SFML/Graphics.hpp>

#include "../Kernel/Kernel.h"

namespace ThreeDRenderer {

class AddNewObjectDialog {
public:
    void ReadPathToObject();
    void ReadObjectColor();
    void ReadObjectCoordinates();
    void AddObjectToKernel(Kernel& ker);

private:
    std::string path_to_file;
    sf::Color color_;
    Eigen::Vector3d position_;
};

}  // namespace ThreeDRenderer
