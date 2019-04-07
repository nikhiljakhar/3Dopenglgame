#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Checkpoint
{
  public:
  Checkpoint()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Checkpoint(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  int covered;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
};

#endif // CHECKPOINT_H
