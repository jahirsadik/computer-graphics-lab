/*
*   Lab-05: Implementation of Cyrus-Beak LCA in OpenGL
*   Jahir Sadik Monon
*   Roll: 32
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


int WIDTH = 640, HEIGHT = 480;  // Width and height of the screen
int MAX_HEIGHT = HEIGHT/2-1;
int MIN_HEIGHT = -HEIGHT/2;
int MAX_WIDTH = WIDTH/2-1;
int MIN_WIDTH = -WIDTH/2;
int x_max = 100; // Clipping window max right
int x_min = -100; // Clipping window min left
int y_max = 100;  // Clipping window max up
int y_min = -100; // Clipping window min down



// Utility functions
float max(float a, float b){
    return a >= b ? a : b;
}

float min(float a, float b){
    return a < b ? a : b;
}

// Struct to store the point (x,y)
class Point {
public:
    int x, y;
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

};

// Function for creating a new point in between the line of two points P0 P1
//      the value of t is put into the parametric equation
Point Create_Point(Point p0,Point p1, float t){
    return Point((int)(p0.x+ t*(p1.x-p0.x)), (int)(p0.y + t*(p1.y-p0.y)));
}


// Line Drawing algorithms zone finding for given line endpoints
int findZone (int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    if (dx >= 0 and dy >= 0)
    {
        if (dx >= dy)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if (dx < 0 and dy >= 0)
    {
        if (-dx >= dy)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else if (dx < 0 and dy < 0)
    {
        if (-dx >= -dy)
        {
             return 4;
        }
        else
        {
             return 5;
        }
    }
    else
    {
        if (dx >= -dy)
        {
           return 7;
        }
        else
        {
             return 6;
        }
    }
}

// Drawing pixel with specific color
// The zone argument is used to do zone-0 to any zone conversion
void drawPixel (int x, int y, int zone, int color)
{
    if(color == 0){
        glColor3f(0.0, 1.0, 0.0);
    }
    if(color == 1){
        glColor3f(1.0, 0.0, 0.0);
    }
    if(color == 2){
        glColor3f(1.0, 0.0, 0.0);
    }
    switch (zone)
    {
    case 0:
        glVertex2i(x, y);
        break;
    case 1:
        glVertex2i(y, x);
        break;
    case 2:
        glVertex2i(-y, x);
        break;
    case 3:
        glVertex2i(-x, y);
        break;
    case 4:
        glVertex2i(-x, -y);
        break;
    case 5:
        glVertex2i(-y, -x);
        break;
    case 6:
        glVertex2i(y, -x);
        break;
    case 7:
        glVertex2i(x, -y);
        break;
    }
}

// DrawLine function for drawing a line from zone-0
void drawLine0 (int x0, int y0, int x1, int y1, int zone, int color)
{
    int dx = x1 - x0, dy = y1 - y0;
    int x = x0, y = y0, d = 2 * dy - dx;
    int de = 2 * dy, dne = 2 * (dy - dx);
    while (x <= x1)
    {
        drawPixel (x, y, zone, color);
        if (d < 0)
        {
            x++;
            d += de;
        }
        else
        {
            x++;
            y++;
            d += dne;
        }
    }
}


/*
    Zone Conversion Table
    Zone        Any-To-Zero
    0           (x,y) -> (x,y)
    1           (x,y) -> (y,x)
    2           (x,y) -> (y,-x)
    3           (x,y) -> (-x,y)
    4           (x,y) -> (-x,-y)
    5           (x,y) -> (-y,-x)
    6           (x,y) -> (-y,x)
    7           (x,y) -> (x,-y)
*/
// Finds zone, converts all to zone-0
//      processes in zone-0 but draws in original zone
void draw8way (int x0, int y0, int x1, int y1, int color)
{
    int zone = findZone(x0, y0, x1, y1);
    switch (zone)
    {
    case 0:
        drawLine0(x0, y0, x1, y1, zone, color);
        break;
    case 1:
        drawLine0(y0, x0, y1, x1, zone, color);
        break;
    case 2:
        drawLine0(y0, -x0, y1, -x1, zone, color);
        break;
    case 3:
        drawLine0(-x0, y0, -x1, y1, zone, color);
        break;
    case 4:
        drawLine0(-x0, -y0, -x1, -y1, zone, color);
        break;
    case 5:

        drawLine0(-y0, -x0, -y1, -x1, zone, color);
        break;
    case 6:

        drawLine0(-y0, x0, -y1, x1, zone, color);
        break;
    case 7:
        drawLine0(x0, -y0, x1, -y1, zone, color);
        break;
    }
}




void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}


