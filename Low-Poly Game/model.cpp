//#include <iostream>
//#include <SOIL.h>
//#include "model.h"
//#include "shader.h"
////#include "mesh.h"
//
//Model::Model(std::string path) {
//	Assimp::Importer import;
//	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
//		std::cout << "ERROR: " << import.GetErrorString() << std::endl;
//		return;
//	}
//	this->directory = path.substr(0, path.find_last_of('/'));
//	this->processNode(scene->mRootNode, scene);
//}
//
//void Model::Draw(Shader shader) {
//	for (int i = 0; i < this->meshes.size(); i++)
//		this->meshes[i].Draw(shader);
//}
//
//void Model::processNode(aiNode* node, const aiScene* scene) {
//	// Process all node meshes
//	for (int i = 0; i < node->mNumMeshes; i++) {
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		this->meshes.push_back(this->processMesh(mesh, scene));
//	}
//	// Do the same for all children
//	for (int i = 0; i < node->mNumChildren; i++) {
//		this->processNode(node->mChildren[i], scene);
//	}
//}
//
//Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//	std::vector<Texture> textures;
//
//	// Vertices
//	for (int i = 0; i < mesh->mNumVertices; i++) {
//		Vertex vertex;
//		// Position
//		glm::vec3 vec;
//		vec.x = mesh->mVertices[i].x;
//		vec.y = mesh->mVertices[i].y;
//		vec.z = mesh->mVertices[i].z;
//		vertex.Position = vec;
//		// Normals
//		vec.x = mesh->mNormals[i].x;
//		vec.y = mesh->mNormals[i].y;
//		vec.z = mesh->mNormals[i].z;
//		// TextureCoords
//		if (mesh->mTextureCoords[0]) {
//			glm::vec2 tVec;
//			tVec.x = mesh->mTextureCoords[0][i].x;
//			tVec.y = mesh->mTextureCoords[0][i].y;
//			vertex.TexCoords = tVec;
//		}
//		else {
//			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//		}
//		vertices.push_back(vertex);
//	}
//
//	// Indices
//	for (int i = 0; i < mesh->mNumFaces; i++) {
//		aiFace face = mesh->mFaces[i];
//		for (int j = 0; j < face.mNumIndices; j++) {
//			indices.push_back(face.mIndices[j]);
//		}
//	}
//
//	// Material
//	if (mesh->mMaterialIndex >= 0) {
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//		// Diffuse maps
//		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//		// Specular maps
//		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//	}
//
//	return Mesh(vertices, indices, textures);
//}
//
//// FIX TEXTURES
//std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
//	std::vector<Texture> textures;
//	for (int i = 0; i < mat->GetTextureCount(type); i++) {
//		aiString str;
//		mat->GetTexture(type, i, &str);
//		bool skip = false;
//		for (int j = 0; j < this->textures_loaded.size(); j++) {
//			//if (std::strcmp(this->textures_loaded[j].path, str.C_Str()) == 0) {
//			if(this->textures_loaded[j].path.compare(std::string(str.data)) == 0) {
//				textures.push_back(this->textures_loaded[j]);
//				skip = true;
//				break;
//			}
//		}
//		if (!skip) {
//			Texture texture;
//			texture.id = this->textureFromFile(str.C_Str(), this->directory);
//			texture.type = typeName;
//			texture.path = std::string(str.data);
//			textures.push_back(texture);
//			this->textures_loaded.push_back(texture);
//		}
//	}
//
//	return textures;
//}
//
//GLuint Model::textureFromFile(const char* path, std::string directory) {
//	//Generate texture ID and load texture data 
//	std::string filename = std::string(path);
//	filename = directory + '/' + filename;
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	int width, height;
//	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	// Assign texture to ID
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	// Parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(image);
//	return textureID;
//}
