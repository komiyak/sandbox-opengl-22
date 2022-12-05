#ifndef SANDBOX_OPENGL_22_GAME_DATA_H_
#define SANDBOX_OPENGL_22_GAME_DATA_H_

// 静的データをまとめるクラス
class GameData {
public:
    // 頂点 2D 四角形 (軸: 左上が原点)
    [[maybe_unused]] constexpr static float kQuad2dPivotTopLeftVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            // GL_TRIANGLE_STRIP
            0, -1, 0, 1,
            0, 0, 0, 0,
            1, -1, 1, 1,
            1, 0, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 左下が原点)
    [[maybe_unused]] constexpr static float kQuad2dPivotBottomLeftVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            // GL_TRIANGLE_STRIP
            0, 0, 0, 1,
            0, 1, 0, 0,
            1, 0, 1, 1,
            1, 1, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 右上が原点)
    [[maybe_unused]] constexpr static float kQuad2dPivotTopRightVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            // GL_TRIANGLE_STRIP
            -1, -1, 0, 1,
            -1, 0, 0, 0,
            0, -1, 1, 1,
            0, 0, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 右下が原点)
    [[maybe_unused]] constexpr static float kQuad2dPivotBottomRightVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            // GL_TRIANGLE_STRIP
            -1, 0, 0, 1,
            -1, 1, 0, 0,
            0, 0, 1, 1,
            0, 1, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 中心が原点)
    [[maybe_unused]] constexpr static float kQuad2dPivotCenterVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            -0.5, -0.5, 0, 1,
            -0.5, 0.5, 0, 0,
            0.5, -0.5, 1, 1,
            0.5, 0.5, 1, 0,
    };

    // 頂点 3D Cube
    [[maybe_unused]] constexpr static float kCube[] = {
            // x, y, z
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
    };
};

#endif //SANDBOX_OPENGL_22_GAME_DATA_H_
