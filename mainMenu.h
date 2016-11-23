#include <stdlib.h>
#include <GL/glut.h>


class MainMenuScene{
    char promptText[20]="Select Game Mode";
    char beginnerText[10]="Beginner";
    char expertText[10]="Expert";
    double xAxis=0;
    double yAxis=0;
    double zAxis=0;
public:
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


    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 0.0, -1.0, 0.0, 0.0 };

        GLfloat white_light[] = { 0.50,0.65,0.56, 1.0 };
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

    void initRendering() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.1,0.1,0.91,1);
        glEnable(GL_LIGHTING); //Enable lighting
        glEnable(GL_LIGHT0); //Enable light #0
        glEnable(GL_LIGHT1); //Enable light #1
        glEnable(GL_SHADE_MODEL);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_TEXTURE);
        glEnable(GL_NORMALIZE);
    }

    void container()
    {
        glPushMatrix(); //Save the current state of transformations
            glColor4f(0.50,0.50,0.50,0.50);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);
            glPushMatrix();
                initRendering();
                init();
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(1.0, 1.0, 1.0);
                quadratic = gluNewQuadric();
                gluCylinder(quadratic,0.1f,0.1f,1.0f,55,55);
            glPopMatrix();
        glDisable(GL_LIGHTING);
        glPopMatrix();
    }

    void viewBoat(Boat* boat)
    {
        if(boat->alive)
        {
            if(boat->getZ()<=0)
                boat->setZ(boat->getZ()-0.3);
        }

    }

    void prompt()
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glEnable(GL_COLOR_MATERIAL);

            glTranslatef(-1.2,0.5,0.02);
            glScalef(.0015,0.002,.001);
            glColor3f(0.90,0.1,0.20);

            for(int i=0; promptText[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, promptText[i]);
            }
        glPopMatrix();
    }

    void beginner()
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glTranslatef(-1.10,0.0,0.02);
            if(nightTex)
                glColor3f(0.37,0.11,0.03);
            else
                glColor3f(0.05,0.29,0.40);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(0,0,0);
                    glVertex3f(0,0.4,0);
                    glVertex3f(1,0.4,0);
                    glVertex3f(1,0,0);
                glEnd();
            glPopMatrix();

            glTranslatef(0.1,0.10,0.02);
            glScalef(.001,0.002,.001);
            glColor3f(0.8,0.8,0.8);
            for(int i=0; beginnerText[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, beginnerText[i]);
            }
        glPopMatrix();
    }

    void expert()
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glTranslatef(0.10,0.0,0.02);
            if(nightTex)
                glColor3f(0.37,0.11,0.03);
            else
                glColor3f(0.05,0.29,0.40);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(0,0,0);
                    glVertex3f(0,0.4,0);
                    glVertex3f(1,0.4,0);
                    glVertex3f(1,0,0);
                glEnd();
            glPopMatrix();

            glTranslatef(0.1,0.10,0.02);
            glScalef(.001,0.002,.001);
            glColor3f(0.8,0.8,0.8);
            for(int i=0; expertText[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, expertText[i]);
            }
        glPopMatrix();
    }

    void display()
    {
        glPushMatrix();
            glTranslatef(getX(),getY(),getZ());
            prompt();
            beginner();
            expert();
        glPopMatrix();
    }
};





void selectOptions(int button,int state, int x, int y)
{


}

