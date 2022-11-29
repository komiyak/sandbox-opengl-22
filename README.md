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
| Length | Len |
| Matrix | Mat |
| Parameter, Parameters | Param, Params |
| Quadrangle (Math) | Quad |
| Vector (Math) | Vec |
| Vertex array object (OpenGL) | VAO, Vao |
| Vertex buffer object (OpenGL) | VBO, Vbo |

### NGs

These words are hard to understand. You should use full spelling.

- rad => radian (Math)
- deg => degree (Math)
- tex => texture

## To identify spelling inconsistency in the code

| Meaning | Words | Should |
| --- | --- | --- |
| plural of `vertex` | `vertexes` or `vertices` | `vertices` |

## Shader files

| Shader's name (and filename) | Description |
| --- | --- |
| texture.frag/vert | A vertex with 5 data as Vertex(x, y, z) and texcoord (s, t). |
| texture_2d.frag/vert | A vertex with 4 data as Vertex(x, y) and texcoord (s, t). For 2D rendering. |
| vertex_color.frag/vert | A vertex with 6 data as Vertex(x, y, z) and Vertex color(r, g, b). |
| white_vertex.frag/vert | A vertex with 3 data as Vertex(x, y, z). Rendering white color vertex (for debug maybe). |

## How to test

Installed the GoogleTest (is a testing framework).

How to test: TODO.
