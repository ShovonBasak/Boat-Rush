#include<GL/glut.h>

class Wood
{
    double xAxis;
    double yAxis;
    double zAxis;
    double size;
public:
    Wood()
    {
        zAxis = -30;
        yAxis = 0.0;
        xAxis = 0.0;
        size = 0.1;
    }
    void display()
    {
        glPushMatrix(); //Save the current state of transformations

        glBindTexture(GL_TEXTURE_2D, textures[4]);
        texture.init();
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(0.0, 0.0, 0.0,1.0);
        glTranslatef(getX(),getY()-1.1,getZ());
        glRotatef(-45,1,0,0);
        glScalef(getSize(),getSize(),1);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);glVertex3f(0.0, 0.0, 0.0);
            glTexCoord2f(1.0, 0.0);glVertex3f(0.0, 0.80, 0.0);
            glTexCoord2f(1.0, 1.0);glVertex3f(0.80, 0.80, 0.0);
            glTexCoord2f(0.0, 1.0);glVertex3f(0.80, 0.0, 0.0);
        glEnd();

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
        size +=.006;
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
        display();
        glPopMatrix();
    }

    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };

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

