//#include <vector>
//#include <string>
//#include <GL/glew.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include "mesh.h"
//
//class Shader;
////class Mesh;
////class Texture;
//
////struct aiScene;
////struct aiNode;
////struct aiMaterial;
////struct aiMesh;
////enum aiTextureType;
//
//class Model {
//public:
//	// Functions
//	Model(std::string path);
//	void Draw(Shader shader);
//private:
//	// Model data
//	std::vector<Mesh> meshes;
//	std::vector<Texture> textures_loaded;
//	std::string directory;
//	// Functions
//	void processNode(aiNode* node, const aiScene* scene);
//	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
//	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
//	GLuint textureFromFile(const char* path, std::string directory);
//};