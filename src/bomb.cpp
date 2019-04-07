#include "bomb.h"
#include "main.h"

const float pi = 4*atan(1);

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationx = 0;
    this->speed = 0;
    this->speedy = 0;
    this->fired = 0;
    this->hit = 0;
 
    static const GLfloat vertex_buffer_data[] = {
        -3.0f,-3.0f,-3.0f, // triangle 1 : begin
        -3.0f,-3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f, // triangle 1 : end
        3.0f, 3.0f ,-3.0f, // triangle 2 : begin
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f, // triangle 2 : end
        3.0f,-3.0f , 3.0f,
        -3.0f,-3.0f,-3.0f,
        3.0f,-3.0f ,-3.0f,
        3.0f, 3.0f ,-3.0f,
        3.0f,-3.0f ,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f,-3.0f , 3.0f,
        -3.0f,-3.0f, 3.0f,
        -3.0f,-3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        -3.0f,-3.0f, 3.0f,
        3.0f,-3.0f , 3.0f,
        3.0f, 3.0f , 3.0f,
        3.0f,-3.0f ,-3.0f,
        3.0f, 3.0f ,-3.0f,
        3.0f,-3.0f ,-3.0f,
        3.0f, 3.0f , 3.0f,
        3.0f,-3.0f , 3.0f,
        3.0f, 3.0f , 3.0f,
        3.0f, 3.0f ,-3.0f,
        -3.0f, 3.0f,-3.0f,
        3.0f, 3.0f , 3.0f,
        -3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f, 3.0f , 3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f,-3.0f , 3.0f

    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    
}

void Bomb::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //printf("%f\n", this->rotation);
    draw3DObject(this->object);
    
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    //this->rotation += 0.05;
    this->position.z += (this->speed+2) * cos((this->rotation)*(pi/180));
    this->position.x += (this->speed+2) * sin((this->rotation)*(pi/180));
    this->position.y -= (this->speedy);
    speedy += 0.05;
    if(this->speed>-2)
        this->speed -= 0.02;
}

bounding_box_t Bomb::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 200, 100, 200};
    return bbox;
}