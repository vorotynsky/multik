#include "ShaderCache.hpp"

namespace multik::core
{
    typename ShaderCache::ShaderSource ShaderCache::resolveName(const std::string &name) const
    {
        auto shader = "shaders/" + name;
        return { shader + ".vertex.glsl", shader + ".fragment.glsl"};
    }

    Ref<render::Shader> ShaderCache::GetShader(const std::string &name) const
    {
        auto it = cache.find(name);
        if (it != cache.end())
        {
            if (auto shader = it->second.lock())
                return shader;
        }
        auto names = resolveName(name);
        auto shader = render::Shader::ReadFiles(names.vertexPath, names.fragmentPath);
        cache.emplace(name, shader);
        return shader;
    }

    ShaderCache ShaderCache::global;

    Ref<render::Shader> ShaderCache::Get(const std::string &name)
    {
        return global.GetShader(name);
    }
}