///*
//    Roll: 32, Jahir Sadik Monon
//*/
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <vector>
//#include <GL/glut.h>
//#include <algorithm>
//#include <stdio.h>
//#include <GL\freeglut.h>
//#include "bitmap.h"
//#include "game.h"
//#define M_PI acos(-1.0)
//
//struct BMPImage* drawImage;
//
//int WIDTH = 800, HEIGHT = 600;  // Width and height of the screen
//int MAX_HEIGHT = HEIGHT/2-1;
//int MIN_HEIGHT = -HEIGHT/2;
//int MAX_WIDTH = WIDTH/2-1;
//int MIN_WIDTH = -WIDTH/2;
//
//
//static void resize(int width, int height)
//{
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//// Utility functions
//float max(float a, float b){
//    return a >= b ? a : b;
//}
//
//float min(float a, float b){
//    return a < b ? a : b;
//}
//
//
//
//
//void reshape (int w, int h){
//    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluOrtho2D (-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1);
//    glMatrixMode (GL_MODELVIEW);
//    glLoadIdentity ();
//}
//
//
//
//
//
//void handleKeysSpecial(int key, int x, int y) {
//    switch(key) {
//        case GLUT_KEY_RIGHT:
//            // do something
//            break;
//        default:
//            break;
//    }
//}
//
//
//void handleKeys(unsigned char key, int x, int y) {
//    switch(key) {
//        case 'a':
//            // do something
//            break;
//        default:
//            break;
//    }
//}
//
//
//
//void display(){
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3d(100, 100, 100);
//    glBegin(GL_LINES);
//    glVertex2i(-WIDTH/2, 0);
//    glVertex2i(WIDTH/2, 0);
//    glVertex2i(0, -HEIGHT/2);
//    glVertex2i(0, HEIGHT/2);
//    glEnd();
//
//    glutSwapBuffers();
//}
//
//static void idle(void)
//{
//    glutPostRedisplay();
//}
//
//
//void update() {
//    // if we press 'x' exit the game
////    if (gIsKeyReleased('x')) {
////        gExit();
////    }
//}
//
//void draw() {
//    // lets draw our pixels from the BMP image
//    for (int r=0; r < drawImage->pixelHeight; r++) {
//        for (int c=0; c < drawImage->pixelWidth; c++) {
//            // opengl is rending from bottom to top but the pixel data is from top to bottom
//            // (I want to fix this later on in another video)
//            int invertRow = drawImage->pixelHeight - r - 1;
//            int index = invertRow * drawImage->pixelWidth + c;
//            struct BMPPixel* px = &drawImage->pixels[index];
//
//            // convert to opengl coords
//            float glX = gGetGLX(wld2scrX(c));
//            float glY = gGetGLY(wld2scrY(invertRow));
//            float w = gGetGLX(1); // 1 pixel tall and wide
//            float h = gGetGLX(1);
//
//            glBegin(GL_POLYGON);
//
//            glColor3f((float)px->r/255, (float)px->g/255, (float)px->b/255); // convert to floating point 0 to 1
//            glVertex2d(glX,     glY    ); // left bottom
//            glVertex2d(glX + w, glY    ); // right bottom
//            glVertex2d(glX + w, glY + h); // right top
//            glVertex2d(glX,     glY + h); // left top
//
//            glEnd();
//        }
//    }
//}
//
//void drawNegative() {
//    // lets draw our pixels from the BMP image
//    for (int r=0; r < drawImage->pixelHeight; r++) {
//        for (int c=0; c < drawImage->pixelWidth; c++) {
//            // opengl is rending from bottom to top but the pixel data is from top to bottom
//            // (I want to fix this later on in another video)
//            int invertRow = drawImage->pixelHeight - r - 1;
//            int index = invertRow * drawImage->pixelWidth + c;
//            struct BMPPixel* px = &drawImage->pixels[index];
//
//            // convert to opengl coords
//            float glX = gGetGLX(wld2scrX(c));
//            float glY = gGetGLY(wld2scrY(invertRow));
//            float w = gGetGLX(1); // 1 pixel tall and wide
//            float h = gGetGLX(1);
//
//            glBegin(GL_POLYGON);
//
//            glColor3f((255 - (float)px->r)/255, (255 - (float)px->g)/255, (255 - (float)px->b)/255); // convert to floating point 0 to 1
//            glVertex2d(glX,     glY    ); // left bottom
//            glVertex2d(glX + w, glY    ); // right bottom
//            glVertex2d(glX + w, glY + h); // right top
//            glVertex2d(glX,     glY + h); // left top
//
//            glEnd();
//        }
//    }
//}
//
//
//void drawH() {
//    // lets draw our pixels from the BMP image
//    for (int r=0; r < drawImage->pixelHeight; r++) {
//        for (int c=0; c < drawImage->pixelWidth; c++) {
//            // opengl is rending from bottom to top but the pixel data is from top to bottom
//            // (I want to fix this later on in another video)
//            int invertRow = drawImage->pixelHeight - r - 1;
//            int index = invertRow * drawImage->pixelWidth + c;
//            struct BMPPixel* px = &drawImage->pixels[index];
//
//            // convert to opengl coords
//            float glX = gGetGLX(wld2scrX(c));
//            float glY = gGetGLY(wld2scrY(invertRow));
//            float w = gGetGLX(1); // 1 pixel tall and wide
//            float h = gGetGLX(1);
//
//            glBegin(GL_POLYGON);
//            float r_norm = (float)px->r;
//            float g_norm = (float)px->g;
//            float b_norm = (float)px->b;
//            float maxRGB = max(max(r_norm, g_norm), b_norm);
//            float minRGB = min(min(r_norm, g_norm), b_norm);
//            float hue = 0.0;
//            if(maxRGB == r_norm){
//                hue = 60*((g_norm - b_norm)/(maxRGB-minRGB));
//            }
//            else if(maxRGB == g_norm){
//                hue = 120 + 60*((b_norm - r_norm)/(maxRGB-minRGB));
//            }
//            else{
//                hue = 240 + 60*((r_norm - g_norm)/(maxRGB-minRGB));
//            }
//            if(hue < 0.0){
//                hue += 360.0;
//                hue /= 360.0;
//                hue *= 240;
//            }
//            glColor3f(hue/240, hue/240, hue/240); // convert to floating point 0 to 1
//            glVertex2d(glX,     glY    ); // left bottom
//            glVertex2d(glX + w, glY    ); // right bottom
//            glVertex2d(glX + w, glY + h); // right top
//            glVertex2d(glX,     glY + h); // left top
//
//            glEnd();
//        }
//    }
//}
//
//void drawV() {
//    // lets draw our pixels from the BMP image
//    for (int r=0; r < drawImage->pixelHeight; r++) {
//        for (int c=0; c < drawImage->pixelWidth; c++) {
//            // opengl is rending from bottom to top but the pixel data is from top to bottom
//            // (I want to fix this later on in another video)
//            int invertRow = drawImage->pixelHeight - r - 1;
//            int index = invertRow * drawImage->pixelWidth + c;
//            struct BMPPixel* px = &drawImage->pixels[index];
//
//            // convert to opengl coords
//            float glX = gGetGLX(wld2scrX(c));
//            float glY = gGetGLY(wld2scrY(invertRow));
//            float w = gGetGLX(1); // 1 pixel tall and wide
//            float h = gGetGLX(1);
//
//            glBegin(GL_POLYGON);
//            float r_norm = (float)px->r/255;
//            float g_norm = (float)px->g/255;
//            float b_norm = (float)px->b/255;
//            float maxRGB = max(max(r_norm, g_norm), b_norm);
//            float minRGB = min(min(r_norm, g_norm), b_norm);
//            glColor3f(maxRGB, maxRGB, maxRGB); // convert to floating point 0 to 1
//            glVertex2d(glX,     glY    ); // left bottom
//            glVertex2d(glX + w, glY    ); // right bottom
//            glVertex2d(glX + w, glY + h); // right top
//            glVertex2d(glX,     glY + h); // left top
//
//            glEnd();
//        }
//    }
//}
//
//void drawS() {
//    // lets draw our pixels from the BMP image
//    for (int r=0; r < drawImage->pixelHeight; r++) {
//        for (int c=0; c < drawImage->pixelWidth; c++) {
//            // opengl is rending from bottom to top but the pixel data is from top to bottom
//            // (I want to fix this later on in another video)
//            int invertRow = drawImage->pixelHeight - r - 1;
//            int index = invertRow * drawImage->pixelWidth + c;
//            struct BMPPixel* px = &drawImage->pixels[index];
//
//            // convert to opengl coords
//            float glX = gGetGLX(wld2scrX(c));
//            float glY = gGetGLY(wld2scrY(invertRow));
//            float w = gGetGLX(1); // 1 pixel tall and wide
//            float h = gGetGLX(1);
//
//            glBegin(GL_POLYGON);
//            float r_norm = (float)px->r/255;
//            float g_norm = (float)px->g/255;
//            float b_norm = (float)px->b/255;
//            float maxRGB = max(max(r_norm, g_norm), b_norm);
//            float minRGB = min(min(r_norm, g_norm), b_norm);
//            float sat = 0.0;
//            if(maxRGB == 0){
//                sat = maxRGB;
//            }
//            else{
//                sat = (maxRGB-minRGB)/maxRGB;
//            }
//            glColor3f(sat, sat, sat); // convert to floating point 0 to 1
//            glVertex2d(glX,     glY    ); // left bottom
//            glVertex2d(glX + w, glY    ); // right bottom
//            glVertex2d(glX + w, glY + h); // right top
//            glVertex2d(glX,     glY + h); // left top
//
//            glEnd();
//        }
//    }
//}
//
//struct BMPImage* turnIntoNegative(struct BMPImage* bmp){
//    for(int i = 0; i < (int)bmp->arraySize; i++){
//        bmp->pixels->b = 255 - bmp->pixels->b;
//        bmp->pixels->r = 255 - bmp->pixels->r;
//        bmp->pixels->g = 255 - bmp->pixels->g;
//    }
//};
//
//
//int main (int argc, char **argv){
////    glutInit(&argc, argv);
////    glutInitWindowSize(WIDTH, HEIGHT);
////    glutInitWindowPosition(10, 10);
////    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//
//        // load our bitmap image
//    char *ch = "F:\\CSEDU semester 7\\CSE-4169 (Computer Graphics Lab)\\My OpenGL Codes\\GraphicsLabOne\\sample.bmp";
//    drawImage = loadBMP(ch);
//    if (drawImage == NULL) {
//        fprintf(stderr, "ERROR: failed to load BMP\n");
//        return 1;
//    }
//
//    //drawImage = turnIntoNegative(drawImage);
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE);
//
//    gSetup(argc, argv, drawImage->pixelWidth, drawImage->pixelHeight, false, update, draw);
//    gSetupNeg(argc, argv, drawImage->pixelWidth, drawImage->pixelHeight, false, update, drawNegative);
//    gSetupH(argc, argv, drawImage->pixelWidth, drawImage->pixelHeight, false, update, drawH);
//    gSetupV(argc, argv, drawImage->pixelWidth, drawImage->pixelHeight, false, update, drawV);
//    gSetupS(argc, argv, drawImage->pixelWidth, drawImage->pixelHeight, false, update, drawS);
//    glutMainLoop();
//    unloadBMP(drawImage);
//
//    return 0;
//}
//
//
