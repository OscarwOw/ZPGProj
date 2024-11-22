#pragma once
#include <string>
#include <unordered_map>

enum class ShaderType {
    CONSTANT,
    Lambert,
    Phong,
    Blinn,
    Test,
    Light,
    Develop,
    Texture,
    Texture_phong
};

struct ShaderInfo {
    std::string vertexPath;
    std::string fragmentPath;
};

const std::unordered_map<ShaderType, ShaderInfo> ShaderMappings = {
    { ShaderType::CONSTANT, { "vert_constant.shader", "frag_constant.shader" } },
    { ShaderType::Lambert, { "vert_lambert.shader", "frag_lambert.shader" } },
    { ShaderType::Phong, { "vert_phong.shader", "frag_phong.shader" } },
    { ShaderType::Blinn, { "vert_blinn.shader", "frag_blinn.shader" } },
    { ShaderType::Test, { "VertLight.shader", "FragLight.shader" } },
    { ShaderType::Light, { "Vert_light.shader", "Frag_light.shader" } },
    { ShaderType::Develop, { "vert_develop.shader", "frag_develop.shader" } },
    { ShaderType::Texture, { "vert_texture.shader", "frag_texture.shader" } },
    { ShaderType::Texture_phong, { "vert_phong_texture.shader", "frag_phong_texture.shader" } }
};
