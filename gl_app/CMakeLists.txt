add_library(
        gl_app
        application.cpp
        frame.cpp
        key_callback_singleton.cpp
        debug_util.cpp)

target_link_libraries(gl_app LINK_PUBLIC glfw_wrap)

target_include_directories(gl_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
