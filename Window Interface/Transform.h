#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Transform {
public:

	//Get compiled transformation matrix
	glm::mat4 getMatrix();
	//Get position
	glm::vec3 getPos();
	//Get rotation
	glm::vec3 getRot();
	//Get scale
	glm::vec3 getScale();

	//Set position
	void setPos(const glm::vec3&);
	//Set rotation
	void setRot(const glm::vec3&);
	//Rotate current matrix
	void rotate(const glm::vec3&);
	//Set scale
	void setScale(const glm::vec3&);


private:

	//Record which properties changed
	bool changed[3] = { false };
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::mat4 matrix = glm::mat4(1);
	glm::mat4 posMat = glm::mat4(1);
	glm::mat4 rotMat = glm::mat4(1);
	glm::mat4 scaleMat = glm::mat4(1);

};