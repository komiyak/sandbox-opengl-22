#ifndef SANDBOX_OPENGL_22_GL_APP_DEBUG_H_
#define SANDBOX_OPENGL_22_GL_APP_DEBUG_H_

#include <cstdlib>
#include "preference.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define GL_APP_DEBUG_ASSERT(expression) do { if (gl_app::kRuntimeAssertion && !(expression)) { abort(); } } while (0)
#define GL_APP_DEBUG_ASSERT_MESSAGE(expression, message) do { if (gl_app::kRuntimeAssertion && !(expression)) { fprintf(stderr, message); fprintf(stderr, "\n"); abort(); } } while (0)
#define GL_APP_DEBUG_ABORT_MESSAGE(message) do { if (gl_app::kRuntimeAssertion) { fprintf(stderr, message); fprintf(stderr, "\n"); abort(); } } while (0)

#pragma clang diagnostic pop

#endif //SANDBOX_OPENGL_22_GL_APP_DEBUG_H_
