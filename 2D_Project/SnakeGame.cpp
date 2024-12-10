#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

float posX = 0.0f, posY = 0.0f;          // Snake head position
float foodX, foodY;                      // Food position
float moveUnit = 4.0f;                   // Movement step size (increased for larger segments)
int direction = 0;                       // 0: Right, 1: Left, 2: Up, 3: Down
const float windowWidth = 80.0f;
const float windowHeight = 60.0f;
std::vector<std::pair<float, float>> snakeBody; // Stores snake segments (x, y)
int score = 0;  // Track the score

void generateFood() {
    foodX = (std::rand() % static_cast<int>(windowWidth / moveUnit * 2) - windowWidth / moveUnit) * moveUnit;
    foodY = (std::rand() % static_cast<int>(windowHeight / moveUnit * 2) - windowHeight / moveUnit) * moveUnit;

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw food
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_QUADS);
    glVertex2f(foodX - 2.0f, foodY - 2.0f);
    glVertex2f(foodX + 2.0f, foodY - 2.0f);
    glVertex2f(foodX + 2.0f, foodY + 2.0f);
    glVertex2f(foodX - 2.0f, foodY + 2.0f);
    glEnd();

    // Draw snake
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    for (const auto& segment : snakeBody) {
        glBegin(GL_QUADS);
        glVertex2f(segment.first - 2.0f, segment.second - 2.0f); // Increased size
        glVertex2f(segment.first + 2.0f, segment.second - 2.0f);
        glVertex2f(segment.first + 2.0f, segment.second + 2.0f);
        glVertex2f(segment.first - 2.0f, segment.second + 2.0f);
        glEnd();
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-windowWidth, windowWidth, -windowHeight, windowHeight);

    // Initialize the snake with one segment
    snakeBody.push_back({ posX, posY });
    generateFood();
}

void processSpecialKeys(int key, int, int) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        if (direction != 1) direction = 0; // Avoid reversing directly
        break;
    case GLUT_KEY_LEFT:
        if (direction != 0) direction = 1;
        break;
    case GLUT_KEY_UP:
        if (direction != 3) direction = 2;
        break;
    case GLUT_KEY_DOWN:
        if (direction != 2) direction = 3;
        break;
    }
}

void gameover() {
    std::cout << std::endl;
    std::cout << "\t\t\t\t GAME OVER !! " << std::endl;
    std::cout << std::endl;
    std::cout << "\t\t\t\t TOTAL SCORE: " << score << std::endl;
    exit(0);
}

void update(int value) {
    // Move the snake by adding a new head position
    switch (direction) {
    case 0: posX += moveUnit; break; // Right
    case 1: posX -= moveUnit; break; // Left
    case 2: posY += moveUnit; break; // Up
    case 3: posY -= moveUnit; break; // Down
    }

    // Check collision with boundaries
    if (posX >= windowWidth || posX <= -windowWidth || posY >= windowHeight || posY <= -windowHeight) {
        gameover();
    }

    // Check collision with itself
    for (size_t i = 1; i < snakeBody.size(); ++i) {
        if (posX == snakeBody[i].first && posY == snakeBody[i].second) {
            gameover();
        }
    }

    // Check if the snake eats the food
    if (posX == foodX && posY == foodY) {
        generateFood();
        snakeBody.push_back({ posX, posY }); // Grow the snake
        score += 1;  // Increase score when food is eaten
    }

    // Move the snake's body
    for (size_t i = snakeBody.size() - 1; i > 0; --i) {
        snakeBody[i] = snakeBody[i - 1];
    }
    snakeBody[0] = { posX, posY };

    glutPostRedisplay();
    glutTimerFunc(200, update, 0);  // Timer delay (slower movement)
}

int main(int argc, char** argv) {
    std::cout << std::endl;
    std::cout << "\t\t ********** WELCOME TO SNAKE GAME ********** " << std::endl;
    std::cout << std::endl;

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random number generator
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Snake Game");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutTimerFunc(120, update, 0);

    glutMainLoop();
    return 0;
}
