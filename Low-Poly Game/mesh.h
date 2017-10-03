#pragma once
#include <string>
#include <vector>
#include <string>
#include <vector>
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>

#define POSITION glm::vec3
#define NORMAL glm::vec3

struct Vertex {
	POSITION Position;
	NORMAL Normal;

	Vertex(POSITION pos) : Position(pos) {}
	Vertex(POSITION pos, NORMAL norm) : Position(pos), Normal(norm) {}
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

	GLuint VAO, VBO, EBO;
private:
	void SetUp();
};