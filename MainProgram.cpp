#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <math.h>
#include<windows.h>
#include <GL/glut.h>


bool mainMenuState = true;
bool liveState = false;
bool gameOverState = false;
int level=0;
int coinValue = 0;
int objectUpdateTimer = 3000;
int updateTimer=30;
int jumpTimer=30;

#include"intToChar.h"
#include"textures.h"
#include"stone.h"
#include"wood.h"
#include"water.h"
#include"sky.h"
#include"tree1.h"
#include"tree2.h"
#include"3dBoat.h"
#include"collider.h"
#include"points.h"
#include"coinPattern.h"
#include"gameOverScene.h"
#include"mainMenu.h"

#define MAXOBJECTS 500

using namespace std;

double camera_Angle = 0;
//double zAxis = -20;
double yAxis = 0;


Stone stone[MAXOBJECTS];
Wood wood[MAXOBJECTS];
Water water;
skyTex sky;
Tree1 tree1[MAXOBJECTS];
Tree2 tree2[MAXOBJECTS];
Boat boat;
Collider collider(&boat);
Points point;
Coin iCoin;
GameOver gameOver;
MainMenuScene mainMenuScene;

int wi=-1;
int t1i=0;
int t2i=0;
int wk=0;
int t1k=0;
int t2k=0;
int minPos=-2,maxPos=-1;
int woodX;
signed int stoneX;
signed int i=-1;
int k=0;

