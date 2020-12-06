#pragma once
#include "vector.h"

class Matrix {
public:
    Matrix(const Matrix &source) noexcept;
    Matrix();
    ~Matrix() noexcept;
    Matrix(float default_value);
    Matrix& operator= (const Matrix &other) noexcept;
    Matrix& operator= (const float &other) noexcept = delete;
    explicit operator bool() const;


    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);

    Matrix& operator+= (const Matrix &other);
    Matrix& operator-= (const Matrix &other);

    Matrix operator-();
    Matrix operator-() const;

    Matrix operator* (const Matrix &other);
    Matrix operator* (const Matrix &other) const;
    Matrix& operator*= (const Matrix &other);

    Matrix operator* (const float &other);
    Matrix& operator*= (const float &other);

    Vector operator* (const Vector& vector);

    float operator~ ();

    Vector x = Vector(0.f);
    Vector y = Vector(0.f);
    Vector z = Vector(0.f);

    Matrix(Vector _x, Vector _y, Vector _z);
};


Matrix operator* (const float& number, const Matrix& matrix);
//Vector Vector::operator* (const Matrix &other);
///Vector& Vector::operator*= (const Matrix &other);

