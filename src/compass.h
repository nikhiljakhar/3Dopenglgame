#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass
{
  public:
  Compass()  {}
  glm::vec3 position;
  float rotation;
  float rotationz;
  float rotationx;
  float radius;
  void right();
  Compass(float x, float y, float z);
  int health;
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
  VAO *object4;
};

#endif // COMPASS_H
