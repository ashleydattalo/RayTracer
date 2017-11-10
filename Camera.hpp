#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ViewFrustrum.hpp"

class Camera {
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 target, int WIDTH, int HEIGHT);
    ~Camera();

    glm::vec3 getPosition();
    glm::vec3 getTarget();
    glm::mat4 getView();
    glm::mat4 getProjection();
    ViewFrustrum getFrustrum();

private:
    glm::vec3 position;
    glm::vec3 target;

    glm::mat4 view;
    glm::mat4 projection;
    ViewFrustrum frustrum;
};

#endif