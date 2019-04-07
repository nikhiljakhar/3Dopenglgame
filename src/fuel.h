#include "main.h"

#ifndef FUEL_H
#define FUEL_H

class Fuel
{
  public:
  Fuel()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Fuel(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  int taken;
  bounding_box_t bounding_box();

private:
  VAO *object;
};

#endif // FUEL_H
