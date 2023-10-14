
/*
    Jahir Sadik Monon
    Roll: 32
    This is OPENGL code to animate a moving circle
        falling in the ground and shrinking into and ellipse
        and moving back up again.
    Press ENTER to move in time (increment time counter)
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define WIDTH 640
#define HEIGHT 480

double init_a = 0, init_b = 0;
double a = 0, b = 0;
double b_shrink = 0.5;
double initial_x = 0, initial_y = HEIGHT / 4;
double offset_x = 0, offset_y = 0;
double dx = 0.0, dy = -0.0, accelaration = -9.8;
double cum_dx = 0, cum_dy = 0;
double initial_area = 0;
double t = 0;
double t_step = 0.01;
int isFalling = 1;
int initial = 0;

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawPixel(double x, double y)
{
    glVertex2d(x, y);
}

void draw4way(double x, double y) {
    drawPixel(x + offset_x, y + offset_y);
    drawPixel(-x + offset_x, y + offset_y);
    drawPixel(-x + offset_x, -y + offset_y);
    drawPixel(x + offset_x, -y + offset_y);
}

void drawRegion1(double a, double b) {
    double x = 0, y = b;
    double d = 4*b*b - 4*a*a*b + a*a;
    draw4way(x, y);
    while ((2*b*b * x+2 * b*b) < (2*a*a*y - a*a)) {
        if (d < 0) {
            d += (2*b*b*x + 3*b*b)*4; // E
            x++;
        } else {
            d += (2*b*b*x + 3*b*b - 2*a*a - 2*a*a*y) * 4; // SE
            x++;
            y--;
        }
        draw4way(x, y);
    }
}

void drawRegion2(double a, double b) {
    double x = a, y = 0;
    double d = 4*a*a-4*a*b*b+b*b;
    draw4way(x, y);
    while ((2*b*b*x - b*b) >= (2*a*a*y + a*a)) {
        if (d < 0) {
            d += (2*a*a*y + 3*a*a) * 4; // E
            y++;
        } else {
            d += (2*a*a*y + 3*a*a - 2*b*b*x + 2*b*b)*4; // SE
            x--;
            y++;
        }
        draw4way(x, y);
    }
}

void drawEllipse() {
    drawRegion1(a, b);
    drawRegion2(a, b);
}

static void display(void)
{
    if (initial) {
        getchar();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(100, 100, 100);
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);

    if (isFalling && ((offset_y - b) <= -HEIGHT/2)) {
        dy = 0;
        b -= b_shrink;
        if (b <= init_b / 2) b_shrink *= -1;
        offset_y = -HEIGHT/2 + b;
        a = sqrt(initial_area - b * b);
        drawEllipse();
        if (b == init_b) {
            isFalling = 0;
            accelaration *= -1;
            t_step *= -1;
            b_shrink *= -1;
        }
    }
    else {
        drawEllipse();
        if ((offset_y) > HEIGHT/4) {
            accelaration *= -1;
            isFalling = 1;
        };
        t += t_step;
        dy = 0.5 * accelaration * t * t;
        cum_dy += dy;
        offset_y = initial_y + cum_dy;
    }

    glEnd();

    glutSwapBuffers();
    initial = 1;
}

static void idle(void)
{
    glutPostRedisplay();
}

// Program entry point

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition (0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ellipse Animation");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    offset_x = 0;
    offset_y = HEIGHT/4;

    init_a = 120;
    init_b = 100;
    a = init_a;
    b = init_b;
    initial_area = init_a * init_a + init_b * init_b;

    glutMainLoop();

    return EXIT_SUCCESS;
}
