#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Transformation variables
float posX = 0.0f, posY = 0.0f, posZ = -5.0f;
float scale = 1.0f;
float rotationAngle = 0.0f;

// Random colors for cube faces
float faceColors[6][3];

// Function to initialize random colors for each face
void initializeColors() {
    std::srand(std::time(0));
    for (int i = 0; i < 6; ++i) {
        faceColors[i][0] = static_cast<float>(std::rand()) / RAND_MAX;
        faceColors[i][1] = static_cast<float>(std::rand()) / RAND_MAX;
        faceColors[i][2] = static_cast<float>(std::rand()) / RAND_MAX;
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply transformations
    glTranslatef(posX, posY, posZ);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);

    // Draw cube with different colors for each face
    glBegin(GL_QUADS);

    // Front face
    glColor3f(faceColors[0][0], faceColors[0][1], faceColors[0][2]);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face
    glColor3f(faceColors[1][0], faceColors[1][1], faceColors[1][2]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Top face
    glColor3f(faceColors[2][0], faceColors[2][1], faceColors[2][2]);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Bottom face
    glColor3f(faceColors[3][0], faceColors[3][1], faceColors[3][2]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Right face
    glColor3f(faceColors[4][0], faceColors[4][1], faceColors[4][2]);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Left face
    glColor3f(faceColors[5][0], faceColors[5][1], faceColors[5][2]);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();

    glutSwapBuffers();
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        posY += 0.1f;
        break;
    case 's':
        posY -= 0.1f;
        break;
    case 'a':
        posX -= 0.1f;
        break;
    case 'd':
        posX += 0.1f;
        break;
    case 'r':
        rotationAngle += 5.0f;
        if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
        break;
    case 'f':
        rotationAngle -= 5.0f;
        if (rotationAngle <= -360.0f) rotationAngle += 360.0f;
        break;
    case '+':
        scale += 0.1f;
        break;
    case '-':
        scale = (scale > 0.1f) ? scale - 0.1f : scale;
        break;
    case 27: // ESC key
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// Initialize OpenGL environment
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    initializeColors();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Interactive 3D Transformations");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
