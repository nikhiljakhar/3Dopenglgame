#include "plane.h"
#include "main.h"
#include <cmath>

const float pi = 4*atan(1);

Plane::Plane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->rotationx = 0;
    this->frotationx = 0;
    this->health = 100;
    this->fuel = 2000;
    this->speed = 0.1;
    this->speedz = 0.1;
    this->protection = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        //right
        6, -2, -3,
        1, 1,13 ,
        6, 2, -3,
        6, -2, -3,
        1, 1,13,
        1, -1,13,
    };
    static const GLfloat vertex_buffer_data1[] = {
        //back
        1, 1, 13,
        -1, -1, 13,
        1, -1, 13,
        1, 1, 13,
        -1, -1, 13,
        -1, 1, 13,
    };
    static const GLfloat vertex_buffer_data2[] = {
        //left
        -1, 1, 13,
        -6, -2, -3,
        -1, -1, 13,
        -1, 1, 13,
        -6, -2, -3,
        -6, 2, -3,
    };
    static const GLfloat vertex_buffer_data3[] = {
        //front
        -8, -2, -3,
        8, 2, -3,
        -8, 2, -3,
        -8, -2, -3,
        8, 2, -3,
        8, -2, -3,
    };
    static const GLfloat vertex_buffer_data4[] = {
        //center
        6, -2, -3,
        - 1, -1, 13,
        1, -1, 13,
        6, -2, -3,
        - 1, -1, 13,
        -6, -2, -3,
    };
    static const GLfloat vertex_buffer_data5[] = {
        //centerdown
        6, 2, -3,
        - 1, 1, 13,
        1, 1, 13,
        6, 2, -3,
        - 1, 1, 13,
        - 6, 2, -3,
    };
    static const GLfloat vertex_buffer_data6[] = {
        //wing1
        8, -2, -3,
        - 16, 1, -16,
        16, 1, -16,
        8, -2, -3,
        - 16, 1, -16,
        -8, -2, -3,
    };
    static const GLfloat vertex_buffer_data7[] = {
        //sidewings
        8, -2, -3,
        8, 2, -3,
        16, 1, -16,

        -8, -2, -3,
        -8, 2, -3,
        -16, 1, -16,
        //wing2
        8, 2, -3,
        - 16, 1, -16,
        16, 1, -16,
        8, 2, -3,
        - 16, 1, -16,
        - 8, 2, -3,
    };
    static const GLfloat vertex_buffer_data8[] = {

        7, 2, -3,
        13, 1, -16,
        10, 1, -16,

        -7, 2, -3,
        -13, 1, -16,
        -10, 1, -16,

        7, 2, -3,
        13, 3, -16,
        10, 3, -16,

        -7, 2, -3,
        -13, 3, -16,
        -10, 3, -16,

        -13, 3, -16,
        -13, 1, -16,
        -10, 1, -16,
        -10, 1, -16,
        -13, 3, -16,
        -10, 3, -16,

        13, 3, -16,
        13, 1, -16,
        10, 1, -16,
        10, 1, -16,
        13, 3, -16,
        10, 3, -16,

        7,2,-3,
        10,1,-16,
        10,3,-16,
        7,2,-3,
        13,1,-16,
        13,3,-16,

        -7,2,-3,
        -10,1,-16,
        -10,3,-16,
        -7,2,-3,
        -13,1,-16,
        -13,3,-16,

    };
    const int n = 100;
    const int tind = n * 9;
    GLfloat vertex_buffer_data9[1000*n*9] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    double radius = 4;
    for(int j=0;j<1000;j++){
        for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data9[ind++] = 0.0;
            vertex_buffer_data9[ind++] = 0.0;
            vertex_buffer_data9[ind++] = -13.0f + j*0.03;

            //Point with lower angle
            vertex_buffer_data9[ind++] = radius * cos(angle);
            vertex_buffer_data9[ind++] = radius * sin(angle);
            vertex_buffer_data9[ind++] = -13.0f +j*0.03;

            //Point with higher angle
            angle += addang;
            vertex_buffer_data9[ind++] = radius * cos(angle);
            vertex_buffer_data9[ind++] = radius * sin(angle);
            vertex_buffer_data9[ind++] = -13.0f +j*0.03;

    }
        radius -= 0.0000075*j;
    }
    GLfloat vertex_buffer_data10[n*9] = {};
    angle = 0;
    ind = 0;
    radius = 4;
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data10[ind++] = 0.0;
            vertex_buffer_data10[ind++] = 0.0;
            vertex_buffer_data10[ind++] = -16.0f;

            //Point with lower angle
            vertex_buffer_data10[ind++] = radius * cos(angle);
            vertex_buffer_data10[ind++] = radius * sin(angle);
            vertex_buffer_data10[ind++] = -16.0f;

            //Point with higher angle
            angle += addang;
            vertex_buffer_data10[ind++] = radius * cos(angle);
            vertex_buffer_data10[ind++] = radius * sin(angle);
            vertex_buffer_data10[ind++] = -16.0f;

    }

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_GREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, COLOR_GREY, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, COLOR_GREY, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, COLOR_DGREY, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data7, COLOR_DGREY, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data8, COLOR_RED, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 1000*n*3, vertex_buffer_data9, COLOR_GREY, GL_FILL);
    this->object10 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data10, COLOR_ORANGE, GL_FILL);
    this->object11 = create3DObject(GL_TRIANGLES, 1000*n*3, vertex_buffer_data9, COLOR_DBLUE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    //glm::mat4 rotate2 = glm::rotate((float)(this->level_angle * M_PI / 180.0f), glm::vec3(this->position.x, this->position.y, this->position.z - 2));
    glm::mat4 rotate3 = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate4 = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate = rotate1 * rotate3;
    rotate = rotate * rotate4;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
    draw3DObject(this->object8);
    if(!this->protection)
        draw3DObject(this->object9);
    if(this->protection)
        draw3DObject(this->object11);
    draw3DObject(this->object10);
}

