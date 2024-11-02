#pragma once
#include <string>
#include <unordered_map>

enum class ShaderType {
    Konstantni,
    Lambert,
    Phong,
    Blinn,
    Test
};

struct ShaderInfo {
    std::string vertexPath;
    std::string fragmentPath;
};

const std::unordered_map<ShaderType, ShaderInfo> ShaderMappings = {
    { ShaderType::Konstantni, { "shaders/konstantni.vert", "shaders/konstantni.frag" } },
    { ShaderType::Lambert, { "shaders/lambert.vert", "shaders/lambert.frag" } },
    { ShaderType::Phong, { "shaders/phong.vert", "shaders/phong.frag" } },
    { ShaderType::Blinn, { "shaders/blinn.vert", "shaders/blinn.frag" } },
    { ShaderType::Test, { "VertLight.shader", "FragLight.shader" } }
};
