

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include <algorithm>



int WIDTH = 800, HEIGHT = 600;  // Width and height of the screen
int MAX_HEIGHT = HEIGHT/2-1;
int MIN_HEIGHT = -HEIGHT/2;
int MAX_WIDTH = WIDTH/2-1;
int MIN_WIDTH = -WIDTH/2;
float d = 300, L = 400, A = 200;
double transMatrix[4][4] = {0};
double primes[8][4];
float GPPM[4][4];

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

class Point3D {
public:
    float x, y, z;
    Point3D(float xVal = 0, float yVal = 0, float zVal = 0) {
        x = xVal;
        y = yVal;
        z = zVal;
    }
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    void setX(float xVal) { x = xVal; }
    void setY(float yVal) { y = yVal; }
    void setZ(float zVal) { z = zVal; }
};
Point3D p2D[8], p3D[8];
Point3D q;
 Utility functions
float max(float a, float b){
    return a >= b ? a : b;
}

float min(float a, float b){
    return a < b ? a : b;
}



 Line Drawing algorithms zone finding for given line endpoints
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

 Drawing pixel with specific color
 The zone argument is used to do zone-0 to any zone conversion
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

 DrawLine function for drawing a line from zone-0
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
 Finds zone, converts all to zone-0
      processes in zone-0 but draws in original zone
void draw8way (int x0, int y0, int x1, int y1, int color = 0)
{
    int zone = findZone(x0, y0, x1, y1);
    glBegin(GL_POINTS);
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
    glEnd();
}




void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}





void fillPoint3d(){
    p3D[0] = Point3D(-A, -A, A);
    p3D[1] = Point3D(A, -A, A);
    p3D[2] = Point3D(A, A, A);
    p3D[3] = Point3D(-A, A, A);
    p3D[4] = Point3D(-A, -A, -A);
    p3D[5] = Point3D(A, -A, -A);
    p3D[6] = Point3D(A, A, -A);
    p3D[7] = Point3D(-A, A, -A);
}

void fillPoint2d(float l, float d){
    p2D[0] = Point3D(-A, -A, A -l -d);
    p2D[1] = Point3D(A, -A, A-l -d);
    p2D[2] = Point3D(A, A, A-l -d);
    p2D[3] = Point3D(-A, A, A-l -d);
    p2D[4] = Point3D(-A, -A, -A-l -d);
    p2D[5] = Point3D(A, -A, -A-l -d);
    p2D[6] = Point3D(A, A, -A-l -d);
    p2D[7] = Point3D(-A, A, -A-l -d);
}


