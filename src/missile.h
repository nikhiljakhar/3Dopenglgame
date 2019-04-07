#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile
{
  public:
  Missile()  {}
  glm::vec3 position;
  float rotation;
  float rotationx;
  void right();
  Missile(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  int fired;
  int hit;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
};

#endif // MISSILE_H
