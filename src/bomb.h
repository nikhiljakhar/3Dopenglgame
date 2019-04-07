#include "main.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb
{
  public:
  Bomb()  {}
  glm::vec3 position;
  float rotation;
  float radius;
  float rotationx;
  void right();
  Bomb(float x, float y, float z);
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  float speed;
  float speedy;
  int fired;
  int hit;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
};

#endif // BOMB_H
