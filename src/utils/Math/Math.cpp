#include "Math.h"

glm::vec3 Math::Rot(const glm::vec3 &vec, const glm::vec3 &rotationDeg) noexcept
{
    float yaw = glm::radians(rotationDeg.x);
    float pitch = glm::radians(rotationDeg.y);
    float roll = glm::radians(rotationDeg.z);

    glm::mat4 yawMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, 1, 0));
    glm::mat4 pitchMatrix = glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(1, 0, 0));
    glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0, 0, 1));
    glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

    glm::vec4 rotatedVec = rotationMatrix * glm::vec4(vec, 1.0f);
    return glm::vec3(rotatedVec.x, rotatedVec.y, rotatedVec.z);
}
