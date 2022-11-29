#include "math.h"

glm::vec2 math::TransformFromScreenCoordinateToDeviceCoordinate(int x, int y, int screen_width, int screen_height) {
    return {((float) x / (float) screen_width * 2.f) - 1.f,
            (((float) y / (float) screen_height * 2.f) - 1.f) * -1.f};
}
