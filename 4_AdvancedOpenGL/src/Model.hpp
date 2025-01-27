#ifndef MODEL_HPP
#define MODEL_HPP

// Assimp Library for model importing
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "stb_image.h"
using namespace std;

class Model
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void Draw(Shader &shader);
    private:
        // model data
        vector<Mesh> meshes;
        vector<Texture> textures_loaded; 
        string directory;

        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                             string typeName);
        unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

};

#endif /* Model_hpp */
