#ifndef SANDBOX_OPENGL_22_SHADER_DATA_H_
#define SANDBOX_OPENGL_22_SHADER_DATA_H_

namespace shader_data {
    // 'font' shader の attrib variable location
    constexpr const char *const kAttribVariableLocationsOfFontShader[] = {
            "position",
            "texcoord"};
    constexpr std::size_t kAttribVariableLocationsOfFontShaderSize =
            std::size(kAttribVariableLocationsOfFontShader);
    // 'font' shader の uniform variable location
    constexpr const char *const kUniformVariableLocationsOfFontShader[] = {
            "translation_vec",
            "scaling_vec",
            "texcoord_translation_vec",
            "texcoord_scaling_vec",
            "tex",
            "color"};
    constexpr std::size_t kUniformVariableLocationsOfFontShaderSize =
            std::size(kUniformVariableLocationsOfFontShader);


    // 'white_vertex' shader の attrib variable location
    constexpr const char *const kAttribVariableLocationsOfWhiteVertexShader[] = {
            "position"};
    constexpr std::size_t kAttribVariableLocationsOfWhiteVertexShaderSize =
            std::size(kAttribVariableLocationsOfWhiteVertexShader);
    // 'white_vertex' shader の uniform variable location
    constexpr const char *const kUniformVariableLocationsOfWhiteVertexShader[] = {
            "projection_mat",
            "view_mat",
            "model_mat"};
    constexpr std::size_t kUniformVariableLocationsOfWhiteVertexShaderSize =
            std::size(kUniformVariableLocationsOfWhiteVertexShader);


    // 'vertex_color' shader の attrib variable location
    constexpr const char *const kAttribVariableLocationsOfVertexColorShader[] = {
            "position",
            "color"};
    constexpr std::size_t kAttribVariableLocationsOfVertexColorShaderSize =
            std::size(kAttribVariableLocationsOfVertexColorShader);
    // 'vertex_color' shader の uniform variable location
    constexpr const char *const kUniformVariableLocationsOfVertexColorShader[] = {
            "projection_mat",
            "view_mat",
            "model_mat"};
    constexpr std::size_t kUniformVariableLocationsOfVertexColorShaderSize =
            std::size(kUniformVariableLocationsOfVertexColorShader);


    // 'texture' shader の attrib variable location
    constexpr const char *const kAttribVariableLocationsOfTextureShader[] = {
            "position",
            "texcoord"};
    constexpr std::size_t kAttribVariableLocationsOfTextureShaderSize =
            std::size(kAttribVariableLocationsOfTextureShader);
    // 'texture' shader の uniform variable location
    constexpr const char *const kUniformVariableLocationsOfTextureShader[] = {
            "projection_mat",
            "view_mat",
            "model_mat",
            "tex"};
    constexpr std::size_t kUniformVariableLocationsOfTextureShaderSize =
            std::size(kUniformVariableLocationsOfTextureShader);


    // 'texture_2d' shader の attrib variable location
    constexpr const char *const kAttribVariableLocationsOfTexture2dShader[] = {
            "position",
            "texcoord"};
    constexpr std::size_t kAttribVariableLocationsOfTexture2dShaderSize =
            std::size(kAttribVariableLocationsOfTexture2dShader);
    // 'texture_2d' shader の uniform variable location
    constexpr const char *const kUniformVariableLocationsOfTexture2dShader[] = {
            "translation_vec",
            "scaling_vec",
            "texcoord_translation_vec",
            "texcoord_scaling_vec",
            "tex"};
    constexpr std::size_t kUniformVariableLocationsOfTexture2dShaderSize =
            std::size(kUniformVariableLocationsOfTexture2dShader);
}

#endif //SANDBOX_OPENGL_22_SHADER_DATA_H_
