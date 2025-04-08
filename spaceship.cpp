#include "spaceship.h"
#include <GL/glut.h>
#include <cmath>

Spaceship::Spaceship() 
    : posX(0.0f), posY(0.0f), posZ(5.0f),
      lookX(0.0f), lookY(0.0f), lookZ(-1.0f),
      upX(0.0f), upY(1.0f), upZ(0.0f),
      angleX(0.0f), angleY(0.0f),
      moveStep(0.1f), rotateStep(5.0f) {
}

void Spaceship::moveForward() {
    posX += lookX * moveStep;
    posY += lookY * moveStep;
    posZ += lookZ * moveStep;
}

void Spaceship::moveBackward() {
    posX -= lookX * moveStep;
    posY -= lookY * moveStep;
    posZ -= lookZ * moveStep;
}

void Spaceship::turnLeft() {
    angleY -= rotateStep;
    lookX = sin(angleY * M_PI / 180.0);
    lookZ = -cos(angleY * M_PI / 180.0);
}

void Spaceship::turnRight() {
    angleY += rotateStep;
    lookX = sin(angleY * M_PI / 180.0);
    lookZ = -cos(angleY * M_PI / 180.0);
}

void Spaceship::applyCameraView() const {
    gluLookAt(posX, posY, posZ,
              posX + lookX, posY + lookY, posZ + lookZ,
              upX, upY, upZ);
}

void Spaceship::render() const {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleX, 1, 0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCone(0.1, 0.3, 10, 10);
    glPopMatrix();
}