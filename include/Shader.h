#pragma  once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader{
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        void Bind() const;
        void UnBind() const;

        void SetMat4(const std::string& name, const glm::mat4& matrix);

    private:
        GLuint ComplieShader(GLenum type, const std::string& source);
    private:
        GLuint m_rendererID;
        
};