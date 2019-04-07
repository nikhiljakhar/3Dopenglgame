#include "efire.h"
#include "main.h"

const float pi = 4*atan(1);

Efire::Efire(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationx = 0;
    this->speed = 0.1;
    this->fired = 0;
    this->hit = 0;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        2,2,0,
        -2,2,0,
        0,0,-10000,

        2,-2,0,
        -2,-2,0,
        0,0,-10000,

        2,2,0,
        2,-2,0,
        0,0,-10000,

        -2,2,0,
        -2,-2,0,
        0,0,-10000,

    };



    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
}

void Efire::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotatey = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatex = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate = rotatey*rotatex;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //printf("%f\n", this->rotation);
    draw3DObject(this->object);
}

void Efire::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Efire::tick() {
    //this->rotation += 0.05;
    if(this->rotationx > 45 || this->rotationx < 0)
        this->speed = 0 - this->speed;
    this->rotationx += this->speed;
    //printf("%f\n", this->rotation); 
}

bounding_box_t Efire::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 100, 100, 10000};
    return bbox;
}