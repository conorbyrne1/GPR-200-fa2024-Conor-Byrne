#ifndef SHADER_H
#define SHADER_H

#include <C:\Users\Conor\Desktop\GPR-200-fa2024-Conor-Byrne\core\ew\external\glad.h>
#include <string>
//cant do any other way of including glad.h for some reason

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};

#endif