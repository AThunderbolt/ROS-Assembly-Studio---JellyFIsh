#pragma once
#include <string>
#include <glm/glm.hpp>


class Entity{
    
    public:
        std::string name;
        std::string type;
        
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        
    
};