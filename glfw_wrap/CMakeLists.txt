add_subdirectory(glfw-3.3.8)
add_library(glfw_wrap STATIC glad-opengl-version-4-6/src/glad.c)

# glfw を取り込む
target_link_libraries(glfw_wrap LINK_PUBLIC glfw)

# glfw と glad の include ファイルを公開する
target_include_directories(
        glfw_wrap
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.3.8/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glad-opengl-version-4-6/include)
