#include <GL/glut.h>
#include "world.h"
#include <stdexcept>
// ======================
// Region Class Functions
// ======================

Region::Region() : id(0) {
    // Default initialization (for instance, id is set to 0)
}

Region::Region(int id) : id(id) {
    // Parameterized constructor
}

Region::Region(const Region &other) : id(other.id) {
    // Copy constructor: copy the id (and add more as needed)
}

Region& Region::operator=(const Region &other) {
    if (this != &other) {
        id = other.id;
    }
    return *this;
}

Region::~Region() {
    // Clean up resources if necessary
}

void Region::print() const {
    std::cout << "Region(" << id << ")";
}

int Region::getId() const {
    return id;
}

// ======================
// Matrix Class Functions
// ======================

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows(rows), cols(cols), data(rows, std::vector<Region>(cols))
{
    // Optionally initialize Regions with some meaningful data.
    // For example, we can number Regions sequentially:
    int counter = 1;
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            data[i][j] = Region(counter++);
        }
    }
}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows), cols(other.cols), data(other.data)
{
    // Copy constructor uses the vector's copy constructor.
}

Matrix& Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;
    }
    return *this;
}

Matrix::~Matrix() {
    // Vectors automatically clean up their memory.
}

Region& Matrix::at(std::size_t row, std::size_t col) {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[row][col];
}

const Region& Matrix::at(std::size_t row, std::size_t col) const {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[row][col];
}

std::size_t Matrix::getRows() const {
    return rows;
}

std::size_t Matrix::getCols() const {
    return cols;
}

void Matrix::print() const {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            data[i][j].print();
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

RenderableObject::RenderableObject(float x, float y, float z)
    : posX(x), posY(y), posZ(z) {}

RenderableObject::~RenderableObject() {}

Sphere::Sphere(float x, float y, float z, float r, int sl, int st)
    : RenderableObject(x, y, z), radius(r), slices(sl), stacks(st) {}

void Sphere::render() {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(0.2f, 0.7f, 0.3f);
    glutSolidSphere(radius, slices, stacks);
    glPopMatrix();
}

Cube::Cube(float x, float y, float z, float s)
    : RenderableObject(x, y, z), size(s) {}

void Cube::render() {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidCube(size);
    glPopMatrix();
}