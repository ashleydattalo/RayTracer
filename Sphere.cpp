#include "Sphere.hpp"
#include <iostream>

// Sphere::Sphere() {
// 	// center = glm::vec3(0.0f);
// 	// radius = 0.5f;
// 	// color = col;
// }
Sphere::Sphere(glm::vec3 c, float r, glm::vec3 col, glm::vec3 camPos) {
	this->center = c;
	this->radius = r;
	this->color = col;
	this->eye = camPos;
   rainbow.setMin(0.0f);
   rainbow.setMax(r);
}

Sphere::~Sphere() {}


bool Sphere::intersects(glm::vec3 d) {
   glm::vec3 eMinC = this->eye - this->center;

   float radSquared = this->radius * this->radius;

   float dDotEminC = glm::dot(d, eMinC);
   float dDotd = glm::dot(d, d);
   float eMinCDotEminC = glm::dot(eMinC, eMinC);

   float discUnSquared = dDotEminC * dDotEminC - dDotd * (eMinCDotEminC - radSquared);
   float disc = glm::sqrt(discUnSquared);

   float t1 = -1 * (dDotEminC + disc) / dDotd;
   float t2 = -1 * (dDotEminC - disc) / dDotd;

   if (disc > 0) {
      this->t = glm::min(t1, t2);
      return true;
   }
   else {
   	this->t = 0.0f;
   	return false;
   }
}

glm::vec3 Sphere::calcBlinnPhong(glm::vec3 dirRay, glm::vec3 lightPos) {
	glm::vec3 point = eye + t * dirRay;
	glm::vec3 normal = glm::normalize((point - this->center)/this->radius);

   glm::vec3 thisColor = rainbow.getColor(dist(point, this->center));
	//ambient
	glm::vec3 ambient = 0.5f * thisColor;
   
   glm::vec3 lightDir = glm::normalize(lightPos - point);
   float diff = glm::max(glm::dot(lightDir, normal), 0.1f);
   glm::vec3 diffuse = diff * thisColor;

   //specular
   glm::vec3 viewDir = glm::normalize(eye - point);
   glm::vec3 reflectDir = glm::reflect(-lightDir, normal);
   glm::vec3 halfwayDir = glm::normalize(lightDir + viewDir);
   float spec = glm::pow(glm::max(glm::dot(normal, halfwayDir), 0.0f), 32.0f);
   glm::vec3 specular = glm::vec3(0.3f) * spec;

	return ambient + diffuse + specular;
}

float Sphere::dist(glm::vec3 point1, glm::vec3 point2) {
   float x1 = point1.x;
   float x2 = point2.x;
   float y1 = point1.y;
   float y2 = point2.y;

   float xTerm = (x2 - x1) * (x2 - x1);
   float yTerm = (y2 - y1) * (y2 - y1);
   return glm::sqrt(xTerm + yTerm);
}


void Sphere::setColor(glm::vec3 col) {
   this->color = col;
}

glm::vec3 Sphere::getColor() {
	return this->color;
}

glm::vec3 Sphere::getCenter() {
	return this->center;
}

float Sphere::getRadius() {
	return this->radius;
}

void Sphere::printVector(glm::vec3 vec, std::string str) {
   std::cout << str << ": ";
   std::cout << vec.x;
   std::cout << " ";
   std::cout << vec.y;
   std::cout << " ";
   std::cout << vec.z;
   std::cout << std::endl;
}