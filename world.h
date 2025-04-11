// world.h
#ifndef WORLD_H
#define WORLD_H

#include <GL/glut.h> // Include OpenGL/GLUT for rendering functions

#include <vector>
#include <cstddef>
#include <iostream>

// The Region class represents an individual cell in the Matrix.
class Region {
public:
    // Default constructor
    Region();

    // Parameterized constructor
    explicit Region(int id);

    // Copy constructor
    Region(const Region &other);

    // Assignment operator
    Region& operator=(const Region &other);

    // Destructor
    ~Region();

    // A simple method to print the Region (for demonstration purposes)
    void print() const;

    // Getter for the Region's id.
    int getId() const;

private:
    int id; // An example property; you can add more properties as needed.
};

// The Matrix class encapsulates a two-dimensional vector (matrix)
// of Region objects.
class Matrix {
public:
    // Constructor: creates a Matrix with given rows and columns.
    Matrix(std::size_t rows, std::size_t cols);

    // Copy constructor
    Matrix(const Matrix &other);

    // Assignment operator
    Matrix& operator=(const Matrix &other);

    // Destructor
    ~Matrix();

    // Access the Region at [row, col]. Throws std::out_of_range if index invalid.
    Region& at(std::size_t row, std::size_t col);
    const Region& at(std::size_t row, std::size_t col) const;

    // Accessors for the dimensions of the matrix.
    std::size_t getRows() const;
    std::size_t getCols() const;

    // Print the entire matrix by printing each Region
    void print() const;

private:
    std::size_t rows, cols;
    std::vector< std::vector<Region> > data;
};

class RenderableObject {
protected:
    float posX, posY, posZ;
public:
    RenderableObject(float x, float y, float z);
    virtual void render() = 0;
    virtual ~RenderableObject();
    // Getters for position (if needed externally)
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }
};

class Sphere : public RenderableObject {
private:
    float radius;
    int slices, stacks;
public:
    Sphere(float x, float y, float z, float r, int sl, int st);
    void render() override;
    // Getters for LOD
    int getSlices() const { return slices; }
    int getStacks() const { return stacks; }
    void setSlices(float sl) { slices = sl; }
    void setStacks(float st) { stacks = st; }
};

class Cube : public RenderableObject {
private:
    float size;
public:
    Cube(float x, float y, float z, float s);
    void render() override;
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