#include <windows.h> //for Code::Blocks user
#include <GL/glut.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageWidth][checkImageHeight][3];

GLuint textures[10];
bool im;

char *arrayOfFileName[10]={"images/1.bmp",
                            "images/2.bmp",
                            "images/front.bmp",
                            "images/top.bmp",
                            "images/wood.bmp",
                            "images/ni.bmp",
                            "images/noise1.bmp",
                            "images/noise2.bmp"
                            };

struct Image {

    unsigned long sizeX;

    unsigned long sizeY;

    char *data;

};

typedef struct Image Image;



#define checkImageWidth 64

#define checkImageHeight 64

class Texture{
public:

void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageWidth; i++) {

        for (j = 0; j < checkImageHeight; j++) {

            c = ((((i&0x8)==0)^((j&0x8)==0)))*255;

            checkImage[i][j][0] = (GLubyte) c;

            checkImage[i][j][1] = (GLubyte) c;

            checkImage[i][j][2] = (GLubyte) c;

        }

    }

}

int ImageLoad(char *filename, Image *image) {

    FILE *file;

    unsigned long size; // size of the image in bytes.

    unsigned long i; // standard counter.

    unsigned short int planes; // number of planes in image (must be 1)

    unsigned short int bpp; // number of bits per pixel (must be 24)

    char temp; // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.

    if ((file = fopen(filename, "rb"))==NULL){

        printf("File Not Found : %s\n",filename);

        return 0;

    }

    // seek through the bmp header, up to the width/height:

    fseek(file, 18, SEEK_CUR);

    // read the width

    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {

        printf("Error reading width from %s.\n", filename);

        return 0;

    }

    //printf("Width of %s: %lu\n", filename, image->sizeX);

    // read the height

    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {

        printf("Error reading height from %s.\n", filename);

        return 0;

    }

    //printf("Height of %s: %lu\n", filename, image->sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).

    size = image->sizeX * image->sizeY * 3;

    // read the planes

    if ((fread(&planes, 2, 1, file)) != 1) {

        printf("Error reading planes from %s.\n", filename);

        return 0;

    }

    if (planes != 1) {

        printf("Planes from %s is not 1: %u\n", filename, planes);

        return 0;

    }

    // read the bitsperpixel

    if ((i = fread(&bpp, 2, 1, file)) != 1) {

        printf("Error reading bpp from %s.\n", filename);

        return 0;

    }

    if (bpp != 24) {

        printf("Bpp from %s is not 24: %u\n", filename, bpp);

        return 0;

    }

    // seek past the rest of the bitmap header.

    fseek(file, 24, SEEK_CUR);

    // read the data.

    image->data = (char *) malloc(size);

    if (image->data == NULL) {

        printf("Error allocating memory for color-corrected image data");

        return 0;

    }

    if ((i = fread(image->data, size, 1, file)) != 1) {

        printf("Error reading image data from %s.\n", filename);

        return 0;

    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)

        temp = image->data[i];

        image->data[i] = image->data[i+2];

        image->data[i+2] = temp;

    }

    // we're done.

    return 1;

}

Image * loadTexture(int index){

    Image *image1;

    // allocate space for texture

    image1 = (Image *) malloc(sizeof(Image));

    if (image1 == NULL) {

        printf("Error allocating space for image");

        exit(0);

    }

    if (!ImageLoad(arrayOfFileName[index], image1)) {

        exit(1);

    }


    return image1;

}

void myinit(void)
{

    glClearColor (0.5, 0.5, 0.5, 0.0);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    Image *image[10];
    image[0] = loadTexture(0);
    image[1] = loadTexture(1);
    image[2] = loadTexture(2);
    image[3] = loadTexture(3);
    image[4] = loadTexture(4);
    image[5] = loadTexture(5);
    image[6] = loadTexture(6);
    image[7] = loadTexture(7);

    /*if(image == NULL || image == NULL){

        printf("Image was not returned from loadTexture\n");

        exit(0);

    }*/

    makeCheckImage();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create Texture

    glGenTextures(10, textures);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[0]->sizeX, image[0]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[1]->sizeX, image[1]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[2]->sizeX, image[2]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[3]->sizeX, image[3]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[5]->sizeX, image[5]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[5]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[4]->sizeX, image[4]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[4]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[6]->sizeX, image[6]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[6]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[7]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //scale linearly when image smalled than texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image[7]->sizeX, image[7]->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image[7]->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBindTexture(GL_TEXTURE_2D, textures[9]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,

    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_FLAT);

}

void init(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

    GLfloat white_light[] = { 0.0, 0.0, 0.0, 0.20 };
    GLfloat lmodel_ambient[] = { 0.1, 0.20, 0.1, 1.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);

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

Texture texture;
