//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//
//#define Width 512
//#define Height 512
//static void display(void);
//static int slices = 16;
//static int stacks = 16;
//#define LINE_COUNT 10
//
//int lineCoords[LINE_COUNT][4];
//
//int ymax = Height/2, ymin = -Height/2, xmax = Width/2, xmin = -Width/2;
//double cx = 50, cy = -100;
//int x_0, x_1, y_0, y_1;
//double r = 50, a_ = r, b_ = r;
//double dx = 0.0, dy = -0.01, addx = 0, addy = 0;
//double t = 0;
//
//int generateRandX() {
//   return (rand() % Width) - Width/2;
//}
//
//int generateRandY() {
//   return (rand() % Height) - Height/2;
//}
//
//void generateLines() {
//   for (int i = 0; i < LINE_COUNT; i++) {
//       lineCoords[i][0] = generateRandX();
//       lineCoords[i][1] = generateRandY();
//       lineCoords[i][2] = generateRandX();
//       lineCoords[i][3] = generateRandY();
//   }
//}
//
//static void resize(int width, int height)
//{
//   const float ar = (float) width / (float) height;
//   glViewport(0, 0, width, height);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glOrtho(-Width/2, Width/2 - 1, -Height/2, Height/2 - 1, -1, 1);
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity() ;
//}
//
//int findZone (int x0, int y0, int x1, int y1)
//{
//   int dx = x1 - x0, dy = y1 - y0;
//   if (dx >= 0 and dy >= 0)
//   {
//       if (dx >= dy)
//       {
//           printf("GREEN\n");
//           return 0;
//       }
//       else
//       {printf("SKYBLUE\n");
//           return 1;
//       }
//   }
//   else if (dx < 0 and dy >= 0)
//   {
//       if (-dx >= dy)
//       {
//           printf("YELLOW\n");
//           return 3;
//       }
//       else
//       {
//          printf("PURPLE\n");
//           return 2;
//       }
//   }
//   else if (dx < 0 and dy < 0)
//   {
//       if (-dx >= -dy)
//       {
//            printf("RED\n");
//            return 4;
//       }
//       else
//       {
//            printf("BLUE\n");
//            return 5;
//       }
//   }
//   else
//   {
//       if (dx >= -dy)
//       {
//           printf("PINK\n");
//           return 7;
//       }
//       else
//       {
//            printf("WHITE\n");
//            return 6;
//       }
//   }
//}
//
//void drawPixel(double x, double y)
//{
//   glVertex2i(x, y);
//}
//
//
//void draw8way(int x, int y){
//   drawPixel(x+cx, y+cy);
//   drawPixel(y+cx, x+cy);
//   drawPixel(-y+cx, x+cy);
//   drawPixel(-x+cx, y+cy);
//   drawPixel(-x+cx, -y+cy);
//   drawPixel(-y+cx, -x+cy);
//   drawPixel(y+cx, -x+cy);
//   drawPixel(x+cx, -y+cy);
//}
//
//void drawCircle0(int r)
//{
//   int x = r, y = 0;
//   int d = 5 - 4*r;
//   draw8way(x, y);
//   while(x >= y)
//   {
//       if(d <= 0)
//       {
//           d += (2*y + 2) * 4; // north
//           y++;
//       }
//       else
//       {
//           d += (2*y - 2*x + 5) * 4; // north-west
//           x--;
//           y++;
//       }
//       draw8way(x,y);
//   }
//}
//
//void draw4way(double x, double y){
//   drawPixel(x+cx, y+cy);
//   drawPixel(y, x);
//   drawPixel(-y, x);
//   drawPixel(-x+cx, y+cy);
//   drawPixel(-x+cx, -y+cy);
//   drawPixel(-y, -x);
//   drawPixel(y, -x);
//   drawPixel(x+cx, -y+cy);
//}
//
//
//void drawEllipse(double a, double b){
//   int x = 0, y = b;
//   int d = 4*(b*b - a*a*b) + a*a;
//   draw4way(x, y);
//   while((2*b*b*x+2*b*b) < (2*a*a*y-a*a)){
//       if(d < 0){  // E
//           d += 4*b*b*(2*x +3);
//           x++;
//       }
//       else{		 // SE
//           d += 4*b*b*(2*x+3) + 4*a*a*(-2*y+2);
//           x++;
//           y--;
//       }
//       draw4way(x,y);
//   }
//   while(y > 0){
//       if(d > 0){	// S
//           d += 4*a*a*(-2*y+3);
//           y--;
//       }
//       else{			// SE
//           d += 4*a*a*(-2*y+3) + 4*b*b*(2*x+2);
//           y--;
//           x++;
//       }
//       draw4way(x,y);
//   }
//}
//
//int call;
//void myMouse (int button, int state, int x, int y)
//{
//   if (button == GLUT_LEFT_BUTTON and state == GLUT_UP)
//   {
//       ++call;
//   }
//}
//
//
//
//void keyPressed (unsigned char key, int x, int y) {
//   if (key == 'a'){
//       call++;
//   }
//}
//
//
//static void idle(void)
//{
//   glutKeyboardFunc(keyPressed);
//   glutPostRedisplay();
//   while(call % 2 == 0){
//           printf("%d\n", call);
//           display();
//   }
//}
//
//
//static void display(void)
//{
//   char ch;
//   scanf("%c", &ch);
//   glutKeyboardFunc(keyPressed);
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//   glColor3d(1,1,1);
//   if (dy < 0) dy = -(.5 * 9.8 * t);
//   else dy = (.5 * 9.8 * t);
//   glPointSize(2);
//   glBegin(GL_POINTS);
//   drawEllipse(a_,b_);
//   if(cx+a_>=xmax) dx*=-1; // collision with right wall
//   else if(cx-a_<=xmin) dx*=-1; // collision with left wall
//   if(cy+b_>=ymax-100){
//       dy*=-1; //collision with top wall
//       t = 0.0;
//   }
//
//   else if(cy-b_<=ymin){
//       dy*=-1; //collision with bottom wall
//       t = 0.0;
//       double tempa = a_, tempb = b_;
//       for(double i = 0; i < 3; i+= 0.1){
//           glClear(GL_COLOR_BUFFER_BIT);
//           glBegin(GL_POINTS);
//           a_ += i;
//           b_ = (r*r)/(a_+i);
//           drawEllipse(a_,b_);
//           glEnd();
//           glutSwapBuffers();
//       }
//       for(double i = 0; i < 3; i+= 0.1){
//           glClear(GL_COLOR_BUFFER_BIT);
//           glBegin(GL_POINTS);
//           a_ -= i;
//           b_ = (r*r)/(a_-i);
//           drawEllipse(a_,b_);
//           glEnd();
//           glutSwapBuffers();
//       }
//       a_ = tempa;
//       b_ = tempb;
//   }
//
//   t += 0.005;
//   cx += dx;
//   cy += dy;
//   glEnd();
//
//   glutSwapBuffers();
//}
//
//
//
//
//int main(int argc, char *argv[])
//{
//   glutInit(&argc, argv);
//   glutInitWindowSize(Width,Height);
//   glutInitWindowPosition(10,10);
//   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//   generateLines();
//   glutCreateWindow("Ellipse");
//   glutReshapeFunc(resize);
//   glutKeyboardFunc(keyPressed);
//   glutDisplayFunc(display);
//   glutIdleFunc(idle);
//
//   glutMainLoop();
//
//   return EXIT_SUCCESS;
//}
