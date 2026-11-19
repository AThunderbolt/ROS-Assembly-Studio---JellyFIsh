#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <memory>
class Camera;
class Shader;
class Renderer{
    public:
        // void draw();
        Renderer() = default;
        ~Renderer() = default;
        bool Init();
        void Shutdown();
        void DrawGrid(const glm::mat4& viewProj);
        void DrawAxes(const glm::mat4& viewProj);

    private:

        std::unique_ptr<Shader> m_shader;
       // GLunit m_program = 0;
        GLuint m_gradVAO{}, m_gridVBO{};
        GLuint m_axesVAO{}, m_axesVBO{};
        GLsizei m_gridVertexCount{};
        GLsizei m_axesVertexCount{};
//GLint m_Viewprojloc = -1;
};
