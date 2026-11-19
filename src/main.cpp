#include <glad/glad.h>
#include <GLFW/glfw3.h>
//classes, also keep main WINDOW code only
#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"





int main(){

    Scene scene;
    Camera camera;
    Renderer renderer;

    if(!glfwInit()){
        return -1;
    }
    //intailze GLFW, then creaate window, mainloop clean up;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ros2 ASSEMBLY STUDIO", nullptr, nullptr);
    
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    while(!glfwWindowShouldClose(window)){
        //renderer logic here
        // renderer.DrawGrid();
        // renderer.DrawAxes();
        // render loop
        // glClearColor(0.1f,0.1f,0.15f,1.0f);
        // glColor(GL_COLOR_BUFFER_BIT);
        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}