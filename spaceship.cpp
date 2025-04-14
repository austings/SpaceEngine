#include "spaceship.h"
#include <GL/glut.h>
#include <cmath>

// Constants for degree-to-radian conversion
constexpr float DEG_TO_RAD = 3.14159265f / 180.0f;

Spaceship::Spaceship() 
    : posX(0.0f), posY(0.0f), posZ(5.0f),
      lookX(0.0f), lookY(0.0f), lookZ(-1.0f),
      upX(0.0f), upY(1.0f), upZ(0.0f),
      angleX(0.0f), angleY(0.0f),
      moveStep(0.1f), rotateStep(5.0f)
{
    updateLookVector();
}

void Spaceship::updateLookVector() {
    float radYaw = angleY * DEG_TO_RAD;
    float radPitch = angleX * DEG_TO_RAD;

    // Compute look vector from yaw & pitch.  
    // (Using the standard spherical coordinates-to-Cartesian conversion)
    lookX = cos(radPitch) * sin(radYaw);
    lookY = sin(radPitch);
    lookZ = -cos(radPitch) * cos(radYaw);
    
    // Optionally, normalize the look vector (it should already be unit length by construction)
    float lookLength = std::sqrt(lookX * lookX + lookY * lookY + lookZ * lookZ);
    if (lookLength != 0.0f) {
        lookX /= lookLength;
        lookY /= lookLength;
        lookZ /= lookLength;
    }
}

void Spaceship::toggleCameraView() {
    thirdPersonView = !thirdPersonView;
}

void Spaceship::moveForward() {
    // Move forward along the current look vector.
    posX += moveStep * lookX;
    posY += moveStep * lookY;
    posZ += moveStep * lookZ;

    // Update the ship's visible heading to match current camera direction
    targetLookX = lookX;
    targetLookY = lookY;
    targetLookZ = lookZ;
}

void Spaceship::moveBackward() {
    posX -= moveStep * lookX;
    posY -= moveStep * lookY;
    posZ -= moveStep * lookZ;
}

void Spaceship::rotateYaw() {
    angleY += rotateStep;
    updateLookVector();
}

void Spaceship::rotatePitch() {
    angleX += rotateStep;
    updateLookVector();
}

void Spaceship::rotateRoll() {
    // To roll the spaceship, rotate the 'up' vector about the 'look' vector.

    // Compute the right vector = cross(look, up)
    float rightX = lookY * upZ - lookZ * upY;
    float rightY = lookZ * upX - lookX * upZ;
    float rightZ = lookX * upY - lookY * upX;
    
    // Normalize the right vector
    float rightLength = std::sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    if (rightLength == 0.0f)
        return; // Prevent division by zero.
    rightX /= rightLength;
    rightY /= rightLength;
    rightZ /= rightLength;
    
    float rollRad = rotateStep * DEG_TO_RAD;
    float cosTheta = cosf(rollRad);
    float sinTheta = sinf(rollRad);
    
    // Rotate the up vector around the look axis: newUp = up*cos(theta) + right*sin(theta)
    float newUpX = upX * cosTheta + rightX * sinTheta;
    float newUpY = upY * cosTheta + rightY * sinTheta;
    float newUpZ = upZ * cosTheta + rightZ * sinTheta;
    
    upX = newUpX;
    upY = newUpY;
    upZ = newUpZ;
    
    // Normalize up vector
    float upLength = std::sqrt(upX * upX + upY * upY + upZ * upZ);
    if (upLength != 0.0f) {
        upX /= upLength;
        upY /= upLength;
        upZ /= upLength;
    }
}

void Spaceship::turnLeft() {
    angleY -= rotateStep;
    updateLookVector();
}

void Spaceship::turnRight() {
    angleY += rotateStep;
    updateLookVector();
}
void Spaceship::pitchShip(float degrees){
    // Convert degrees to radians
    float radians = degrees * DEG_TO_RAD;

    // Calculate the right vector (facing × up)
    float rightX = targetLookY * upZ - targetLookZ * upY;
    float rightY = targetLookZ * upX - targetLookX * upZ;
    float rightZ = targetLookX * upY - targetLookY * upX;

    // Normalize right vector
    float length = std::sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
    if (length == 0.0f) return;
    rightX /= length;
    rightY /= length;
    rightZ /= length;

    // Rotate facing vector around right vector
    // Rodrigues' rotation formula
    float cosTheta = cosf(radians);
    float sinTheta = sinf(radians);

    float newtargetLookX =
        targetLookX * cosTheta +
        (rightY * targetLookZ - rightZ * targetLookY) * sinTheta +
        rightX * (rightX * targetLookX + rightY * targetLookY + rightZ * targetLookZ) * (1 - cosTheta);

    float newtargetLookY =
        targetLookY * cosTheta +
        (rightZ * targetLookX - rightX * targetLookZ) * sinTheta +
        rightY * (rightX * targetLookX + rightY * targetLookY + rightZ * targetLookZ) * (1 - cosTheta);

    float newtargetLookZ =
        targetLookZ * cosTheta +
        (rightX * targetLookY - rightY * targetLookX) * sinTheta +
        rightZ * (rightX * targetLookX + rightY * targetLookY + rightZ * targetLookZ) * (1 - cosTheta);

    // Update facing vector
    targetLookX = newtargetLookX;
    targetLookY = newtargetLookY;
    targetLookZ = newtargetLookZ;

    // Optionally: normalize facing
    /*
    float fLen = std::sqrt(targetLookX * targetLookX + targetLookY * targetLookY + targetLookZ * targetLookZ);
    if (fLen != 0.0f) {
        targetLookX /= fLen;
        targetLookY /= fLen;
        targetLookZ /= fLen;
    }*/
}

void Spaceship::turnUp() {
    pitchShip(rotateStep); // pitch up
    updateLookVector();
}

void Spaceship::turnDown() {
    pitchShip(-rotateStep); // pitch down
    updateLookVector();
}

void Spaceship::applyCameraView(int scale) const {
    if (thirdPersonView) {
        // Offset the camera behind the ship:
        float camX = posX - lookX;
        float camY = 0.0f;
        float camZ = posZ - lookZ;
        gluLookAt(camX, camY, camZ,
                  posX, posY, posZ,
                  upX, upY, upZ);
    } else {
        // First-person view
        gluLookAt(posX, posY, posZ,
                  posX + lookX, posY + lookY, posZ + lookZ,
                  upX, upY, upZ);
    }
}

void Spaceship::render(int scale) const {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    
    // Calculate yaw and pitch from the *facing* vector, not the live look vector.
    float yaw   = atan2(targetLookX, targetLookZ) * 180.0f / M_PI;
    float pitch = -asin(targetLookY) * 180.0f / M_PI;

    glRotatef(yaw,   0.0f, 1.0f, 0.0f);
    glRotatef(pitch, 1.0f, 0.0f, 0.0f);

    float scaleFactor = 1.0f / static_cast<float>(scale);
    glScalef(scaleFactor, scaleFactor, scaleFactor);

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCone(0.1, 0.3, 10, 10);
    glPopMatrix();
}