signed int rand_interval(signed int min, signed int max)
{
    int r;
    const signed int range = 1 + max - min;
    const signed int buckets = RAND_MAX / range;
    const signed int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

void init()
{
   GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { 0.0, 3.0, 2.0, 0.0 };
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 0.0 };

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

void initializeLevelValues()
{
    if(level == 1)
    {
        objectUpdateTimer = 4000;
        point.healthPoint = 1.1;
        point.healthBarSize = 1.1;
        point.healthBarX = 1.1;
        coinValue = 1;
        updateTimer = 30;
        jumpTimer = 30;
    }
    else if(level == 2)
    {
        objectUpdateTimer = 2000;
        point.healthPoint = 0.5;
        point.healthBarSize = 0.5;
        point.healthBarX = 0.5;
        coinValue = 2;
        updateTimer =15;
        jumpTimer = 25;
    }
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

	gluPerspective(45.0, (double)w / (double)h, 2.0, 200.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0.0, 0.0, -3.6);
}

bool collidesWithStone(Boat boat, Stone stone)
{

    if((boat.getX() <= stone.getX() && boat.getX()+.1 >= stone.getX()+stone.getSize()) || (boat.getX()>= stone.getX() &&boat.getX()<= stone.getX()+stone.getSize()))
    {
        if(boat.getZ()>=stone.getZ() && boat.getZ()-1<= stone.getZ())
        {
            collider.collissionDetectedWithStone = true;
            collider.leftPart = true;
            return true;
        }
    }
    else if(boat.getX()+0.6 >= stone.getX() && (boat.getX()+0.6) <= stone.getX()+stone.getSize() )
    {
        if(boat.getZ()>=stone.getZ() && boat.getZ()-1<= stone.getZ())
        {
            collider.collissionDetectedWithStone = true;
            collider.rightPart = true;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool collidesWithWood(Boat boat, Wood wood)
{
    if(!collider.collissionDetectedWithWood && !boat.dead)
        if((boat.getX() >= wood.getX() && boat.getX() <= wood.getX()+wood.getSize()) || (boat.getX()+0.6 >= wood.getX() &&boat.getX()+0.6<= wood.getX()+wood.getSize()))
        {
            if(boat.getZ()>=wood.getZ() && boat.getZ()-0.4<= wood.getZ())
            {
                collider.collissionDetectedWithWood = true;
                return true;
            }
        }
        else
        {
            return false;
        }
}

void createWood()
{
    for(int j=wk; j<wi; j++)
    {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            wood[j].display();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        if(wood[j].getZ()>5)
            wk++;

        if(!collider.collissionDetectedWithWood)
            if(collidesWithWood(boat, wood[j]))
            {
                collider.jumpDone = false;;
            }

        if(wood[j].getZ() > 0)
            collider.collissionDetectedWithWood = false;
    }
}

void createStone()
{
    for(int j=k; j<i; j++)
    {
        glPushMatrix();
            stone[j].createStone();
            stone[j].reflect();
            glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        if(stone[j].getZ()>5)
            k++;

        if(!stone[j].collided && !boat.dead)
            if(collidesWithStone(boat, stone[j]))
            {
                collider.disPlace();
                collider.rotationDone = false;
                stone[j].collided= true;
                if(point.getHealth() > 0.2)
                    point.setHealth(point.getHealth()-0.2);
                else if(point.getHealth() > 0)
                {
                    point.setHealth(point.getHealth()-0.1);
                    boat.alive = false;
                }
            }
    }

}

bool collidesWithCoin(Boat boat, Coin *coin)
{
        if((boat.getX() >= coin->getX() && boat.getX() <= coin->getX()+coin->getSize()) || (boat.getX()+0.6 >= coin->getX() &&boat.getX()+0.6<= coin->getX()+coin->getSize()))
        {
            if(boat.getZ()>=coin->getZ() && boat.getZ()-0.3<= coin->getZ())
            {
                coin->visible = false;
                return true;
            }
        }
        else if((boat.getX() <= coin->getX() && (boat.getX()+0.6) >= coin->getX()) || (boat.getX() <= coin->getX()+coin->getSize()*2 && (boat.getX()+0.6) >= coin->getX()+coin->getSize()*2))
        {
            if(boat.getZ()>=coin->getZ() && boat.getZ()-0.5<= coin->getZ())
            {
                coin->visible = false;
                return true;
            }
        }
        else
        {
            return false;
        }
}

void createCoin()
{
    for(int j=0; j<20; j++)
    {
        glPushMatrix();
        if(coin[j].visible)
        {
            coin[j].createCoin();
            //coin[j].reflection();
            if(collidesWithCoin(boat, &coin[j]) && !boat.dead)
            {
                point.addNewCoin();
                coin[j].visible = false;
            }

        }

        glPopMatrix();



        if(coin[j].getZ() > 4.9)
            coin[j].visible = false;
    }
}

void createCoinCounter()
{
    //Coin Counter
    glPushMatrix();
        glTranslatef(0,0,boat.getZ());
        glPushMatrix();
            glTranslatef(-2.47,2.72,0.1);
            iCoin.setSize(0.15);
            iCoin.createCoin();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,1.8,0);
            glScalef(1.2,1.3,1);
            point.pointsContainer();
        glPopMatrix();

        glPushMatrix();
            glEnable(GL_COLOR_MATERIAL);
            glEnable(GL_LINE_SMOOTH);
            glTranslatef(-2.15,1.62,0.2);
            glScalef(.002,0.002,.001);
            glColor3f(1,1,1);
            point.numberToChar(point.getCollectedCoins());
            for(int i=0; point.c[i]!='\0'; i++)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, point.c[i]);
            }
        glPopMatrix();
    glPopMatrix();
}

void createTree()
{
    for(int j=t1k; j<t1i; j++)
    {
        glPushMatrix();
            tree1[j].createTree1();
        glPopMatrix();

        if(tree1[j].getZ()>5)
            t1k++;
    }

    for(int j=t2k; j<t2i; j++)
    {
        glPushMatrix();
            tree2[j].createTree2();
        glPopMatrix();

        if(tree2[j].getZ()>5)
            t2k++;
    }
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glTranslatef(0.0, 0.0, -5.0); //Move forward 5 units

    gameOver.gameOver();
    gameOver.totalCoin(&point);

    mainMenuScene.display();

    createCoinCounter();

    if(boat.alive)
    {
        glPushMatrix();
            glTranslatef(1.2,1.8,0);
            glTranslatef(1-point.healthBarX,0,0);
            glScalef(1.2,1.3,1);
            glScalef(point.healthBarX,1,1);
            point.healthBar();
        glPopMatrix();
    }

    createTree();

    createCoin();

    createStone();

    createWood();


    sky.createSky();

    water.createWater();

    boat.createBoat();

	glutSwapBuffers();
}

void update(int value)
{
    camera_Angle += 2;
    if(camera_Angle > 360)
    {
        camera_Angle -= 360;
    }
    if(!boat.dead)
    {
        for(int j=k; j<i; j++)
        {
            if(stone[j].getZ() < 5)
            {
                stone[j].setZ(stone[j].getZ()+.3);
                stone[j].resize();
                stone[j].setX(stone[j].getX()-0.00035);
            }
            else
            {
                k++;
            }
        }

        for(int j=wk; j<wi; j++)
        {
            if(wood[j].getZ() < 5)
            {
                wood[j].setZ(wood[j].getZ()+.3);
                wood[j].resize();
                wood[j].setX(wood[j].getX()-0.0029);
            }
            else
            {
                wk++;
            }
        }

        for(int j=t1k; j<t1i; j++)
        {
            if(tree1[j].getZ() < 5)
            {
                tree1[j].setZ(tree1[j].getZ()+.3);
                tree1[j].resize();
            }
            else
            {
                t1k++;
            }
        }

        for(int j=t2k; j<t2i; j++)
        {
            if(tree2[j].getZ() < 5)
            {
                tree2[j].setZ(tree2[j].getZ()+.3);
                tree2[j].resize();
            }
            else
            {
                t2k++;
            }
        }

        for(int j=0; j<20; j++)
        {
            if(coin[j].visible)
            {
                coin[j].setZ(coin[j].getZ()+.3);
                coin[j].resize();
                coin[j].setX(coin[j].getX()-0.003);
            }
            if(coin[j].getZ()> 4.9)
            {
                coin[j].visible = false;
            }

        }

    }

    if(point.getHealth() < point.healthBarX && !boat.dead)
    {
        point.healthBarX-=0.01;
        if(!boat.alive && point.healthBarX <= 0.1)
        {
            boat.dead = true;
        }

    }

    if(boat.dead)
    {
        gameOver.update();
        boat.afterDead();
        point.getHighestCoinCollection();
        point.mergeCoins();
        point.addCoins();
    }


    boat.update();

    glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(updateTimer, update, 0);
}

void updateWood_Stone(int value)
{
    if(boat.alive)
    {
        stoneX = rand_interval(-1,1);
        woodX = rand_interval(-1,1);

        if(i < MAXOBJECTS && !boat.dead)
        {
            stone[i++].setX(stoneX);
            if(i%3 == 0 && stoneX == woodX)
                afterStone(stoneX);
        }

        if(stoneX != woodX)
        {
            if(wi<MAXOBJECTS && !boat.dead)
            {
                wood[wi++].setX(woodX);
                if(addCoinPatternAfterWood)
                {
                    afterWood(woodX);
                    addCoinPatternAfterWood = false;
                }
                else
                    addCoinPatternAfterWood = true;
            }
        }
        if(level ==2 && stoneX == woodX)
        {
            if(stoneX == -1)
                stoneX = 0;
            else if(stoneX == 0)
                stoneX = 1;
            else if(stoneX == 1)
                stoneX = -1;

            stone[i++].setX(stoneX);
            stone[i-1].setZ(-35);
            stone[i-1].setSize(0.05);
        }
    }
	glutTimerFunc(objectUpdateTimer, updateWood_Stone, 0);
}

/*
void updateWood(int value)
{
    if(boat.alive)
    {
        woodX = rand_interval(-1,1);
        if(stoneX != woodX)
        {
            if(wi<MAXOBJECTS && !boat.dead)
            {
                wood[wi++].setX(woodX);
                if(addCoinPatternAfterWood)
                {
                    addCoinPatternAfterWood = false;
                    afterWood(woodX);
                }
                else
                    addCoinPatternAfterWood = true;
            }
        }
    }

	glutTimerFunc(objectUpdateTimer, updateWood, 0);
}
*/
void updateTree(int value)
{
    if(boat.alive)
    {
        if(minPos == -2)
        {
            minPos = 4;
            maxPos = 6;
        }
        else
        {
            minPos = -6;
            maxPos = -4;
        }

        int treeType = rand_interval(1,2);

        if(treeType == 1)
        {
            if(t1i<MAXOBJECTS && !boat.dead)
                tree1[t1i++].setX(rand_interval(minPos,maxPos));
        }
        else
        {
            if(t2i<MAXOBJECTS && !boat.dead)
                tree2[t2i++].setX(rand_interval(minPos,maxPos));
        }
    }




	glutTimerFunc(10000, updateTree, 0);
}

void waterUpdate(int value)
{
    if (im)
    {
        im = false;
    }
    else
    {
        im = true;
    }

    glutTimerFunc(100, waterUpdate, 0);
}

void jumpUpdate(int value)
{
    if (!collider.jumpDone){
        collider.jump();
    }

    glutTimerFunc(jumpTimer, jumpUpdate, 0);
}

void rotateUpdate(int value)
{
    if (!collider.rotationDone){
        collider.rotate();
    }

    glutTimerFunc(30, rotateUpdate, 0);
}

void stateChange(int value)
{
    if(!mainMenuState)
    {
        if(mainMenuScene.getY()<4)
        {
            mainMenuScene.setY(mainMenuScene.getY()+0.07);
        }
        else
        {
            liveState = true;
        }
    }

    glutTimerFunc(20, stateChange, 0);
}


void jetControl(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_LEFT:
            if(boat.getX() > -1.25 && !boat.dead)
                boat.move(-0.08);
            if(mainMenuState)
            {
                if(nightTex == true)
                    nightTex =false;
                else
                    nightTex = true;
            }
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            if(boat.getX() < 1.25 && !boat.dead)
                boat.move(+0.08);
            if(mainMenuState)
            {
                if(nightTex == true)
                    nightTex =false;
                else
                    nightTex = true;
            }
            glutPostRedisplay();
            break;

        default:
            break;
        }

}


