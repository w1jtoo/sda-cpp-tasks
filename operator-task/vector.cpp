#include "vector.h"

Vector::Vector(const Vector &source)
    : Vector { source.x, source.y, source.z} {}

Vector::Vector(float _x, float _y, float _z){
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

Vector::Vector(float default_value){
    x = default_value;
    y = default_value;
    z = default_value;
}

Vector Vector::operator* (const float &number) {
    return Vector(number * x, number * y, number * z);
}

Vector operator* (const float& n,const Vector& v) {
    return Vector(n * v.x, n * v.y, n * v.z);
}

Vector Vector::operator* (const Vector &other) {
    return Vector(x * other.x, y * other.y, z * other.z);
}

Vector Vector::operator* (const Vector &other) const{
    return Vector(x * other.x, y * other.y, z * other.z);
}

Vector::operator bool() const {
    return bool(x) || bool(y) || bool(z);
}

Vector Vector::operator+ (const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator+ (const Vector &other) {
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator- (const Vector &other) {
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator- (const Vector &other) const{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector& Vector::operator+= (const Vector &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector& Vector::operator-= (const Vector &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector& Vector::operator*= (const Vector &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Vector& Vector::operator *= (const float &number) {
    x *= number;
    y *= number;
    z *= number;

    return *this;
}

Vector& Vector::operator= (const Vector &other) noexcept = default;
Vector::Vector() = default;
Vector::~Vector() = default;

Vector Vector::operator-() {
    return Vector(-x, -y, -z);
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}
