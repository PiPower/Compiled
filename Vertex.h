#pragma once
struct Vertex
{
	Vertex() = default;
	Vertex(const Vertex& base) : X(base.X), Y(base.Y) {}
	Vertex(double x, double y) : X(x), Y(y) {}
	Vertex operator+(const Vertex& rhs)
	{
		return Vertex(X + rhs.X, Y + rhs.Y);
	}
	Vertex operator-(const Vertex& rhs)
	{
		Vertex out(X - rhs.X, Y - rhs.Y);
		return out;
	}
	Vertex operator/(const double c)
	{
		return Vertex(X / c, Y / c);
	}
	Vertex operator*(const Vertex& Scalar)
	{
		return Vertex{ X * Scalar.X,Y * Scalar.Y };
	}
	void operator*=(const Vertex& Scalar)
	{
		X *= Scalar.X;
		Y *= Scalar.Y;
	}
	void operator+=(const Vertex& Offset)
	{
		X += Offset.X;
		Y += Offset.Y;
	}
	void operator+=(const double c)
	{
		X += c;
		Y += c;
	}
	void operator-=(const double c)
	{
		X -= c;
		Y -= c;
	}
	double X;
	double Y;
};