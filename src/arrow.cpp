#include "arrow.h"
#include "main.h"

const float pi = 4*atan(1);

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        0, 0, 13,
        3, 0, 0,
        -3, 0, 0,
        0, 1, 13,
        3, 1, 0,
        -3, 1, 0,

        3, 0, 0,
        -3, 0, 0,
        3, 1, 0,
        -3, 1, 0,
        3, 1, 0,
        -3, 0, 0,

        0, 0, 13,
        3, 0, 0,
        3, 1, 0,
        3, 1, 0,
        0, 1, 13,
        0, 0, 13,

        0, 0, 13,
        -3, 0, 0,
        -3, 1, 0,
        -3, 1, 0,
        0, 1, 13,
        0, 0, 13,


    };

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //printf("%f\n", this->rotation);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {

}