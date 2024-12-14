#include <GL/glut.h>
#include <vector>
#include <iostream>

// Struct to store vertex points
struct Point3D {
    float x, y, z;
};

std::vector<Point3D> vertices; // Store vertices of the shape
float currentColor[3] = { 1.0, 1.0, 1.0 }; // Default color is white
bool drawing = true;

void setColor(float r, float g, float b) {
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
    glColor3f(r, g, b);
}

void drawShape() {
    if (vertices.size() < 3) {
        return; // Not enough points to draw a shape
    }

    glBegin(GL_POLYGON);
    for (const auto& vertex : vertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (!vertices.empty()) {
        setColor(currentColor[0], currentColor[1], currentColor[2]);
        drawShape();
    }

    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && drawing) {
        Point3D point;
        point.x = (float)(x - 250) / 250; // Normalize to range [-1, 1]
        point.y = (float)(250 - y) / 250; // Normalize to range [-1, 1]
        point.z = 0.0f; // Flat 2D shape for simplicity
        vertices.push_back(point);
    }

    glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'r': // Change color to red
    case 'R':
        setColor(1.0, 0.0, 0.0);
        break;
    case 'g': // Change color to green
    case 'G':
        setColor(0.0, 1.0, 0.0);
        break;
    case 'b': // Change color to blue
    case 'B':
        setColor(0.0, 0.0, 1.0);
        break;
    case 13: // Enter key to finish shape
        drawing = false;
        break;
    case 'c': // Clear the screen and reset
    case 'C':
        vertices.clear();
        drawing = true;
        setColor(1.0, 1.0, 1.0); // Reset to white color
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Shape Drawer");

    initOpenGL();

    glutDisplayFunc(display);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();
    return 0;
}