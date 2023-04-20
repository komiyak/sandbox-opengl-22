
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <gl_app/gl.h>
#include <gl_app/gl_debug.h>

#include "assimp_mesh.h"

struct Vertex_ {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

struct Texture_ {
    unsigned int id;
    std::string type;
};

class Mesh_ {
public:
    Mesh_(const std::vector<Vertex_> &vertices, const std::vector<unsigned int> &indices,
          const std::vector<Texture_> &textures) : vertices_(vertices), indices_(indices), textures_(textures) {
        setupMesh();
    }

private:
    std::vector<Vertex_> vertices_{}; // FIXME: これ array にするべきでは？
    std::vector<unsigned int> indices_{}; // FIXME: これ array にするべきでは？
    std::vector<Texture_> textures_{};

    GLuint vao_{};
    GLuint vbo_{};
    GLuint ebo_{};

    void setupMesh() {
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);
        GL_APP_CHECK_GL_ERROR();

        // vbo
        glGenBuffers(1, &vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        GL_APP_CHECK_GL_ERROR();
        glBufferData(
                GL_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(vertices_.size() * sizeof(Vertex_)),
                &vertices_[0],
                GL_STATIC_DRAW);
        GL_APP_CHECK_GL_ERROR();

        // ebo
        glGenBuffers(1, &ebo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        GL_APP_CHECK_GL_ERROR();
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                static_cast<GLsizeiptr>(indices_.size() * sizeof(unsigned int)),
                &indices_[0],
                GL_STATIC_DRAW);
        GL_APP_CHECK_GL_ERROR();

        // FIXME: need vertex specification
    }
};