void multiplyMatrices(float firstMatrix[][4], float secondMatrix[][8], float multResult[][8], int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
     Initializing elements of multResult to 0
    for(int i = 0; i < rowFirst; ++i)
    {
        for(int j = 0; j < columnSecond; ++j)
        {
            multResult[i][j] = 0.0;
        }
    }

     Multiplying matrix firstMatrix and secondMatrix and storing in array multResult
    for(int i = 0; i < rowFirst; ++i)
    {
        for(int j = 0; j < columnSecond; ++j)
        {
            for(int k=0; k<columnFirst; ++k)
            {
                multResult[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void initialGPPM(Point3D q, float z_p) {
    GPPM[0][0] = 1;
    GPPM[0][1] = 0;
    GPPM[0][2] = - (q.x / q.z);
    GPPM[0][3] = z_p * (q.x / q.z);
    GPPM[1][0] = 0;
    GPPM[1][1] = 1;
    GPPM[1][2] = - (q.y / q.z);
    GPPM[1][3] = z_p * (q.y / q.z);
    GPPM[2][0] = 0;
    GPPM[2][1] = 0;
    GPPM[2][2] = - (z_p / q.z);
    GPPM[2][3] = z_p * (1 + z_p / q.z);
    GPPM[3][0] = 0;
    GPPM[3][1] = 0;
    GPPM[3][2] = - (1 / q.z);
    GPPM[3][3] = 1 + z_p / q.z;
}

void transformPoint2d(float l, float D, Point3D q){
    for(int i = 0; i < 8; i++){
        Point3D point = p2D[i];
        int x = point.x, y = point.y, z = point.z;
        int xp, yp, zp;
        xp = x/(-z/d);
        yp = y/(-z/d);
        zp = -d;
        p2D[i] = Point3D(xp, yp, zp);
    }
    float p2DTemp[4][8];
    float p2DTempAns[4][8];

    for(int i = 0; i < 8; i++){
        p2DTemp[0][i] = p2D[i].x;
        p2DTemp[1][i] = p2D[i].y;
        p2DTemp[2][i] = p2D[i].z;
        p2DTemp[3][i] = 1;
    }
     multiply  with GPPM (4*4) = (n,m) point2dTemp(4 * 8)
    initialGPPM(q, -D);

    multiplyMatrices(GPPM, p2DTemp, p2DTempAns, 4, 4, 4, 8);

    for(int i = 0; i < 8; i++){
        p2D[i].x = p2DTempAns[0][i]/p2DTempAns[3][i];
        p2D[i].y = p2DTempAns[1][i]/p2DTempAns[3][i];
        p2D[i].z = p2DTempAns[2][i]/p2DTempAns[3][i];
    }

    printf("\n\n");
    for(int i = 0; i < 8; i++){
        printf("%f %f %f %f\n", p2DTempAns[0][i], p2DTempAns[1][i], p2DTempAns[2][i], p2DTempAns[3][i]);
    }
    printf("\n\n");
}

void drawCube(){
    draw8way(p2D[0].x, p2D[0].y, p2D[1].x, p2D[1].y);
    draw8way(p2D[1].x, p2D[1].y, p2D[2].x, p2D[2].y);
    draw8way(p2D[2].x, p2D[2].y, p2D[3].x, p2D[3].y);
    draw8way(p2D[3].x, p2D[3].y, p2D[0].x, p2D[0].y);
    draw8way(p2D[4].x, p2D[4].y, p2D[5].x, p2D[5].y);
    draw8way(p2D[5].x, p2D[5].y, p2D[6].x, p2D[6].y);
    draw8way(p2D[6].x, p2D[6].y, p2D[7].x, p2D[7].y);
    draw8way(p2D[7].x, p2D[7].y, p2D[4].x, p2D[4].y);
    draw8way(p2D[3].x, p2D[3].y, p2D[7].x, p2D[7].y);
    draw8way(p2D[0].x, p2D[0].y, p2D[4].x, p2D[4].y);
    draw8way(p2D[2].x, p2D[2].y, p2D[6].x, p2D[6].y);
    draw8way(p2D[1].x, p2D[1].y, p2D[5].x, p2D[5].y);
}



void handleKeysSpecial(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_RIGHT:
            d+=10.0;
            printf("RIGHT\n");
            break;
        case GLUT_KEY_LEFT:
            d-=10.0;
            printf("LEFT\n");
            break;
        case GLUT_KEY_UP:
            L+=10.0;
            printf("UP\n");
            break;
        case GLUT_KEY_DOWN:
            L-=10.0;
            printf("DOWN\n");
            break;
        default:
            break;
    }
}


void handleKeys(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            q.x = q.x + 10;
            break;
        case 's':
            q.y = q.y + 10;
            break;
        case 'd':
            q.z = q.z + 10;
            break;
        case 'f':
            q.x = q.x - 10;
            break;
        case 'g':
            q.y = q.y - 10;
            break;
        case 'h':
            q.z = q.z - 10;
            break;
        default:
            break;
    }
}



void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(100, 100, 100);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH/2, 0);
    glVertex2i(WIDTH/2, 0);
    glVertex2i(0, -HEIGHT/2);
    glVertex2i(0, HEIGHT/2);
    glEnd();

    fillPoint3d();
    fillPoint2d(L, d);
    transformPoint2d(L, d, q);
    drawCube();

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}


int main (int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Lab on cube projection");
    q = Point3D(0, 0, d);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutSpecialFunc(handleKeysSpecial);
    glutKeyboardFunc(handleKeys);

    glutMainLoop();
    return 0;
}

