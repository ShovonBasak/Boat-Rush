#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <math.h>
#include<windows.h>

#include <GL/glut.h>


class Collider{
    bool heightReached;
    bool rotationReached;
    double rotation;
    Boat* boat;
public:
    bool leftPart;
    bool rightPart;
    bool jumpDone;
    bool rotationDone;
    bool collissionDetectedWithStone;
    bool collissionDetectedWithWood;
    bool collissionDetectedWithCoin;
    Collider(Boat* boat){
        this->boat = boat;
        leftPart=false;
        rightPart=false;
        heightReached = false;
        rotationReached = false;
        rotation=0;
        jumpDone = true;
        rotationDone = true;
        collissionDetectedWithStone = false;
        collissionDetectedWithWood = false;
        collissionDetectedWithCoin = false;
    }


    void disPlace(){
        if(leftPart)
        {
            boat->setDirection(1);
            boat->setX(boat->getX()+0.2);
        }

        if(rightPart)
        {
            boat->setDirection(-1);
            boat->setX(boat->getX()-0.2);
        }
    }


    void rotate()
    {
        if(rotationReached)
        {
            if(rotation>0)
            {
                rotation-=2;
                boat->setRotation(rotation);
            }
            else if(rotation<=0)
            {
                rotation = 0;
                boat->setRotation(rotation);
                rotationReached = false;
                rotationDone = true;
                leftPart=false;
                rightPart=false;
            }
        }
        else
        {
            if(rotation < 15)
            {
                rotation+=2;
                boat->setRotation(rotation);
            }
            else if(rotation>=15)
            {
                rotationReached = true;
            }
        }
    }

    void jump(){
        if(heightReached)
        {
            if(boat->getY()>0)
            {
                boat->setY(boat->getY()-0.09);
                if(boat->getRotateByX()<0)
                    boat->setRotateByX(boat->getRotateByX()+ 2.5);
            }
            else if(boat->getY() <= 0)
            {
                boat->setY(-0.02);
                heightReached = false;
                jumpDone = true;
                leftPart=false;
                rightPart=false;
            }
        }
        else
        {
            if(boat->getY()<0.8)
            {
                boat->setY(boat->getY()+0.09);
                if(boat->getRotateByX()>=-10)
                    boat->setRotateByX(boat->getRotateByX()- 2.5);
            }
            else if(boat->getY() >= 0.8)
            {
                heightReached = true;
            }
        }
    }
};

