#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include "Log.h"
#include "basic_func.h"

class Vector2D
{
    public:
        Vector2D();
        Vector2D(float nx, float ny) { x = nx; y = ny; }
        virtual ~Vector2D();

        void normalize();
        int dotProduct(const Vector2D& b) { return (x*b.x) + (y*b.y); }
        Vector2D lNormal();
        Vector2D rNormal();

        Vector2D project(Vector2D& vec_p);

        void setComponents(float nx, float ny) { x = nx; y = ny; }
        void componentFromPolar(float magnitude, int angle);

        void setAngle(int new_ang);
        void setMagnitude(float magn);

        void setX(float val) { x = val; }
        void setY(float val) { y = val; }

        int getAngle();
        float length();

        Vector2D& operator+=(const Vector2D &rhs) { x += rhs.x; y += rhs.y; return *this; }
        Vector2D& operator-=(const Vector2D &rhs) { y += rhs.y; x += rhs.x; return *this; }
        Vector2D& operator/=(const float &f) {x /= f; y /= f; return *this; }
        Vector2D& operator*=(const float &f) {x *= f; y *= f; return *this; }

        Vector2D& operator+ (const Vector2D &rhs) { Vector2D new_vec(*this); new_vec += rhs; return new_vec; }
        Vector2D& operator- (const Vector2D &rhs) {Vector2D new_vec(*this); new_vec -= rhs; return new_vec; }
        Vector2D& operator* (const float &f) { Vector2D new_vec(*this); new_vec *= f; return new_vec; }
        Vector2D& operator/ (const float &f) { Vector2D new_vec(*this); new_vec /= f; return new_vec; }

        float x;
        float y;
};

#endif // VECTOR2D_H
