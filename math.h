#ifndef SANDBOX_OPENGL_22_MATH_H_
#define SANDBOX_OPENGL_22_MATH_H_

#include <glm/glm.hpp>

namespace math {
    // Screen 座標系 (0 ~ screen width/height) から Device 座標系 (-1 ~ 1) に変換
    // Screen 座標系の X 軸は右、Y 軸は下。Device 座標系の X 軸は右、Y 軸は "上" なので、Y 軸のみ符号を反転する。
    glm::vec2 TransformFromScreenCoordinateToDeviceCoordinate(int x, int y, int screen_width, int screen_height);
}

#endif //SANDBOX_OPENGL_22_MATH_H_
