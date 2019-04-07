#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano
{
  public:
  Volcano()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Volcano(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  int alive;
  int range;
  float health;
  float radius;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
  VAO *object4;
};

#endif // VOLCANO_H
