#ifndef SANDBOX_OPENGL_22_PREFERENCE_H_
#define SANDBOX_OPENGL_22_PREFERENCE_H_

// Print debug logs about OpenGL.
static const bool kOpenGLDebugLogging = true;
// Use debug context in OpenGL (since version 4.3). This option has a significant performance impact. So you turn on it when you need it.
// See: https://learnopengl.com/In-Practice/Debugging
static const bool kOpenGLDebugContext = true;

// Enabling assertions in the game runtime.
static const bool kRuntimeAssertion = true;

#endif //SANDBOX_OPENGL_22_PREFERENCE_H_
