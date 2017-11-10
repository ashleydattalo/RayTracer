#include "ViewFrustrum.hpp"
#include <glm/glm.hpp>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

ViewFrustrum::ViewFrustrum() {}

ViewFrustrum::ViewFrustrum(glm::mat4 P, glm::mat4 V) {
	extractPlanes(P, V);	
}
ViewFrustrum::~ViewFrustrum() {}

void ViewFrustrum::extractPlanes(glm::mat4 P, glm::mat4 V) {
	glm::mat4 comp = P*V;
	glm::vec3 n;
	float l;

	left.x = comp[0][3] + comp[0][0];
	left.y = comp[1][3] + comp[1][0];
	left.z = comp[2][3] + comp[2][0];
	left.w = comp[3][3] + comp[3][0];
	n = glm::vec3(left.x, left.y, left.z);
	l = glm::length(n);
	planes[0] = left/l;
	left = planes[0];

	right.x = comp[0][3] - comp[0][0];
	right.y = comp[1][3] - comp[1][0];
	right.z = comp[2][3] - comp[2][0];
	right.w = comp[3][3] - comp[3][0];

	n = glm::vec3(right.x, right.y, right.z);
	l = glm::length(n);
	planes[1] = right/l;
	right = planes[1];

	bottom.x = comp[0][3] + comp[0][1];
	bottom.y = comp[1][3] + comp[1][1];
	bottom.z = comp[2][3] + comp[2][1];
	bottom.w = comp[3][3] + comp[3][1];

	n = glm::vec3(bottom.x, bottom.y, bottom.z);
	l = glm::length(n);
	planes[2] = bottom/l;
	bottom = planes[2];

	top.x = comp[0][3] - comp[0][1];
	top.y = comp[1][3] - comp[1][1];
	top.z = comp[2][3] - comp[2][1];
	top.w = comp[3][3] - comp[3][1];

	n = glm::vec3(top.x, top.y, top.z);
	l = glm::length(n);
	planes[3] = top/l;
	top = planes[3];

	near.x = comp[0][3] + comp[0][2];
	near.y = comp[1][3] + comp[1][2];
	near.z = comp[2][3] + comp[2][2];
	near.w = comp[3][3] + comp[3][2];

	n = glm::vec3(near.x, near.y, near.z);
	l = glm::length(n);
	planes[4] = near/l;
	near = planes[4];

	far.x = comp[0][3] - comp[0][2];
	far.y = comp[1][3] - comp[1][2];
	far.z = comp[2][3] - comp[2][2];
	far.w = comp[3][3] - comp[3][2];

	n = glm::vec3(far.x, far.y, far.z);
	l = glm::length(n);
	planes[5] = far/l;
	far = planes[5];
}

void ViewFrustrum::printPlanes() {
	for (int i = 0; i < 6; i++) {
		std::cout << glm::to_string(planes[i]) << std::endl;
	}
}