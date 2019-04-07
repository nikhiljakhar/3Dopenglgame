#include "volcano.h"
#include "main.h"

const float pi = 4*atan(1);

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->alive = 1;
    this->range = 0;
    this->radius = 500;
    this->health = 100;

    const int n = 60;
    const int tind = n * 9;
    const double pi = 4 * atan(1);
    GLfloat vertex_buffer_data[13*n*18] = {};

    double angle = 0;
    double angle2 = (pi/2);
    double addang = (2 * pi) / (double)n;
    int ind = 0;
    float d = 0;
    for(int j=0;j<13;j++){
        for (int i = 0; i < n; i++)
        {
            d = this->radius*sqrt((cos(angle+addang)-cos(angle))*(cos(angle+addang)-cos(angle)) + (sin(angle+addang)-sin(angle))*(sin(angle+addang)-sin(angle)));
            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*cos(angle);
            vertex_buffer_data[ind++] = j*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*sin(angle);

            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*cos(angle);
            vertex_buffer_data[ind++] = (j+1)*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*sin(angle);

            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*cos(angle + addang);
            vertex_buffer_data[ind++] = j*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*sin(angle + addang);

            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*cos(angle);
            vertex_buffer_data[ind++] = (j+1)*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*sin(angle);

            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*cos(angle + addang);
            vertex_buffer_data[ind++] = (j+1)*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - (j+1)*d*cos(pi/3))*sin(angle + addang);

            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*cos(angle + addang);
            vertex_buffer_data[ind++] = (j)*d*sin(pi/3);
            vertex_buffer_data[ind++] = (this->radius - j*d*cos(pi/3))*sin(angle + addang);

            angle += addang;

        }
    }

    this->object = create3DObject(GL_TRIANGLES, 6*n*13, vertex_buffer_data, COLOR_BROWN, GL_FILL);
    GLfloat vertex_buffer_data2[n*9];
    ind = 0;
    angle = 0;
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data2[ind++] = 0.0;
            vertex_buffer_data2[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data2[ind++] = 0.0;

            //Point with lower angle
            vertex_buffer_data2[ind++] = (this->radius - (13)*d*cos(pi/3)) * cos(angle);
            vertex_buffer_data2[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data2[ind++] = (this->radius - (13)*d*cos(pi/3)) * sin(angle);

            //Point with higher angle
            angle += addang;
            vertex_buffer_data2[ind++] = (this->radius - (13)*d*cos(pi/3)) * cos(angle);
            vertex_buffer_data2[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data2[ind++] = (this->radius - (13)*d*cos(pi/3)) * sin(angle);

    }

    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_ORANGE, GL_FILL);

    GLfloat vertex_buffer_data3[n*18];
    ind = 0;
    angle = 0;
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * cos(angle);
            vertex_buffer_data3[ind++] = 14*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * sin(angle);

            //Point with lower angle
            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * cos(angle);
            vertex_buffer_data3[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * sin(angle);

            //Point with higher angle
            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * cos(angle + addang);
            vertex_buffer_data3[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * sin(angle + addang);

            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * cos(angle + addang);
            vertex_buffer_data3[ind++] = 13*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13)*d*cos(pi/3)) * sin(angle + addang);

            //Point with lower angle
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * cos(angle + addang);
            vertex_buffer_data3[ind++] = 14*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * sin(angle + addang);;

            //Point with higher angle
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * cos(angle);
            vertex_buffer_data3[ind++] = 14*d*sin(pi/3);
            vertex_buffer_data3[ind++] = (this->radius - (13.5)*d*cos(pi/3)) * sin(angle);

            angle += addang;

    }
    this->object3 = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data3, COLOR_BROWN, GL_FILL);

    GLfloat vertex_buffer_data4[n*9];
    ind = 0;
    angle = 0;
    for (int i = 0; i < n; i++)
        {

            //Origin
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = 0.0;

            //Point with lower angle
            vertex_buffer_data4[ind++] = (this->radius + 200) * cos(angle);
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = (this->radius + 200) * sin(angle);

            //Point with higher angle
            angle += addang;
            vertex_buffer_data4[ind++] = (this->radius + 200) * cos(angle);
            vertex_buffer_data4[ind++] = 0.0;
            vertex_buffer_data4[ind++] = (this->radius + 200) * sin(angle);

    }
    this->object4 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data4, COLOR_SGREEN, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    //if(this->range && this->alive)
    //{
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    //}
}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() {
    //if(this->range && this->alive)
    //    this->position.y -= 0.1;

}


bounding_box_t Volcano::bounding_box() {
    bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, 3000, 30000, 3000};
    return bbox;
}
