#include <stdlib.h>
#include <GL/glut.h>
#include"coin.h"
Coin coin[20];
bool addCoinPatternAfterStone;
bool addCoinPatternAfterWood;
void afterWood(double woodX)
{
    coin[0].setZ(-32);
    coin[1].setZ(-33.5);
    coin[2].setZ(-35);
    coin[3].setZ(-36.5);

    coin[0].setSize(0.001);
    coin[1].setSize(0.001);
    coin[2].setSize(0.001);
    coin[3].setSize(0.001);

    coin[0].setX(woodX+0.2);
    coin[1].setX(woodX+0.2);
    coin[2].setX(woodX+0.2);
    coin[3].setX(woodX+0.2);

    coin[0].setY(-0.5);
    coin[1].setY(-0.3);
    coin[2].setY(-0.5);
    coin[3].setY(-0.9);

    coin[0].visible = true;
    coin[1].visible = true;
    coin[2].visible = true;
    coin[3].visible = true;
}

void afterStone(double stoneX)
{
    if(addCoinPatternAfterStone)
    {
        if(stoneX == -1)
            stoneX = 1;
        else if(stoneX == 0)
            stoneX = -1;
        else if(stoneX == 1)
            stoneX = 0;

        coin[5].setZ(-31);
        coin[6].setZ(-33);
        coin[7].setZ(-35);
        coin[8].setZ(-37);
        coin[9].setZ(-39);
        coin[10].setZ(-40);

        coin[5].setSize(0.003);
        coin[6].setSize(0.003);
        coin[7].setSize(0.003);
        coin[8].setSize(0.003);
        coin[9].setSize(0.0043);
        coin[10].setSize(0.0043);

        coin[5].setX(stoneX+0.1);
        coin[6].setX(stoneX+0.2);
        coin[7].setX(stoneX+0.3);
        coin[8].setX(stoneX+0.4);
        coin[9].setX(stoneX+0.5);
        coin[10].setX(stoneX+0.6);

        coin[5].visible = true;
        coin[6].visible = true;
        coin[7].visible = true;
        coin[8].visible = true;
        coin[9].visible = true;
        coin[10].visible = true;
    }
    else
    {
        addCoinPatternAfterStone = true;
    }


}
