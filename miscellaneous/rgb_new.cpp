//#include <GL/glut.h>
//#include<stdio.h>
//
//  #if defined __UINT32_MAX__ or UINT32_MAX
//  #include <inttypes.h>
//  #else
//  typedef unsigned char uint8_t;
//  typedef unsigned short uint16_t;
//  typedef unsigned long uint32_t;
//  typedef unsigned long long uint64_t;
//  #endif
//
//using namespace std;
//
//#define BI_RGB 0
//
//#pragma pack(push, 1)
//typedef struct {
//    uint16_t bfType;
//    uint32_t bfSize;
//    uint16_t bfReserved1;
//    uint16_t bfReserved2;
//    uint32_t bfOffBits;
//} BITMAPFILEHEADERNEW;
//#pragma pack(pop)
//
//#pragma pack(push, 1)
//typedef struct {
//    uint32_t biSize;
//    int32_t biWidth;
//    int32_t biHeight;
//    uint16_t biPlanes;
//    uint16_t biBitCount;
//    uint32_t biCompression;
//    uint32_t biSizeImage;
//    int32_t biXPelsPerMeter;
//    int32_t biYPelsPerMeter;
//    uint32_t biClrUsed;
//    uint32_t biClrImportant;
//} BITMAPINFOHEADERNEW;
//#pragma pack(pop)
//
//
//GLuint LoadTexture(const char* filename)
//{
//    GLuint texture;
//    FILE* file;
//    unsigned char* imageData;
//    BITMAPFILEHEADERNEW fileHeader;
//    BITMAPINFOHEADERNEW infoHeader;
//    int width, height, size, offset;
//
//    file = fopen(filename, "rb");
//    if (!file) {
//        printf("Error: could not open file %s\n", filename);
//        return 0;
//    }
//
//    fread(&fileHeader, sizeof(fileHeader), 1, file);
//    fread(&infoHeader, sizeof(infoHeader), 1, file);
//
//    // Check if the color data is stored in reverse byte order (BGR)
//    bool reverseBytes = false;
//    if (infoHeader.biBitCount == 24 && infoHeader.biCompression == BI_RGB) {
//        reverseBytes = true;
//    }
//
//    width = infoHeader.biWidth;
//    height = infoHeader.biHeight;
//    size = width * height * 3;
//
//    // Allocate memory for the pixel data buffer
//    imageData = new unsigned char[size];
//
//    // Seek to the beginning of the pixel data
//    offset = fileHeader.bfOffBits;
//    fseek(file, offset, SEEK_SET);
//
//    // Read the pixel data into the buffer
//    fread(imageData, size, 1, file);
//
//    // If the color data is stored in reverse byte order, swap the order of the color bytes
//    if (reverseBytes) {
//        for (int i = 0; i < size; i += 3) {
//            unsigned char temp = imageData[i];
//            imageData[i] = imageData[i+2];
//            imageData[i+2] = temp;
//        }
//    }
//
//    fclose(file);
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//
//    delete[] imageData;
//
//    return texture;
//}
//
//void display()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, LoadTexture("image2.bmp"));
//
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 0.0f);
//    glEnd();
//
//    glFlush();
//    glutSwapBuffers();
//}
//
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("BMP Image");
//
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}
