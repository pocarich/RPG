#pragma once

template<typename T>
class Vector2
{
public:
	T x;
	T y;
public:
	Vector2() :x(0), y(0) {}
	Vector2(const Vector2& v) :x(v.x), y(v.y) {}
	Vector2(T x, T y) :x(x), y(y) {}

	Vector2& operator = (const Vector2& v) 
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	bool operator == (const Vector2& v) const 
	{
		return (x == v.x && y == v.y);
	}
	bool operator != (const Vector2& v) const 
	{
		return (x != v.x || y != v.y);
	}
	const Vector2& operator+() const
	{
		return *this;
	}
	Vector2& operator+() 
	{
		return *this;
	}
	Vector2 operator-() const 
	{
		return Vector2(-x, -y);
	}
	Vector2& operator+=(const Vector2& v) 
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2& operator+(Vector2&& v) const
	{
		return v += *this;
	}
	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2 operator-(const Vector2& v) const 
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2& operator-(Vector2&& v) const
	{
		v.x = -v.x;
		v.y = -v.y;
		v += *this;
		return v;
	}
	Vector2& operator*=(T k) 
	{
		x *= k;
		y *= k;
		return *this;
	}
	Vector2 operator*(T k) const 
	{
		return Vector2(x * k, y * k);
	}
	Vector2& operator/=(T k)
	{
		x /= k;
		y /= k;
		return *this;
	}
	Vector2 operator/(T k) const
	{
		return Vector2(x / k, y / k);
	}
	T operator*(const Vector2& v) const
	{
		return (x * v.x) + (y * v.y);
	}
	T operator/(const Vector2& v) const
	{
		return (x * v.y) - (y * v.x);
	}
	double length() const 
	{
		return std::sqrt((*this) * (*this));
	}
	Vector2 unit() const
	{
		const T len = length();
		return len == 0 ? *this : *this / len;
	}
	double angle() const 
	{
		return std::atan2(y, x);
	}

	static Vector2<T> CalcDifference(const Vector2<T>& a, const Vector2<T>& b)
	{
		Vector2<T> difference;
		difference.x = a.x - b.x;
		difference.y = a.y - b.y;
		return difference;
	}

	static bool CheckIn(const Vector2<T>& a, const Vector2<T>& min, const Vector2<T>& max)
	{
		Vector2<T> v(abs(a.x), abs(a.y));
		return min.x <= v.x&&v.x <= max.x&&min.y <= v.y &&v.y <= max.y;
	}

	static const Vector2<double> UP;
	static const Vector2<double> DOWN;
	static const Vector2<double> RIGHT;
	static const Vector2<double> LEFT;
	static const Vector2<double> ZERO;
};