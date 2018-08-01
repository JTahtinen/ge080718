#pragma once

struct Vec2
{
	float		x;
	float		y;

	Vec2(float x, float y);
	Vec2();
	void set(float x, float y);
	void setX(float x);
	void setY(float y);
	float length();
	Vec2& normalize();
	Vec2 getNormal() const;
	Vec2& add(const Vec2& other);
	Vec2& add(float x, float y);
	Vec2& sub(const Vec2& other);
	Vec2& sub(float x, float y);
	Vec2& mul(float r);
	Vec2& mul(float x, float y);
	Vec2& mul(const Vec2& other);

	Vec2 operator+(const Vec2& other) const;
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator-() const;
	Vec2 operator*(const Vec2& other) const;
	Vec2 operator*(float r)	const;
	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);
	Vec2& operator*=(const Vec2& other);
	Vec2& operator*=(float r);
	bool operator==(const Vec2& other);
	bool operator!=(const Vec2& other);
};