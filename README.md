# sandbox-opengl-22

A sandbox project of OpenGL that was created in 2022.

## Prerequisites

- Linux platform only.
- C++17
- CMake
- Installed `xorg-dev`
- OpenGL 4.6 compatibility graphic card (and its hardware drivers to your PC)

## To install required libraries.

You should run the command once to start development the first time.

```sh
./install.sh
```

## Abbreviated words

These words can be abbreviated as another one.

| Full | To abbreviate |
| --- | --- |
| Attribute | Attrib |
| Function | Func |
| Iterator (C++) | Iter |
| Length | Len |
| Matrix | Mat |
| Parameter, Parameters | Param, Params |
| Quadrangle (Math) | Quad |
| Vector (Math) | Vec |
| Vertex array object (OpenGL) | VAO, Vao |
| Vertex buffer object (OpenGL) | VBO, Vbo |
| GL_ELEMENT_ARRAY_BUFFER's object (OpenGL) | EBO, Ebo |

### NGs

These words are hard to understand. You should use full spelling.

- rad => radian (Math)
- deg => degree (Math)
- mat => material
- tex => texture

## To identify spelling inconsistency in the code

| Meaning | Words | Should |
| --- | --- | --- |
| plural of `vertex` | `vertexes` or `vertices` | `vertices` |

## Scenes

| Scene's name | Description |
| --- | --- |
| StartingScene | The first scene to start up. |
| SandboxScene | A sandbox with no purpose. It's OK if it breaks. |
| LearnOpenGlLightingScene | A scene to learn lighting from LearnOpenGL.com |
| LearnOpenGlLightingLightCastersScene | A scene to learn light casters from LearnOpenGL.com |
| LearnOpenGlLightingMultipleLightsScene | A scene to learn multiple lights from LearnOpenGL.com |

## Shader files

| Shader's name (and filename) | Description |
| --- | --- |
| font.frag/vert | A vertex with 4 data as Vertex(x, y) and texcoord (s, t). 2D bitmap font rendering with color by uniform. |
| learnopengl_lighting_directional_light.frag/vert | In LearnOpenGL.com the Lighting chapter, A vertex with 8 data as Vertex (x, y, z), normal (x, y, z) and texcoord (s, t). It's a directional light shader. |
| learnopengl_lighting_multiple_lights.frag/vert | In LearnOpenGL.com the Lighting chapter, A vertex with 8 data as Vertex (x, y, z), normal (x, y, z) and texcoord (s, t). It's a spotlight shader. |
| learnopengl_lighting_point_light.frag/vert | In LearnOpenGL.com the Lighting chapter, A vertex with 8 data as Vertex (x, y, z), normal (x, y, z) and texcoord (s, t). It's a point light shader. |
| learnopengl_lighting_spotlight.frag/vert | In LearnOpenGL.com the Lighting chapter, A vertex with 8 data as Vertex (x, y, z), normal (x, y, z) and texcoord (s, t). It's a spotlight shader. |
| practice_lighting_gouraud_shading.frag/vert | A vertex with 6 data as Vertex (x, y, z) and normal (x, y, z). To practice lighting with gouraud shading. |
| practice_lighting_lighting_map.frag/vert | A vertex with 8 data as Vertex (x, y, z), normal (x, y, z) and texcoord (s, t). To practice lighting map. |
| practice_lighting_phong_shading.frag/vert | A vertex with 6 data as Vertex (x, y, z) and normal (x, y, z). To practice lighting with phong shading. |
| texture.frag/vert | A vertex with 5 data as Vertex (x, y, z) and texcoord (s, t). |
| texture_2d.frag/vert | A vertex with 4 data as Vertex (x, y) and texcoord (s, t). For 2D rendering. |
| vertex_color.frag/vert | A vertex with 6 data as Vertex (x, y, z) and Vertex color (r, g, b). |
| white_vertex.frag/vert | A vertex with 3 data as Vertex (x, y, z). Rendering white color vertex (for debug maybe). |

## How to test

Installed the GoogleTest (is a testing framework).

How to test: TODO.
