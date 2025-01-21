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
#include "Camera.hpp"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const GLint WIDTH = 800, HEIGHT = 800;

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// --------------------- Camera --------------------- //
Camera camera(glm::vec3(2.0f, 0.0f, 6.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;


int main() {
    // --------------------- Initialization --------------------- //
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    lastX = WIDTH;
    lastY = HEIGHT;
    
    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if(GLEW_OK != glewInit()) 
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        
        return -1;
    }
    stbi_set_flip_vertically_on_load(true); 
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    glViewport(0, 0, screenWidth, screenHeight);
    
    // Shader Compilation
    Shader lightingShader("phongLighting.vert", "phongLighting.frag");
    Shader lightCubeShader("lightSource.vert", "lightSource.frag");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    int strideLength = 8;

    glm::vec3 lightPosition = glm::vec3(1.2f, 0.0f, 2.0f);

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

    // Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, strideLength * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, strideLength * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, strideLength * sizeof(float), (void*)(6 * sizeof(float)));
    
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    
    VAO VAO_Light;
    VAO_Light.Bind();
    VAO_Light.LinkAttrib(VBO1, 0, 3, GL_FLOAT, strideLength * sizeof(float), (void*)0);
    VAO_Light.Unbind();
    
    
    // --------------------- Textures --------------------- //
    unsigned int diffuseMap;
    glGenTextures(1, &diffuseMap);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    
    // Load our images using stb_images, passing in variables we want to save the values to
    int texWidth, texHeight, numChannels;
    unsigned char *data = stbi_load("container2.png", &texWidth, &texHeight, &numChannels, 0);
    if (data) {
        // Generate texture from image using currently bound texture
        // (JPG -> RGB, PNG -> RGBA)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    unsigned int specularMap;
    glGenTextures(1, &specularMap);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    
    // Load our images using stb_images, passing in variables we want to save the values to
    data = stbi_load("container2_specular.png", &texWidth, &texHeight, &numChannels, 0);
    if (data) {
        // Generate texture from image using currently bound texture
        // (JPG -> RGB, PNG -> RGBA)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    // --------------------- Render Loop --------------------- //
    while(!glfwWindowShouldClose(window))
    {
        // Calculate delta time so that device frame rate doesn't affect the controls
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        processInput(window);
        
        // Calculate time-based variables //
        lightPosition.x = sin(currentFrame) * 3;
        lightPosition.z = cos(currentFrame) * 3;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // --------------------- Cameras --------------------- //
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        
        lightingShader.Activate();
        
        // Vertex Shader Uniforms
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);
        
        // Fragment Shader Uniforms
        lightingShader.setInt("material.diffuse", 0); // Bind diffuse and specular to texture locations
        lightingShader.setInt("material.specular", 1);
        lightingShader.setFloat("material.shininess", 32.0f);
        
        lightingShader.setVec3("light.position", camera.Position);
        lightingShader.setVec3("light.direction", camera.Front);
        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        
        lightingShader.setVec3("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
        lightingShader.setVec3("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        lightingShader.setFloat("light.constant",  1.0f);
        lightingShader.setFloat("light.linear",    0.09f);
        lightingShader.setFloat("light.quadratic", 0.032f);
        
        // Activate and bind our respective textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        // Draw the triangle using the GL_TRIANGLES primitive
        VAO1.Bind();
        
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        // Draw our lighting cube
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPosition);
        lightModel = glm::scale(lightModel, glm::vec3(0.5f));
        
        lightCubeShader.Activate();
        // Vertex Shader Uniforms
        lightCubeShader.setMat4("model", lightModel);
        lightCubeShader.setMat4("view", view);
        lightCubeShader.setMat4("projection", projection);
        
        // Fragment shader Uniforms
        lightCubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lightCubeShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit

        VAO_Light.Bind();
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    // --------------------- Clean up --------------------- //

    VAO1.Delete();
    VBO1.Delete();
    
    lightingShader.Delete();
    lightCubeShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
