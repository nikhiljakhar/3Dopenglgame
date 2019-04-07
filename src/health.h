#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H

class Health
{
  public:
  Health()  {}
  glm::vec3 position;
  float rotation;
  float rotationz;
  float rotationx;
  Health(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float health;

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
};

#endif // HEALTH_H
