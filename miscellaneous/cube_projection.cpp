//
///*
//*   Lab-05: Implementation of Cyrus-Beak LCA in OpenGL
//*   Jahir Sadik Monon
//*   Roll: 32
//*/
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <vector>
//#include <GL/glut.h>
//#include <algorithm>
//
//
//
//int WIDTH = 800, HEIGHT = 600;  // Width and height of the screen
//int MAX_HEIGHT = HEIGHT/2-1;
//int MIN_HEIGHT = -HEIGHT/2;
//int MAX_WIDTH = WIDTH/2-1;
//int MIN_WIDTH = -WIDTH/2;
//int x_max = 100; // Clipping window max right
//int x_min = -100; // Clipping window min left
//int y_max = 100;  // Clipping window max up
//int y_min = -100; // Clipping window min down
//int globalMaxY, globalMinY;
//
//class Point {
//public:
//    int x, y;
//    Point(int xVal = 0, int yVal = 0) {
//        x = xVal;
//        y = yVal;
//    }
//    int getX() const { return x; }
//    int getY() const { return y; }
//    void setX(int xVal) { x = xVal; }
//    void setY(int yVal) { y = yVal; }
//    double distanceTo(const Point& other) const {
//        int dx = x - other.x;
//        int dy = y - other.y;
//        return std::sqrt(dx * dx + dy * dy);
//    }
//};
//
//class Edge {
//public:
//    Point p1, p2;
//    Edge(){};
//    Edge(const Point& point1, const Point& point2) {
//        p1 = point1;
//        p2 = point2;
//    }
//    Point getP1() const { return p1; }
//    Point getP2() const { return p2; }
//    double length() const {
//        return p1.distanceTo(p2);
//    }
//};
//
//struct
//{
//    bool operator()(const Edge& e1, const Edge& e2) const {
//        int e1pmin = std::min(e1.p1.y, e1.p2.y);
//        int e2pmin = std::min(e2.p1.y, e2.p2.y);
//        return e1pmin < e2pmin;
//    }
//}
//customLess;
//
//struct BucketEntry{
//    int y,x;
//    float m_inv;
//    BucketEntry *next = NULL;
//};
//
//struct Bucket{
//    BucketEntry *head = NULL;
//    BucketEntry *tail= NULL;
//
//
//    void insert(int y,int x, float _m_inv){
//        BucketEntry * bucketEntry = (BucketEntry*)malloc(sizeof(BucketEntry));
//        bucketEntry->x = x;
//        bucketEntry->y = y;
//        bucketEntry->m_inv = _m_inv;
//        bucketEntry->next = NULL;
//        if(head==NULL){
//            head = bucketEntry;
//        }
//
//        else if(head->x > x){
//            bucketEntry->next=head;
//            head=bucketEntry;
//        }
//        else{
//            BucketEntry* temp = head;
//            while (temp->next!=NULL && temp->next->x < x){
//                temp = temp->next;
//            }
//            bucketEntry->next = temp->next;
//            temp->next = bucketEntry;
//        }
//    }
//
//    void print(){
//        BucketEntry* bucketEntry = head;
//        while(bucketEntry!=NULL){
//            printf("%d %d %f\t\t", bucketEntry->y, bucketEntry->x, bucketEntry->m_inv);
//            bucketEntry = bucketEntry->next;
//        }
//    }
//};
//
//int noOfPoints;
//Point points[100];
//Edge edges[100];
//Edge edgesP[100];
//Bucket edgeTable[1000];
//Bucket activeEdgeTable[1000];
//
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
//// Function for creating a new point in between the line of two points P0 P1
////      the value of t is put into the parametric equation
//Point Create_Point(Point p0,Point p1, float t){
//    return Point((int)(p0.x+ t*(p1.x-p0.x)), (int)(p0.y + t*(p1.y-p0.y)));
//}
//
//
//// Line Drawing algorithms zone finding for given line endpoints
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
//// Drawing pixel with specific color
//// The zone argument is used to do zone-0 to any zone conversion
//void drawPixel (int x, int y, int zone, int color)
//{
//    if(color == 0){
//        glColor3f(0.0, 1.0, 0.0);
//    }
//    if(color == 1){
//        glColor3f(1.0, 0.0, 0.0);
//    }
//    if(color == 2){
//        glColor3f(1.0, 0.0, 0.0);
//    }
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
//// DrawLine function for drawing a line from zone-0
//void drawLine0 (int x0, int y0, int x1, int y1, int zone, int color)
//{
//    int dx = x1 - x0, dy = y1 - y0;
//    int x = x0, y = y0, d = 2 * dy - dx;
//    int de = 2 * dy, dne = 2 * (dy - dx);
//    while (x <= x1)
//    {
//        drawPixel (x, y, zone, color);
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
//// Finds zone, converts all to zone-0
////      processes in zone-0 but draws in original zone
//void draw8way (int x0, int y0, int x1, int y1, int color)
//{
//    int zone = findZone(x0, y0, x1, y1);
//    switch (zone)
//    {
//    case 0:
//        drawLine0(x0, y0, x1, y1, zone, color);
//        break;
//    case 1:
//        drawLine0(y0, x0, y1, x1, zone, color);
//        break;
//    case 2:
//        drawLine0(y0, -x0, y1, -x1, zone, color);
//        break;
//    case 3:
//        drawLine0(-x0, y0, -x1, y1, zone, color);
//        break;
//    case 4:
//        drawLine0(-x0, -y0, -x1, -y1, zone, color);
//        break;
//    case 5:
//
//        drawLine0(-y0, -x0, -y1, -x1, zone, color);
//        break;
//    case 6:
//
//        drawLine0(-y0, x0, -y1, x1, zone, color);
//        break;
//    case 7:
//        drawLine0(x0, -y0, x1, -y1, zone, color);
//        break;
//    }
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
//// Draws a grid around the clipping window
//void draw_grid(void){
//    glBegin(GL_LINES);
//    glVertex2i(x_min, MIN_HEIGHT);
//    glVertex2i(x_min, MAX_HEIGHT);
//    glVertex2i(x_max, MIN_HEIGHT);
//    glVertex2i(x_max, MAX_HEIGHT);
//    glVertex2i(MIN_WIDTH,   y_max);
//    glVertex2i(MAX_WIDTH,  y_max);
//    glVertex2i(MIN_WIDTH,  y_min);
//    glVertex2i(MAX_WIDTH, y_min);
//    glEnd();
//}
//
//
////void mouse(int button, int state, int x, int y) {
////    // Save the left button state
////    if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN&&!inputDone) {
////        Point p(x + MIN_WIDTH, -y + MAX_HEIGHT);
//////        points.push_back(p);
//////        counts.push_back(0);
////        print("%d %d\n", p.x, p.y);
////        glutPostRedisplay();
////    }
////}
//
//
//
//void display(){
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3d(1,1,1);
//    glBegin(GL_LINES);
//    glVertex2i(MIN_WIDTH, 0);
//    glVertex2i(MAX_WIDTH, 0);
//    glVertex2i(0, MIN_HEIGHT);
//    glVertex2i(0, MAX_HEIGHT);
//    glEnd();
//
//    glPointSize(3);
//    glColor3d(1,0,0);
//    glBegin(GL_POINTS);
//    glPointSize(10);
//    for (int i = 0; i < noOfPoints; i++){
//        glVertex2i(points[i].x, points[i].y);
//    }
//    glEnd();
//
//    glPointSize(1);
//    glColor3d(0,0,1);
//    glBegin(GL_LINES);
//    for (int i = 0; i < noOfPoints; i++){
//        glVertex2i(edgesP[i].p1.x, edgesP[i].p1.y);
//        glVertex2i(edgesP[i].p2.x, edgesP[i].p2.y);
//    }
//    glEnd();
//
//    glPointSize(1);
//    glColor3d(0,0,1);
//    glBegin(GL_LINES);
//    for(int i = 0; i < globalMaxY-globalMinY; i++){
//        if(activeEdgeTable[i].head !=  NULL) {
//            BucketEntry* bucketEntry = activeEdgeTable[i].head;
//            while(bucketEntry != NULL){
//                glVertex2i(bucketEntry->x, i + globalMinY);
//                glVertex2i(bucketEntry->next->x, i + globalMinY);
//                bucketEntry = bucketEntry->next->next;
//            }
//        }
//    }
//    glEnd();
//
//    glFlush();
//}
//
//
//int main (int argc, char **argv){
//    glutInit (&argc, argv);
//    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize (WIDTH, HEIGHT);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("ScanLine Polygon Filling in C");
//    printf("Enter number of points in polygon:\n");
//    scanf("%d", &noOfPoints);
//    for (int i = 0; i < noOfPoints; i++){
//        int tempx, tempy;
//        printf("Enter point %d: ", i);
//        scanf("%d %d", &tempx, &tempy);
//        points[i] = Point(tempx, tempy);
//        if(i > 0){
//            edges[i-1] = Edge(points[i-1], points[i]);
//            edgesP[i-1] = Edge(points[i-1], points[i]);
//        }
//    }
//    edges[noOfPoints-1] = Edge(points[noOfPoints-1], points[0]);
//    edgesP[noOfPoints-1] = Edge(points[noOfPoints-1], points[0]);
//    std::sort(edges, edges + noOfPoints, customLess);
//    for (int i = 0; i < noOfPoints; i++){
//        printf("Edge %d is from: (%d, %d) to (%d, %d)\n", i, edges[i].p1.getX(), edges[i].p1.getY(), edges[i].p2.getX(), edges[i].p2.getY());
//    }
//    globalMinY = min(edges[0].p1.y, edges[0].p2.y);
//    globalMaxY = max(edges[noOfPoints-1].p1.y, edges[noOfPoints-1].p2.y);
//    printf("AMAR BHALOBASHAR GlobalMinY: %d\n", globalMinY);
//    printf("AMAR BHALOBASHAR GlobalMaxY: %d\n", globalMaxY);
//    for(int i = 0; i < noOfPoints; i++){
//        Edge edge = edges[i];
//        int minY = min(edge.p1.y, edge.p2.y);
//        int maxY = max(edge.p1.y, edge.p2.y);
//        int minX = (minY == edge.p1.y) ? edge.p1.x : edge.p2.x;
//        printf("For edge (%d, %d) to (%d, %d): minY-> %d, maxY -> %d\n", edge.p1.x,edge.p1.y, edge.p2.x,edge.p2.y, minY, maxY);
//        if(!(minY ==  maxY)){
//            //printf("(%d - %d) and (%d - %d)\n", edge.p2.x, edge.p1.x, edge.p2.y, edge.p1.y);
//            edgeTable[minY-globalMinY].insert(maxY, minX, (float)(edge.p2.x-edge.p1.x)/(edge.p2.y-edge.p1.y));
//        }
//    }
//    printf("\nPrinting Edge Table: \n");
//    for(int i = 0; i < globalMaxY-globalMinY; i++){
//        if(edgeTable[i].head !=  NULL) {
//            edgeTable[i].print();
//            printf("\n");
//        }
//    }
//
//    // AET
//    printf("\n\n\n");
//    for(int i = 0; i < globalMaxY-globalMinY; i++){
//        if(edgeTable[i].head !=  NULL) {
//            BucketEntry* bucketEntry = edgeTable[i].head;
//            printf("%d========== %d %d %f\n", i, bucketEntry->y, bucketEntry->x, bucketEntry->m_inv);
//            while(bucketEntry != NULL){
//                activeEdgeTable[i].insert(bucketEntry->y, bucketEntry->x, bucketEntry->m_inv);
//                for(int j=i+1; j+globalMinY < bucketEntry->y; j++){
//                    float oneByM = bucketEntry->m_inv;
//                    printf("%d: %d %d %f\n", j, bucketEntry->y, (int)(bucketEntry->x + (float)((j-i)*oneByM)), oneByM);
//                    activeEdgeTable[j].insert(bucketEntry->y, (int)(bucketEntry->x + (float)((j-i)*oneByM)), oneByM);
//                }
//                bucketEntry = bucketEntry->next;
//            }
//        }
//    }
//
//    printf("\nPrinting Active Edge Table: \n");
//    for(int i = 0; i < globalMaxY-globalMinY; i++){
//        if(activeEdgeTable[i].head !=  NULL) {
//            printf("i: %d\t",i);
//            activeEdgeTable[i].print();
//            printf("\n");
//        }
//    }
//
//    glutReshapeFunc(reshape);
//    //glutMouseFunc(mouse);
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}
//
//
///* EXAMPLE INPUT
//10
//-240 -120
//-160 -120
//-50 -100
//100 -60
//150 -10
//200 50
//240 100
//280 250
//150 250
//-100 230
//*/
////
