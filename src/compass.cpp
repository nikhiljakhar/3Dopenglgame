#include "compass.h"
#include "main.h"

const float pi = 4*atan(1);

Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationz = 0;
    this->rotationx = 0;
    this->radius = 3;
    const int n = 100;
    const int tind = n * 9;
    GLfloat vertex_buffer_data[n*9] = {};

    double angle = 0;
    const double pi = 4 * atan(1);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data[ind++] = 0.0;
            vertex_buffer_data[ind++] = 0.0;
            vertex_buffer_data[ind++] = 0.0f;

            //Point with lower angle
            vertex_buffer_data[ind++] = radius * cos(angle);
            vertex_buffer_data[ind++] = radius * sin(angle);
            vertex_buffer_data[ind++] = 0.0f;

            //Point with higher angle
            angle += addang;
            vertex_buffer_data[ind++] = radius * cos(angle);
            vertex_buffer_data[ind++] = radius * sin(angle);
            vertex_buffer_data[ind++] = 0.0f;

    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    static const GLfloat vertex_buffer_data2[] = {
        0,2.7,-0.1,
        -1,0,-0.1,
        1,0,-0.1,
    };

    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    static const GLfloat vertex_buffer_data3[] = {
        0,-2.7,-0.1,
        -1,0,-0.1,
        1,0,-0.1,
    };

    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_BLUE, GL_FILL);

    GLfloat vertex_buffer_data4[n*9] = {};
    angle = 0;
    ind = 0;
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = 0.1f;

            //Point with lower angle
            vertex_buffer_data4[ind++] = (radius + 0.5)* cos(angle);
            vertex_buffer_data4[ind++] = (radius + 0.5)* sin(angle);
            vertex_buffer_data4[ind++] = 0.1f;

            //Point with higher angle
            angle += addang;
            vertex_buffer_data4[ind++] = (radius + 0.5) * cos(angle);
            vertex_buffer_data4[ind++] = (radius + 0.5)* sin(angle);
            vertex_buffer_data4[ind++] = 0.1f;

    }

    this->object4 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatez = glm::rotate((float)(this->rotationz * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotatex = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate = rotate * rotatex;
    rotate = rotate * rotatez;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick() {


}
