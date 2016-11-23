#include<GL/glut.h>

class Stone
{
    double xAxis;
    double yAxis;
    double zAxis;
    double size;
public:
    bool collided;
    Stone()
    {
        zAxis = -30;
        yAxis = -1.0;
        xAxis = 0;
        size = .1;
        collided = false;
    }
    void createStone()
    {
        glPushMatrix(); //Save the current state of transformations
        init();
        glTranslatef(getX(), getY(), getZ()); //Move to the center of the triangle
        glRotatef(90, 1.0, 0.0, 1.0);
        glScalef(getSize(), getSize(), getSize());
        glColor3f(0.50,0.50,0.50);
        glDisable(GL_COLOR_MATERIAL);
        glutSolidSphere(.4,4,3);
        glPopMatrix();

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
    void setSize(double size)
    {
        this->size = size;
    }
    void setY()
    {
        //yAxis -= .005;
    }
    void setZ()
    {
        zAxis += 0.3;
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
        size +=.007;
    }
    double getSize()
    {
        return size;
    }

    void reflect()
    {
        glPushMatrix();
        glTranslatef(0,-2,0);
        glScalef(1,-1,1);
        createStone();
        glPopMatrix();
    }

    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

        GLfloat white_light[] = { 0.50, 0.50, 0.50, 1.0 };
        GLfloat lmodel_ambient[] = { 0.1, 0.20, 0.1, 1.0 };

        //glClearColor(0.0, 0.0, 0.0, 0.0);

        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_DEPTH_TEST);
    }

};
