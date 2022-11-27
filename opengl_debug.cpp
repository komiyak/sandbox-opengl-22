#include <string>
#include <iostream>
#include <glad/glad.h>

#include <execinfo.h>
#include <unistd.h>

#include "opengl_debug.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
#pragma ide diagnostic ignored "UnreachableCode"

[[maybe_unused]] void opengl_debug::CheckError(const char *file, int line) {
    if (kOpenGLDebugLogging == false) { return; }

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
        std::cout << "opengl_debug::CheckError | " << error << " | " << file << " (" << line << ")" << std::endl;

        // For linux platform, to get and print stacktrace.
        const int kBacktraceSize = 10;
        void *backtrace_array[kBacktraceSize];
        const int backtrace_size = backtrace(backtrace_array, kBacktraceSize);
        backtrace_symbols_fd(backtrace_array, backtrace_size, STDOUT_FILENO);
    }
}

#pragma clang diagnostic pop

[[maybe_unused]] void APIENTRY opengl_debug::DebugMessageCallback(
        GLenum source,
        GLenum type,
        unsigned int id,
        GLenum severity,
        [[maybe_unused]] GLsizei length,
        const char *message,
        [[maybe_unused]] const void *userParam) {

    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "opengl_debug::DebugMessageCallback" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "  Source: API(GL_DEBUG_SOURCE_API)";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "  Source: Window System(GL_DEBUG_SOURCE_WINDOW_SYSTEM)";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "  Source: Shader Compiler(GL_DEBUG_SOURCE_SHADER_COMPILER)";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "  Source: Third Party(GL_DEBUG_SOURCE_THIRD_PARTY)";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "  Source: Application(GL_DEBUG_SOURCE_APPLICATION)";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "  Source: Other(GL_DEBUG_SOURCE_OTHER)";
            break;
        default:; // nothing
    }
    std::cout << ", ";

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error(GL_DEBUG_TYPE_ERROR)";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability(GL_DEBUG_TYPE_PORTABILITY)";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance(GL_DEBUG_TYPE_PERFORMANCE)";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker(GL_DEBUG_TYPE_MARKER)";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group(GL_DEBUG_TYPE_PUSH_GROUP)";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group(GL_DEBUG_TYPE_POP_GROUP)";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other(GL_DEBUG_TYPE_OTHER)";
            break;
        default:; // nothing
    }
    std::cout << ", ";

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high(GL_DEBUG_SEVERITY_HIGH)";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium(GL_DEBUG_SEVERITY_MEDIUM)";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low(GL_DEBUG_SEVERITY_LOW)";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification(GL_DEBUG_SEVERITY_NOTIFICATION)";
            break;
        default:; // nothing
    }
    std::cout << std::endl;

    // For linux platform, to get and print stacktrace.
    const int kBacktraceSize = 10;
    void *backtrace_array[kBacktraceSize];
    const int backtrace_size = backtrace(backtrace_array, kBacktraceSize);
    backtrace_symbols_fd(backtrace_array, backtrace_size, STDOUT_FILENO);

    std::cout << std::endl;
}


#pragma clang diagnostic pop
