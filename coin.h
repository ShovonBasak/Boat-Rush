#include<fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<windows.h>
#include<string>

#include <GL/glut.h>
using namespace std;

class Coin{
    double xAxis;
    double yAxis;
    double zAxis;
    double size;
public:
    bool visible;
    Coin()
    {
        zAxis = 0;
        yAxis = -1.0;
        xAxis = 0;
        size = .005;
        visible = false;
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
    void setSize(double size)
    {
        this->size = size;;
    }
    double getSize()
    {
        return size;
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
    void resize()
    {
        size +=0.002;
    }

void createCoin()
{
    glPushMatrix();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5,0.5,0.5,0.5);
        glTranslatef(getX(), getY(), getZ()); //Move forward 5 units
        glScalef(getSize(),getSize(),getSize());
        glColor4f(0.8039,0.6275,0.0275,0.0);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        //initRendering();
        drawScene();
    glPopMatrix();
}
void reflection()
{
    glPushMatrix();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5,0.5,0.5,0.5);
        glScalef(1,-1,1);
        glTranslatef(0,2,0);
        createCoin();
        glDisable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPopMatrix();
}

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
//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)w / (double)h, 1.0, 200.0);
}
void circle(float r, float z,float line){
    glLineWidth(line);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<200; i++){
        float pi = 3.1416;
        float angle = (i*2*pi)/100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex3f(x+0.55,y+0.55,z);
    }
    glEnd();

}
void filledCircle(float r, float z){
    glLineWidth(10.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<100; i++){
        float pi = 3.1416;
        float angle = (i*2*pi)/100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex3f(x+0.55,y+0.55,z);
    }
    glEnd();

}

float angle = 0.0;
bool l=true,r=false;
float _cameraAngle = 0.0;
float translate = 0;
//Draws the 3D scene
void drawScene() {
    ///coin
    glPushMatrix();

    glRotatef(angle, 0,1,0);
    glPushMatrix();
    filledCircle(1.0,0.0);
    filledCircle(1.0,0.01);
    filledCircle(1.0,0.02);
    filledCircle(1.0,0.03);
    filledCircle(1.0,0.04);
    filledCircle(1.0,0.05);
    filledCircle(1.0,0.06);
    filledCircle(1.0,0.07);
    filledCircle(1.0,0.08);
    filledCircle(1.0,0.09);
    filledCircle(1.0,0.10);
    filledCircle(1.0,0.11);
    filledCircle(1.0,0.12);
    filledCircle(1.0,0.13);

    ///Silver Circle on Coin
    glColor3f(0.5,0.0,0.5);
   /// circle(0.6, 0.14, 10);
    ///circle(0.6, -0.01, 10);
    glPushMatrix();
    glTranslatef(0.55, 0.55, 0.14);
    gluDisk(gluNewQuadric(), 0.6, 0.7,50,20);
    glTranslatef(0.0, 0.0, -0.15);
    gluDisk(gluNewQuadric(), 0.6, 0.7,50,20);
    glPopMatrix();

    ///Green Circle on Coin
    glColor3f(0,1,0);
    ///circle(0.7, 0.14, 15);
    ///circle(0.7, -0.01, 15);
    glPushMatrix();
    glTranslatef(0.55, 0.55, 0.14);
    gluDisk(gluNewQuadric(), 0.7, 0.8,50,20);
    glTranslatef(0.0, 0.0, -0.15);
    gluDisk(gluNewQuadric(), 0.7, 0.8,50,20);
    glPopMatrix();

    ///Red Circle on Coin
    glColor3f(1,0,0);
    ///circle(0.8, 0.14, 25);
    ///circle(0.8, -0.01, 25);
    glPushMatrix();
    glTranslatef(0.55, 0.55, 0.14);
    gluDisk(gluNewQuadric(), 0.8, 1,50,20);
    glTranslatef(0.0, 0.0, -0.15);
    gluDisk(gluNewQuadric(), 0.8, 1,50,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05,0.1,0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.50, 0.30, 0.14);/// a
        glVertex3f(0.80, 0.10, 0.14);/// b
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.60, 0.50, 0.14);/// c
        glVertex3f(0.90, 0.65, 0.14);/// d
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(0.60, 0.65, 0.14);/// e
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.50, 0.95, 0.14);/// f
        glVertex3f(0.40, 0.65, 0.14);/// g
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.10, 0.65, 0.14);/// h
        glVertex3f(0.40, 0.50, 0.14);/// i
        glVertex3f(0.20, 0.10, 0.14); /// a

        glEnd();



    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.50, 0.30, -0.01);/// a
        glVertex3f(0.80, 0.10, -0.01);/// b
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.60, 0.50, -0.01);/// c
        glVertex3f(0.90, 0.65, -0.01);/// d
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(0.60, 0.65, -0.01);/// e
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.50, 0.95, -0.01);/// f
        glVertex3f(0.40, 0.65, -0.01);/// g
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(0.10, 0.65, -0.01);/// h
        glVertex3f(0.40, 0.50, -0.01);/// i
        glVertex3f(0.20, 0.10, -0.01); /// a

        glEnd();glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void update(int value) {
    angle += 3.10f;
	if (angle > 360) {
		angle=-360;
	}
}

};
//Initializes 3D rendering
