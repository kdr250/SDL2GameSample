#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

Vector2D operator+(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Add(vector2);
}

Vector2D operator-(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Subtract(vector2);
}

Vector2D operator*(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Multiply(vector2);
}

Vector2D operator/(Vector2D& vector1, const Vector2D& vector2)
{
	return vector1.Divide(vector2);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
	return this->Add(other);
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
	return this->Subtract(other);
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
	return this->Multiply(other);
}

Vector2D& Vector2D::operator/=(const Vector2D& other)
{
	return this->Divide(other);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vector)
{
	stream << "(" << vector.x << "," << vector.y << ")";
	return stream;
}