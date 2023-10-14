#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int x_0, x_1, y_0, y_1;
double a = 0, b = 0, r = 50;
double dx = 0.5, dy = 0.5;
int colorGrad = 0;
int WIDTH = 800;
int HEIGHT = 400;



static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawPixel(double x, double y)
{
    if(colorGrad == 0) glColor3d(0,0,1);
    if(colorGrad == 1) glColor3d(1,0,0);
    if(colorGrad == 2) glColor3d(0,1,0);
    if(colorGrad == 3) glColor3d(1,1,1);
    glVertex2d(x, y);
}


void draw8way(double x, double y){
    drawPixel(x+a, y+b);
    drawPixel(y+a, x+b);
    drawPixel(-y+a, x+b);
    drawPixel(-x+a, y+b);
    drawPixel(-x+a, -y+b);
    drawPixel(-y+a, -x+b);
    drawPixel(y+a, -x+b);
    drawPixel(x+a, -y+b);
}

void drawCircle1(double r){
    double x = 0, y = r;
    double d = 5- 4*r;
    draw8way(x, y);
    while(x < y){
        if(d < 0){
            d += (2*x + 3) *4; // east
            x++;
        }else{
            d += (2*x - 2*y + 5) * 4; // south-east
            x++;
            y--;
        }
        draw8way(x, y);
    }
}




static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH/2, 0);
    glVertex2i(WIDTH/2-1, 0);
    glVertex2i(0, -HEIGHT/2);
    glVertex2i(0, HEIGHT/2-1);
    glEnd();

    glPointSize(1);
    glBegin(GL_POINTS);
    if (a + r >= WIDTH/2){
        dx *= -1;
        colorGrad = 0;
    }
    if (a - r <= -WIDTH/2){
         dx *= -1;
         colorGrad = 1;
    }
    if (b + r >= HEIGHT/2){
        dy *= -1;
        colorGrad = 2;
    }
    if (b - r <= -HEIGHT/2){
        dy *= -1;
        colorGrad = 3;
    }
    a += dx;
    b += dy;
    drawCircle1(r);
    glEnd();

    glutSwapBuffers();
}



static void idle(void)
{
    glutPostRedisplay();
}

// Program entry point

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Animation of moving circle");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
