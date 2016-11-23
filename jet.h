#include<GL/glut.h>


//GLUquadricObj *quadratic;
class Jet
{
    double xAxis;
    double yAxis;
    double zAxis;
    int health;
    double size;
public:
    Jet()
    {
        zAxis = 0;
        yAxis = 0.0;
        xAxis = 0.0;
        size = .1;
        setHealth(3);
    }
    void createJet()
    {
        glPushMatrix(); //Save the current state of transformations
        glTranslatef(getX(), -0.90, getZ()); //Move to the center of the triangle
        glRotatef(0, 0.0, 0.0, 0.0);
        glScalef(1.0, 1.0, 1.0);
        //init();
        glColor3f(0.3,0.4,0.9);
        quadratic = gluNewQuadric();
        gluCylinder(quadratic,0.1f,0.1f,2.0f,32,32);
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

        GLfloat white_light1[] = { 0.0, 0.0, 0.55, 1.0 };
        GLfloat lmodel_ambient[] = { 0.1, 0.20, 0.1, 1.0 };

        //glClearColor(0.0, 0.0, 0.0, 0.0);

        glShadeModel(GL_SMOOTH);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glLightfv(GL_LIGHT1, GL_POSITION, light_position);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light1);
        glLightfv(GL_LIGHT1, GL_SPECULAR, white_light1);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glEnable(GL_DEPTH_TEST);
    }

};
