#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute
{
  public:
  Parachute()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Parachute(float x, float y, float z);
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

#endif // PARACHUTE_H
