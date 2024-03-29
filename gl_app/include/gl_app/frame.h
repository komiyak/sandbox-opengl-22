#ifndef SANDBOX_OPENGL_22_GL_APP_FRAME_H_
#define SANDBOX_OPENGL_22_GL_APP_FRAME_H_

namespace gl_app {
    // Frame 管理
    // 内部的に高精度時間取得のため GLFW を使用している
    class Frame {
    public:
        // Frame レンダリング開始時にコールするフレームカウンタ
        void StartFrame();

        // Frame レンダリング終了時にコールするフレームカウンタ
        void EndFrame();

        // FPS 値を取得
        [[maybe_unused]] [[nodiscard]] int GetFps() const {
            return fps_;
        }

        // フレームが最後に更新されてからの経過時間
        [[maybe_unused]] [[nodiscard]] double GetDeltaTime() const {
            return last_frame_elapsed_time_;
        }

        // フレームが最後に更新されてからの経過時間 (float)
        [[maybe_unused]] [[nodiscard]] float GetDeltaTimeF() const {
            return (float) last_frame_elapsed_time_;
        }

    private:
        // 最新のFPS
        int fps_{};
        // フレームの回数カウント
        int frame_count_{};
        // 最後のフレームのレンダリング開始時間
        double frame_begin_time_{};
        // 最後のフレームのレンダリング終了時間
        double frame_end_time_{};
        // fps 計測開始時間
        double frame_fps_time_{};
        // 最後のフレームで消費した時間
        double last_frame_elapsed_time_{};
        // 初回実行フラグ
        bool started_{};
    };
}

#endif //SANDBOX_OPENGL_22_GL_APP_FRAME_H_
