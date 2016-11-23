#include<cstdlib>
#include<cstring>

GLUquadricObj *quadratic;

class Points{
    int coinsCollected;
    int previouslyCollectedCoins;
    int highestCoinCollection;
    int distanceTraveled;

public:
    double healthPoint;
    double healthBarSize;
    double healthBarX;
    char c[20];
    Points()
    {
        coinsCollected = 0;
        distanceTraveled = 0;
        healthPoint = 1.1;
        healthBarSize = 1.1;
        healthBarX = 1.1;
    }


    void readHighestCoinCollectionFromFile()
    {
        ifstream f("coins.txt");
            f>>highestCoinCollection;
        fclose(stdin);
    }

    int getHighestCoinCollection()
    {
        readHighestCoinCollectionFromFile();
        if(coinsCollected > highestCoinCollection)
            highestCoinCollection = coinsCollected;
        addCoins();
        return highestCoinCollection;
    }

    void mergeCoins()
    {
        if(coinsCollected != 0)
        {
            for(int i=1; i<=coinsCollected; i++)
                previouslyCollectedCoins+=coinValue;
        }
    }

    void addCoins()
    {
          ofstream myfile;
          myfile.open ("coins.txt");
          myfile <<highestCoinCollection;
          myfile.close();
    }

    void addNewCoin()
    {
        coinsCollected+=coinValue;
    }
    int getCollectedCoins()
    {
        return coinsCollected;
    }
    void mergeDistance()
    {
        distanceTraveled++;
    }
    int getdistanceTraveled()
    {
        return distanceTraveled;
    }
    void setHealth(double healthPoint)
    {
        this->healthPoint = healthPoint;
    }
    double getHealth()
    {
        return healthPoint;
    }
    void createHealthBar()
    {
        glPushMatrix();

        glPopMatrix();
    }

    void init(void)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 100.0 };
        GLfloat light_position[] = { 0.0, -1.0, 1.0, 0.0 };

        GLfloat white_light[] = { 0.0, 0.0, 0.55, 1.0 };
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


    void numberToChar(int number)
    {
        int i=0;
        if(number==0)
            c[i++]='0';
        else
            while(number!=0)
            {
                int remainder = number%10;
                c[i++]='0'+remainder;
                number = number/10;
            }
        strrev(c);
        c[i]='\0';
    }

    void pointsContainer()
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
                gluCylinder(quadratic,0.1f,0.1f,1.0f,32,32);
            glPopMatrix();
        glDisable(GL_LIGHTING);
        glPopMatrix();
    }

    void healthBar()
    {
        glPushMatrix(); //Save the current state of transformations
            glColor4f(0.50,0.50,0.50,0.50);
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_COLOR_MATERIAL);
            glEnable(GL_LIGHTING);
            glPushMatrix();
                    GLfloat light_position[] = { 0.0, 0.0, 0.10, 0.0 };
                    GLfloat white_light[] = { 1-healthBarX,healthBarX, 0.0, 0.0 };
                    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
                    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
                    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
                glRotatef(90, 0.0, 1.0, 0.0);
                glScalef(1.0, 1.0, 1.0);
                quadratic = gluNewQuadric();
                gluCylinder(quadratic,0.1f,0.1f,1.0f,32,32);
            glPopMatrix();
        glPopMatrix();
    }


};
