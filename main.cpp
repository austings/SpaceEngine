#include <GL/glut.h>
#include "spaceship.h"

// Global spaceship object
Spaceship spaceship;

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Apply spaceship's camera view
    spaceship.applyCameraView();
    
    // Draw the sphere (greenish)
    glColor3f(0.2f, 0.7f, 0.3f);
    glutSolidSphere(1.0, 50, 50);
    
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

// Reshape callback
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
    glutSpecialFunc(specialKeys);
    
    initGL();
    glutMainLoop();
    return 0;
}