///*
//Circle with 8 regions without printing table
//*/
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//
//
//#define Height 512
//#define Width 512
//
//
//static void resize(int width, int height)
//{
//    const float ar = (float) width / (float) height;
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-Width/2, Width/2 - 1, -Height/2, Height/2 - 1, -1, 1);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity() ;
//}
//
//void drawPixel(int x, int y)
//{
//    glVertex2i(x, y);
//}
//
//int centre_x, centre_y, radius, region, a, b;
//
//void draw4way(int x, int y){
//    drawPixel(x+centre_x, y+centre_y);
//    //drawPixel(y+centre_x, x+centre_y);
//   // drawPixel(-y+centre_x, x+centre_y);
//    drawPixel(-x+centre_x, y+centre_y);
//    drawPixel(-x+centre_x, -y+centre_y);
//    //drawPixel(-y+centre_x, -x+centre_y);
//    //drawPixel(y+centre_x, -x+centre_y);
//    drawPixel(x+centre_x, -y+centre_y);
//}
//
//
//void drawEllipse0(int r,int a,int b)
//{
//    int x = 0;
//    int y = b;
//    int d = 4*(b*b-a*a*b)+a*a;
//    draw4way(x, y);
//    // while((double)(b*b*(x+1)) < (double)(a*a*((double)y-.5)))
//    while(2*b*b*(x+1) < a*a*(2*y-1))
//    {
//        if(d < 0)
//        {
//            d += 4*b*b*(2*x+3); // north
//            x++;
//        }
//        else
//        {
//            d += 4*(b*b*(2*x+3)-a*a*(2*y-2));
//            x++;
//            y--;
//        }
//        draw4way(x,y);
//    }
//    while(y > 0){
//        if(d > 0){
//            d += 4*a*a*(-2*y+3);
//            y--;
//        }
//        else{
//            d += 4*a*a*(-2*y+3) + 4*b*b*(2*x+2);
//            y--;
//            x++;
//        }
//        draw4way(x,y);
//    }
//}
//
//void drawEllipse1(int r,int a,int b)
//{
//    int x = -a;
//    int y = 0;
//    int d = 4*(-a*b*b + a*a)+b*b;
//    draw4way(x, y);
//    // while((double)(b*b*(x+1)) < (double)(a*a*((double)y-.5)))
//    while(abs(b*b*(2*x+1)) > abs(2*a*a*(y+1)))
//    {
//        if(d < 0)
//        {
//            d += 4*a*a*(2*y+3); // north
//            y++;
//        }
//        else
//        {
//            d += 4*a*a*(2*y+3) + 4*b*b*(2*x+2);
//            x++;
//            y++;
//        }
//        draw4way(x,y);
//    }
//    while(x < 0){
//        if(d > 0){
//            d += 4*b*b*(2*x+3);
//            x++;
//        }
//        else{
//            d += 4*b*b*(2*x+3) + 4*a*a*(2*y+2);
//            y++;
//            x++;
//        }
//        draw4way(x,y);
//    }
//}
//void drawEllipse2(int r,int a,int b)
//{
//    int x = 0;
//    int y = -b;
//    int d = 4*(b*b-a*a*b)+a*a;
//    draw4way(x, y);
//    // while((double)(b*b*(x+1)) < (double)(a*a*((double)y-.5)))
//    while(abs(2*b*b*(x-1)) < abs(a*a*(2*y+1)))
//    {
//        if(d < 0)
//        {
//            d += 4*b*b*(3-2*x); // north
//            x--;
//        }
//        else
//        {
//            d += 4*b*b*(3-2*x) + 4*a*a*(2*y+2);
//            x--;
//            y++;
//        }
//        draw4way(x,y);
//    }
//    while(y < 0){
//        if(d > 0){
//            d += 4*a*a*(2*y+3);
//            y++;
//        }
//        else{
//            d +=4*a*a*(2*y+3) + 4*b*b*(2-2*x);
//            y++;
//            x--;
//        }
//        draw4way(x,y);
//    }
//}
//void drawEllipse3(int r,int a,int b)
//{
//    int x = a;
//    int y = 0;
//    int d = 4*(a*a-a*b*b)+b*b;
//    draw4way(x, y);
//    // while((double)(b*b*(x+1)) < (double)(a*a*((double)y-.5)))
//    while(abs(b*b*(2*x-1)) > abs(2*a*a*(y-1)))
//    {
//        if(d < 0)
//        {
//            d += 4*a*a*(3-2*y); // north
//            y--;
//        }
//        else
//        {
//            d += 4*b*b*(2-2*x) + 4*a*a*(3-2*y);
//            x--;
//            y--;
//        }
//        draw4way(x,y);
//    }
//    while(x>0){
//        if(d > 0){
//            d += 4*b*b*(3-2*x);
//            x--;
//        }
//        else{
//            d +=4*a*a*(2-2*y) + 4*b*b*(3-2*x);
//            y--;
//            x--;
//        }
//        draw4way(x,y);
//    }
//}
//
//
//
//
//void drawEllipse(int rad, int a,int b,int reg)
//{
//    switch (reg)
//    {
//    case 0:
//        glColor3ub(255, 0, 0);
//        drawEllipse0(rad,a,b);
//        break;
//    case 1:
//        glColor3ub(0, 255, 0);
//        drawEllipse1(rad,a,b);
//        break;
//    case 2:
//        glColor3ub(0,0,255);
//        drawEllipse2(rad,a,b);
//    case 3:
//        glColor3ub(255,0,255);
//        drawEllipse3(rad,a,b);
//    }
//}
//
//
//int x_0, x_1, y_0, y_1;
//
//static void display(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3d(1,1,1);
//    glBegin(GL_LINES);
//    glVertex2i(-Width/2, 0);
//    glVertex2i(Width/2 - 1, 0);
//    glVertex2i(0, -Height/2);
//    glVertex2i(0, Height/2 - 1);
//    glEnd();
//
//    glPointSize(2);
//    glBegin(GL_POINTS);
//    drawEllipse(radius,a,b,region);
//    glEnd();
//
//    glutSwapBuffers();
//}
//
//
//
//static void idle(void)
//{
//    glutPostRedisplay();
//}
//
//// Program entry point
//
//int main(int argc, char *argv[])
//{
//    printf("Enter Center of Ellipse in following format: x y\n");
//    scanf("%d %d",&centre_x,&centre_y);
//    printf("Enter a and b of Ellipse:\n");
//    scanf("%d %d",&a,&b);
//    printf("Enter Region you wish to draw from, from (0-7):\n");
//    scanf("%d",&region);
//    glutInit(&argc, argv);
//    glutInitWindowSize(Width,Height);
//    glutInitWindowPosition(10,10);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//    //generateLines();
//    glutCreateWindow("Experiment 01");
//
//    glutReshapeFunc(resize);
//    glutDisplayFunc(display);
//    glutIdleFunc(idle);
//
//    glutMainLoop();
//
//    return EXIT_SUCCESS;
//}
