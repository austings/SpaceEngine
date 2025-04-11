#include <GL/glut.h>
#include "world.h"
#include "spaceship.h"
#include <algorithm>
#include <cmath>

// Global spaceship object
Spaceship spaceship;

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Apply spaceship's camera view
    spaceship.applyCameraView();

    Sphere planet(0.0f, 0.0f, 0.0f, 1.0f, 10, 10); // low res to start

    // Determine LOD based on distance
    // Calculate distance from spaceship to sphere
    float dx = spaceship.getPosX() - planet.getPosX();
    float dy = spaceship.getPosY() - planet.getPosY();
    float dz = spaceship.getPosZ() - planet.getPosZ();
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    int maxDetail = 50;
    int minDetail = 8;
    int detail = std::max(minDetail, maxDetail - (int)distance * 2); // crude scaling
    detail = std::min(detail, maxDetail); // clamp to maxDetail
    
    planet.setSlices(detail);
    planet.setStacks(detail);

    // Render the planet
    planet.render();

    // Render the spaceship
    spaceship.render();
    
    glutSwapBuffers();
}

// Keyboard callback for arrow keys
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            spaceship.moveForward();
            break;
        case GLUT_KEY_DOWN:
            spaceship.moveBackward();
            break;
        case GLUT_KEY_LEFT:
            spaceship.turnLeft();
            break;
        case GLUT_KEY_RIGHT:
            spaceship.turnRight();
            break;
    }
    glutPostRedisplay();
}

// Keyboard callback for alphanumerical
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c': // Switch camera view
        case 'C':
            spaceship.toggleCameraView();
            break;
    }
    glutPostRedisplay();
}

//The reshape callback in OpenGL 
//is used to handle window resizing events.
void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialize OpenGL state
void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spaceship Around Sphere");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); 
    glutSpecialFunc(specialKeys);
    
    initGL();
    glutMainLoop();
    return 0;
}