#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Wrapper classes
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Shader.hpp"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


const GLint WIDTH = 800, HEIGHT = 800;

int main() {
    glfwInit();
    
    // Tell GLFW OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS specific
    
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
    stbi_set_flip_vertically_on_load(true);  
    glViewport(0, 0, screenWidth, screenHeight);
    
    // Shader Compilation
    Shader shaderProgram("default.vert", "default.frag");

    // Vertices coordinates
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };


    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


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
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    
    // Texture Stuff //
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    // Load our images using stb_images, passing in variables we want to save the values to
    int texWidth, texHeight, numChannels;
    unsigned char *data = stbi_load("container.jpg", &texWidth, &texHeight, &numChannels, 0);
    if (data) {
        // Generate texture from image using currently bound texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    // Repeat for second texture
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("awesomeface.png", &texWidth, &texHeight, &numChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shaderProgram.Activate(); // don't forget to activate/use the shader before setting uniforms!
    // Set the value of the uniforms to the texture units we want
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");

    
    // --------------------- Render Loop --------------------- //
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Activate texture unit and bind our textures to them to pass to frag shader
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        shaderProgram.Activate();

        VAO1.Bind();
        
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    // --------------------- Render Loop --------------------- //

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
