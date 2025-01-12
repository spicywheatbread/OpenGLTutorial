#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// My code
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Shader.hpp"

using namespace std;

// Vertices coordinates
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Upper triangle
    5, 4, 1 // Lower right triangle
};

const GLint WIDTH = 800, HEIGHT = 800;

int main() {
    glfwInit();
    
    // Tell GLFW OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // MacOS specific
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Initialize window object
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jonathan's Window", NULL, NULL);
    
    // This is because of a mac's display. It's high retina or resolution or something
    // Therefore, it can differ from the actual size of the window.
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if(GLEW_OK != glewInit()) 
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        
        return -1;
    }
    glViewport(0, 0, screenWidth, screenHeight);
    
    // Shader Compilation
    Shader shaderProgram("default.vert", "default.frag");

    
    /* Create reference containers
     VAO (VERTEX ARRAY OBJECT):
        - specifies where to find data and how to read it
        - stores pointers to VBOs
        - allow you to switch quickly between different VBOs
        - stores vertex attribute configuration
     VBO (VERTEX BUFFER OBJECT) - holds our actual vertex data that we want to send to the GPU
     EBO (ELEMENT BUFFER OBJECT) - holds the indices of the vertices we want to access
     */
    
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    

    float time;
    // Render Loop
    while(!glfwWindowShouldClose(window))
    {
        time = cos(glfwGetTime());
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProgram.Activate();
        VAO1.Bind();
        
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
