//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>
//#include <GL/glut.h>
//
//
//int Wi=640, He=480;
//
////##############################Define Variables here###########################
//int maxy =He/2-1 ;
//int miny =-He/2 ;
//int maxx =Wi/2-1 ;
//int minx =-Wi/2 ;
//int top = 8;
//int bottom = 4;
//int right_ = 2;
//int left_ = 1;
//
//class Point {
//
//public:
//   int x, y;
//   Point(int x1, int y1)
//   {
//       x = x1;
//       y = y1;
//   }
//
//};
//
////##############################################################################
//
//
//void myInit (void);
//void display(void);
//void reshape (int w, int h);
//void draw_grid(void);
////##############################Define Prototypes here###########################
//int get_zone(int x_0,int y_0, int x_1, int y_1);
//void drawline_midpoint(int x_0,int y_0, int x_1, int y_1,int zone);
//void draw_vertex(int x, int y, int zone);
//void draw_line(int x_0,int y_0, int x_1, int y_1,int col);
//void clipline_cyrus_beak(int x0,int y0,int x1,int y1);
//Point find_t(Point p0,Point p1, float t);
////##############################################################################
//
//void myInit (void){
//   glClearColor(0.0, 0.0, 0.0,1.0);
//}
//
//void reshape (int w, int h){
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//   glMatrixMode (GL_PROJECTION);
//   glLoadIdentity ();
//   gluOrtho2D (-Wi/2, Wi/2-1, -He/2, He/2-1); // size of projection plane (origin at the center)
//   glMatrixMode (GL_MODELVIEW);
//   glLoadIdentity ();
//}
//
////draws the grid
//void draw_grid(void){
//   glBegin(GL_LINES);
//   glVertex2i(-140,miny);
//   glVertex2i(-140,maxy);
//   glVertex2i(140,miny);
//   glVertex2i(140,maxy);
//   glVertex2i(minx,100);
//   glVertex2i(maxx,100);
//   glVertex2i(minx,-100);
//   glVertex2i(maxx,-100);
//
//   glEnd();
//}
//
//Point find_t(Point p0,Point p1, float t){
//   return Point((int)(p0.x+t*(p1.x-p0.x)),(int)(p0.y+t*(p1.y-p0.y)));
//}
//
//int inpx0, inpx1, inpy0, inpy1;
////generates rand integers for origin and radius of circles and draws them
//void display(){
//   glClear(GL_COLOR_BUFFER_BIT);
//   glColor3f(0.2, 0.2, 0.2);
//
//   draw_grid();
//
//   glColor3f(1.0, 1.0, 1.0);
//   glBegin(GL_POINTS);
//
//   clipline_cyrus_beak(inpx0, inpy0, inpx1, inpy1)
//   glEnd();
//   glFlush();
//}
//
//void clipline_cyrus_beak(int x0,int y0,int x1,int y1){
//   float t,temax = 0.0,tlmin = 1.0;
//
//   t = -(float)(y0-100)/(y1-y0);
//   if(y1-y0>=0){
//       tlmin = min(tlmin,t);
//   } else{
//       temax = max(temax,t);
//   }
//
//   t = -(float)(y0-(-100))/(y1-y0);
//   if(-(y1-y0)>=0){
//       tlmin = min(tlmin,t);
//   } else{
//       temax = max(temax,t);
//   }
//
//   t = -(float)(x0-140)/(x1-x0);
//   if((x1-x0)>=0){
//       tlmin = min(tlmin,t);
//
//   } else{
//       temax = max(temax,t);
//   }
//
//   t = -(float)(x0-(-140))/(x1-x0);
//   if(-(x1-x0)>=0){
//       tlmin = min(tlmin,t);
//   } else{
//       temax = max(temax,t);
//   }
//   printf("tlmin: %f\n", tlmin);
//   printf("temax: %f\n", temax);
//
//   if(tlmin<=1.0 && temax>=0.0 && tlmin>=temax){
//       Point p0 = find_t(Point(x0,y0),Point(x1,y1),tlmin);
//       Point p1 = find_t(Point(x0,y0),Point(x1,y1),temax);
//       glEnd();
//       glPointSize(5);
//       glColor3f(1.0,1.0,1.0);
//
//       glBegin(GL_POINTS);
//       glVertex2i(p0.x,p0.y);
//       glVertex2i(p1.x,p1.y);
//       glVertex2i(x0,y0);
//       glVertex2i(x1,y1);
//       glEnd();
//       glPointSize(1);
//       glBegin(GL_POINTS);
//       draw_line(p0.x,p0.y,p1.x,p1.y,0);
//       draw_line(x0,y0,p1.x,p1.y,2);
//       draw_line(p0.x,p0.y,x1,y1,2);
//   }
//   else{
//       printf("Rejected\n");
//       glEnd();
//       glPointSize(5);
//       glColor3f(1.0,1.0,1.0);
//
//       glBegin(GL_POINTS);
//       glVertex2i(x0,y0);
//       glVertex2i(x1,y1);
//       glEnd();
//       glPointSize(1);
//       glBegin(GL_POINTS);
//       draw_line(x0,y0,x1,y1,1);
//   }
//
//}
//
////draws line by using midpoint line drawing algorithm for zone 0 after necessary transformation
////uses different colors for different zones
//void draw_line(int x_0,int y_0, int x_1, int y_1,int col){
//   if(col==0){
//       glColor3f(0.0, 1.0, 0.0);
//   }
//   if(col==1){
//       glColor3f(1.0, 0.0, 0.0);
//   }
//   if(col==2){
//       glColor3f(0.5, 0.5, 0.5);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 0){
//       drawline_midpoint(x_0,y_0,x_1,y_1, 0);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 1){
//       drawline_midpoint(y_0,x_0,y_1,x_1,1);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 2){
//       drawline_midpoint(y_0,-x_0,y_1,-x_1,2);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 3){
//       drawline_midpoint(-x_0,y_0,-x_1,y_1,3);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 4){
//       drawline_midpoint(-x_0,-y_0,-x_1,-y_1,4);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 5){
//       drawline_midpoint(-y_0,-x_0,-y_1,-x_1,5);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 6){
//       drawline_midpoint(-y_0,x_0,-y_1,x_1,6);
//   }
//   if (get_zone(x_0,y_0,x_1,y_1) == 7){
//       drawline_midpoint(x_0,-y_0,x_1,-y_1,7);
//   }
//}
//
////midpoint line drawing algorithm for zone 0
//void drawline_midpoint(int x_0,int y_0, int x_1, int y_1, int zone){
//   int dx = x_1 - x_0;
//   int dy = y_1 - y_0;
//   int d = 2*dy - dx;
//   int de = 2*dy;
//   int den = 2*(dy-dx);
//   int x,y;
//   x= x_0;
//   y= y_0;
//
//   draw_vertex(x,y,zone);
//   while(x<x_1){
//       if(d<0){
//           x++;
//           d+=de;
//       }
//       else{
//           x++;
//           y++;
//           d+=den;
//       }
//       draw_vertex(x,y,zone);
//   }
//}
//
////draws the pixel using 8 way symmetry
//void draw_vertex(int x, int y, int zone){
//   if(zone==0)
//       glVertex2i(x,y);
//   else if(zone==1)
//       glVertex2i(y,x);
//   else if(zone==2)
//       glVertex2i(-y,x);
//   else if(zone==3)
//       glVertex2i(-x,y);
//   else if(zone==4)
//       glVertex2i(-x,-y);
//   else if(zone==5)
//       glVertex2i(-y,-x);
//   else if(zone==6)
//       glVertex2i(y,-x);
//   else if(zone==7)
//       glVertex2i(x,-y);
//
//}
//
//// returns the zone of a line
//int get_zone(int x_0,int y_0, int x_1, int y_1){
//   int dx = x_1 - x_0;
//   int dy = y_1 -y_0;
//   if(dx>=0 && dy>=0){
//       if (abs(dx)>=abs(dy))
//           return 0;
//       else
//           return 1;
//   }
//   else if(dx<0 && dy>=0){
//       if (abs(dx)>=abs(dy))
//           return 3;
//       else
//           return 2;
//   }
//   else if(dx<0 && dy<0){
//       if (abs(dx)>=abs(dy))
//           return 4;
//       else
//           return 5;
//   }
//   else if(dx>=0 && dy<0){
//       if (abs(dx)>=abs(dy))
//           return 7;
//       else
//           return 6;
//   }
//
//}
//
//int main (int argc, char **argv){
//   glutInit (&argc, argv); // to initialize the toolkit;
//   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
//   glutInitWindowSize (Wi, He); // sets the window size
//   glutInitWindowPosition (0, 0); // sets the starting position for the window
//   glutCreateWindow ("Line Drawing"); // creates the window and sets the title
//   scanf("%d %d %d %d", &inpx0, &inpy0, &inpx1, &inpy1);
//   myInit(); // additional initializations as necessary
//   glutReshapeFunc(reshape);
//   glutDisplayFunc (display);
//   glutMainLoop(); // go into a loop until event occurs
//   return 0;
//}
