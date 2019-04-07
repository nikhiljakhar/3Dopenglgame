#include "score.h"
#include "main.h"

Score::Score(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationx = 0;
    
    static const GLfloat vertex_buffer_data[] = {
        0,0,0,
        1.00,0,0,
        1.00,-0.08,0,
        0,0,0,
        0,-0.08,0,
        1.00,-0.08,0,

        0,0,0.01,
        1.00,0,0.01,
        1.00,-0.08,0.01,
        0,0,0.01,
        0,-0.08,0.01,
        1.00,-0.08,0.01,
    };
    static const GLfloat vertex_buffer_data2[] = {
        0,-1.00,0,
        1.00,-1.00,0,
        1.00,-1.08,0,
        0,-1.00,0,
        0,-1.08,0,
        1.00,-1.08,0,

        0,-1.00,0.01,
        1.00,-1.00,0.01,
        1.00,-1.08,0.01,
        0,-1.00,0.01,
        0,-1.08,0.01,
        1.00,-1.08,0.01,
    
    };
    static const GLfloat vertex_buffer_data3[] = {
        0,-2.00,0,
        1.00,-2.00,0,
        1.00,-2.08,0,
        0,-2.00,0,
        0,-2.08,0,
        1.00,-2.08,0,

        0,-2.00,0.01,
        1.00,-2.00,0.01,
        1.00,-2.08,0.01,
        0,-2.00,0.01,
        0,-2.08,0.01,
        1.00,-2.08,0.01,
    
    };
    static const GLfloat vertex_buffer_data4[] = {
        0,0,0,
        0,-1.00,0,
        0.08,-1.00,0,
        0,0,0,
        0.08,0,0,
        0.08,-1.00,0,

        0,0,0.01,
        0,-1.00,0.01,
        0.08,-1.00,0.01,
        0,0,0.01,
        0.08,0,0.01,
        0.08,-1.00,0.01,
    
    };
    static const GLfloat vertex_buffer_data5[] = {
        1.00,0,0,
        1.00,-1.00,0,
        1.08,-1.00,0,
        1.00,0,0,
        1.08,0,0,
        1.08,-1.00,0,

        1.00,0,0.01,
        1.00,-1.00,0.01,
        1.08,-1.00,0.01,
        1.00,0,0.01,
        1.08,0,0.01,
        1.08,-1.00,0.01,
    
    };
    static const GLfloat vertex_buffer_data6[] = {
        0,-1.00,0,
        0,-2.00,0,
        0.08,-2.00,0,
        0,-1.00,0,
        0.08,-1.00,0,
        0.08,-2.00,0,

        0,-1.00,0.01,
        0,-2.00,0.01,
        0.08,-2.00,0.01,
        0,-1.00,0.01,
        0.08,-1.00,0.01,
        0.08,-2.00,0.01,
    
    };
    static const GLfloat vertex_buffer_data7[] = {
        1.00,-1.00,0,
        1.00,-2.00,0,
        1.08,-2.00,0,
        1.00,-1.00,0,
        1.08,-1.00,0,
        1.08,-2.00,0,

        1.00,-1.00,0.01,
        1.00,-2.00,0.01,
        1.08,-2.00,0.01,
        1.00,-1.00,0.01,
        1.08,-1.00,0.01,
        1.08,-2.00,0.01,
    
    };
    static const GLfloat vertex_buffer_data8[] = {
        1,-1.00,0.01,
        0,-2.00,0.01,
        0.08,-2.00,0.01,
        1,-1.00,0.01,
        1.08,-1.00,0.01,
        0.08,-2.00,0.01,

        1,-1.00,0,
        0,-2.00,0,
        0.08,-2.00,0,
        1,-1.00,0,
        1.08,-1.00,0,
        0.08,-2.00,0,
    
    };
    static const GLfloat vertex_buffer_data9[] = {
        0,0,0,
        0.1,0,0,
        1.5,-1.7,0,
        1.5,-1.7,0,
        1.6,-1.7,0,
        0.1,0,0,

        1.5,0,0,
        1.6,0,0,
        0,-1.7,0,
        0,-1.7,0,
        0.1,-1.7,0,
        1.6,0,0,
        
    
    };

    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, COLOR_WHITE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, COLOR_WHITE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_WHITE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data4, COLOR_WHITE, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data5, COLOR_WHITE, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data6, COLOR_WHITE, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data7, COLOR_WHITE, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data8, COLOR_WHITE, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data9, COLOR_WHITE, GL_FILL);

}

void Score::draw(glm::mat4 VP, int disp) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotatex = glm::rotate((float)(this->rotationx * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate = rotate * rotatex;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if( disp!=1 && disp!=4 && disp<10)
        draw3DObject(this->object);
    if(disp<=-4 || (disp>1 && disp<7) || disp == 8 || disp == 9 || disp == -1)
        draw3DObject(this->object2);
    if((disp<=0 && disp != -4) || disp == 2 || disp == 3 || disp == 5 || disp == 6 || disp == 8)
        draw3DObject(this->object3);
    if(disp <= 0 || (disp>3 && disp<10 && disp!=7))
        draw3DObject(this->object5);
    if(disp == - 3 || disp == -4 || (disp>=0 && (disp != 5 && disp !=6) && disp < 10))
        draw3DObject(this->object4);
    if(disp<=-2 || disp == 2 || disp == 6 || disp == 8 || disp == 0)
        draw3DObject(this->object7);
    if(disp != -2 && disp != -5 && disp != 2 && disp != -4 && disp<10)
        draw3DObject(this->object6);
    if(disp == -4)
        draw3DObject(this->object8);
    if(disp == 10)
        draw3DObject(this->object9);
}

void Score::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}


