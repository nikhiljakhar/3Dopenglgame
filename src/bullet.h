#include "main.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet
{
  public:
  Bullet()  {}
  glm::vec3 position;
  float rotation;
  float rotationx;
  void right();
  Bullet(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  int fired;
  int hit;
  bounding_box_t bounding_box();

private:
  VAO *object;
};

#endif // BULLET_H
