#include "main.h"

#ifndef CIRCULARPATH_H
#define CIRCULARPATH_H

class Circularpath
{
  public:
  Circularpath()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Circularpath(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  int before;
  int inside;
  int after;
  float radius;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
  VAO *object4;
};

#endif // CIRCULARPATH_H
