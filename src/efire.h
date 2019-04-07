#include "main.h"

#ifndef EFIRE_H
#define EFIRE_H

class Efire
{
  public:
  Efire()  {}
  glm::vec3 position;
  float rotation;
  float rotationx;
  void right();
  Efire(float x, float y, float z);
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

#endif // EFIRE_H
