#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

#include "Rainbow.hpp"

class Sphere {
public:
    // Sphere();
    Sphere(glm::vec3 center, float radius, glm::vec3 col, glm::vec3 eye);
    ~Sphere();

    bool intersects(glm::vec3 d);
    glm::vec3 calcBlinnPhong(glm::vec3 SOURCE, glm::vec3 lightPos);
    
    void setColor(glm::vec3 col);

    glm::vec3 getColor();
    glm::vec3 getCenter();
    float getRadius();

    float dist(glm::vec3 point1, glm::vec3 point2);
    
    void printVector(glm::vec3 vec, std::string str);

private:
	glm::vec3 center;
    glm::vec3 color;
    glm::vec3 eye;
	float radius;
	float t;

    Rainbow rainbow;
};

#endif