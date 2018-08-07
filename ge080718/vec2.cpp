#include "vec2.h"
#include <math.h>

Vec2::Vec2(float x, float y)
	: x(x)
	, y(y)
{
}

Vec2::Vec2()
	: Vec2(0, 0)
{
}

void Vec2::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vec2::setX(float x)
{
	this->x = x;
}

void Vec2::setY(float y)
{
	this->y = y;
}

float Vec2::length() const
{
	return sqrtf(x * x + y * y);
}

Vec2& Vec2::normalize()
{
	float len = length();
	if (len != 0)
	{
		x /= len;
		y /= len;
	}

	return *this;
}

Vec2 Vec2::getNormal() const
{
	return Vec2(*this).normalize();
}

Vec2& Vec2::add(const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vec2& Vec2::add(float x, float y)
{
	this->x += x;
	this->y += y;
	return *this;
}

Vec2& Vec2::sub(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2& Vec2::sub(float x, float y)
{
	this->x -= x;
	this->y -= y;
	return *this;
}
Vec2& Vec2::mul(float r)
{
	x *= r;
	y *= r;
	return *this;
}

Vec2& Vec2::mul(float x, float y)
{
	x *= x;
	y *= y;
	return *this;
}

Vec2& Vec2::mul(const Vec2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator*(const Vec2& other) const
{
	return Vec2(x * other.x, y * other.y);
}

Vec2 Vec2::operator*(float r) const
{
	return Vec2(x * r, y * r);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	return add(other);
}

Vec2& Vec2::operator-=(const Vec2& other)
{
	return sub(other);
}

Vec2& Vec2::operator*=(const Vec2& other)
{
	return mul(other);
}

Vec2& Vec2::operator*=(float r)
{
	return mul(r);
}

bool Vec2::operator==(const Vec2& other)
{
	return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2& other)
{
	return !(*this == other);
}