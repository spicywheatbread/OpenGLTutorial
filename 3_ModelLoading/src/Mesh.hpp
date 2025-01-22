#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.hpp"

using namespace std;
// --------------------- Models & Meshes --------------------- //
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
        // mesh data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture>      textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
}; 
#endif /* Mesh_hpp */
