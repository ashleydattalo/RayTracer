#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(glm::vec3 pos, glm::vec3 target, int WIDTH, int HEIGHT) {
	this->position = pos;
	this->target = target;


	// glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 direction = glm::normalize(pos - target);

	glm::vec3 upTemp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(glm::normalize(glm::cross(upTemp, direction)));

	glm::vec3 up = glm::vec3(glm::normalize(glm::cross(right, direction)));

	this->view = glm::lookAt(pos, target, up);
  	this->projection = glm::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
    this->frustrum.extractPlanes(this->projection, this->view);
}

Camera::~Camera() {}

glm::vec3 Camera::getPosition() {
	return this->position;
}

glm::vec3 Camera::getTarget() {
	return this->target;
}

glm::mat4 Camera::getView() {
	return this->view;
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}

ViewFrustrum Camera::getFrustrum() {
	return this->frustrum;
}