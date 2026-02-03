#ifndef SHADER_H
#define SHADER_H

#include<glad/gl.h>
#include<string>

namespace amorfati {
    class Shader {
    public:
        unsigned int ID;

        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        
        void useShader();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec4(const std::string &name, float r, float g, float b, float a) const;
    };
}

#endif
