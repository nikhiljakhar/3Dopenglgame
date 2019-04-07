#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y, float z);
    double rotation;
    float rotationx;
    glm::vec3 position;
    void draw(glm::mat4 VP, int disp);
    void set_position(float x, float y, float z);
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
};

#endif // BALL_H
