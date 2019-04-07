#include "shield.h"
#include "main.h"

const float pi = 4*atan(1);

Shield::Shield(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5;
    this->taken = 0;
    this->time = 15.00;
    this->expire = 0;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        0,-5,-2,
        0,5,-2,
        6,9,-2,
        0,-5,-2,
        0,5,-2,
        -6,9,-2,

        0,-5,2,
        0,5,2,
        6,9,2,
        0,-5,2,
        0,5,2,
        -6,9,2,

        6,9,-2,
        6,9,2,
        0,5,2,
        0,5,2,
        0,5,-2,
        6,9,-2,

        -6,9,-2,
        -6,9,2,
        0,5,2,
        0,5,2,
        0,5,-2,
        -6,9,-2,



    };

    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, COLOR_DBLUE, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        0,-5,-2,
        4,-2,-2,
        6,9,-2,
        0,-5,-2,
        -4,-2,-2,
        -6,9,-2,

        0,-5,2,
        4,-2,2,
        6,9,2,
        0,-5,2,
        -4,-2,2,
        -6,9,2,

        0,-5,-2,
        4,-2,-2,
        4,-2,2,
        4,-2,2,
        0,-5,2,
        0,-5,-2,

        0,-5,-2,
        -4,-2,-2,
        -4,-2,2,
        -4,-2,2,
        0,-5,2,
        0,-5,-2,

        4,-2,-2,
        6,9,-2,
        6,9,2,
        6,9,2,
        4,-2,2,
        4,-2,-2,

        -4,-2,-2,
        -6,9,-2,
        -6,9,2,
        -6,9,2,
        -4,-2,2,
        -4,-2,-2,


    };

    this->object2 = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Shield::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Shield::tick() {
    this->rotation += 1;
}


bounding_box_t Shield::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 20, 40, 30};
    return bbox;
}
