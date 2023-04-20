add_library(
        gl_app
        gl_debug.cpp
        key_callback_singleton.cpp
        frame.cpp
        application.cpp)

target_link_libraries(gl_app LINK_PUBLIC glfw_wrap)

target_include_directories(gl_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
