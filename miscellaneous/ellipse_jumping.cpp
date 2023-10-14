//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <string.h>
//#include <GL/glut.h>
//
//int Wi=640, He=480;
//void myInit (void);
//void display(void);
//void reshape (int w, int h);
//void draw_grid(void);
//void draw_ellipse(int cx,int cy, int a, int b);
//void draw4way(int x,int y,int cx,int cy);
//void ellipse_jumper(void);
//
//void myInit (void){
//    glClearColor(0.0, 0.0, 0.0,1.0);
//}
//
//double min(double x, double y){
//    return x<=y? x: y;
//}
//
//double square(double x){
//    return x*x;
//}
//
//void reshape (int w, int h){
//    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluOrtho2D (-Wi/2, Wi/2-1, -He/2, He/2-1);
//    glMatrixMode (GL_MODELVIEW);
//    glLoadIdentity ();
//}
//
//void draw_grid(void){
//    glBegin(GL_LINES);
//    glVertex2i(-320,0);
//    glVertex2i(319,0);
//    glVertex2i(0,239);
//    glVertex2i(0,-240);
//    glEnd();
//}
//
//void draw_ellipse(int cx,int cy, int a, int b){
//    int d = 4*b*b-a*a*(4*b-1);
//    int x = 0,y = b;
//    draw4way(x,y,cx,cy);
//    while(a*a*(4*y-2)>4*b*b*(x+1)){
//        if (d<0){
//            d+= 4*b*b*(2*x+3);
//            x++;
//        }
//        else{
//            d+=4*b*b*(2*x+3)-4*a*a*(2*y-2);
//            x++;
//            y--;
//        }
//        draw4way(x,y,cx,cy);
//    }
//    while (y>0){
//        if(d<0){
//            d+=4*(a*a*(3-2*y)+b*b*(2*x+2));
//            x++;
//            y--;
//        } else{
//            d+=4*a*a*(3-2*y);
//            y--;
//        }
//        draw4way(x,y,cx,cy);
//    }
//}
//
//void draw4way(int x,int y,int cx,int cy){
//    glVertex2i(x+cx,y+cy);
//    glVertex2i(-x+cx,y+cy);
//    glVertex2i(x+cx,-y+cy);
//    glVertex2i(-x+cx,-y+cy);
//}
//
//void display(){
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0, 1.0, 1.0);
//    glBegin(GL_POINTS);
//    ellipse_jumper();
//    glEnd();
//    glFlush();
//}
//int call = 0;
//void keyUp (unsigned char key, int x, int y) {
//    if (key == 'a'){
//        call++;
//        printf("called");
//    }
//}
//
//void myMouse (int button, int state, int x, int y)
//{
//    if (button == GLUT_LEFT_BUTTON and state == GLUT_UP)
//    {
//        //printf())
//        ++call;
//    }
//}
//
//void ellipse_jumper(){
//    int cx = 0;
//    int cy = 0;
//    int a = 70;
//    int b = 70;
//    int r = a;
//    int maxy =He/2-1 ;
//    int miny =-He/2 ;
//    int maxx =Wi/2-1 ;
//    int minx =-Wi/2 ;
//    while(1){
//        glutMouseFunc(myMouse);
//        while(call % 2 == 1);
//        while (cy>miny+35){
//            glClear(GL_COLOR_BUFFER_BIT);
//            glBegin(GL_POINTS);
//            draw_ellipse(cx,cy,(int)sqrt(2*square(r)-square(min(b,cy-miny))),min(b,cy-miny));
//            cy-=(1 - cy/100);
//            glEnd();
//            glutSwapBuffers();
//        }
//        while(cy<0){
//            glClear(GL_COLOR_BUFFER_BIT);
//            glBegin(GL_POINTS);
//            draw_ellipse(cx,cy,(int)sqrt(2*square(r)-square(min(b,cy-miny))),min(b,cy-miny));
//            cy+=(1 - cy/100);
//            glEnd();
//            glutSwapBuffers();
//
//        }
//    }
//}
//
//
//int main (int argc, char **argv){
//    glutInit (&argc, argv);
//    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize (Wi, He);
//    glutInitWindowPosition (0, 0);
//    glutCreateWindow ("Line Drawing");
//    myInit();
//    glutReshapeFunc(reshape);
//    glutDisplayFunc (display);
//    glutMainLoop();
//    return 0;
//}
