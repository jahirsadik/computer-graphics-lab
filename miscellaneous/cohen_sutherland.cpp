/*
*   Author: Jahir Sadik Monon
*   Roll: 32
*   This is an implementation of the Cohen-Sutherland
*       algorithm for line-clipping.
*/

//
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
//#include <GL/glut.h>
//
//int WIDTH = 1200, HEIGHT = 700;
//int MAX_HEIGHT = HEIGHT/2-1;
//int MIN_HEIGHT = -HEIGHT/2;
//int MAX_WIDTH = WIDTH/2-1;
//int MIN_WIDTH = -WIDTH/2;
//int Y_MAX = 100;
//int Y_MIN = -100;
//int X_MAX = 140;
//int X_MIN = -140;
//int TOP = 8;
//int BOTTOM = 4;
//int RIGHT = 2;
//int LEFT = 1;
//
//
//void reshape (int w, int h){
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity ();
//   gluOrtho2D (-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1); // size of projection plane (origin at the center)
//   glMatrixMode (GL_MODELVIEW);
//   glLoadIdentity ();
//}
//
////draws the grid
//void draw_grid(void){
//   glBegin(GL_LINES);
//   glVertex2i(X_MIN, MIN_HEIGHT);
//   glVertex2i(X_MIN, MAX_HEIGHT);
//   glVertex2i(X_MAX, MIN_HEIGHT);
//   glVertex2i(X_MAX, MAX_HEIGHT);
//
//   glVertex2i(MIN_WIDTH, Y_MAX);
//   glVertex2i(MAX_WIDTH, Y_MAX);
//   glVertex2i(MIN_WIDTH, Y_MIN);
//   glVertex2i(MAX_WIDTH, Y_MIN);
//   glEnd();
//}
//
//int findZone (int x0, int y0, int x1, int y1)
//{
//    int dx = x1 - x0, dy = y1 - y0;
//    if (dx >= 0 and dy >= 0)
//    {
//        if (dx >= dy)
//        {
//            return 0;
//        }
//        else
//        {
//            return 1;
//        }
//    }
//    else if (dx < 0 and dy >= 0)
//    {
//        if (-dx >= dy)
//        {
//            return 3;
//        }
//        else
//        {
//            return 2;
//        }
//    }
//    else if (dx < 0 and dy < 0)
//    {
//        if (-dx >= -dy)
//        {
//             return 4;
//        }
//        else
//        {
//             return 5;
//        }
//    }
//    else
//    {
//        if (dx >= -dy)
//        {
//           return 7;
//        }
//        else
//        {
//             return 6;
//        }
//    }
//}
//
//void drawPixel (int x, int y, int zone)
//{
//    switch (zone)
//    {
//    case 0:
//        glVertex2i(x, y);
//        break;
//    case 1:
//        glVertex2i(y, x);
//        break;
//    case 2:
//        glVertex2i(-y, x);
//        break;
//    case 3:
//        glVertex2i(-x, y);
//        break;
//    case 4:
//        glVertex2i(-x, -y);
//        break;
//    case 5:
//        glVertex2i(-y, -x);
//        break;
//    case 6:
//        glVertex2i(y, -x);
//        break;
//    case 7:
//        glVertex2i(x, -y);
//        break;
//    }
//}
//
//void drawLine0 (int x0, int y0, int x1, int y1, int zone)
//{
//    int dx = x1 - x0, dy = y1 - y0;
//    int x = x0, y = y0, d = 2 * dy - dx;
//    int de = 2 * dy, dne = 2 * (dy - dx);
//    while (x <= x1)
//    {
//        drawPixel (x, y, zone);
//        if (d < 0)
//        {
//            x++;
//            d += de;
//        }
//        else
//        {
//            x++;
//            y++;
//            d += dne;
//        }
//    }
//}
//
//
///*
//    Zone Conversion Table
//    Zone        Any-To-Zero
//    0           (x,y) -> (x,y)
//    1           (x,y) -> (y,x)
//    2           (x,y) -> (y,-x)
//    3           (x,y) -> (-x,y)
//    4           (x,y) -> (-x,-y)
//    5           (x,y) -> (-y,-x)
//    6           (x,y) -> (-y,x)
//    7           (x,y) -> (x,-y)
//*/
//
//void draw8way (int x0, int y0, int x1, int y1)
//{
//    int zone = findZone(x0, y0, x1, y1);
//    switch (zone)
//    {
//    case 0:
//        drawLine0(x0, y0, x1, y1, zone);
//        break;
//    case 1:
//        drawLine0(y0, x0, y1, x1, zone);
//        break;
//    case 2:
//        drawLine0(y0, -x0, y1, -x1, zone);
//        break;
//    case 3:
//        drawLine0(-x0, y0, -x1, y1, zone);
//        break;
//    case 4:
//        drawLine0(-x0, -y0, -x1, -y1, zone);
//        break;
//    case 5:
//
//        drawLine0(-y0, -x0, -y1, -x1, zone);
//        break;
//    case 6:
//
//        drawLine0(-y0, x0, -y1, x1, zone);
//        break;
//    case 7:
//        drawLine0(x0, -y0, x1, -y1, zone);
//        break;
//    }
//}
//
//
//
//int makeCode(int x,int y){
//   int code = 0;
//   if(y > Y_MAX){
//       code+=TOP;
//   }
//   else if(y < Y_MIN){
//       code+=BOTTOM;
//   }
//   if(x > X_MAX){
//       code+=RIGHT;
//   }
//   else if(x < X_MIN){
//       code+=LEFT;
//   }
//   return code;
//}
//
//void clipLine_cohen_sutherland(int x0, int y0, int x1, int y1){
//   glPointSize(1);
//   glBegin(GL_POINTS);
//
//
////   int x0_ = x0;
////   int x1_ = x1;
////   int y0_ = y0;
////   int y1_ = y1;
//   int code0, code1;
//   code0 = makeCode(x0, y0);
//   code1 = makeCode(x1, y1);
//   while(1){
//       if((code0|code1) == 0){
//           glEnd();
////           //glPointSize(5);
////           //glColor3f(1.0,1.0,1.0);
//           glBegin(GL_POINTS);
//           glVertex2i(x0, y0);
//           glVertex2i(x1, y1);
//           glEnd();
//           glPointSize(1);
//           glColor3f(1.0, 0.0, 0.0);
//           glBegin(GL_POINTS);
//           draw8way(x0, y0, x1, y1);
//           break;
//       } else if(code0 & code1){
//           glColor3f(0.0, 1.0, 0.0);
//           draw8way(x0, y0, x1, y1);
//           break;
//       }
//       else{
//           int code, x, y;
//           if(code0){
//               code = code0;
//           } else{
//               code  = code1;
//           }
//           if(code & TOP){
//               y = Y_MAX;
//               x = x0 + (y - y0)*(x1 - x0)/(y1 - y0);
//           }
//           else if(code & BOTTOM){
//               y = Y_MIN;
//               x = x0 + (y - y0)*(x1 - x0)/(y1 - y0);
//           }
//           else if(code & RIGHT){
//               x = X_MAX;
//               y = y0 + (x - x0)*(y1 - y0)/(x1 - x0);
//           }
//           else if(code & LEFT){
//               x = X_MIN;
//               y = y0 + (x - x0)*(y1 - y0)/(x1 - x0);
//           }
//           if(code == code0){
//               glColor3f(0.0, 1.0, 0.0);
//               draw8way(x0, y0, x, y);
//               x0 = x;
//               y0 = y;
//               code0 = makeCode(x0, y0);
//           }
//           else{
//               glColor3f(0.0, 1.0, 0.0);
//               draw8way(x1, y1, x, y);
//               x1 = x;
//               y1 = y;
//               code1 = makeCode(x1, y1);
//           }
//       }
//   }
//   glEnd();
//}
//
//
//
//
//void display(){
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3f(1.0,1.0,1.0);
//   draw_grid();
//   // Loop to generate random endpoints for lines
//   for (int i=0;i < 2000;i++){
//       int x0 = (rand()%(2*MAX_WIDTH))-MAX_WIDTH;
//       int x1 = (rand()%(2*MAX_WIDTH))-MAX_WIDTH;
//       int y0 = (rand()%(2*MAX_HEIGHT))-MAX_HEIGHT;
//       int y1 = (rand()%(2*MAX_HEIGHT))-MAX_HEIGHT;
//       clipLine_cohen_sutherland(x0,y0,x1,y1);
//   }
//   glFlush();
//}
//
//
//
//int main (int argc, char **argv){
//   glutInit (&argc, argv);
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
//   glutInitWindowSize (WIDTH, HEIGHT);
//   glutInitWindowPosition (0, 0);
//   glutCreateWindow ("Line Clipping Using Cohen Sutherland Algorithm");
//   glutReshapeFunc(reshape);
//   glutDisplayFunc (display);
//   glutMainLoop();
//   return 0;
//}
