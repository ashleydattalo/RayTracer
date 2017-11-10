#ifndef VIEWFRUSTRUM_HPP
#define VIEWFRUSTRUM_HPP

#include <glm/glm.hpp>

class ViewFrustrum {
public:
    ViewFrustrum();
    ViewFrustrum(glm::mat4 P, glm::mat4 V);
    ~ViewFrustrum();

    void extractPlanes(glm::mat4 P, glm::mat4 V);
    void printPlanes();

// private:
    glm::vec4 left, right, bottom, top, near, far;
    glm::vec4 planes[6];
};

#endif