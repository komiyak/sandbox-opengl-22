//
// Created by komiyak on 22/11/21.
//

#ifndef SANDBOX_OPENGL_22_BASE_OBJECT_H_
#define SANDBOX_OPENGL_22_BASE_OBJECT_H_

// Finalizing and deleting
#define FINALIZE_AND_DELETE(p) if (p) {(p)->Finalize(); delete (p); (p) = nullptr;} do {} while (0)

class BaseObject {
public:
    // 終了時に必ず実行するべき処理を記述、失敗する場合は例外を返却する
    virtual void Finalize() = 0;
};

#endif //SANDBOX_OPENGL_22_BASE_OBJECT_H_
