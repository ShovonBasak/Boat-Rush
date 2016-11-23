#include <GL/glut.h>


class Tree1{
    double xAxis;
    double yAxis;
    double zAxis;
    double size;
    GLUquadricObj *quadratic;
public:
    Tree1()
    {
        zAxis = -50;
        yAxis = -1.0;
        xAxis = 0;
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
    void resize()
    {
        size +=.007;
    }

void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat white_light[] = { 0.48, 0.64, 0.38, 1.0 };
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


    /*GLfloat light1_position[] = { 0.0, 1.0, 1.0, 0.0 };
    GLfloat white1_light[] = { 0.0, 1.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white1_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white1_light);

    glEnable(GL_LIGHT1);
    */
    glEnable(GL_DEPTH_TEST);
}

void initStick(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat white_light[] = { 0.80, 0.40, 0.30, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.20, 0.1, 1.0 };

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

void initLand(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat white_light[] = { 0.37, 0.30, 0.29, 1.0 };
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


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//glClearColor(0.1,0.1,0.91,1);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_SHADE_MODEL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE);
	glEnable(GL_NORMALIZE);
}


void drawScene()
{
    //tree
    glPushMatrix();
        init();
        glRotatef(-90,1.0,0.0,0.0);
        glutSolidCone(.3,.5,10,10);
    glPopMatrix();

    glPushMatrix();
    init();
    glRotatef(-90,1.0,0.0,0.0);
    glTranslatef(0.0,0.0,-0.20);
    glutSolidCone(.3,.5,10,10);
    glPopMatrix();

    glPushMatrix();
    init();
    glRotatef(-90,1.0,0.0,0.0);
    glTranslatef(0.0,0.0,-0.40);
    glutSolidCone(.3,.5,10,10);
    glPopMatrix();

    //stick
    glPushMatrix();
    initStick();
    glRotatef(-90,1.0,0.0,0.0);
    glTranslatef(0.0,0.0,-0.70);

        quadratic = gluNewQuadric();
        gluCylinder(quadratic,0.05f,0.05f,0.50f,32,32);

    glPopMatrix();

    //land
    glPushMatrix(); //Save the current state of transformations
    glTranslatef(0.0,-1.0,0.0); //Move to the center of the triangle
    glRotatef(50, 0.50, 1.0, 0.0);
    glScalef(2,1,1);
    initLand();
    glutSolidSphere(.4,4,3);
    glPopMatrix();
}

void createTree1()
{    glPushMatrix();
        glColor3f(0.50,0.50,0.50);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
        glPushMatrix();
            initRendering();
            glTranslatef(getX(),getY(),getZ());
            glRotatef(0,0,0,0);
            glScalef(1,1,1);
            drawScene();
        glPopMatrix();

        glPushMatrix();
            initRendering();
            glColor4f(0.5,0.5,0.5,0.5);
            glTranslatef(getX(),getY()-2,getZ());
            glRotatef(0,0,0,0);
            glScalef(1,-1,1);
            drawScene();
        glPopMatrix();
    glPopMatrix();
}

};


