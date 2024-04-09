#include <SFML/Graphics.hpp>

#include "../Kernel/Kernel.h"
#include "../Utilities/GLogger.h"
#include "../Utilities/Response.h"

namespace ThreeDRenderer {

class AddNewObjectDialog {
    using ResponseColor = Utilities::Response<sf::Color>;
    using ResponseVector3 = Utilities::Response<Eigen::Vector3d>;

    static const Utilities::GLogger<Utilities::ConsoleLoggerInstance> kLogger;

public:
    bool ReadPathToObject();
    bool ReadObjectColor();
    bool ReadObjectCoordinates();
    bool AddObjectToKernel(Kernel& ker);

private:
    static ResponseColor ParseColor(const std::string& str);
    static ResponseVector3 ParsePosition(const std::string& str);

    std::string path_to_file_;
    sf::Color color_;
    Eigen::Vector3d position_;
};

}  // namespace ThreeDRenderer
