//
// Created by komiyak on 22/10/05.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "fps.h"

void Fps::StartRecord() {
    const double time = glfwGetTime();

    // 初回実行時の初期設定
    if (!started_) {
        started_ = true;
        frame_fps_time_ = time;
    }

    // 1秒以上経過したら FPS を決定する
    if (time - frame_fps_time_ >= 1.0) {
        fps_ = frame_count_;
        frame_count_ = 0;
        frame_fps_time_ = time;
    }

    // frame の経過時間を測定する
    last_frame_elapsed_time_ = frame_end_time_ - frame_begin_time_;
    frame_begin_time_ = time;
}

void Fps::EndRecord() {
    frame_end_time_ = glfwGetTime();
    frame_count_++;
}
