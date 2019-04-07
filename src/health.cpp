#include "health.h"
#include "main.h"

const float pi = 4*atan(1);

Health::Health(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->rotationx = 0;
    this->health = 1;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces withCOLOR_BALL2 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {

        -30,0,0,
        -30,1,0,
        30,0,0,
        30,0,0,
        30,1,0,
        -30,1,0,

    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        -30,0,0,
        -30,1,0,
        30,0,0,
        30,0,0,
        30,1,0,
        -30,1,0,       

    };

    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
    static const GLfloat vertex_buffer_data3[] = {

       -30,0,0,
        -30,1,0,
        30,0,0,
        30,0,0,
        30,1,0,
        -30,1,0,        

    };

    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Health::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    //Matrices.model = glm::scale(Matrices.model, glm::vec3(this->health, 1, 1));
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate1 = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate2 = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate = rotate1 * rotate2;
    Matrices.model *= (translate * rotate);
    Matrices.model = glm::scale(Matrices.model, glm::vec3(this->health, 1, 1));
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->health > 0.7)
        draw3DObject(this->object);
    if(this->health <= 0.7 && this->health > 0.2)
        draw3DObject(this->object2);
    if(this->health < 0.2)
        draw3DObject(this->object3);
}

void Health::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Health::tick() {


}