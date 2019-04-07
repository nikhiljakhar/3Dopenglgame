#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
  public:
  Enemy()  {}
  glm::vec3 position;
  float rotation;
  void right();
  Enemy(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  int alive;
  int fired;
  float radius;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
  VAO *object4;
};

#endif // ENEMY_H
