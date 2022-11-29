#ifndef SANDBOX_OPENGL_22_MATH_H_
#define SANDBOX_OPENGL_22_MATH_H_

#include <glm/glm.hpp>

namespace math {
    // Screen 座標系 (0 ~ screen width/height) から Device 座標系 (-1 ~ 1) に変換
    glm::vec2 TransformFromScreenCoordinateToDeviceCoordinate(int x, int y, int screen_width, int screen_height) {
        return {((float) x / (float) screen_width * 2.f) - 1.f,
                ((float) y / (float) screen_height * 2.f) - 1.f};
    }
}

#endif //SANDBOX_OPENGL_22_MATH_H_
