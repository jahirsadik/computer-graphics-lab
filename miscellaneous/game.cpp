//#include <GL\freeglut.h>
//#include<stdio.h>
//#define NUM_KEYS 256
//bool keysDown[NUM_KEYS];
//bool lastKeysDown[NUM_KEYS];
//#define NUM_MOUSE_BUTTONS 10
//bool mouseButtonsDown[NUM_MOUSE_BUTTONS];
//bool lastMouseButtonsDown[NUM_MOUSE_BUTTONS];
//int mouseX = 0, mouseY = 0;
//
//int window = 0;
//int windowWidth, windowHeight;
//void(*clientUpdate)();
//void(*clientDraw)();
//
//void(*clientUpdateNeg)();
//void(*clientDrawNeg)();
//
//void(*clientUpdateH)();
//void(*clientDrawH)();
//
//void(*clientUpdateV)();
//void(*clientDrawV)();
//
//void(*clientUpdateS)();
//void(*clientDrawS)();
//
//void onKeyboardDown(unsigned char key, int x, int y) {
//    lastKeysDown[key] = keysDown[key];
//    keysDown[key] = true;
//}
//void onKeyboardUp(unsigned char key, int x, int y) {
//    lastKeysDown[key] = keysDown[key];
//    keysDown[key] = false;
//}
//void onMouseButton(int button, int state, int x, int y) {
//    lastMouseButtonsDown[button] = mouseButtonsDown[button];
//    mouseButtonsDown[button] = (state == 0); // down
//    printf("Button Click: %d %d\n", x, y);
//}
//void onMouseMove(int x, int y) {
//    mouseX = x;
//    mouseY = y;
//}
//
//void onDisplay() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    clientDraw();
//
//    glFlush();
//}
//
//void onDisplayNeg() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    clientDrawNeg();
//
//    glFlush();
//}
//
//void onDisplayH() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    clientDrawH();
//
//    glFlush();
//}
//
//void onDisplayV() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    clientDrawV();
//
//    glFlush();
//}
//
//void onDisplayS() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    clientDrawS();
//
//    glFlush();
//}
//
//
//void updateLoop(int val) {
//    clientUpdate();
//    clientUpdateNeg();
//    clientUpdateH();
//    clientUpdateV();
//    clientUpdateS();
//
//
//    // update input because events are not immediate enough
//    for (int i = 0; i < NUM_KEYS; i++) {
//        lastKeysDown[i] = keysDown[i];
//    }
//    for (int i = 0; i < NUM_MOUSE_BUTTONS; i++) {
//        lastMouseButtonsDown[i] = mouseButtonsDown[i];
//    }
//
//    glutTimerFunc(16, updateLoop, 0); // 16 ms = 60 fps
//}
//
//void drawLoop(int val) {
//    if (window) {
//        glutPostRedisplay();
//        glutTimerFunc(8, drawLoop, 0); // 8 ms = 120 fps
//    }
//}
//
//void gSetup(int argc, char** argv, int w, int h, bool fs, void(*u)(), void(*d)()) {
//
//    windowWidth = w;
//    windowHeight = h;
//    clientUpdate = u;
//    clientDraw = d;
//
//    glutInitWindowSize(w, h);
//    glutInitWindowPosition(0, 0);
//    window = glutCreateWindow("1");
//    if (fs)
//        glutFullScreen();
//
//    glutDisplayFunc(onDisplay);
//
//    glutKeyboardUpFunc(onKeyboardUp);
//    glutKeyboardFunc(onKeyboardDown);
//    glutMouseFunc(onMouseButton);
//    glutMotionFunc(onMouseMove);
//    glutPassiveMotionFunc(onMouseMove);
//
//    glutTimerFunc(0, updateLoop, 0);
//    glutTimerFunc(0, drawLoop, 0);
//
//
//}
//
//void gSetupNeg(int argc, char** argv, int w, int h, bool fs, void(*u)(), void(*d)()) {
//
//    windowWidth = w;
//    windowHeight = h;
//    clientUpdateNeg = u;
//    clientDrawNeg = d;
//
//    glutInitWindowSize(w, h);
//    glutInitWindowPosition(600, 0);
//    window = glutCreateWindow("2");
//    if (fs)
//        glutFullScreen();
//
//    glutDisplayFunc(onDisplayNeg);
//
//    glutKeyboardUpFunc(onKeyboardUp);
//    glutKeyboardFunc(onKeyboardDown);
//    glutMouseFunc(onMouseButton);
//    glutMotionFunc(onMouseMove);
//    glutPassiveMotionFunc(onMouseMove);
//
//    glutTimerFunc(0, updateLoop, 0);
//    glutTimerFunc(0, drawLoop, 0);
//
//}
//
//void gSetupH(int argc, char** argv, int w, int h, bool fs, void(*u)(), void(*d)()) {
//
//    windowWidth = w;
//    windowHeight = h;
//    clientUpdateH = u;
//    clientDrawH = d;
//    glutInitWindowSize(w, h);
//    glutInitWindowPosition(300, 300);
//    window = glutCreateWindow("3");
//    if (fs)
//        glutFullScreen();
//
//    glutDisplayFunc(onDisplayH);
//    glutTimerFunc(0, updateLoop, 0);
//    glutTimerFunc(0, drawLoop, 0);
//}
//
//void gSetupV(int argc, char** argv, int w, int h, bool fs, void(*u)(), void(*d)()) {
//
//    windowWidth = w;
//    windowHeight = h;
//    clientUpdateV = u;
//    clientDrawV = d;
//    glutInitWindowSize(w, h);
//    glutInitWindowPosition(100, 100);
//    window = glutCreateWindow("4");
//    if (fs)
//        glutFullScreen();
//
//    glutDisplayFunc(onDisplayV);
//    glutTimerFunc(0, updateLoop, 0);
//    glutTimerFunc(0, drawLoop, 0);
//}
//
//void gSetupS(int argc, char** argv, int w, int h, bool fs, void(*u)(), void(*d)()) {
//
//    windowWidth = w;
//    windowHeight = h;
//    clientUpdateS = u;
//    clientDrawS = d;
//    glutInitWindowSize(w, h);
//    glutInitWindowPosition(200, 200);
//    window = glutCreateWindow("5");
//    if (fs)
//        glutFullScreen();
//
//    glutDisplayFunc(onDisplayS);
//    glutTimerFunc(0, updateLoop, 0);
//    glutTimerFunc(0, drawLoop, 0);
//}
//
//void gExit() {
//    glutLeaveMainLoop();
//    glutDestroyWindow(window);
//    window = 0;
//}
//
//// OpenGL has -.5 to .5 coords and we want to scale
//// ours to match the mixel dimensions of the window
//float gGetGLX(float x) {
//    return x / windowWidth * 2;
//}
//float gGetGLY(float y) {
//    return y / windowHeight * 2;
//}
//float gGetWinW() {
//    return windowWidth;
//}
//float gGetWinH() {
//    return windowHeight;
//}
//float wld2scrX(float x) {
//    return x - gGetWinW() / 2;
//}
//float wld2scrY(float y) {
//    return y - gGetWinH() / 2;
//}
//float scr2wldX(float x) {
//    return x;
//}
//float scr2wldY(float y) {
//    return gGetWinH() - y; // screen pixel top left to world coord bottom left
//}
//
//// input functions
//bool gIsKeyDown(unsigned char key) {
//    return keysDown[key];
//}
//bool gIsKeyReleased(unsigned char key) {
//    return lastKeysDown[key] && !keysDown[key];
//}
//bool gIsMouseButtonDown(int button) {
//    return mouseButtonsDown[button];
//}
//bool gIsMouseButtonReleased(int button) {
//    return lastMouseButtonsDown[button] && !mouseButtonsDown[button];
//}
//int gGetMouseX() {
//    return mouseX;
//}
//int gGetMouseY() {
//    return mouseY;
//}
