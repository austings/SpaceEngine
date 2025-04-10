#ifndef SPACESHIP_H
#define SPACESHIP_H

class Spaceship {
private:
    float posX, posY, posZ;         // Spaceship position
    float lookX, lookY, lookZ;      // Look direction
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
    void applyCameraView() const;
    void render() const;
    void toggleCameraView();
    
    // Getters for position (if needed externally)
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }
};

#endif // SPACESHIP_H