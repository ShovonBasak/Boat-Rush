#include <windows.h> //for Code::Blocks user
#include <GL/glut.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>

bool nightTex = false;

class skyTex{
public:
    skyTex()
    {
    }
    void setEnvironMent(bool environment)
    {
        nightTex=environment;
    }

void day(void){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        texture.init();
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(0.0, 0.0, 0.0,0.70);
        glRotatef(90,0,0,1);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.47);glVertex3f(-02.0, -60.0, -60.0);
            glTexCoord2f(1.0, 0.47);glVertex3f(-02.0, 60.0, -60.0);
            glTexCoord2f(1.0, 1.0);glVertex3f(30, 60.0, -60.0);
            glTexCoord2f(0.0, 1.0);glVertex3f(30, -60.0, -60.0);
        glEnd();
    glPopMatrix();
}

void night()
{
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[5]);
        texture.init();
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(0.0, 0.0, 0.0,0.70);
        glRotatef(90,0,0,1);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.47);glVertex3f(0.0, -300.0, -60.0);
            glTexCoord2f(1.0, 0.47);glVertex3f(0.0, 300.0, -60.0);
            glTexCoord2f(1.0, 1.0);glVertex3f(30, 300.0, -60.0);
            glTexCoord2f(0.0, 1.0);glVertex3f(30, -300.0, -60.0);
        glEnd();
    glPopMatrix();
}

void createSky()
{
    if(!nightTex)
    {
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                day();
            glPopMatrix();

            glPushMatrix();
                glColor4f(0.0, 0.0, 0.0,0.3);
                glScalef(1,-1,1);
                day();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
            glTranslatef(0,0,0);
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glPushMatrix();
                night();
        glPopMatrix();

        glPushMatrix();
                glColor4f(0.0, 0.0, 0.0,0.3);
                glScalef(1,-1,1);
                night();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPopMatrix();
    }

}
};
