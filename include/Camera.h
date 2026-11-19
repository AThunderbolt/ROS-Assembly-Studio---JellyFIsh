#pragma once
#include<glm/glm.hpp>
    // this class is responsible for camera position, rotation, and zoom;
class Camera{
    public:
    glm::vec3 position;
    glm::vec3 target;

    Camera():position(0.0f,0.0f,3.0f), target(0.0f, 0.0f, 0.0f){}
    
    
};