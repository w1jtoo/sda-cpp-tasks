#include "matrix.h"

Matrix::Matrix() = default;
Matrix::~Matrix() noexcept = default;
Matrix &Matrix::operator= (const Matrix &other) noexcept = default;
Matrix::Matrix (const Matrix &source) noexcept :
    x (source.x), y (source.y), z (source.z)
{}


Matrix::Matrix(Vector _x, Vector _y, Vector _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}
Matrix Matrix::operator* (const float& n) {
    return Matrix(n * x, n * y, n * z);
}

Matrix Matrix::operator+ (const Matrix &other) {
    return Matrix(x + other.x, y +other.y, z + other.z);
}

Matrix& Matrix::operator+= (const Matrix &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Matrix Matrix::operator- (const Matrix &other) {
    return Matrix(x - other.x, y - other.y, z - other.z);
}

Matrix& Matrix::operator-= (const Matrix &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Matrix::Matrix(float default_value) {
    this->x = Vector(default_value);
    this->y = Vector(default_value);
    this->z = Vector(default_value);
}

float Matrix::operator~ () {
    return x.x * y.y * z.z 
        + x.y * z.x * y.z 
        + y.z * x.z * z.y 
        - ( x.z * y.y * z.x 
                + y.x * x.y * z.z 
                + x.x * y.z * z.y);
}

Matrix Matrix::operator* (const Matrix &other) {
    return Matrix(x * other.x, y * other.y, z * other.z);
}

Matrix Matrix::operator* (const Matrix &other) const {
    return Matrix(x * other.x, y * other.y, z * other.z);
}

Matrix& Matrix::operator*= (const Matrix &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Matrix& Matrix::operator*= (const float &number) {
    x *= number;
    y *= number;
    z *= number;

    return *this;
}

#define     MUL(base)       x.base * v.x + y.base * v.y + z.base * v.z

Vector Matrix::operator* (const Vector& v) {
    return Vector(MUL(x), MUL(y), MUL(z));
}

Matrix operator* (const float& n, const Matrix& m) {
    return Matrix(n * m.x, n * m.y, n * m.z);
}


Matrix::operator bool() const {
    return bool(x) & bool(y) & bool(z);
}

Matrix Matrix::operator- () {
    return Matrix(-x, -y, -z);
}

Matrix Matrix::operator- () const {
    return Matrix(-x, -y, -z);
}


//#define MULR(base)          m.base.x * x \
//                            + m.base.y * y + m.base.z * z
//
//Vector Vector::operator* (const Matrix &m) {
//    return Vector(MULR(x), MULR(y), MULR(z));
//}
//
//Vector& Vector::operator*= (const Matrix &m) {
//    x = MULR(x);
//    y = MULR(y);
//    z = MULR(z);
//
//    return *this;
//}

