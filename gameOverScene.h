#include <stdlib.h>
#include <GL/glut.h>




class GameOver{
    char gameOverText[20]="GAME OVER";
    char coins[20]="Max Collection ";
    double y=2.5;
    double z=5;
public:
    void gameOver()
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glTranslatef(-1.3,0,z);
                glPushMatrix();
                    glScalef(3.5,2.5,1);
                    glTranslatef(-0.1,0.05,-0.5);
                    container();
                glPopMatrix();
            glScalef(.003,0.003,.001);
            glColor3f(0.94,0.19,0.15);
            for(int i=0; gameOverText[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, gameOverText[i]);
            }
        glPopMatrix();
    }

    void totalCoin(Points* point)
    {
        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glTranslatef(-1.65,y+1.2,0.2);
            glScalef(.002,0.002,.001);
            glColor3f(1,1,1);
            numberToChar(point->getHighestCoinCollection());
            for(int i=0; coins[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, coins[i]);
            }
            for(int i=0; c[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, c[i]);
            }
        glPopMatrix();
    }

    void update()
    {
        if(y>=-0.6)
            y-=0.05;
        if(z>=0.15)
            z-=0.05;
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

};

