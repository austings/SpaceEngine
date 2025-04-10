#include "spaceship.h"
#include <GL/glut.h>
#include <cmath>
/*
gluLookAt moves the world so that:

The camera ("eye") is at the origin (0,0,0)

The "center" is what you're looking at — in the negative Z direction

The "up" vector controls the camera tilt (normally (0,1,0))

*/
Spaceship::Spaceship() 
    : posX(0.0f), posY(0.0f), posZ(5.0f),
      lookX(0.0f), lookY(0.0f), lookZ(-1.0f),
      upX(0.0f), upY(1.0f), upZ(0.0f),
      angleX(0.0f), angleY(0.0f),
      moveStep(0.1f), rotateStep(5.0f) {
}
void Spaceship::updateLookVector() {
    float radYaw = angleY * M_PI / 180.0f;
    float radPitch = angleX * M_PI / 180.0f;

    lookX = cos(radPitch) * sin(radYaw);
    lookY = sin(radPitch);
    lookZ = -cos(radPitch) * cos(radYaw);
}

void Spaceship::toggleCameraView() {
    thirdPersonView = !thirdPersonView;
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
    updateLookVector();
}

void Spaceship::turnRight() {
    angleY += rotateStep;
    updateLookVector();
}

void Spaceship::turnUp() {
    angleX += rotateStep;
    if (angleX > 89.0f) angleX = 89.0f;
    updateLookVector();
}

void Spaceship::turnDown() {
    angleX -= rotateStep;
    if (angleX < -89.0f) angleX = -89.0f;
    updateLookVector();
}

void Spaceship::applyCameraView() const {
    if (thirdPersonView) {
        // Offset the camera behind the ship
        float camX = posX - lookX * 2.0f;
        float camY = posY + 1.0f; // Raise the camera a bit
        float camZ = posZ - lookZ * 2.0f;

        gluLookAt(camX, camY, camZ,
                  posX, posY, posZ,
                  upX, upY, upZ);
    } else {
        // First person view
        gluLookAt(posX, posY, posZ,
                  posX + lookX, posY + lookY, posZ + lookZ,
                  upX, upY, upZ);
    }
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