#include "parachute.h"
#include "main.h"

const float pi = 4*atan(1);

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->alive = 1;
    this->range = 0;
    this->radius = 8;
    this->health = 100;

    const int n = 60;
    const int tind = n * 9;
    const double pi = 4 * atan(1);
    GLfloat vertex_buffer_data[8*n*18] = {};

    double angle = 0;
    double angle2 = (pi/2);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    for(int j=0;j<8;j++){
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

    this->object = create3DObject(GL_TRIANGLES, 6*n*8, vertex_buffer_data, COLOR_WHITE, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {
        this->radius*cos(angle2)*cos(pi/4), this->radius*sin(angle2), this->radius*cos(angle2)*sin(pi/4),
        this->radius*cos(angle2)*cos(pi/4 + pi/30), this->radius*sin(angle2), this->radius*cos(angle2)*sin(pi/4 + pi/30),
        2, 0, 2,

        -this->radius*cos(angle2)*cos(pi/4), this->radius*sin(angle2), this->radius*cos(angle2)*sin(pi/4),
        -this->radius*cos(angle2)*cos(pi/4 + pi/30), this->radius*sin(angle2), this->radius*cos(angle2)*sin(pi/4 + pi/30),
        -2, 0, 2,        

        -this->radius*cos(angle2)*cos(pi/4), this->radius*sin(angle2), -this->radius*cos(angle2)*sin(pi/4),
        -this->radius*cos(angle2)*cos(pi/4 + pi/30), this->radius*sin(angle2), -this->radius*cos(angle2)*sin(pi/4 + pi/30),
        -2, 0, -2,

        this->radius*cos(angle2)*cos(pi/4), this->radius*sin(angle2), -this->radius*cos(angle2)*sin(pi/4),
        this->radius*cos(angle2)*cos(pi/4 + pi/30), this->radius*sin(angle2), -this->radius*cos(angle2)*sin(pi/4 + pi/30),
        2, 0, -2,


    };
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, COLOR_GREY, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {
        -2.0f,-2.0f - 2,-2.0f, // triangle 1 : begin
        -2.0f,-2.0f - 2, 2.0f,
        -2.0f, 2.0f - 2, 2.0f, // triangle 1 : end
        2.0f, 2.0f - 2,-2.0f, // triangle 2 : begin
        -2.0f,-2.0f - 2,-2.0f,
        -2.0f, 2.0f - 2,-2.0f, // triangle 2 : end
        2.0f,-2.0f - 2, 2.0f,
        -2.0f,-2.0f - 2,-2.0f,
        2.0f,-2.0f - 2,-2.0f,
        2.0f, 2.0f - 2,-2.0f,
        2.0f,-2.0f - 2,-2.0f,
        -2.0f,-2.0f - 2,-2.0f,
        -2.0f,-2.0f - 2,-2.0f,
        -2.0f, 2.0f - 2, 2.0f,
        -2.0f, 2.0f - 2,-2.0f,
        2.0f,-2.0f - 2, 2.0f,
        -2.0f,-2.0f - 2, 2.0f,
        -2.0f,-2.0f - 2,-2.0f,
        -2.0f, 2.0f - 2, 2.0f,
        -2.0f,-2.0f - 2, 2.0f,
        2.0f,-2.0f - 2, 2.0f,
        2.0f, 2.0f - 2, 2.0f,
        2.0f,-2.0f - 2,-2.0f,
        2.0f, 2.0f - 2,-2.0f,
        2.0f,-2.0f - 2,-2.0f,
        2.0f, 2.0f - 2, 2.0f,
        2.0f,-2.0f - 2, 2.0f,
        2.0f, 2.0f - 2, 2.0f,
        2.0f, 2.0f - 2,-2.0f,
        -2.0f, 2.0f - 2,-2.0f,
        2.0f, 2.0f - 2, 2.0f,
        -2.0f, 2.0f - 2,-2.0f,
        -2.0f, 2.0f - 2, 2.0f,
        2.0f, 2.0f - 2, 2.0f,
        -2.0f, 2.0f - 2, 2.0f,
        2.0f,-2.0f - 2, 2.0f

    };
    this->object3 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data3, COLOR_BROWN, GL_FILL);

    // static const GLfloat vertex_buffer_data4[] = {
    // };
    // this->object4 = create3DObject(GL_TRIANGLES, 12*3*2, vertex_buffer_data4, COLOR_BACKGROUND, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    if(this->range && this->alive)
    {
        draw3DObject(this->object);
        draw3DObject(this->object2);
        draw3DObject(this->object3);
    }
}

void Parachute::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    if(this->range && this->alive)
        this->position.y -= 0.1;
}


bounding_box_t Parachute::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y - 4, this->position.z, 10, 30, 10};
    return bbox;
}