void mouseClick(int button,int state, int x, int y)
{
    if(gameOverState)
    {
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                if(((double)x/glutGet(GLUT_WINDOW_WIDTH)>=0.225 && (double)x/glutGet(GLUT_WINDOW_WIDTH)<=0.80625 )&&
                   (((double)y/glutGet(GLUT_WINDOW_HEIGHT))>=0.56833 && (double)y/glutGet(GLUT_WINDOW_HEIGHT)<=0.66))
                   {
                       cout<<1;
                   }
                break;
                glutPostRedisplay();
            default:
                break;
        }
    }

    if(mainMenuState)
    {
        switch(button){
            case GLUT_LEFT_BUTTON:
                //cout<<(double)x/glutGet(GLUT_WINDOW_WIDTH)<<" "<< (double)y/glutGet(GLUT_WINDOW_HEIGHT)<<endl;
                if((((double)x/glutGet(GLUT_WINDOW_WIDTH)>=0.3)&& (double)x/glutGet(GLUT_WINDOW_WIDTH)<=0.48) &&
                (((double)y/glutGet(GLUT_WINDOW_HEIGHT)>= 0.4) && ((double)y/glutGet(GLUT_WINDOW_HEIGHT)<= 0.49)))
                {
                    level = 1;
                    mainMenuState = false;
                    glutTimerFunc(100, stateChange, 0);
                }
                else if((((double)x/glutGet(GLUT_WINDOW_WIDTH)>=0.52)&& (double)x/glutGet(GLUT_WINDOW_WIDTH)<=0.7) &&
                (((double)y/glutGet(GLUT_WINDOW_HEIGHT)>= 0.4) && ((double)y/glutGet(GLUT_WINDOW_HEIGHT)<= 0.49)))
                {
                    level = 2;
                    mainMenuState = false;
                    glutTimerFunc(100, stateChange, 0);
                }
                initializeLevelValues();
                break;
    }

    }

}

int main(int argc, char** argv)
{
    //Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	//Create the window
	glutCreateWindow("Nouka");

    texture.myinit();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	glutTimerFunc(35, jumpUpdate, 0);
	glutTimerFunc(70, rotateUpdate, 0);
	//glutTimerFunc(1500, updateWood, 0);
	glutTimerFunc(3000, updateWood_Stone, 0);
	glutTimerFunc(3000, updateTree, 0);
	glutTimerFunc(150, waterUpdate, 0);
	glutSpecialFunc(jetControl);
	glutMouseFunc(mouseClick);

	glutMainLoop();
	return 0;
}
