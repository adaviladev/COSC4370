#include "GameModels.h"
#include <iostream>

using namespace Models;
using namespace std;

GameModels::GameModels()
{

}

GameModels::~GameModels()
{

	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModels::CreateTriangleModel(const std::string& gameModelName, std::vector<VertexFormat> vertexHolder)
{
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	float ratio = 0.5;

	std::vector<VertexFormat> vertices;
	std::cout << "Building kettle" << std::endl;
	int vertexSize = vertexHolder.size();

	/*
	vertices.push_back(VertexFormat(glm::vec3( ratio, -ratio, 0), glm::vec4(0, 1, 0, 1))); // bottom-right
	vertices.push_back(VertexFormat(glm::vec3(-ratio, -ratio, 0), glm::vec4(0, 1, 0, 1))); // bottom-left
	vertices.push_back(VertexFormat(glm::vec3( ratio,  ratio, 0), glm::vec4(0, 0, 1, 1))); // top-right

	vertices.push_back(VertexFormat(glm::vec3(-ratio, ratio, 0.0), glm::vec4(1, 1, 1, 1))); // top-left
	vertices.push_back(VertexFormat(glm::vec3(-ratio, -ratio, 0.0), glm::vec4(0, 1, 0, 1))); // bottom-left
	vertices.push_back(VertexFormat(glm::vec3(ratio, ratio, 0.0), glm::vec4(0, 0, 1, 1))); // top-right
	*/

	//vertexSize = vertices.size();
	std::cout << "Size of transfered: " << vertexSize << std::endl;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertexSize, &vertexHolder[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;

}

void GameModels::DeleteModel(const std::string& gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);

}

unsigned int GameModels::GetModel(const std::string& gameModelName)
{
	return GameModelList[gameModelName].vao;
}