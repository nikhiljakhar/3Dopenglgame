#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

class Dashboard
{
  public:
  Dashboard()  {}
  glm::vec3 position;
  float rotation;
  float rotationx;
  void right();
  Dashboard(float x, float y, float z);
  int health;
  void draw(glm::mat4 VP, int hieghtlimit, float fuel, float health);
  void set_position(float x, float y, float z);
  void tick();
  float speed;

private:
  VAO *object;
  VAO *object2;
  VAO *object3;
  VAO *object4;
  VAO *object5;
  VAO *object6;
  VAO *object7;
  VAO *object8;
  VAO *object9;
  VAO *object10;
  VAO *object11;
  VAO *object12;
  VAO *object13;
};

#endif // DASHBOARD_H
