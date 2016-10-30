#include "../include/Vector2D.h"

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::~Vector2D()
{

}

void Vector2D::normalize()
{
    float len = length();

    x /= len;
    y /= len;

}

float Vector2D::length()
{
    return sqrt((x*x)+(y*y));
}

Vector2D Vector2D::lNormal()
{
    Vector2D vec_n;

    vec_n.x = y;
    vec_n.y = -x;

    return vec_n;
}

Vector2D Vector2D::rNormal()
{
    Vector2D vec_n;

    vec_n.x = -y;
    vec_n.y = x;

    return vec_n;
}

void Vector2D::componentFromPolar(float magnitude, int angle)
{
    x = magnitude * cos(angle*(3.14159265358979/180));
    y = magnitude * sin(angle*(3.14159265358979/180));
}

void Vector2D::setAngle(int new_ang)
{
    float mag = length();

    x = mag * cos(new_ang*(3.14159265358979/180));
    y = mag * sin(new_ang*(3.14159265358979/180));
}

void Vector2D::setMagnitude(float magn)
{
    int ang = getAngle();

    x = magn * cos(ang*(3.14159265358979/180));
    y = magn * sin(ang*(3.14159265358979/180));
}

int Vector2D::getAngle()
{
    if (x == 0)
    {
        if (y > 0)
        {
            return 270;
        }
        else if (y < 0)
        {
            return 90;
        }
        else
        {
            return 0;
        }
    }

    if (y == 0)
    {
        if (x < 0)
        {
            return 180;
        }
        else if (x > 0)
        {
            return 0;
        }
        else
        {
            return 0;
        }
    }

    float angle = (atan((-y)/x) * (180/3.14159265358979));


    if (x < 0)
    {
        angle += 180;
    }
    else if (y > 0)
    {
        angle += 360;
    }

    return (int)angle;

}

Vector2D Vector2D::project(Vector2D& axis)
{
    Vector2D proj_vec;
    int dot = this->dotProduct(axis);
    float len = axis.length();

    proj_vec.x = axis.x * dot / len;
    proj_vec.y = axis.y * dot / len;

    return proj_vec;
}
