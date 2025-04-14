#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship {
private:
    float posX, posY, posZ;         // Spaceship position x,y,z
    float lookX, lookY, lookZ;      // spaceship heading direction
    float targetLookX, targetLookY, targetLookZ; //player positioned camera direction
    float upX, upY, upZ;            // Up vector
    float angleX, angleY;           // Pitch and yaw angles
    float moveStep;                 // Movement speed
    float rotateStep;               // Rotation speed
    bool thirdPersonView = false;

public:
    Spaceship();
    void updateLookVector();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnUp();
    void turnDown();
    void turnRight();
    void rotateYaw();
    void rotatePitch();
    void rotateRoll();
    void applyCameraView(int scale) const;
    void render(int scale) const;
    void toggleCameraView();
    
    // Getters for position (if needed externally)
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }
};

#endif // SPACESHIP_H