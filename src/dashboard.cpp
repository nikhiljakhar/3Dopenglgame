#include "dashboard.h"
#include "main.h"

const float pi = 4*atan(1);

Dashboard::Dashboard(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 5;
    this->rotationx = 0;
    
    static const GLfloat vertex_buffer_data[] = {

        0,0,0,
        2,0,0,
        1,1,0,
        0,1,0,
        2,1,0,
        1,2,0,


    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_PGREEN, GL_FILL);
    static const GLfloat vertex_buffer_data2[] = {
        -2.5,2.8,0,
        -1,2.8,0,
        -2.5,4.8,0,
    };

    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_PGREEN, GL_FILL);
    static const GLfloat vertex_buffer_data3[] = {
        -0.5,2.8,0,
        1.5,2.8,0,
        0.5,4.8,0,
    };

    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_RED, GL_FILL);
    static const GLfloat vertex_buffer_data4[] = {
        0,38,0,
        0,41,0,
        -5,41,0,

        0,38,0,
        -5,38,0,
        -5,41,0,

        -5,38.5,0,
        -5,40.5,0,
        -5.4,40.5,0,
        -5.4,40.5,0,
        -5.4,38.5,0,
        -5,38.5,0,
    };

    this->object4 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data4, COLOR_GREY, GL_FILL);

    static const GLfloat vertex_buffer_data5[] = {
        -0.20,38.2,-0.03,
        -0.20,40.8,-0.03,
        -1.25,40.8,-0.03,

        -0.2,38.2,-0.03,
        -1.25,38.2,-0.03,
        -1.25,40.8,-0.03,
    };

    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, COLOR_GREEN, GL_FILL);
    static const GLfloat vertex_buffer_data6[] = {
        -1.38,38.2,-0.03,
        -1.38,40.8,-0.03,
        -2.43,40.8,-0.03,

        -1.38,38.2,-0.03,
        -2.43,38.2,-0.03,
        -2.43,40.8,-0.03,
    };

    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, COLOR_GREEN, GL_FILL);
    static const GLfloat vertex_buffer_data7[] = {
        -2.56,38.2,-0.03,
        -2.56,40.8,-0.03,
        -3.62,40.8,-0.03,

        -2.56,38.2,-0.03,
        -3.62,38.2,-0.03,
        -3.62,40.8,-0.03,
    };

    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7, COLOR_GREEN, GL_FILL);
    static const GLfloat vertex_buffer_data8[] = {
        -3.75,38.2,-0.03,
        -3.75,40.8,-0.03,
        -4.8,40.8,-0.03,

        -3.75,38.2,-0.03,
        -4.8,38.2,-0.03,
        -4.8,40.8,-0.03,
    };

    this->object8 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data8, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_buffer_data9[] = {
        -0.2,38.2,-0.03,
        -1.25,38.2,-0.03,
        -0.2,40.8,-0.03,
    };

    this->object9 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data9, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data10[] = {
        - 39.5,37,0,
        - 37,41,0,
        -42,41,0,

        - 37,41,0,
        - 40.5,41,0,
        - 38.25,43,0,

        - 42,41,0,
        - 38.5,41,0,
        - 40.75,43,0,

    };

    this->object10 = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data10, COLOR_PINK, GL_FILL);

    static const GLfloat vertex_buffer_data11[] = {
        - 39.5,37.2,-0.03,
        - 38.4,39,-0.03,
        -40.6,39,-0.03,
    };

    this->object11 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data11, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data12[] = {
        - 37.2,40.9,-0.03,
        - 38.35,39.2,-0.03,
        -40.63,39.2,-0.03,

        - 37.2,40.9,-0.03,
        - 41.8,40.9,-0.03,
        -40.63,39.2,-0.03,
    };

    this->object12 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data12, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data13[] = {
        - 37.2,41.1,-0.03,
        - 40.2,41.1,-0.03,
        - 38.25,42.7,-0.03,

        - 41.8,41.1,-0.03,
        - 38.8,41.1,-0.03,
        - 40.75,42.7,-0.03,
    };

    this->object13 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data13, COLOR_RED, GL_FILL);

}

void Dashboard::draw(glm::mat4 VP, int hieghtlimit, float fuel, float health) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatex = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate = rotate * rotatex;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    draw3DObject(this->object);
    draw3DObject(this->object2);
    if(hieghtlimit)
        draw3DObject(this->object3);
    draw3DObject(this->object4);
    if(fuel>=200)
        draw3DObject(this->object5);
    if(fuel>=650)
        draw3DObject(this->object6);
    if(fuel>=1100)
        draw3DObject(this->object7);
    if(fuel>=1550)
        draw3DObject(this->object8);
    if(fuel<200 && fuel>0)
        draw3DObject(this->object9);
}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick() {


}
