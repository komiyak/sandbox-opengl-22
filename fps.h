#ifndef CPP_GLFW3_SANDBOX_FPS_H
#define CPP_GLFW3_SANDBOX_FPS_H

class Fps {
public:
    // Frame レンダリング開始時にコールする FPS カウンタ
    void StartRecord();

    // Frame レンダリング終了時にコールする FSP カウンタ
    void EndRecord();

    // FPS 値を取得
    [[maybe_unused]] [[nodiscard]] int Get() const {
        return fps_;
    }

    // 1 frame の正確な経過時間を取得する
    [[maybe_unused]] [[nodiscard]] double GetElapsedTime() const {
        return last_frame_elapsed_time_;
    }

    Fps() :
            fps_(0), frame_count_(0), frame_begin_time_(0), frame_end_time_(0), frame_fps_time_(0),
            last_frame_elapsed_time_(0), started_(false) {}

private:
    // 最新のFPS
    int fps_;
    // フレームの回数カウント
    int frame_count_;
    // 最後のフレームのレンダリング開始時間
    double frame_begin_time_;
    // 最後のフレームのレンダリング終了時間
    double frame_end_time_;
    // fps 計測開始時間
    double frame_fps_time_;
    // 最後のフレームで消費した時間
    double last_frame_elapsed_time_;
    // 初回実行フラグ
    bool started_;
};

#endif //CPP_GLFW3_SANDBOX_FPS_H
