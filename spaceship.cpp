#include "spaceship.h"
#include <GL/glut.h>
#include <cmath>
// Constants for degree-to-radian conversion
constexpr float DEG_TO_RAD = 3.14159265f / 180.0f;
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
        updateLookVector();
        
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
    // Move forward along the current look vector. 
    // For a simple forward movement, ignore any acceleration mechanics.
    posX += moveStep * lookX;
    posY += moveStep * lookY;
    posZ += moveStep * lookZ;
    
}

void Spaceship::rotateYaw() {
    // Adjust yaw angle by the rotation step and update look vector
    angleY += rotateStep;
    updateLookVector();
}

void Spaceship::rotatePitch() {
    // Adjust pitch angle by the rotation step and update look vector
    angleX += rotateStep;
    updateLookVector();
}

void Spaceship::rotateRoll() {
    // To roll the spaceship, we rotate the 'up' vector about the 'look' vector.
    // First, compute the 'right' vector which is perpendicular to both look and up.
    // right = cross(look, up)
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
    
    // Calculate roll in radians using the rotate step (assuming rotateStep is in degrees)
    float rollRad = rotateStep * DEG_TO_RAD;
    float cosTheta = cosf(rollRad);
    float sinTheta = sinf(rollRad);
    
    // Update up vector with the rotation around the look vector:
    // Using the formula: newUp = up * cos(theta) + right * sin(theta)
    float newUpX = upX * cosTheta + rightX * sinTheta;
    float newUpY = upY * cosTheta + rightY * sinTheta;
    float newUpZ = upZ * cosTheta + rightZ * sinTheta;
    
    upX = newUpX;
    upY = newUpY;
    upZ = newUpZ;
    
    // (Optional) Normalize the up vector if needed.
    float upLength = std::sqrt(upX * upX + upY * upY + upZ * upZ);
    if (upLength != 0.0f) {
        upX /= upLength;
        upY /= upLength;
        upZ /= upLength;
    }
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

void Spaceship::applyCameraView(int scale) const {
    if (thirdPersonView) {
        // Offset the camera behind the ship
        float camX = posX - lookX ;//* .10f;
        float camY = 0.0f;//posY + 1.0f; // Raise the camera a bit
        float camZ = posZ - lookZ ;//* .10f;

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
//glScalef(scaleX, scaleY, scaleZ) scales the current matrix according to planet LOD
void Spaceship::render(int scale) const {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(angleY, 0, 1, 0);
    glRotatef(angleX, 1, 0, 0);

    // Apply inverse scaling: higher scale value = smaller render size
    float scaleFactor = 1.0f / static_cast<float>(scale);
    glScalef(scaleFactor, scaleFactor, scaleFactor);

    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCone(0.1, 0.3, 10, 10);
    glPopMatrix();
}
