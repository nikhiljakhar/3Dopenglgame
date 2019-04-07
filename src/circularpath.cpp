#include "circularpath.h"
#include "main.h"

const float pi = 4*atan(1);

Circularpath::Circularpath(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->before = 1;
    this->inside = 0;
    this->after = 0;
    this->radius = 300;

    const int n = 60;
    const int tind = (n * 9)/2;
    const double pi = 4 * atan(1);
    GLfloat vertex_buffer_data[2*n*18] = {};

    double angle = - pi/2;
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    for (int i = 0; i < n/2; i++)
    {
        vertex_buffer_data[ind++] = this->radius*cos(angle);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = this->radius*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);



        vertex_buffer_data[ind++] = this->radius*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = this->radius*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle + addang);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);



        vertex_buffer_data[ind++] = this->radius*cos(angle);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = this->radius*sin(angle);

        vertex_buffer_data[ind++] = (this->radius )*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius)*sin(angle + addang);



        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle + addang);
        vertex_buffer_data[ind++] = 4;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle + addang);

        vertex_buffer_data[ind++] = (this->radius + 4)*cos(angle + addang);
        vertex_buffer_data[ind++] = 0;
        vertex_buffer_data[ind++] = (this->radius + 4)*sin(angle + addang);
        angle += addang;

    }
    this->object = create3DObject(GL_TRIANGLES, 2*n*6, vertex_buffer_data, COLOR_WHITE, GL_FILL);

}

void Circularpath::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    //if(this->range && this->alive)
    //{
    if(this->before && !this->inside)
        draw3DObject(this->object);
    if(this->inside)
        draw3DObject(this->object2);
    if(!this->inside && this->after)
        draw3DObject(this->object3);
    //}
}

void Circularpath::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Circularpath::tick() {
    //if(this->range && this->alive)
    //    this->position.y -= 0.1;

}


bounding_box_t Circularpath::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 3000, 30000, 3000};
    return bbox;
}
