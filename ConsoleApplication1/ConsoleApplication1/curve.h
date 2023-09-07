#pragma once
#include <math.h>

// структуры, описывающие точку и вектор в 3D-пространстве
struct Point3D { double x{}, y{}, z{}; };
struct Vector3D { double x{}, y{}, z{}; };

// базовый класс кривой
class Curve 
{
public:
	virtual ~Curve() {}
	// функции для получения трехмерной точки и первой производной по параметру t вдоль кривой
	virtual Point3D curve_point(double t) const = 0; 
	virtual Vector3D curve_vector(double t) const = 0;
protected:
	// точка-центр
	Point3D center;
	Curve() = default;
	Curve(const Point3D& c) : center(c){}
};

class Circle : public Curve
{
	double radii{};

public:
	Circle() = default;
	Circle(const Point3D& c, double r) : Curve(c), radii(r) {}

	virtual ~Circle() {}
	// функция геттер для радиуса
	double getRadii() const 
	{ 
		return radii; 
	}

	virtual Point3D curve_point(double t) const override
	{
		return Point3D { radii * cos(t) + center.x, 
						 radii * sin(t) + center.y, 
						 center.z};
	}
	virtual Vector3D curve_vector(double t) const override
	{
		return Vector3D{ -1 * radii * sin(t), 
						 radii * cos(t)};
	}

};

class Ellipse : public Curve
{
	double radii_x{};
	double radii_y{};
public:
	Ellipse() = default;
	Ellipse(const Point3D& c, double rx, double ry) : Curve(c), radii_x(rx), radii_y(ry) {}

	virtual ~Ellipse() {}

	virtual Point3D curve_point(double t) const override
	{
		return Point3D{ radii_x * cos(t) + center.x,
						radii_y * sin(t) + center.y,
						center.z };
	}
	
	virtual Vector3D curve_vector(double t) const override
	{
		return Vector3D{ -1 * radii_x *sin(t),
						 radii_y * cos(t)};
	}
};

class Helix : public Curve
{
	double step{};
	double radii{};
public:
	Helix() = default;
	Helix(const Point3D& c, double s, double r) : Curve(c), step(s), radii(r) {}

	virtual ~Helix() {}

	virtual Point3D curve_point(double t) const override
	{
		return Point3D{ radii * t * cos(t) + center.x,
						radii * t * sin(t) + center.y,
						step * t * center.z };
	}

	virtual Vector3D curve_vector(double t) const override
	{
		return Vector3D { radii * (cos(t) - t * sin(t)),
						  radii * (sin(t) + t * cos(t)),
						  step
		};
	}
	
};

