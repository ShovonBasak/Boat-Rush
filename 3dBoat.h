/*
This 3D Boat is not created manually, It's collected from net and vertex, normal and textures are plotted here only
*/

#include<fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<windows.h>
#include <GL/glut.h>

using namespace std;

GLfloat vertex[118][3]; //To store vertex, normal & textures points from file


class Boat
{
    double xAxis;
    double yAxis;
    double zAxis;
    double rotationByZ; //Rotation variable to store position after collision with stone by Z axis
    double rotateByX; //Rotation variable to store position after collision with plank by X axis
    int direction;
    int health;
    double size;
public:
    bool alive;
    bool dead;
    Boat()
    {
        alive = false;
        dead = false;
        zAxis = 4;
        yAxis = -0.02;
        xAxis = 0.0;
        size = .1;
        setHealth(3);
        initVertex();
    }
    void setRotation(double rotationByZ)
    {
        this->rotationByZ=rotationByZ;
    }
    void setRotateByX(double rotation)
    {
        this->rotateByX=rotation;
    }
    void setDirection(int direction)
    {
        this->direction=direction;
    }
    double getRotateByX()
    {
        return this->rotateByX;
    }
    double getX()
    {
        return xAxis;
    }
    double getY()
    {
        return yAxis;
    }
    double getZ()
    {
        return zAxis;
    }
    void setX(double x)
    {
        xAxis = x;
    }
    void setY(double y)
    {
        yAxis = y;
    }
    void setZ(double z)
    {
        zAxis = z;
    }
    void setHealth(int health)
    {
        this->health = health;
    }
    int getHealth()
    {
        return health;
    }
    void move(double value)
    {
        setX(getX()+ value);
    }
    double getSize()
    {
        return size;
    }
    void initVertex(){
        freopen("input.txt","r",stdin);

        for(int i=0;i<116;i++){
            for(int j=0;j<3;j++){
                cin>>vertex[i][j];
            }
        }
        fclose(stdin);
    }

    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 };

        GLfloat white_light[] = { 1.0, 0.0, 0.0, 1.0 };
        GLfloat lmodel_ambient[] = { 0.1, 0.20, 0.1, 1.0 };

        glClearColor(0.0, 0.0, 0.0, 0.0);

        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);

        glEnable(GL_DEPTH_TEST);
    }


    //Initializes 3D rendering
    void initRendering() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.0,0.0,0.0,1);
        //glEnable(GL_LIGHTING); //Enable lighting
        //glEnable(GL_LIGHT0); //Enable light #0
        //glEnable(GL_LIGHT1); //Enable light #1
        glEnable(GL_SHADE_MODEL);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_TEXTURE);
        glEnable(GL_NORMALIZE);
    }


    ///drawing
    void normal(int index){
        glNormal3f(vertex[index-1][0], vertex[index-1][1], vertex[index-1][2]);
    }

    void texture(int index){
        glTexCoord3f(vertex[index-1][0], vertex[index-1][1], vertex[index-1][2]);
    }

    void vtx(int index){
        glVertex3f(vertex[index-1][0], vertex[index-1][1], vertex[index-1][2]);
    }

    void drawTwelve(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,int l){
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        normal(c); texture(b); vtx(a);
        glColor3f(0.3,0.3,0.3);
        normal(f); texture(e); vtx(d);
        glColor3f(2.0,2.0,2.0);
        normal(i); texture(h); vtx(g);
        glColor3f(3.0,3.0,3.0);
        normal(l); texture(k); vtx(j);
        glEnd();
    }

    void drawthree(int a,int b,int c){
        glColor3f(0.9,0.9,0.9);
        normal(c); texture(b); vtx(a);
    }

    float angle = 0.0;
    bool l=true,r=false;
    float _cameraAngle = 0.0;
    float translate = 0;
    //Draws the 3D scene
    void drawScene() {
        glPushMatrix();
        drawTwelve(1,1,1,4,2,1,3,3,1,2,4,1);
        drawTwelve(2,4,2,6,5,2,5,6,2,1,1,2);
        drawTwelve(7,7,3,5,6,3,6,5,3,8,8,3);
        drawTwelve(9,9,4,7,7,4,8,8,4,10,10,4);
        drawTwelve(11,11,5,9,9,5,10,10,5,12,12,5);
        drawTwelve(13,13,6,11,11,6,12,12,6,14,14,6);
        drawTwelve(15,15,7,13,13,7,14,14,7,16,16,7);
        drawTwelve(17,17,8,15,15,8,16,16,8,18,18,8);
        drawTwelve(19,19,9,17,17,9,18,18,9,20,20,9);
        drawTwelve(21,21,10,19,19,10,20,20,10,22,22,10);
        drawTwelve(23,23,11,21,21,11,22,22,11,24,24,11);
        drawTwelve(25,25,12,23,23,12,24,24,12,26,26,12);
        drawTwelve(27,27,13,25,25,13,26,26,13,28,28,13);
        drawTwelve(27,27,14,28,28,14,30,29,14,29,30,14);
        drawTwelve(30,31,15,43,32,15,31,33,15,29,34,15);
        drawTwelve(44,35,16,42,36,16,31,37,16,43,38,16);

        glBegin(GL_POLYGON);
        drawthree(43,39,17);
        drawthree(30,40,17);
        drawthree(102,41,17);
        drawthree(46,42,17);
        drawthree(47,43,17);
        drawthree(48,44,17);
        drawthree(45,45,17);
        drawthree(44,46,17);
        glEnd();

        drawTwelve(2,47,17,3,48,17,74,49,17,76,50,17);
        drawTwelve(50,51,18,51,52,18,53,53,18,52,54,18);
        drawTwelve(48,55,19,50,56,19,52,57,19,54,58,19);
        drawTwelve(45,59,20,48,60,20,54,61,20,55,62,20);
        drawTwelve(56,63,21,45,59,21,55,62,21,57,64,21);
        drawTwelve(58,65,22,56,63,22,57,64,22,59,66,22);
        drawTwelve(60,67,23,58,65,23,59,66,23,61,68,23);
        drawTwelve(62,69,24,60,67,24,61,68,24,63,70,24);
        drawTwelve(64,71,25,62,69,25,63,70,25,65,72,25);
        drawTwelve(66,73,26,64,71,26,65,72,26,67,74,26);
        drawTwelve(68,75,27,66,73,27,67,74,27,69,76,27);
        drawTwelve(70,77,28,68,75,28,69,76,28,71,78,28);
        drawTwelve(72,79,29,70,77,29,71,78,29,73,80,29);
        drawTwelve(74,81,30,72,79,30,73,80,30,75,82,30);
        drawTwelve(76,83,31,74,81,31,75,82,31,77,84,31);
        drawTwelve(78,85,32,76,83,32,77,84,32,79,86,32);
        drawTwelve(80,87,33,78,85,33,79,86,33,81,88,33);
        drawTwelve(82,89,34,80,87,34,81,88,34,83,90,34);
        drawTwelve(84,91,35,82,89,35,83,90,35,85,92,35);
        drawTwelve(86,93,36,84,91,36,85,92,36,87,94,36);
        drawTwelve(88,95,37,86,93,37,87,94,37,89,96,37);
        drawTwelve(90,97,38,88,95,38,89,96,38,91,98,38);
        drawTwelve(92,99,39,90,97,39,91,98,39,93,100,39);
        drawTwelve(94,101,40,92,99,40,93,100,40,95,102,40);
        drawTwelve(96,103,41,94,101,41,95,102,41,97,104,41);
        drawTwelve(98,105,42,96,103,42,97,104,42,99,106,42);
        drawTwelve(100,107,43,98,105,43,99,106,43,101,108,43);
        drawTwelve(51,52,44,100,107,44,101,108,44,53,53,44);
        drawTwelve(116,109,17,44,46,17,45,45,17,56,110,17);
        drawTwelve(49,111,45,104,112,45,103,113,45,102,114,45);
        drawTwelve(102,114,46,103,113,46,105,115,46,46,116,46);
        drawTwelve(47,43,17,49,117,17,50,118,17,48,44,17);
        drawTwelve(46,116,47,105,115,47,106,119,47,47,120,47);
        drawTwelve(47,120,15,106,119,15,104,112,15,49,111,15);
        drawTwelve(104,121,17,106,122,17,105,123,17,103,124,17);
        drawTwelve(24,125,17,22,126,17,96,127,17,98,128,17);
        drawTwelve(22,126,17,20,129,17,94,130,17,96,127,17);
        drawTwelve(20,129,17,18,131,17,92,132,17,94,130,17);
        drawTwelve(18,131,17,16,133,17,90,134,17,92,132,17);
        drawTwelve(16,133,17,14,135,17,88,136,17,90,134,17);
        drawTwelve(14,135,17,12,137,17,86,138,17,88,136,17);
        drawTwelve(12,137,17,10,139,17,84,140,17,86,138,17);

        glBegin(GL_POLYGON);
        drawthree(84,140,17);
        drawthree(10,139,17);
        drawthree(8,141,17);
        drawthree(6,142,17);
        drawthree(82,143,17);
        glEnd();

        drawTwelve(26,144,17,24,125,17,98,128,17,100,145,17);

        glBegin(GL_POLYGON);
        drawthree(2,47,17);
        drawthree(78,146,17);
        drawthree(80,147,17);
        glEnd();

        glBegin(GL_POLYGON);
        drawthree(76,50,17);
        drawthree(78,146,17);
        drawthree(2,47,17);
        glEnd();

        drawTwelve(6,142,17,2,47,17,80,147,17,82,143,17);

        glBegin(GL_POLYGON);
        drawthree(3,48,17);
        drawthree(107,148,17);
        drawthree(108,149,17);
        drawthree(72,150,17);
        drawthree(74,49,17);
        glEnd();

        drawTwelve(108,149,17,109,151,17,70,152,17,72,150,17);
        drawTwelve(109,151,17,110,153,17,68,154,17,70,152,17);
        drawTwelve(110,153,17,111,155,17,66,156,17,68,154,17);
        drawTwelve(111,155,17,112,157,17,64,158,17,66,156,17);
        drawTwelve(112,157,17,113,159,17,62,160,17,64,158,17);
        drawTwelve(113,159,17,114,161,17,60,162,17,62,160,17);
        drawTwelve(114,161,17,115,163,17,58,164,17,60,162,17);
        drawTwelve(115,163,17,116,109,17,56,110,17,58,164,17);
        drawTwelve(41,165,48,42,36,48,44,35,48,116,166,48);
        drawTwelve(40,167,49,41,165,49,116,166,49,115,168,49);
        drawTwelve(39,169,50,40,167,50,115,168,50,114,170,50);
        drawTwelve(38,171,51,39,169,51,114,170,51,113,172,51);
        drawTwelve(37,173,52,38,171,52,113,172,52,112,174,52);
        drawTwelve(36,175,53,37,173,53,112,174,53,111,176,53);
        drawTwelve(35,177,54,36,175,54,111,176,54,110,178,54);
        drawTwelve(34,179,55,35,177,55,110,178,55,109,180,55);
        drawTwelve(33,181,56,34,179,56,109,180,56,108,182,56);
        drawTwelve(32,183,57,33,181,57,108,182,57,107,184,57);
        drawTwelve(4,2,58,32,183,58,107,184,58,3,3,58);

        glBegin(GL_POLYGON);
        drawthree(52,185,59);
        drawthree(53,186,59);
        drawthree(101,187,59);
        drawthree(99,188,59);
        drawthree(97,189,59);
        drawthree(95,190,59);
        drawthree(93,191,59);
        drawthree(91,192,59);
        drawthree(89,193,59);
        drawthree(87,194,59);
        drawthree(85,195,59);
        drawthree(83,196,59);
        drawthree(81,197,59);
        drawthree(79,198,59);
        drawthree(77,199,59);
        drawthree(75,200,59);
        drawthree(73,201,59);
        drawthree(71,202,59);
        drawthree(69,203,59);
        drawthree(67,204,59);
        drawthree(65,205,59);
        drawthree(63,206,59);
        drawthree(61,207,59);
        drawthree(59,208,59);
        drawthree(57,209,59);
        drawthree(55,210,59);
        drawthree(54,211,59);
        glEnd();

        glBegin(GL_POLYGON);
        drawthree(49,117,17);
        drawthree(102,41,17);
        drawthree(30,40,17);
        drawthree(28,212,17);
        drawthree(51,213,17);
        drawthree(50,118,17);
        glEnd();

        glBegin(GL_POLYGON);
        drawthree(42,214,17);
        drawthree(41,215,17);
        drawthree(40,216,17);
        drawthree(39,217,17);
        drawthree(38,218,17);
        drawthree(37,219,17);
        drawthree(36,220,17);
        drawthree(35,221,17);
        drawthree(34,222,17);
        drawthree(33,223,17);
        drawthree(32,224,17);
        drawthree(4,225,17);
        drawthree(1,226,17);
        drawthree(5,227,17);
        drawthree(7,228,17);
        drawthree(9,229,17);
        drawthree(11,230,17);
        drawthree(13,231,17);
        drawthree(15,232,17);
        drawthree(17,233,17);
        drawthree(19,234,17);
        drawthree(21,235,17);
        drawthree(23,236,17);
        drawthree(25,237,17);
        drawthree(27,238,17);
        drawthree(29,239,17);
        drawthree(31,240,17);
        glEnd();

        drawTwelve(51,213,17,28,212,17,26,144,17,100,145,17);

        glPopMatrix();

        glPushMatrix();
        //glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex3i(0,500,0);
        glVertex3i(0,600,1);
        glVertex3i(700,600,1);
        glVertex3i(700,500,0);
        glEnd();
        glPopMatrix();
        //glutSwapBuffers();
    }

    void update()
    {
        if(!dead && liveState)
        {
            if(getZ()>0)
            {
                setZ(getZ()-0.05);
            }
            else
            {
                alive = true;
            }

            if(l)
                angle += 0.10f;
            else if(r)
                angle -= 0.10f;
            if (angle > 6) {
                l=false; r=true;
            }
            else if (angle < -6) {
                l=true; r=false;
            }

        }

    }

    void reflect()
    {
        glPushMatrix();
        initRendering();
        glColor4f(0.5,0.5,0.5,0.5);
        glTranslatef(0,-2,0);
        glScalef(1,-1,1);
        display();
        glPopMatrix();
    }

    void display()
    {
        glPushMatrix();

        glTranslatef(getX(), getY()-0.80,getZ()+0.50); //Move forward 5 units
        glScaled(0.3,0.3,0.3);

        glRotatef(5,1,0,0);
        glRotatef(180,0,1,0);
        glRotatef(rotationByZ,0,0,direction);
        glRotatef(rotateByX,1,0,0);

        glRotatef(angle,0,1,0);
        drawScene();
        glPopMatrix();
    }

    void createBoat()
    {
        glPushMatrix();
            initRendering();
            init();
            display();
            reflect();
        glPopMatrix();
    }

    void afterDead()
    {
        if(angle < 90)
            angle += 2;
        else
        {
            liveState = false;
            gameOverState = true;
        }
    }
};
