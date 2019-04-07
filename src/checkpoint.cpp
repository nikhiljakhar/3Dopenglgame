#include "checkpoint.h"
#include "main.h"

const float pi = 4*atan(1);

Checkpoint::Checkpoint(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5;
    this->covered = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        0, -9*5, -2*5,
        5*5, 6*5, -2*5,
        -5*5, 6*5, -2*5,
        0, - 9*5, 2*5,
        5*5, 6*5, 2*5,
        -5*5, 6*5, 2*5,

        5*5, 6*5, -2*5,
        -5*5, 6*5, -2*5,
        5*5, 6*5, 2*5,
        -5*5, 6*5, 2*5,
        5*5, 6*5, 2*5,
        -5*5, 6*5, -2*5,

        0, - 9*5, -2*5,
        5*5, 6*5, -2*5,
        5*5, 6*5, 2*5,
        5*5, 6*5, 2*5,
        0,- 9*5, 2*5,
        0, - 9*5, -2*5,

        0,- 9*5, -2*5,
        -5*5, 6*5, -2*5,
        -5*5, 6*5, 2*5,
        -5*5, 6*5, 2*5,
        0, - 9*5, 2*5,
        0, - 9*5, 2*5,
    };

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        0,0,-2*5,
        0,-3*5,-2*5,
        4*5,1*5,-2*5,
        4*5,1*5,-2*5,
        4*5,4*5,-2*5,
        0,0,-2*5,

        0,0,2*5,
        0,-3*5,2*5,
        4*5,1*5,2*5,
        4*5,1*5,2*5,
        4*5,4*5,2*5,
        0,0,2*5,

        4*5,1*5,-2*5,
        4*5,1*5,2*5,
        0,-3*5,2*5,
        0,-3*5,2*5,
        0,-3*5,-2*5,
        4*5,1*5,-2*5,

        4*5,4*5,-2*5,
        4*5,4*5,2*5,
        0,0,2*5,
        0,0,2*5,
        0,0,-2*5,
        4*5,4*5,-2*5,

        0,0,-2*5,
        0,-3*5,-2*5,
        -8*5,5*5,-2*5,
        -8*5,5*5,-2*5,
        -8*5,8*5,-2*5,
        0,0,-2*5,

        0,0,2*5,
        0,-3*5,2*5,
        -8*5,8*5,2*5,
        -8*5,8*5,2*5,
        -8*5,8*5,2*5,
        0,0,2*5,

        -8*5,5*5,-2*5,
        -8*5,5*5,2*5,
        0,-3*5,2*5,
        0,-3*5,2*5,
        0,-3*5,-2*5,
        -8*5,5*5,-2*5,

        -8*5,8*5,-2*5,
        -8*5,8*5,2*5,
        0,0,2*5,
        0,0,2*5,
        0,0,-2*5,
        -8*5,8*5,-2*5,

        -8*5,8*5,2*5,
        -8*5,8*5,-2*5,
        -8*5,5*5,-2*5,
        -8*5,5*5,-2*5,
        -8*5,5*5,2*5,
        -8*5,8*5,2*5,

        4*5,4*5,2*5,
        4*5,4*5,-2*5,
        4*5,1*5,-2*5,
        4*5,1*5,-2*5,
        4*5,1*5,2*5,
        4*5,4*5,2*5,

    };

    this->object2 = create3DObject(GL_TRIANGLES, 60, vertex_buffer_data2, COLOR_PGREEN, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->covered)
        draw3DObject(this->object2);
    if(!this->covered)
        draw3DObject(this->object);

}

void Checkpoint::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick() {
    this->rotation += 1;
}

bounding_box_t Checkpoint::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 3000, 300000, 3000};
    return bbox;
}