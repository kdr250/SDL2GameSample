#pragma once

#include <iostream>

struct Vector2D
{
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	Vector2D& Add(const Vector2D& other);
	Vector2D& Subtract(const Vector2D& other);
	Vector2D& Multiply(const Vector2D& other);
	Vector2D& Divide(const Vector2D& other);

	friend Vector2D operator+(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D operator-(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D operator*(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D operator/(Vector2D& vector1, const Vector2D& vector2);

	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D& operator*=(const Vector2D& other);
	Vector2D& operator/=(const Vector2D& other);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vector);
};
