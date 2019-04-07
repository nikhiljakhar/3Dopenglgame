#include "aim.h"
#include "main.h"

const float pi = 4*atan(1);

Aim::Aim(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->rotationx = 0;
    this->speed = 5;
    this->type = 1;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        0,2,0,
        0,2.3,0,
        2,0,0,
        2,0,0,
        2.3,0,0,
        0,2.3,0,

        0,2,0,
        0,2.3,0,
        -2,0,0,
        -2,0,0,
        -2.3,0,0,
        0,2.3,0,

        0,-2,0,
        0,-2.3,0,
        -2,0,0,
        -2,0,0,
        -2.3,0,0,
        0,-2.3,0,

        0,-2,0,
        0,-2.3,0,
        2,0,0,
        2,0,0,
        2.3,0,0,
        0,-2.3,0,

        2,0.1,0,
        2,-0.1,0,
        4,-0.1,0,
        4,-0.1,0,
        4,0.1,0,
        2,0.1,0,

        -2,0.1,0,
        -2,-0.1,0,
        -4,-0.1,0,
        -4,-0.1,0,
        -4,0.1,0,
        -2,0.1,0,

    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_GREY, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        4,4 + 9,0,
        4,4.1 + 9,0,
        2,4.1 + 9,0,
        2,4.1 + 9,0,
        2,4 + 9,0,
        4,4 + 9,0,

        -4,4 + 9,0,
        -4,4.1 + 9,0,
        -2,4.1 + 9,0,
        -2,4.1 + 9,0,
        -2,4 + 9,0,
        -4,4 + 9,0,

        4,-4 + 9,0,
        4,-4.1 + 9,0,
        2,-4.1 + 9,0,
        2,-4.1 + 9,0,
        2,-4 + 9,0,
        4,-4 + 9,0,

        -4,-4 + 9,0,
        -4,-4.1 + 9,0,
        -2,-4.1 + 9,0,
        -2,-4.1 + 9,0,
        -2,-4 + 9,0,
        -4,-4 + 9,0,

        4,4 + 9,0,
        4.1,4 + 9,0,
        4.1,2 + 9,0,
        4.1,2 + 9,0,
        4,2 + 9,0,
        4,4 + 9,0,

        -4,4 + 9,0,
        -4.1,4 + 9,0,
        -4.1,2 + 9,0,
        -4.1,2 + 9,0,
        -4,2 + 9,0,
        -4,4 + 9,0,

        4,-4 + 9,0,
        4.1,-4 + 9,0,
        4.1,-2 + 9,0,
        4.1,-2 + 9,0,
        4,-2 + 9,0,
        4,-4 + 9,0,

        -4,-4 + 9,0,
        -4.1,-4 + 9,0,
        -4.1,-2 + 9,0,
        -4.1,-2 + 9,0,
        -4,-2 + 9,0,
        -4,-4 + 9,0,        

    };

    this->object2 = create3DObject(GL_TRIANGLES, 48, vertex_buffer_data2, COLOR_GREY, GL_FILL);
}

void Aim::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate3 = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate4 = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate = rotate1 * rotate3;
    rotate = rotate * rotate4;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->type)
        draw3DObject(this->object);
    if(!this->type)
         draw3DObject(this->object2);
}

void Aim::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Aim::tick() {


}