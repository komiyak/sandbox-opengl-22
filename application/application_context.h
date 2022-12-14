#ifndef SANDBOX_OPENGL_22_APPLICATION_CONTEXT_H_
#define SANDBOX_OPENGL_22_APPLICATION_CONTEXT_H_

// Application の状態を保持するクラス
class ApplicationContext {
public:
    [[nodiscard]] int GetWindowScreenWidth() const {
        return windowScreenWidth_;
    }

    [[nodiscard]] int GetWindowScreenHeight() const {
        return windowScreenHeight_;
    }

private:
    // 現在のウィンドウのスクリーンサイズ（描画領域）の横幅ピクセルサイズ
    int windowScreenWidth_{1920}; // Note: 現在は固定値だが、将来的には動的に横幅をセットする
    // 現在のウィンドウのスクリーンサイズ（描画領域）の縦幅ピクセルサイズ
    int windowScreenHeight_{1080}; // Note: 現在は固定値だが、将来的には動的に横幅をセットする
};

#endif //SANDBOX_OPENGL_22_APPLICATION_CONTEXT_H_
