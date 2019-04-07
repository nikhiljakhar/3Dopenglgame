#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "arrow.h"
#include "dashboard.h"
#include "score.h"
#include "aim.h"
#include "enemy.h"
#include "fuel.h"
#include "checkpoint.h"
#include "missile.h"
#include "bomb.h"
#include "bullet.h"
#include "efire.h"
#include "parachute.h"
#include "volcano.h"
#include "ring.h"
#include "compass.h"
#include "health.h"
#include "circularpath.h"
#include "shield.h"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Missile missile[60];
Bullet bullet[1000];
Efire efire[240];
Enemy enemy[60];
Parachute parc[10];
Checkpoint checkp[10];
Bomb bomb[10];
Volcano volc[20];
Ring rings[20];
Sea sea;
Circularpath cpath;
Health hbar;
Aim aim;
Arrow arrow;
Compass comp;
Dashboard dash;
Shield shield;
Fuel fuel[10];
Score meter[170];

Timer t60(1.0 / 60);

int cv = 0, lives=5, lostlife = 0, hieghtlimit = 0, checkind = 0, mind = 0, bind = 0, bfind = 0, llock = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, score = 0;
float camera_rotation_angle = 0, xcamera=0, ycamera= 25, zcamera=-60, xtarget=0, ytarget=25, ztarget=0,hca = 0,hca2 = 0;   
const float pi = 4*atan(1);


