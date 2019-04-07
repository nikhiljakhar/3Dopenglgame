#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H

class Shield
{
  public:
  Shield()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Shield(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  float time;
  int expire;
  int taken;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
};

#endif // SHIELD_H
