#include "main.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow
{
  public:
  Arrow()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Arrow(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;

private:
  VAO *object;
};

#endif // ARROW_H
