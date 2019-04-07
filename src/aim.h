#include "main.h"

#ifndef AIM_H
#define AIM_H

class Aim
{
  public:
  Aim()  {}
  glm::vec3 position;
  float rotation;
  float rotationz;
  float rotationx;
  int type;
  Aim(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;

private:
  VAO *object;
  VAO *object2;
};

#endif // AIM_H
