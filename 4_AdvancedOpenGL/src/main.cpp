#include <iostream>
#include <map>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Wrapper classes
#include "Camera.hpp"
#include "Model.hpp"
#include "Shader.hpp"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned int loadTexture(char const *path);

const GLint WIDTH = 800, HEIGHT = 800;

float deltaTime = 0.0f; // Time between current frame and last frame
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
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Jonathan's Window", NULL, NULL);

  // This is because of a mac's display. It's high retina or resolution or
  // something Therefore, it can differ from the actual size of the window.
  int screenWidth, screenHeight;
  glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

  if (window == NULL) {
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
  if (GLEW_OK != glewInit()) {
    std::cout << "Failed to initialize GLEW" << std::endl;

    return -1;
  }
  stbi_set_flip_vertically_on_load(true);

  glClearColor(0.91f, 0.949f, 0.894f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glViewport(0, 0, screenWidth, screenHeight);

  // Shader Compilation
  Shader lightingShader("resources/shaders/lightingShader.vert",
                        "resources/shaders/lightingShader.frag");
  Shader screenQuadShader("resources/shaders/framebuffer.vert",
                          "resources/shaders/framebuffer.frag");

  /*
      Remember: to specify vertices in a counter-clockwise winding order you
     need to visualize the triangle as if you're in front of the triangle and
     from that point of view, is where you set their order.

      To define the order of a triangle on the right side of the cube for
     example, you'd imagine yourself looking straight at the right side of the
     cube, and then visualize the triangle and make sure their order is
     specified in a counter-clockwise order. This takes some practice, but try
     visualizing this yourself and see that this is correct.
  */

  float cubeVertices[] = {
      // Back face
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-right
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
      // Front face
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom-right
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top-left
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
      // Left face
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-left
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
                                       // Right face
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-left
      // Bottom face
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // top-left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
      // Top face
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-right
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f   // bottom-left
  };

  float planeVertices[] = {
      // positions          // texture Coords (note we set these higher than 1
      // (together with GL_REPEAT as texture wrapping mode). this will cause the
      // floor texture to repeat)
      5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, 5.0f,
      0.0f, 0.0f,  -5.0f, -0.5f, -5.0f, 0.0f,  2.0f,

      5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, -5.0f,
      0.0f, 2.0f,  5.0f,  -0.5f, -5.0f, 2.0f,  2.0f};
  float transparentVertices[] = {
      // positions
      0.0f, 0.5f, 0.0f, 0.0f,  1.0f, 0.0f, -0.5f, 0.0f,
      0.0f, 0.0f, 1.0f, -0.5f, 0.0f, 1.0f, 0.0f,

      0.0f, 0.5f, 0.0f, 0.0f,  1.0f, 1.0f, -0.5f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.5f,  0.0f, 1.0f, 1.0f};

  glm::vec3 windows[] = {
      glm::vec3(-1.5f, 0.0f, -0.48f), glm::vec3(1.5f, 0.0f, 0.51f),
      glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(-0.3f, 0.0f, -2.3f),
      glm::vec3(0.5f, 0.0f, -0.6f)};

  float quadVertices[] = {// positions   // texCoords
                          -1.0f, 1.0f, 0.0f, 1.0f,  -1.0f, -1.0f,
                          0.0f,  0.0f, 1.0f, -1.0f, 1.0f,  0.0f,

                          -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  -1.0f,
                          1.0f,  0.0f, 1.0f, 1.0f,  1.0f,  1.0f};

  std::map<float, glm::vec3> sorted;
  for (unsigned int i = 0; i < sizeof(windows) / sizeof(windows[0]); i++) {
    float distance = glm::length(camera.Position - windows[i]);
    sorted[distance] = windows[i];
  }

  // grass VAO
  unsigned int grassVAO, grassVBO;
  glGenVertexArrays(1, &grassVAO);
  glGenBuffers(1, &grassVBO);
  glBindVertexArray(grassVAO);
  glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices),
               &transparentVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT),
                        (void *)(3 * sizeof(GL_FLOAT)));

  // cube VAO
  unsigned int cubeVAO, cubeVBO;
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glBindVertexArray(0);

  // plane VAO
  unsigned int planeVAO, planeVBO;
  glGenVertexArrays(1, &planeVAO);
  glGenBuffers(1, &planeVBO);
  glBindVertexArray(planeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glBindVertexArray(0);

  unsigned int FBO;
  glGenFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  unsigned int colorTexture;
  glGenTextures(1, &colorTexture);
  glBindTexture(GL_TEXTURE_2D, colorTexture);
  // 1. Set texture dimensions to screen size
  // 2. No data passed, simply allocating mem
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         colorTexture, 0);

  unsigned int RBO;                         // Reminders:
  glGenRenderbuffers(1, &RBO);              // Generate ID
  glBindRenderbuffer(GL_RENDERBUFFER, RBO); // Bind ID to target
  glRenderbufferStorage(
      GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth,
      screenHeight); // Allocate mem and specify internal format
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER,
                            RBO); // Attach renderbuffer to framebuffer

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!"
              << std::endl;
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Screen VAO
  unsigned int screenQuadVAO, screenQuadVBO;
  glGenVertexArrays(1, &screenQuadVAO);
  glGenBuffers(1, &screenQuadVBO);
  glBindVertexArray(screenQuadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT),
                        (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT),
                        (void *)(2 * GL_FLOAT));

  unsigned int cubeTexture = loadTexture("resources/textures/container.jpg");
  unsigned int floorTexture = loadTexture("resources/textures/metal.png");

  lightingShader.Activate();
  lightingShader.setInt("texture1", 0);
  screenQuadShader.Activate();
  screenQuadShader.setInt("screenTexture", 0);

  glEnable(GL_DEPTH_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  while (!glfwWindowShouldClose(window)) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Calculate delta time so that device frame rate doesn't affect the
    // controls
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight,
        0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    // glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
    glEnable(GL_DEPTH_TEST);

    lightingShader.Activate();
    lightingShader.setMat4("view", view);
    lightingShader.setMat4("projection", projection);

    // FLOOR //
    glBindVertexArray(planeVAO);
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    lightingShader.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // CUBE 1 //
    glEnable(GL_CULL_FACE);

    glBindVertexArray(cubeVAO);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 1.0f, -1.0f));
    lightingShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // CUBE 2 //
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 1.0f, 0.0f));
    lightingShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisable(GL_CULL_FACE);

    /* second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    screenQuadShader.Activate();
    glBindVertexArray(screenQuadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    */
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // --------------------- Clean up --------------------- //
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteVertexArrays(1, &planeVAO);
  glDeleteBuffers(1, &cubeVBO);
  glDeleteBuffers(1, &planeVBO);
  glDeleteFramebuffers(1, &FBO);

  lightingShader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
void processInput(GLFWwindow *window) {
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

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path) {
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}
