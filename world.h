// world.h
#ifndef WORLD_H
#define WORLD_H

#include <GL/glut.h> // Include OpenGL/GLUT for rendering functions

// Abstract base class for all renderable objects in the world
class RenderableObject {
protected:
    float posX, posY, posZ; // Position in 3D space (x, y, z coordinates)

public:
    // Constructor to initialize position
    RenderableObject(float x, float y, float z) : posX(x), posY(y), posZ(z) {}

    // Pure virtual function for rendering the object
    virtual void render() = 0;

    // Virtual destructor for proper cleanup in derived classes
    virtual ~RenderableObject() {}
};

// Concrete class representing a spherical object (e.g., a planet) in the world
class Sphere : public RenderableObject {
private:
    float radius;        // Radius of the sphere
    int slices, stacks;  // Number of subdivisions for smooth rendering

public:
    // Constructor to initialize position and sphere properties
    Sphere(float x, float y, float z, float r, int sl, int st)
        : RenderableObject(x, y, z), radius(r), slices(sl), stacks(st) {}

    // Render the sphere using OpenGL
    void render() override {
        glPushMatrix();                    // Save current matrix state
        glTranslatef(posX, posY, posZ);    // Move to object's position
        glColor3f(0.2f, 0.7f, 0.3f);      // Set greenish color
        glutSolidSphere(radius, slices, stacks); // Draw the sphere
        glPopMatrix();                     // Restore matrix state
    }
};
class Cube : public RenderableObject {
private:
    float size;
public:
    Cube(float x, float y, float z, float s) : RenderableObject(x, y, z), size(s) {}
    void render() override {
        glPushMatrix();
        glTranslatef(posX, posY, posZ);
        glColor3f(0.5f, 0.5f, 0.5f);
        glutSolidCube(size);
        glPopMatrix();
    }
};

#include <vector>

class World {
private:
    std::vector<RenderableObject*> objects;

public:
    World() {}
    ~World() { for (auto obj : objects) delete obj; }

    void addObject(RenderableObject* obj) { objects.push_back(obj); }
    void render() {
        for (auto obj : objects) obj->render();
    }
};
#endif // WORLD_H