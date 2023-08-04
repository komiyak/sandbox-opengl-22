
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

#include <gl_app/gl.h>
#include <gl_app/gl_debug.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
    Mesh_(const std::vector<Vertex_> &vertices,
          const std::vector<unsigned int> &indices,
          const std::vector<Texture_> &textures) : vertices_(vertices), indices_(indices), textures_(textures) {

        SetupMesh();
    }

private:
    std::vector<Vertex_> vertices_{}; // FIXME: これ array にするべきでは？
    std::vector<unsigned int> indices_{}; // FIXME: これ array にするべきでは？
    std::vector<Texture_> textures_{};

    GLuint vao_{};
    GLuint vbo_{};
    GLuint ebo_{};

    void SetupMesh() {
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

        // todo: to need vertex specifications
    }

    // todo: to need a shader reference.
    void Draw(/*Shader shader*/) {
        unsigned int diffuse_number = 1;
        unsigned int specular_number = 1;

        for (int i = 0; i < textures_.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = textures_[i].type;
            if (name == "texture_diffuse") {
                number = std::to_string(diffuse_number);
            } else if (name == "texture_specular") {
                number = std::to_string(specular_number);
            }

            // shader.SetInt(("material." + name + number), i);
            glBindTexture(GL_TEXTURE_2D, textures_[i].id);
        }

        // ?: いったん影響を 0 にしてるのかな？
        glActiveTexture(GL_TEXTURE0);

        // draw meshes
        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0); // ?: これも影響を消すための対応？
    }
};

class Model_ {
public:
    Model_(std::string &path) {
        LoadModel(path);
    }

    void Draw(/* shader */) {
        // loop
        //    meshes[i].Draw(shader)
    }

private:
    std::string directory;

    void LoadModel(const std::string &path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }

        directory = path.substr(0, path.find_last_of('/'));

        ProcessNode(scene->mRootNode, scene);
    }
    
    void ProcessNode(aiNode *mesh, const aiScene *scene) {

    }


};
