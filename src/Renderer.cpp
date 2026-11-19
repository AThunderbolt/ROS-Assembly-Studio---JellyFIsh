#include "Renderer.h"
#include "Shader.h"

#include <vector>

namespace {

const int   GRID_HALF_EXTENT = 20;
const float GRID_SPACING     = 1.0f;
const int   MAJOR_LINE_EVERY = 5;
const float AXIS_LENGTH      = 5.0f;

const char* VERTEX_SHADER_SRC = R"(#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uViewProj;
out vec3 vColor;

void main() {
    vColor = aColor;
    gl_Position = uViewProj * vec4(aPos, 1.0);
}
)";

const char* FRAGMENT_SHADER_SRC = R"(#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};

void UploadLines(const std::vector<Vertex>& verts, GLuint& vao, GLuint& vbo) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
}

std::vector<Vertex> BuildGridVertices() {
    const glm::vec3 minorColor(0.25f, 0.25f, 0.30f);
    const glm::vec3 majorColor(0.45f, 0.45f, 0.52f);
    const float extent = GRID_HALF_EXTENT * GRID_SPACING;
    
    std::vector<Vertex> verts;
    verts.reserve((GRID_HALF_EXTENT * 2 + 1) * 4);

    for (int i = -GRID_HALF_EXTENT; i <= GRID_HALF_EXTENT; ++i) {
        if (i == 0) continue; // Skip center to avoid z-fighting with main axes

        float p = i * GRID_SPACING;
        glm::vec3 color = (i % MAJOR_LINE_EVERY == 0) ? majorColor : minorColor;

        // Z-parallel lines
        verts.push_back({{p, 0.0f, -extent}, color});
        verts.push_back({{p, 0.0f,  extent}, color});

        // X-parallel lines
        verts.push_back({{-extent, 0.0f, p}, color});
        verts.push_back({{ extent, 0.0f, p}, color});
    }
    return verts;
}

std::vector<Vertex> BuildAxesVertices() {
    const glm::vec3 red(1.0f, 0.2f, 0.2f);
    const glm::vec3 green(0.2f, 1.0f, 0.2f);
    const glm::vec3 blue(0.3f, 0.5f, 1.0f);
    const glm::vec3 origin(0.0f);

    return {
        {origin, red},   {{AXIS_LENGTH, 0.0f, 0.0f}, red},    // X
        {origin, green}, {{0.0f, AXIS_LENGTH, 0.0f}, green},  // Y
        {origin, blue},  {{0.0f, 0.0f, AXIS_LENGTH}, blue},   // Z
    };
}

} // end anonymous namespace

bool Renderer::Init() {
    m_shader = std::make_unique<Shader>(VERTEX_SHADER_SRC, FRAGMENT_SHADER_SRC);

    auto gridVerts = BuildGridVertices();
    m_gridVertexCount = static_cast<GLsizei>(gridVerts.size());
    UploadLines(gridVerts, m_gridVAO, m_gridVBO);

    auto axesVerts = BuildAxesVertices();
    m_axesVertexCount = static_cast<GLsizei>(axesVerts.size());
    UploadLines(axesVerts, m_axesVAO, m_axesVBO);

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Renderer::Shutdown() {
    glDeleteVertexArrays(1, &m_gridVAO);
    glDeleteBuffers(1, &m_gridVBO);
    
    glDeleteVertexArrays(1, &m_axesVAO);
    glDeleteBuffers(1, &m_axesVBO);
    
    m_shader.reset();
    
    m_gridVAO = m_gridVBO = m_axesVAO = m_axesVBO = 0;
}

void Renderer::DrawGrid(const glm::mat4& viewProj) {
    m_shader->Bind();
    m_shader->SetMat4("uViewProj", viewProj);
    
    glBindVertexArray(m_gridVAO);
    glDrawArrays(GL_LINES, 0, m_gridVertexCount);
    glBindVertexArray(0);
}

void Renderer::DrawAxes(const glm::mat4& viewProj) {
    m_shader->Bind();
    m_shader->SetMat4("uViewProj", viewProj);
    
    glBindVertexArray(m_axesVAO);
    glDrawArrays(GL_LINES, 0, m_axesVertexCount);
    glBindVertexArray(0);
}