#include <GL/glut.h>

class RenderableObject {
protected:
    float posX, posY, posZ; // Position in 3D space
public:
    RenderableObject(float x, float y, float z) : posX(x), posY(y), posZ(z) {}
    virtual void render() = 0; // Pure virtual function for rendering
    virtual ~RenderableObject() {} // Virtual destructor for proper cleanup
};

class Sphere : public RenderableObject {
private:
    float radius;
    int slices, stacks;
public:
    Sphere(float x, float y, float z, float r, int sl, int st)
        : RenderableObject(x, y, z), radius(r), slices(sl), stacks(st) {}

    void render() override {
        glPushMatrix();
        glTranslatef(posX, posY, posZ);
        glColor3f(0.2f, 0.7f, 0.3f); // Greenish color for the planet
        glutSolidSphere(radius, slices, stacks);
        glPopMatrix();
    }
};