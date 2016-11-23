#include<GL/glut.h>
#include<math.h>

class Water
{
public:
    Water()
    {

    }

void display(void){
    glPushMatrix();
        if(im)
        {
            glBindTexture(GL_TEXTURE_2D, textures[0]);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, textures[1]);
        }

        texture.init();

        glColor4f(0.0, 0.0, 0.0,0.08);
        for(double j=7; j>-50; j=j-5.66)
        {
            for(double i=-50; i<50; i=i+2)
            {
                glPushMatrix();
                    glTranslatef(i,-1,j);
                    glRotatef(90,0,0,1);
                    glRotatef(90,0,1,0);
                    glScalef(4,1,1);

                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
                        glTexCoord2f(1.0, 0.0);glVertex3f(1.0, 1.0, -1.0);
                        glTexCoord2f(1.0, 1.0);glVertex3f(2.41421, 1.0, -1.0);
                        glTexCoord2f(0.0, 1.0);glVertex3f(2.41421, -1.0, -1.0);
                    glEnd();
                glPopMatrix();
            }
        }
    glPopMatrix();
}

void createWater()
{
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_COLOR_MATERIAL);
        display();
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

};
