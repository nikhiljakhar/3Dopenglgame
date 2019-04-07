#include "main.h"

#ifndef PLANE_H
#define PLANE_H

class Plane
{
  public:
  Plane()  {}
  glm::vec3 position;
  float rotation;
  float rotationz;
  float rotationx;
  float frotationx;
  float fuel;
  void right();
  Plane(float x, float y, float z);
  float health;
  void left();
  void forward();
  void down();
  void up();
  void loop();
  void draw(glm::mat4 VP);
  void set_position(float x, float y, float z);
  void tick();
  void clockwise();
  void anticlockwise();
  float speed;
  float speedz;
  int protection;
  bounding_box_t bounding_box();

private:
  VAO *object;
  VAO *object1;
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
};

#endif // PLANE_H
