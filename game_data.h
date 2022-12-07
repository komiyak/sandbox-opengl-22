#ifndef SANDBOX_OPENGL_22_GAME_DATA_H_
#define SANDBOX_OPENGL_22_GAME_DATA_H_

// 静的データをまとめるクラス
class GameData {
public:
    // 頂点 2D 四角形 (軸: 左上が原点)
    // GL_TRIANGLE_STRIP
    [[maybe_unused]] constexpr static float kQuad2dPivotTopLeftVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            0, -1, 0, 1,
            0, 0, 0, 0,
            1, -1, 1, 1,
            1, 0, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 左下が原点)
    // GL_TRIANGLE_STRIP
    [[maybe_unused]] constexpr static float kQuad2dPivotBottomLeftVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            0, 0, 0, 1,
            0, 1, 0, 0,
            1, 0, 1, 1,
            1, 1, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 右上が原点)
    // GL_TRIANGLE_STRIP
    [[maybe_unused]] constexpr static float kQuad2dPivotTopRightVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            -1, -1, 0, 1,
            -1, 0, 0, 0,
            0, -1, 1, 1,
            0, 0, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 右下が原点)
    // GL_TRIANGLE_STRIP
    [[maybe_unused]] constexpr static float kQuad2dPivotBottomRightVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            -1, 0, 0, 1,
            -1, 1, 0, 0,
            0, 0, 1, 1,
            0, 1, 1, 0,
    };
    // 頂点 2D 四角形 (軸: 中心が原点)
    // GL_TRIANGLE_STRIP
    [[maybe_unused]] constexpr static float kQuad2dPivotCenterVertices[] = {
            // x, y, s, t (texcoord st は左上を原点として定義)
            -0.5, -0.5, 0, 1,
            -0.5, 0.5, 0, 0,
            0.5, -0.5, 1, 1,
            0.5, 0.5, 1, 0,
    };

    // 頂点 3D Cube
    // GL_TRIANGLES
    [[maybe_unused]] constexpr static float kCubeVertices[] = {
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

    // 頂点カラー 3軸表示 3D
    // GL_LINES
    [[maybe_unused]] constexpr static float kAxisVertices[] = {
            // x, y, z, r, g, b
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
    };
    [[maybe_unused]] constexpr static std::size_t kAxisVerticesSize = sizeof(kAxisVertices);

    // グリッド 3D
    // GL_LINES
    [[maybe_unused]] constexpr static float kGridVertices[] = {
            -5.0f, 0.0f, -5.f,
            -5.0f, 0.0f, 5.0f,

            -4.0f, 0.0f, -5.0f,
            -4.0f, 0.0f, 5.0f,

            -3.0f, 0.0f, -5.0f,
            -3.0f, 0.0f, 5.0f,

            -2.0f, 0.0f, -5.0f,
            -2.0f, 0.0f, 5.0f,

            -1.0f, 0.0f, -5.0f,
            -1.0f, 0.0f, 5.0f,

            0.0f, 0.0f, -5.0f,
            0.0f, 0.0f, 5.0f,

            1.0f, 0.0f, -5.0f,
            1.0f, 0.0f, 5.0f,

            2.0f, 0.0f, -5.0f,
            2.0f, 0.0f, 5.0f,

            3.0f, 0.0f, -5.0f,
            3.0f, 0.0f, 5.0f,

            4.0f, 0.0f, -5.0f,
            4.0f, 0.0f, 5.0f,

            5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, 5.0f,


            -5.0f, 0.0f, -5.0f,
            5.0f, 0.0f, -5.0f,

            -5.0f, 0.0f, -4.0f,
            5.0f, 0.0f, -4.0f,

            -5.0f, 0.0f, -3.0f,
            5.0f, 0.0f, -3.0f,

            -5.0f, 0.0f, -2.0f,
            5.0f, 0.0f, -2.0f,

            -5.0f, 0.0f, -1.0f,
            5.0f, 0.0f, -1.0f,

            -5.0f, 0.0f, 0.0f,
            5.0f, 0.0f, 0.0f,

            -5.0f, 0.0f, 1.0f,
            5.0f, 0.0f, 1.0f,

            -5.0f, 0.0f, 2.0f,
            5.0f, 0.0f, 2.0f,

            -5.0f, 0.0f, 3.0f,
            5.0f, 0.0f, 3.0f,

            -5.0f, 0.0f, 4.0f,
            5.0f, 0.0f, 4.0f,

            -5.0f, 0.0f, 5.0f,
            5.0f, 0.0f, 5.0f,
    };
    [[maybe_unused]] constexpr static std::size_t kGridVerticesSize = sizeof(kGridVertices);
};

#endif //SANDBOX_OPENGL_22_GAME_DATA_H_
