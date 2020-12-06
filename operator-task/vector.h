#pragma once

class Vector {
public:
    Vector(const Vector &source);
    Vector();
    ~Vector();
    Vector(float default_value);
    Vector(float _x, float _y, float _z);

    Vector& operator= (const Vector &other) noexcept;

    explicit operator bool() const;

    Vector operator+ (const Vector &other) const;
    Vector operator+ (const Vector &other);

    Vector operator- (const Vector &other);
    Vector operator- (const Vector &other) const;

    Vector operator-();
    Vector operator-() const;


    Vector& operator+= (const Vector &other);
    Vector& operator-= (const Vector &other);
    Vector& operator*= (const Vector &other);
    Vector& operator*= (const float &other);

    Vector operator* (const Vector &other);
    Vector operator* (const Vector &other) const;

    Vector operator* (const float &other);

    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};


Vector operator* (const float& number,const Vector& vector);
