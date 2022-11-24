#ifndef SANDBOX_OPENGL_22_DEBUG_H_
#define SANDBOX_OPENGL_22_DEBUG_H_

#include <cstdlib>
#include "preference.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define DEBUG_ASSERT(expression) do { if (kRuntimeAssertion && !(expression)) { abort(); } } while (0)
#define DEBUG_ASSERT_MESSAGE(expression, message) do { if (kRuntimeAssertion && !(expression)) { fprintf(stderr, message); fprintf(stderr, "\n"); abort(); } } while (0)

#pragma clang diagnostic pop

#endif //SANDBOX_OPENGL_22_DEBUG_H_
