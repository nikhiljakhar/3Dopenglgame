#include "enemy.h"
#include "main.h"

const float pi = 4*atan(1);

Enemy::Enemy(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->alive = 1;
    this->fired = 0;
    this->radius = 500;

    const int n = 60;
    const int tind = n * 9;
    const double pi = 4 * atan(1);
    GLfloat vertex_buffer_data[5*n*18] = {};

    double angle = 0;
    double angle2 = (pi/2);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    for(int j=0;j<5;j++){
        for (int i = 0; i < n; i++)
        {

            vertex_buffer_data[ind++] = this->radius*cos(angle2)*cos(angle);
            vertex_buffer_data[ind++] = this->radius*sin(angle2);
            vertex_buffer_data[ind++] = this->radius*cos(angle2)*sin(angle);

            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*cos(angle);
            vertex_buffer_data[ind++] = this->radius*sin(angle2 - addang);
            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*sin(angle);

            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*cos(angle + addang);
            vertex_buffer_data[ind++] = this->radius*sin(angle2 - addang);
            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*sin(angle + addang);

            vertex_buffer_data[ind++] = this->radius*cos(angle2)*cos(angle);
            vertex_buffer_data[ind++] = this->radius*sin(angle2);
            vertex_buffer_data[ind++] = this->radius*cos(angle2)*sin(angle);

            vertex_buffer_data[ind++] = this->radius*cos(angle2)*cos(angle + addang);
            vertex_buffer_data[ind++] = this->radius*sin(angle2);
            vertex_buffer_data[ind++] = this->radius*cos(angle2)*sin(angle + addang);

            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*cos(angle + addang);
            vertex_buffer_data[ind++] = this->radius*sin(angle2 - addang);
            vertex_buffer_data[ind++] = this->radius*cos(angle2 - addang)*sin(angle + addang);

            angle += addang;

        }
        angle2 -= addang;
    }

    this->object = create3DObject(GL_TRIANGLES, 6*n*5, vertex_buffer_data, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {
        -30.0f,400.0f,-30.0f, // triangle 1 : begin
        -30.0f,400.0f, 30.0f,
        -30.0f, 602.0f, 30.0f,
                             // triangle 1 : end
        30.0f, 602.0f,-30.0f, // triangle 2 : begin
        -30.0f,400.0f,-30.0f,
        -30.0f, 602.0f,-30.0f, // triangle 2 : end

        30.0f,400.0f, 30.0f,
        -30.0f,400.0f,-30.0f,
        30.0f,400.0f,-30.0f,

        30.0f, 602.0f,-30.0f,
        30.0f,400.0f,-30.0f,
        -30.0f,400.0f,-30.0f,

        -30.0f,400.0f,-30.0f,
        -30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f,-30.0f,

        30.0f,400.0f, 30.0f,
        -30.0f,400.0f, 30.0f,
        -30.0f,400.0f,-30.0f,

        -30.0f, 602.0f, 30.0f,
        -30.0f,400.0f, 30.0f,
        30.0f,400.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        30.0f,400.0f,-30.0f,
        30.0f, 602.0f,-30.0f,

        30.0f,400.0f,-30.0f,
        30.0f, 602.0f, 30.0f,
        30.0f,400.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        30.0f, 602.0f,-30.0f,
        -30.0f, 602.0f,-30.0f,

        30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f,-30.0f,
        -30.0f, 602.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f, 30.0f,
        30.0f,400.0f, 30.0f,


    };
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_BEIGE, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {

        0.0f,400.0f,-30.0f*1.414, // triangle 1 : begin
        -30.0f*1.414,400.0f, 0.0f,
        -30.0f*1.414, 603.0f, 0.0f,
                             // triangle 1 : end
        30.0f*1.414, 603.0f,0.0f, // triangle 2 : begin
        0.0f,400.0f,-30.0f*1.414,
        0.0f, 603.0f,-30.0f*1.414, // triangle 2 : end

        0.0f,400.0f, 30.0f*1.414,
        0.0f,400.0f,-30.0f*1.414,
        30.0f*1.414,400.0f,0.0f,

        30.0f*1.414, 603.0f,0.0f,
        30.0f*1.414,400.0f,0.0f,
        0.0f,400.0f,-30.0f*1.414,

        0.0f,400.0f,-30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,
        0.0f, 603.0f,-30.0f*1.414,

        0.0f,400.0f, 30.0f*1.414,
        -30.0f*1.414,400.0f, 0.0f,
        0.0f,400.0f,-30.0f*1.414,

        -30.0f*1.414, 603.0f, 0.0f,
        -30.0f*1.414,400.0f, 0.0f,
        0.0f,400.0f, 30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        30.0f*1.414,400.0f,0.0f,
        30.0f*1.414, 603.0f,0.0f,

        30.0f*1.414,400.0f,0.0f,
        0.0f, 603.0f, 30.0f*1.414,
        0.0f,400.0f, 30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        30.0f*1.414, 603.0f,0.0f,
        0.0f, 603.0f,-30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        0.0f, 603.0f,-30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,

        0.0f, 603.0f, 30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,
        0.0f,400.0f, 30.0f*1.414


    };
    this->object3 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data3, COLOR_AGREEN, GL_FILL);

    static const GLfloat vertex_buffer_data4[] = {
        -30.0f,400.0f,-30.0f, // triangle 1 : begin
        -30.0f,400.0f, 30.0f,
        -30.0f, 602.0f, 30.0f,
                             // triangle 1 : end
        30.0f, 602.0f,-30.0f, // triangle 2 : begin
        -30.0f,400.0f,-30.0f,
        -30.0f, 602.0f,-30.0f, // triangle 2 : end

        30.0f,400.0f, 30.0f,
        -30.0f,400.0f,-30.0f,
        30.0f,400.0f,-30.0f,

        30.0f, 602.0f,-30.0f,
        30.0f,400.0f,-30.0f,
        -30.0f,400.0f,-30.0f,

        -30.0f,400.0f,-30.0f,
        -30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f,-30.0f,

        30.0f,400.0f, 30.0f,
        -30.0f,400.0f, 30.0f,
        -30.0f,400.0f,-30.0f,

        -30.0f, 602.0f, 30.0f,
        -30.0f,400.0f, 30.0f,
        30.0f,400.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        30.0f,400.0f,-30.0f,
        30.0f, 602.0f,-30.0f,

        30.0f,400.0f,-30.0f,
        30.0f, 602.0f, 30.0f,
        30.0f,400.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        30.0f, 602.0f,-30.0f,
        -30.0f, 602.0f,-30.0f,

        30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f,-30.0f,
        -30.0f, 602.0f, 30.0f,

        30.0f, 602.0f, 30.0f,
        -30.0f, 602.0f, 30.0f,
        30.0f,400.0f, 30.0f,

         0.0f,400.0f,-30.0f*1.414, // triangle 1 : begin
        -30.0f*1.414,400.0f, 0.0f,
        -30.0f*1.414, 603.0f, 0.0f,
                             // triangle 1 : end
        30.0f*1.414, 603.0f,0.0f, // triangle 2 : begin
        0.0f,400.0f,-30.0f*1.414,
        0.0f, 603.0f,-30.0f*1.414, // triangle 2 : end

        0.0f,400.0f, 30.0f*1.414,
        0.0f,400.0f,-30.0f*1.414,
        30.0f*1.414,400.0f,0.0f,

        30.0f*1.414, 603.0f,0.0f,
        30.0f*1.414,400.0f,0.0f,
        0.0f,400.0f,-30.0f*1.414,

        0.0f,400.0f,-30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,
        0.0f, 603.0f,-30.0f*1.414,

        0.0f,400.0f, 30.0f*1.414,
        -30.0f*1.414,400.0f, 0.0f,
        0.0f,400.0f,-30.0f*1.414,

        -30.0f*1.414, 603.0f, 0.0f,
        -30.0f*1.414,400.0f, 0.0f,
        0.0f,400.0f, 30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        30.0f*1.414,400.0f,0.0f,
        30.0f*1.414, 603.0f,0.0f,

        30.0f*1.414,400.0f,0.0f,
        0.0f, 603.0f, 30.0f*1.414,
        0.0f,400.0f, 30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        30.0f*1.414, 603.0f,0.0f,
        0.0f, 603.0f,-30.0f*1.414,

        0.0f, 603.0f, 30.0f*1.414,
        0.0f, 603.0f,-30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,

        0.0f, 603.0f, 30.0f*1.414,
        -30.0f*1.414, 603.0f, 0.0f,
        0.0f,400.0f, 30.0f*1.414

    };
    this->object4 = create3DObject(GL_TRIANGLES, 12*3*2, vertex_buffer_data4, COLOR_BACKGROUND, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    if(this->alive)
    {
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
    if(!this->alive)
    {
        draw3DObject(this->object4);
    }
}

void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemy::tick() {
    this->rotation += 0.5;

}


bounding_box_t Enemy::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y + 500, this->position.z, 60, 200, 60};
    return bbox;
}