void Plane::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {

    if(fmod(this->rotationz,360)>=0.5 && fmod(this->rotationz,360)<=180)
        this->rotationz = this->rotationz - 0.5;
    if(fmod(this->rotationz,360)<=359.5 && fmod(this->rotationz,360)>180)
        this->rotationz = this->rotationz + 0.5;

    if(fmod(this->rotationz,360)<=-0.5 && fmod(this->rotationz,360)>=-180)
        this->rotationz = this->rotationz + 0.5;
    if(fmod(this->rotationz,360)>=-359.5 && fmod(this->rotationz,360)<-180)
        this->rotationz = this->rotationz - 0.5;

    if(fmod(this->rotationx,360)<=-0.5 && fmod(this->rotationx,360)>=-180)
        this->rotationx = this->rotationx + 0.5;
    if(fmod(this->rotationx,360)>=-359.9 && fmod(this->rotationx,360)<-180)
        this->rotationx = this->rotationx - 0.1;
    if(fmod(this->rotationx,360)>=0.5 && fmod(this->rotationx,360)<=180)
        this->rotationx = this->rotationx - 0.5;
    if(fmod(this->rotationx,360)<=359.9 && fmod(this->rotationx,360)>180)
        this->rotationx = this->rotationx + 0.1;
    if(fmod(this->frotationx,360)>=0.5 && fmod(this->frotationx,360)<=180)
        this->frotationx = this->frotationx - 0.5;
    if(fmod(this->frotationx,360)<=359.9 && fmod(this->frotationx,360)>180)
        this->frotationx = this->frotationx + 0.1;

    this->rotationz = fmod(this->rotationz,360);
    this->position.z += this->speedz * cos((this->rotation)*(pi/180))* cos((this->rotationx)*(pi/180));
    this->position.x += this->speedz* sin((this->rotation)*(pi/180))* cos((this->rotationx)*(pi/180));
    this->position.y -= this->speedz*sin((this->rotationx)*(pi/180));

    if(this->speedz > 0.1)
        this->speedz -= 0.005;
    this->speed = this->speedz;
    this->fuel -= 0.15*this->speedz;
    //printf("%f\n", this->fuel);

}

void Plane::right() {
    
    this->rotation = this->rotation - 0.5;
    if(this->rotationz<=30)
        this->rotationz = this->rotationz + 1;
    this->position.z += 0.5 * cos((this->rotation)*(pi/180));
    this->position.x += 0.5 * sin((this->rotation)*(pi/180));
    this->speed = this->speedz + 0.5;
    //printf("%f\n", this->rotationz);
}

void Plane::left() {
    this->rotation = this->rotation + 0.5;
    if(this->rotationz>=-30)
        this->rotationz = this->rotationz - 1;
    this->position.z += cos((this->rotation)*(pi/180))*0.5;
    this->position.x += sin((this->rotation)*(pi/180))*0.5;
    this->speed = this->speedz + 0.5;
    //printf("%f\n", this->rotationz);
}

void Plane::forward() {
    this->position.z += this->speedz * cos((this->rotation)*(pi/180));
    this->position.x += this->speedz * sin((this->rotation)*(pi/180));
    if(this->speedz < 3)
        this->speedz += 0.02;
    this->speed = this->speedz;
    //printf("%f\n", this->position.z);
}

void Plane::down() {
    if(this->rotationx<=30)
        this->rotationx = this->rotationx + 1;
    this->position.y -= this->speedz*sin((this->rotationx)*(pi/180));
    this->position.z += this->speedz * cos((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
    this->position.x += this->speedz * sin((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
    if(this->speedz < 3)
        this->speedz += 0.008;
    //printf("%f\n", this->position.y);
}

void Plane::up() {
    if(this->rotationx>=-30)
        this->rotationx = this->rotationx - 1;
    this->frotationx = 0 - this->rotationx;
    this->position.y -= this->speedz*sin((this->rotationx)*(pi/180));
    this->position.z += this->speedz * cos((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
    this->position.x += this->speedz * sin((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
    if(this->speedz < 3)
        this->speedz += 0.008;
    //printf("%f\n", this->position.y);
}

void Plane::loop() {
    this->frotationx = this->frotationx + 1;
    this->rotationx = 0 - fmod(this->frotationx,360);
    this->position.y -= 2*sin((this->rotationx)*(pi/180));
    this->position.z += 2 * cos((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
    this->position.x += 2 * sin((this->rotation)*(pi/180)) * cos((this->rotationx)*(pi/180));
}

void Plane::clockwise() {
    
    this->rotationz = this->rotationz + 2;
    this->position.z += this->speedz * cos((this->rotation)*(pi/180));
    this->position.x += this->speedz * sin((this->rotation)*(pi/180));
    if(this->speedz < 3)
        this->speedz += 0.01;
    this->speed = this->speedz;
    //printf("%f\n", this->rotationz);
}
void Plane::anticlockwise() {
    
    this->rotationz = this->rotationz - 2;
    this->position.z += this->speedz * cos((this->rotation)*(pi/180));
    this->position.x += this->speedz * sin((this->rotation)*(pi/180));
    if(this->speedz < 3)
        this->speedz += 0.01;
    this->speed = this->speedz;
    //printf("%f\n", this->rotationz);
}


bounding_box_t Plane::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 18, 10, 20};
    return bbox;
}
