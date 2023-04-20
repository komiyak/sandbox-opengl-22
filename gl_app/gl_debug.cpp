#include <iostream>
#include <glad/glad.h>

#include <execinfo.h>
#include <unistd.h>

#include "include/gl_app/gl_debug.h"
#include "include/gl_app/preference.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"

[[maybe_unused]] void gl_app::CheckGlError(const std::string &file, int line) {
    if (gl_app::kOpenGLDebugLogging == false) { return; }

    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM (0x0500)";
                break;
            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE (0x0501)";
                break;
            case GL_INVALID_OPERATION:
                error = "GL_INVALID_OPERATION (0x0502)";
                break;
            case GL_STACK_OVERFLOW:
                error = "GL_STACK_OVERFLOW (0x0503)";
                break;
            case GL_STACK_UNDERFLOW:
                error = "GL_STACK_UNDERFLOW (0x0504)";
                break;
            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY (0x0505)";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "GL_INVALID_FRAMEBUFFER_OPERATION (0x0506)";
                break;
            default:; // nothing
        }
        std::cout << "gl_app::CheckGlError | " << error << " | " << file << " (" << line << ")" << std::endl;

        // For linux platform, to get and print stacktrace.
        const int kBacktraceSize = 10;
        void *backtrace_array[kBacktraceSize];
        const int backtrace_size = backtrace(backtrace_array, kBacktraceSize);
        backtrace_symbols_fd(backtrace_array, backtrace_size, STDOUT_FILENO);
    }
}

#pragma clang diagnostic pop