void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);
    //camera
    glm::vec3 eye(xcamera, ycamera, zcamera);
    // Target
    glm::vec3 target (xtarget, ytarget, ztarget);
    // Up - Up vector defines tilt of camera.
    glm::vec3 up (0, 1, 0);

    // View Matrices
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;

    // Scene render
        
    sea.draw(VP);
    arrow.draw(VP);
    plane.draw(VP);
    cpath.draw(VP);
    if(!shield.taken)
        shield.draw(VP);
    
    for(int i =0; i<20; i++)
    {
        rings[i].draw(VP);
        volc[i].draw(VP);
    }
    for(int i =0; i<10; i++)
    {
        if(bomb[i].fired && !bomb[i].hit)
                bomb[i].draw(VP);
        if(!fuel[i].taken)
            fuel[i].draw(VP);
        if(parc[i].alive)
            parc[i].draw(VP);
        
    }
    for(int i=0; i<60; i++)
    {
        enemy[i].draw(VP);
        if(enemy[i].fired && enemy[i].alive)
        {
            efire[4*i].draw(VP);
            efire[4*i + 1].draw(VP);
            efire[4*i + 2].draw(VP);
            efire[4*i + 3].draw(VP);
        }
        if(missile[i].fired && !missile[i].hit)
            missile[i].draw(VP);
    }
    for(int i=0; i<1000; i++)
    {
        if(bullet[i].fired && !bullet[i].hit)
            bullet[i].draw(VP);
    }
    if(cv==0 || cv==3)
    {
        aim.draw(VP);
        hbar.draw(VP);
        dash.draw(VP, hieghtlimit, plane.fuel, plane.health);
        for(int i=0; i<10; i++)
            checkp[i].draw(VP);
        comp.draw(VP);
        int t1 = (int)fmod(plane.speedz*1000,10);
        for (int i = 0; i < 10; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(plane.speedz*100,10);
        for (int i = 10; i < 20; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(plane.speedz*10,10);
        for (int i = 20; i < 30; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(plane.speedz,10);
        for (int i = 30; i < 40; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod((plane.position.y+100)/100,10);
        for (int i = 40; i < 50; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod((plane.position.y+100)/1000,10);
        for (int i = 50; i < 60; ++i)
            meter[i].draw(VP,t1);
        for (int i = 60; i < 70; ++i)
            meter[i].draw(VP,lives);
        for (int i = 70; i < 80; ++i)
            meter[i].draw(VP,10);
        for (int i = 80; i < 90; ++i)
            meter[i].draw(VP,-1);
        for (int i = 90; i < 100; ++i)
            meter[i].draw(VP,-2);
        for (int i = 100; i < 110; ++i)
            meter[i].draw(VP,-3);
        for (int i = 110; i < 120; ++i)
            meter[i].draw(VP,-4);
        for (int i = 120; i < 130; ++i)
            meter[i].draw(VP,-5);
        t1 = (int)fmod(score/1000,10);
        for (int i = 130; i < 140; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(score/100,10);
        for (int i = 140; i < 150; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(score/10,10);
        for (int i = 150; i < 160; ++i)
            meter[i].draw(VP,t1);
        t1 = (int)fmod(score,10);
        for (int i = 160; i < 170; ++i)
            meter[i].draw(VP,t1);
    }
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int forward = glfwGetKey(window, GLFW_KEY_W);
    int clrot = glfwGetKey(window, GLFW_KEY_E);
    int acrot = glfwGetKey(window, GLFW_KEY_Q);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int bfire  = glfwGetKey(window, GLFW_KEY_Z);
    int rmo = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int lmo = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    
    glfwSetScrollCallback(window, scroll_callback);

    
    
    if (left) {
        plane.left();
    }
    if (right) {
        plane.right();
    }
    if (up && llock) {
        if((plane.position.y+100)/100<=23)
            plane.up();
    }
    if(up && !llock)
    {
        if((plane.position.y+100)/100<=23)
            plane.loop();
    }
    if (down) {
        if(plane.position.y>-48)
            plane.down();
        else
            lostlife = 1;
    }
    if (forward) {
        plane.forward();
        
    }
    if (clrot) {
        plane.clockwise();
    }
    if (acrot) 
    {
        plane.anticlockwise();
    }
    if(bfire)
    {
        bullet[bfind].fired = 1;
        if(bfind<999)
            bfind += 1;
    }
    if(lmo && cv)
    {
        hca2 -= 0.01;
        ycamera = ytarget + 60*sin(hca2);
    }
    if(rmo && cv)
    {
        hca2 += 0.01;
        ycamera = ytarget + 60*sin(hca2);
    }
}

void tick_elements() {
    float theta = (plane.rotation)*(pi/180);
    float theta2 = (plane.rotationx)*(pi/180);
    score += plane.speedz/100;
    plane.tick();
    if(plane.position.y<-48)
        lostlife = 1;
    if(!shield.taken)
        shield.tick();
    for(int i=0; i<60; i++)
    {
        if(!missile[i].fired){
            missile[i].position.x = plane.position.x;
            missile[i].position.y = plane.position.y -1;
            missile[i].position.z = plane.position.z;
            missile[i].rotation = plane.rotation;
            missile[i].rotationx = plane.rotationx; 
        }

        if(missile[i].fired && !missile[i].hit)
            missile[i].tick();

        if(enemy[i].alive)
            enemy[i].tick();

        if(enemy[i].fired)
        {
            efire[4*i].tick();
            efire[4*i + 1].tick();
            efire[4*i + 2].tick();
            efire[4*i + 3].tick();
        }
    }
    for(int i=0; i<1000; i++)
    {
        if(!bullet[i].fired){
            bullet[i].position.x = plane.position.x;
            bullet[i].position.y = plane.position.y -1;
            bullet[i].position.z = plane.position.z;
            bullet[i].rotation = plane.rotation;
            bullet[i].rotationx = plane.rotationx; 
        }

        if(bullet[i].fired && !bullet[i].hit)
            bullet[i].tick();
    }
    arrow.rotation = - atan(arrow.position.x/(checkp[checkind].position.z-arrow.position.z));
    if(checkp[checkind].position.z<arrow.position.z)
        arrow.rotation = - pi + arrow.rotation;
    for(int i=0; i<10; i++)
    {
        checkp[i].tick();
        parc[i].tick();
        if(!fuel[i].taken)
            fuel[i].tick();

        if(bomb[i].fired && !bomb[i].hit)
            bomb[i].tick();

        if(!bomb[i].fired){
            bomb[i].position.x = plane.position.x;
            bomb[i].position.y = plane.position.y -1;
            bomb[i].position.z = plane.position.z;
            bomb[i].rotation = plane.rotation;
            bomb[i].rotationx = plane.rotationx;
            bomb[i].speed = plane.speedz; 
        }
    }
    if(lostlife)
    {
        lives-=1;
        plane.position.y = 200;
        plane.position.x = 0;
        plane.rotation = 0;
        plane.rotationx = 0;
        plane.rotationx = 0;
        plane.fuel = 1500;
        lostlife = 0;
        plane.health = 100;
        hbar.health = 1;
        cout<<lives<<" = remaining lives\n";
        if(lives<=0)
        {
            cout<<"YOUR SCORE : "<<score<<"\n";
            quit(window);
        }
    }

    for(int i=0; i<10; i++)
    {
        if ((detect_collision(plane.bounding_box(), fuel[i].bounding_box())) && !fuel[i].taken)
        {
            cout<<"fueled up\n"; 
            fuel[i].taken = 1;
            plane.fuel += 1000;
        }
        if ((detect_collision(plane.bounding_box(), parc[i].bounding_box())) && parc[i].alive)
        {
            cout<<"damaged\n"; 
            parc[i].alive = 0;
            plane.health -= 30;
            hbar.health -= 0.3;
            if(plane.health<0)
                lostlife = 1;
            if(hbar.health<0)
                lostlife = 1;
        }
        if(sqrt((plane.position.x - parc[i].position.x)*(plane.position.x - parc[i].position.x) + (plane.position.z - parc[i].position.z)*(plane.position.z - parc[i].position.z)) < 1000)
        {
            parc[i].range = 1;
        }
        for(int j=0; j<1000; j++)
        {
            if(detect_collision(bullet[j].bounding_box(), parc[i].bounding_box()) && parc[i].alive && !bullet[j].hit && parc[i].range && bullet[j].fired)
            {
                bullet[j].hit = 1;
                parc[i].health -= 20;
                score += 4;
                if(parc[i].health < 0)
                    parc[i].alive = 0;
                //cout<<"hit\n";
            }
        }
        for(int j=0; j<60; j++)
        {
            if(detect_collision(missile[j].bounding_box(), parc[i].bounding_box()) && parc[i].alive && !missile[j].hit && parc[i].range && missile[j].fired)
            {
                missile[j].hit = 1;
                score += 4;
                parc[i].alive = 0;
                //cout<<"hit\n";
            }
        }
    }
    for(int i=0; i<60; i++)
    {
        for(int j=0; j<60; j++)
        {
            if ((missile[j].position.y>-50 && detect_collision(missile[j].bounding_box(), enemy[i].bounding_box())) && !missile[j].hit && missile[j].fired)
            {
                cout<<"enemy dead\n"; 
                missile[j].hit = 1;
                enemy[i].alive = 0;
                score += 10;
            }
        }
        for(int j=0; j<10; j++)
        {
            if ((bomb[j].position.y>-50 && detect_collision(bomb[j].bounding_box(), enemy[i].bounding_box())) && !bomb[j].hit && bomb[j].fired)
            {
                cout<<"enemy dead\n"; 
                bomb[j].hit = 1;
                score += 10;
                enemy[i].alive = 0;
            }
        }
        if ((detect_collision(plane.bounding_box(), enemy[i].bounding_box())) && !lostlife)
        {
            cout<<"dead\n";
            lostlife = 1; 
        }
        if(sqrt((plane.position.x - enemy[i].position.x)*(plane.position.x - enemy[i].position.x) + (plane.position.z - enemy[i].position.z)*(plane.position.z - enemy[i].position.z)) < 3000)
        {
            enemy[i].fired = 1;
        }
        if ((detect_lasercollision(i) && !lostlife && enemy[i].fired && plane.position.y > 80) && !plane.protection)
        {
            plane.health -= 1;
            hbar.health -= 0.01;
            //cout<<plane.health<<" = current health\n";
            if(plane.health < 1)
                lostlife = 1;
            if(hbar.health < 0.01)
                lostlife = 1;
        }
    }
    for(int i =0; i<20; i++)
    {
        if((detect_collision(plane.bounding_box(), volc[i].bounding_box())) && !lostlife)
            lostlife = 1;

    }
    if ((detect_collision(plane.bounding_box(), checkp[checkind].bounding_box())) && !checkp[checkind].covered)
    {
        cout<<"checkpoint\n";
        checkp[checkind].covered = 1;
        score += 10;
        if(checkind<10)
            checkind += 1;
        if(checkind == 9)
        {
            cout<<"YOU WON"<<"\n";
            cout<<"Lives remaining : "<<lives<<"\n";
            cout<<"Score : "<<score<<"\n";
            cout<<"Total Score : "<<lives*score<<"\n";
        }
    }
    if ((detect_collision(plane.bounding_box(), shield.bounding_box())) && !shield.taken)
    {
        cout<<"shield up\n"; 
        shield.taken = 1;
        plane.protection = 1;
    }
    if(shield.taken && !shield.expire)
    {
        shield.time -= 0.01667;
        //cout<<shield.time<<"\n";
        if(shield.time < 0)
        {
            shield.expire = 1;
            plane.protection = 0;
        }
    }
    if(plane.fuel<10)
    {
        plane.down();
        if(plane.position.y<-50)
            lostlife = 1;
    }
    enemyammo();
    movedash();
    ringcheck();
    if((plane.position.y+100)/100>=22 || plane.position.y<=10)
        hieghtlimit = 1;
    if((plane.position.y+100)/100<22 && plane.position.y>10)
        hieghtlimit = 0;
    if(collision_circle())
    {
        //cout<<"in proximity\n";
        circular_motion();
    }
    //cout<<plane.speed*700<<"\n";
}


void initGL(GLFWwindow *window, int width, int height) {

    plane = Plane(0, 0, 0);
    for(int i=0; i<50; i++)
    {
        float xi = ((float) rand()*(3000)/(float)RAND_MAX) -1500;
        float zi = ((float) rand()*(100000)/(float)RAND_MAX) + 1000;
        enemy[i] = Enemy(xi,-481,zi);
    }
    arrow = Arrow(0, 52, 0);
    comp = Compass(0,-100,0);
    aim = Aim(0,15,0);
    hbar = Health(0,54,0);
    sea = Sea(0, -50, 0);
    dash = Dashboard(30, -7, 0);
    cpath = Circularpath(0,40,500);
    shield = Shield(-50,600, 3300);
    for(int i=0; i<5; i++)
        rings[i] = Ring(-50,600,3000+i*30);
    for(int i=5; i<10; i++)
        rings[i] = Ring(-50,600,22000 + (i-5)*40);
    for(int i=10; i<15; i++)
        rings[i] = Ring(-50,600,42000 + (i-10)*40);
    for(int i=15; i<20; i++)
        rings[i] = Ring(-50,600,62000 + (i-15)*40);
    for (int i = 0; i < 60; ++i)
        missile[i] = Missile(0,-500, 0);
    for (int i = 0; i < 170; ++i)
        meter[i] = Score(0,25,0);
    for (int i = 0; i < 1000; ++i)
        bullet[i] = Bullet(0,-500, 0);
    for (int i = 0; i < 240; ++i)
        efire[i] = Efire(0,-500, 0);
    for(int i=0; i<10; i++)
    {
        fuel[i] = Fuel(0,500,10000*(i+1));
        checkp[i] = Checkpoint(0,140,10000*(i+1) + 5000);
        enemy[50+i] = Enemy(0,-500,10000*(i+1) + 5000);
        bomb[i] = Bomb(0,-500,0);
        float zi = ((float) rand()*(30000)/(float)RAND_MAX) + 200;
        parc[i] = Parachute(0,40,zi);
    }
    for(int i=0; i<20; i++)
        volc[i] = Volcano(2000*( 2*(i%2) - 1),-48,7500 + 5000*i);

    plane.rotation = 0;
    plane.rotationz = 0;
    plane.rotationx = 0;
        
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
}


int main(int argc, char **argv) {
    system("aplay ../punisher.wav&");
    srand(time(0));
    int width  = 700;
    int height = 700;
    window = initGLFW(width, height);

    initGL (window, width, height);

    while (!glfwWindowShouldClose(window)) {


            if (t60.processTick()) {

                draw();
                glfwSwapBuffers(window);
                tick_elements();
                tick_input(window);
                cameraview();
                
                
        }
        glfwPollEvents();
    }

    quit(window);
}


bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.width + b.width)/2) && 
    (abs(a.y - b.y) < (a.height + b.height)/2) &&
    (abs(a.z - b.z) < (a.depth + b.depth)/2) ;
}

int detect_lasercollision(int index) {

    for(int j = 0; j<4; j++)
    {
        float ex1 = efire[4*index + j].position.x, ey1 = efire[4*index + j].position.y, ez1 = efire[4*index + j].position.z;
        float ex2 = ex1 - 10000*sin(efire[4*index + j].rotation*(pi/180))*cos(efire[4*index + j].rotationx*(pi/180)), ey2 = ey1 + 10000*sin(efire[4*index + j].rotationx*(pi/180)), ez2 = ez1 - 10000*cos(efire[4*index + j].rotation*(pi/180))*cos(efire[4*index + j].rotationx*(pi/180));
        float x1 = plane.position.x, y1 = plane.position.y, z1 = plane.position.z;
        float t = -((ex1 - x1)*(ex2 - ex1) + (ey1 - y1)*(ey2 - ey1) + (ez1 - z1)*(ez2 - ez1));
        t = t/((ex2 - ex1)*(ex2 - ex1) + (ey2 - ey1)*(ey2 - ey1) + (ez2 - ez1)*(ez2 - ez1));
        float dsq = (ex1 - x1 + t*(ex2 - ex1))*(ex1 - x1 + t*(ex2 - ex1)) + (ey1 - y1 + t*(ey2 - ey1))*(ey1 - y1 + t*(ey2 - ey1)) + (ez1 - z1 + t*(ez2 - ez1))*(ez1 - z1 + t*(ez2 - ez1));
        float d = sqrt(dsq);
        if(d<50)
            return 1;
        // if(enemy[index].fired)
        //     cout<<d<<"\n";
    }
    return 0;
}

void reset_screen() {
    Matrices.projection = glm::perspective(45.0f, 1.0f, 30.0f, 9000.0f);
}

void viewdiff(){
    cv = (cv+1)%5;
}

void llockc(){
    llock = (llock+1)%2;
}

void aimc(){
    aim.type = (aim.type + 1)%2;
}

void fire(int mob)
{
    if(!mob)
    {
        missile[mind].fired = 1;
        if(mind<59)
            mind += 1;
    }
    if(mob)
    {
        bomb[bind].fired = 1;
        if(bind<9)
            bind += 1;
    }
}

void cameraview(){
    if(cv == 0)
    {
        //follow-cam view
        float theta = (plane.rotation)*(pi/180);
        float theta2 = (plane.rotationx)*(pi/180);
        xcamera = plane.position.x - 60 * sin(theta);
        ycamera = plane.position.y + 25 + 20*sin(theta2);
        zcamera = plane.position.z - 60 * cos(theta);
        //cout<<"xcamera = "<<xcamera<<"\n";

        xtarget = plane.position.x;
        ytarget = plane.position.y + 25;
        ztarget = plane.position.z;
    }
    else if(cv == 2)
    {
        //Top View
        xcamera = plane.position.x;
        if(plane.position.y<500)
            ycamera = 800;
        else
            ycamera = 400 + plane.position.y;
        zcamera = plane.position.z;

        xtarget = plane.position.x;
        ytarget = plane.position.y;
        ztarget = plane.position.z + 0.1;
    }
    else if(cv == 3)
    {
        //Plane view
        float theta = (plane.rotation)*(pi/180);
        float theta2 = (plane.rotationx)*(pi/180);
        xcamera = plane.position.x;
        ycamera = plane.position.y;
        zcamera = plane.position.z;

        xtarget = plane.position.x + 60 * sin(theta)*cos(theta2);
        ytarget = plane.position.y - 60*sin(theta2);
        ztarget = plane.position.z + 60 * cos(theta)*cos(theta2);
    }
    else if(cv == 4)
    {
        //Tower view
        xcamera = plane.position.x + 80;
        ycamera = plane.position.y + 80;
        zcamera = plane.position.z;

        xtarget = plane.position.x;
        ytarget = plane.position.y;
        ztarget = plane.position.z;
    }
}

void movedash(){

    sea.position.x = plane.position.x;
    sea.position.z = plane.position.z;
    if(cv == 0 || cv == 3)
    {
        float theta = (plane.rotation)*(pi/180);
        float thetax = (plane.rotationx)*(pi/180);
        arrow.position.y = ycamera + 27 -20*sin(thetax);
        arrow.position.x = xcamera + 60 * sin(theta);
        arrow.position.z = zcamera + 60 * cos(theta);
        if(cv == 3)
            arrow.position.y = ycamera + 27 -60*sin(thetax);

        aim.position.y = ycamera - 10 -20*sin(thetax);
        aim.position.x = xcamera + 60 * sin(theta);
        aim.position.z = zcamera + 60 * cos(theta);
        aim.rotation = plane.rotation;
        aim.rotationz = plane.rotationz;
        aim.rotationx = plane.rotationx;
        if(cv == 3)
            aim.position.y = ycamera - 10 -60*sin(thetax);

        hbar.position.y = ycamera + 29 - 20*sin(thetax);
        hbar.position.x = xcamera + 60 * sin(theta);
        hbar.position.z = zcamera + 60 * cos(theta);
        hbar.rotation = plane.rotation;
        hbar.rotationx = plane.rotationx;
        if(cv == 3)
        {
            hbar.position.y = ytarget + 29;
            hbar.position.x = xtarget;
            hbar.position.z = ztarget;
        }
        
        float theta2 = (plane.rotation+26.7 - 5)*(pi/180);
        dash.position.y = ycamera - 19.7-20*sin(thetax);
        dash.position.x = xcamera + 57 * sin(theta2);
        dash.position.z = zcamera + 57 * cos(theta2);
        dash.rotation = plane.rotation;
        if(cv == 3)
            dash.position.y = ycamera - 19.7 -60*sin(thetax);

        theta2 = (plane.rotation -21.5)*(pi/180);
        comp.position.y = ycamera  - 20*sin(thetax) + 12;
        comp.position.x = xcamera + 57 * sin(theta2);
        comp.position.z = zcamera + 57 * cos(theta2);
        comp.rotation = plane.rotation;
        comp.rotationz = plane.rotation;
        if(cv == 3)
            comp.position.y = ycamera + 12 -60*sin(thetax);

        theta2 = (plane.rotation+21.4 - 5)*(pi/180);
        float k = 57;
        for (int i = 0; i < 10; ++i){
            meter[i].position.y = ycamera - 18.2-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 18.2-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation+22.8 - 5)*(pi/180);
        for (int i = 10; i < 20; ++i){
            meter[i].position.y = ycamera - 18.05-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);    
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 18.05-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation+24.2 - 5)*(pi/180);
        for (int i = 20; i < 30; ++i){
            meter[i].position.y = ycamera - 17.9-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 17.9-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation+25.6 - 5)*(pi/180);
        for (int i = 30; i < 40; ++i){
            meter[i].position.y = ycamera - 17.7-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 17.7-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation+21.4 - 5)*(pi/180);
        for (int i = 40; i < 50; ++i){
            meter[i].position.y = ycamera - 15.5-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 15.5-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation+22.8 - 5)*(pi/180);
        for (int i = 50; i < 60; ++i){
            meter[i].position.y = ycamera - 15.4-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 15.4-60*sin(thetax);
            k -= 0.01;
        }
        k = 57;
        theta2 = (plane.rotation - 25)*(pi/180);
        for (int i = 60; i < 70; ++i){
            meter[i].position.y = ycamera + 23 - 20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera + 24-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 23.5)*(pi/180);
        for (int i = 70; i < 80; ++i){
            meter[i].position.y = ycamera + 23-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera + 24-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 16.4)*(pi/180);
        for (int i = 80; i < 90; ++i){
            meter[i].position.y = ycamera - 16.2 -20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 16.2 -60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 17.8)*(pi/180);
        for (int i = 90; i < 100; ++i){
            meter[i].position.y = ycamera - 16-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 16-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 19.2)*(pi/180);
        for (int i = 100; i < 110; ++i){
            meter[i].position.y = ycamera - 15.8-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 15.8-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 20.6)*(pi/180);
        for (int i = 110; i < 120; ++i){
            meter[i].position.y = ycamera - 15.59-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 15.59-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 22)*(pi/180);
        for (int i = 120; i < 130; ++i){
            meter[i].position.y = ycamera - 15.38-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 15.38-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 17.2)*(pi/180);
        for (int i = 130; i < 140; ++i){
            meter[i].position.y = ycamera - 18.1-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 18.1-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 18.6)*(pi/180);
        for (int i = 140; i < 150; ++i){
            meter[i].position.y = ycamera - 17.9-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 17.9-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 20)*(pi/180);
        for (int i = 150; i < 160; ++i){
            meter[i].position.y = ycamera - 17.69-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 17.69-60*sin(thetax);
            k -= 0.01;
        }
        theta2 = (plane.rotation - 21.4)*(pi/180);
        for (int i = 160; i < 170; ++i){
            meter[i].position.y = ycamera - 17.48-20*sin(thetax);
            meter[i].position.x = xcamera + k * sin(theta2);
            meter[i].position.z = zcamera + k * cos(theta2);
            meter[i].rotation = plane.rotation;
            if(cv == 3)
                meter[i].position.y = ycamera - 17.48-60*sin(thetax);
            k -= 0.01;
        }
        for(int i = 0; i<10; i++)
        {
            if(!parc[i].range)
                parc[i].position.y = plane.position.y + 50;
        }
    }
    else
    {
        arrow.position.y = plane.position.y + 10;
        arrow.position.x = plane.position.x;
        arrow.position.z = plane.position.z;

    }
    return;
}

void enemyammo()
{
    for(int i=0; i<60; i++)
    {
            efire[4*i].position.x = enemy[i].position.x;
            efire[4*i].position.z = enemy[i].position.z;
            efire[4*i].position.y = enemy[i].position.y + 580;
            efire[4*i].rotation = 0 + enemy[i].rotation;

            efire[4*i + 1].position.x = enemy[i].position.x;
            efire[4*i + 1].position.z = enemy[i].position.z;
            efire[4*i + 1].position.y = enemy[i].position.y + 580;
            efire[4*i + 1].rotation = 180 + enemy[i].rotation;

            efire[4*i + 2].position.x = enemy[i].position.x;
            efire[4*i + 2].position.z = enemy[i].position.z;
            efire[4*i + 2].position.y = enemy[i].position.y + 580;
            efire[4*i + 2].rotation = 90 + enemy[i].rotation;

            efire[4*i + 3].position.x = enemy[i].position.x;
            efire[4*i + 3].position.z = enemy[i].position.z;
            efire[4*i + 3].position.y = enemy[i].position.y + 580;
            efire[4*i + 3].rotation = 270 + enemy[i].rotation;
    }

}

void ringcheck()
{
    for(int i=0;i<20;i++)
    {
        if(rings[i].position.z + 3>plane.position.z)
        {
            rings[i].before = 1;
            rings[i].after = 0;
        }
        else
        {
            rings[i].before = 0;
            rings[i].after = 1;
        }
        if(rings[i].before)
        {
            if(rings[i].position.z + 3>plane.position.z && rings[i].position.z - 3 < plane.position.z)
            {
                float disr = sqrt( (plane.position.x - rings[i].position.x)*(plane.position.x - rings[i].position.x) + (plane.position.y - rings[i].position.y)*(plane.position.y - rings[i].position.y) );
                if(disr<=7)
                {
                    rings[i].inside = 1;
                    score += 5;
                }
            }   
        }
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset){
    if(cv == 1)
    {
        if(yoffset>0)
        {
            xtarget += 5*sin(hca);
            ztarget += 5*cos(hca);
            ytarget -= 5*sin(hca2);

        }
        if(yoffset<0)
        {
            xtarget -= 5*sin(hca);
            ztarget -= 5*cos(hca);
            ytarget += 5*sin(hca2);
        }

        if(xoffset>0)
        {
            hca += 0.01;
        }
        if(xoffset<0)
        {
            hca -= 0.01;
        }

        xcamera = xtarget - 60 * sin(hca);
        ycamera = ytarget + 60*sin(hca2);
        zcamera = ztarget - 60 * cos(hca);
            //cout<<"xcamera = "<<xcamera<<"\n";

        
        //cout<<yoffset<<" : "<<xoffset<<"\n";
    }
}

int collision_circle(){
    float xdis = (plane.position.x - cpath.position.x) * (plane.position.x - cpath.position.x);
    float zdis = (plane.position.z - cpath.position.z + 300) * (plane.position.z - cpath.position.z + 300);
    float dis = sqrt(xdis + zdis);
    //cout<<dis<<"\n";
    if (dis <= 10 && plane.position.y > cpath.position.y - 10 && plane.position.y < cpath.position.y + 10)
        return 1;

    return 0;
}

void circular_motion()
{
    plane.position.x = cpath.position.x;
    plane.position.y = cpath.position.y;
    plane.position.z = cpath.position.z - 300;
    plane.rotation = 90;
    plane.rotationz = 30;
    double spee = plane.speedz, addy = 0;
    while(plane.position.z < cpath.position.z + 300)
    {
        plane.position.z += spee;
        if(plane.position.z<=cpath.position.z)
        { 
            spee += 0.05;
        }
        else
        {
            spee -= 0.049;
        }
        //cout<<spee<<"\n";
        plane.rotation -= spee*0.25;
        if((plane.position.z - cpath.position.z)*(plane.position.z - cpath.position.z) < 90000)
            plane.position.x = sqrt(90000 - (plane.position.z - cpath.position.z)*(plane.position.z - cpath.position.z));
        //cout<<plane.position.x<<" = x\n";
        //cout<<plane.position.z<<" = z\n";
        xtarget = plane.position.x;
        ztarget = plane.position.z;
        if(cv == 3)
        {
            float theta = (plane.rotation)*(pi/180);
            float theta2 = (plane.rotationx)*(pi/180);
            xcamera = plane.position.x;
            ycamera = plane.position.y;
            zcamera = plane.position.z;

            xtarget = plane.position.x + 60 * sin(theta)*cos(theta2);
            ytarget = plane.position.y - 60*sin(theta2);
            ztarget = plane.position.z + 60 * cos(theta)*cos(theta2);
            movedash();
        }
        draw();
        glfwSwapBuffers(window);
    }
    //cout<<plane.position.x<<"\n";
    //cout<<plane.position.z<<"\n";

    //if(plane.speedz == 0)
    //    plane.speedz = 0.1;
    //else
        //plane.speedz = 0 - plane.speedz;
    return;
}