// Draws a grid around the clipping window
void draw_grid(void){
    glBegin(GL_LINES);
    glVertex2i(x_min, MIN_HEIGHT);
    glVertex2i(x_min, MAX_HEIGHT);
    glVertex2i(x_max, MIN_HEIGHT);
    glVertex2i(x_max, MAX_HEIGHT);
    glVertex2i(MIN_WIDTH,   y_max);
    glVertex2i(MAX_WIDTH,  y_max);
    glVertex2i(MIN_WIDTH,  y_min);
    glVertex2i(MAX_WIDTH, y_min);
    glEnd();
}


// Implementation of the Cyrus Beak LCA for clipping one line
void cyrus_beak(int x0, int y0, int x1, int y1){
    float t_temp, temax = 0.0, tlmin = 1.0;


    t_temp = -(float)(x0-x_max)/(x1-x0);
    if((x1-x0)>=0){
        tlmin = min(tlmin, t_temp);

    } else{
        temax = max(temax, t_temp);
    }

    t_temp = -(float)(x0-(x_min))/(x1-x0);
    if(-(x1-x0)>=0){
        tlmin = min(tlmin, t_temp);
    } else{
        temax = max(temax, t_temp);
    }


    t_temp = -(float)(y0 - y_max)/(y1-y0);
    if(y1-y0>=0){
        tlmin = min(tlmin, t_temp);
    } else{
        temax = max(temax, t_temp);
    }

    t_temp = -(float)(y0-(y_min))/(y1-y0);
    if(-(y1-y0)>=0){
        tlmin = min(tlmin, t_temp);
    } else{
        temax = max(temax, t_temp);
    }

    t_temp = -(float)(x0-x_max)/(x1-x0);
    if((x1-x0)>=0){
        tlmin = min(tlmin, t_temp);

    } else{
        temax = max(temax, t_temp);
    }

    t_temp = -(float)(x0-(x_min))/(x1-x0);
    if(-(x1-x0)>=0){
        tlmin = min(tlmin, t_temp);
    } else{
        temax = max(temax, t_temp);
    }

    printf("For points (%d, %d, %d, %d): tlmin: %f\n", x0, y0, x1, y1, tlmin);
    printf("For points (%d, %d, %d, %d): temax: %f\n", x0, y0, x1, y1, temax);

    if(tlmin>=temax && tlmin<=1.0 && temax>=0.0){
        Point p0 = Create_Point(Point(x0,y0),Point(x1,y1),tlmin);
        Point p1 = Create_Point(Point(x0,y0),Point(x1,y1),temax);
        glEnd();
        glPointSize(5);
        glColor3f(1.0,1.0,1.0);

        glBegin(GL_POINTS);
        glVertex2i(p0.x,p0.y);
        glVertex2i(p1.x,p1.y);
        glVertex2i(x0,y0);
        glVertex2i(x1,y1);
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        draw8way(p0.x, p0.y, p1.x, p1.y, 0);
        draw8way(x0, y0, p1.x, p1.y, 2);
        draw8way(p0.x, p0.y, x1, y1, 2);
    }
    else{
        printf("Entirely Rejected. Case[Point:(%d, %d, %d, %d), tlmin: %f, tlmax: %f]\n", x0, y0, x1, y1, temax, tlmin);
        glEnd();
        glPointSize(5);
        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_POINTS);
        glVertex2i(x0,y0);
        glVertex2i(x1,y1);
        glEnd();
        glPointSize(1);
        glBegin(GL_POINTS);
        draw8way(x0, y0, x1, y1, 1);
        draw8way(x0, y0, x1, y1, 1);
    }

}

int myx0, myy0, myx1, myy1;
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    draw_grid();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    // if we randomly generated numbers
//    for (int i=0; i < 10; i++){
//        int x0 = (rand()%(2*MAX_WIDTH))-MAX_WIDTH;
//        int x1 = (rand()%(2*MAX_WIDTH))-MAX_WIDTH;
//        int y0 = (rand()%(2*MAX_HEIGHT))-MAX_HEIGHT;
//        int y1 = (rand()%(2*MAX_HEIGHT))-MAX_HEIGHT;
//        if(x0==x1) x0 += 1;
//        if(y0==y1) y0 += 1;
//        cyrus_beak(x0,y0,x1,y1);
//    }
    // if only the taken points are used to draw line
    cyrus_beak(myx0, myy0, myx1, myy1);
    glEnd();
    glFlush();
}


int main (int argc, char **argv){
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cyrus-Beak LCA");
    printf("Enter co-ordinates(x0, y0, x1, y1):\n");
    scanf("%d %d %d %d", &myx0, &myy0, &myx1, &myy1);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

