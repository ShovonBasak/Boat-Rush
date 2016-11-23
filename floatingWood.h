#include<GL/glut.h>

class FloatingWood
{
    double xAxis;
    double yAxis;
    double zAxis;
    double size;
public:
    FloatingWood()
    {
        zAxis = -25;
        yAxis = -1.0;
        xAxis = 0;
        size = .1;
    }
    void createWood()
    {
        glutSolidCube(.4);
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
        this->xAxis = x;
    }
    void setY()
    {
        //yAxis -= .005;
    }
    void setZ()
    {
        zAxis += 0.2;
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
        size +=.01;
    }
    double getSize()
    {
        return size;
    }
    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 0.0, 1.0, 0.0, 0.0 };

        GLfloat white_light[] = { 0.0, 0.0, 0.55, 1.0 };
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


        /*GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
        GLfloat white1_light[] = { 0.0, 1.0, 0.0, 1.0 };

        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white1_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, white1_light);

        glEnable(GL_LIGHT1);
        */
        glEnable(GL_DEPTH_TEST);
    }

};
