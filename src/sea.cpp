#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {

    -100000,-1,-100000, // triangle 1 : begin
        -100000,-1, 100000,
        100000, -1, 100000,
         // triangle 1 : end
        100000, -1,-100000, // triangle 2 : begin
        -100000,-1,-100000,
        100000, -1,100000,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sea::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}


