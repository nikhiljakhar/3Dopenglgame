#include "bullet.h"
#include "main.h"

const float pi = 4*atan(1);

Bullet::Bullet(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationx = 0;
    this->speed = 5;
    this->fired = 0;
    this->hit = 0;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    const int n = 100;
    const int tind = n * 9;
    GLfloat vertex_buffer_data[50*n*9] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    double radius = 0.5;
    for(int j=0;j<50;j++){
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data[ind++] = 0.0;
            vertex_buffer_data[ind++] = 0.0;
            vertex_buffer_data[ind++] = -1.5f + j*0.03;

            //Point with lower angle
            vertex_buffer_data[ind++] = radius * cos(angle);
            vertex_buffer_data[ind++] = radius * sin(angle);
            vertex_buffer_data[ind++] = -1.5f +j*0.03;

            //Point with higher angle
            angle += addang;
            vertex_buffer_data[ind++] = radius * cos(angle);
            vertex_buffer_data[ind++] = radius * sin(angle);
            vertex_buffer_data[ind++] = -1.5f +j*0.03;

    }
        radius -= 0.00008*j;
    };

    this->object = create3DObject(GL_TRIANGLES, 3*n*50, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //printf("%f\n", this->rotation);
    draw3DObject(this->object);
}

void Bullet::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bullet::tick() {
    //this->rotation += 0.05;
    this->position.z += 20 * cos((this->rotation)*(pi/180));
    this->position.x += 20 * sin((this->rotation)*(pi/180));
    this->position.y -= 16*tan((this->rotationx)*(pi/180));
}

bounding_box_t Bullet::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y + 4, this->position.z, 1, 1, 3};
    return bbox;
}