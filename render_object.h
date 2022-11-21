//
// Created by komiyak on 22/11/21.
//

#ifndef SANDBOX_OPENGL_22_RENDER_OBJECT_H_
#define SANDBOX_OPENGL_22_RENDER_OBJECT_H_

#include <glad/glad.h>
#include "base_object.h"

class Shader;

class RenderObject : public BaseObject {
public:
    void BindRender();

    void Render() const;

    void Initialize(
            GLsizeiptr vertex_size,
            const void *vertex_data,
            GLenum usage,
            GLenum draw_mode,
            GLsizei draw_count,
            Shader *p_shader);

    void Finalize() override;

private:
    GLuint vao_{};
    GLuint vbo_{};

    GLenum draw_mode_{};
    GLsizei draw_count_first_{};
    GLsizei draw_count_{};

    Shader *p_shader_{nullptr};
};

#endif //SANDBOX_OPENGL_22_RENDER_OBJECT_H_
