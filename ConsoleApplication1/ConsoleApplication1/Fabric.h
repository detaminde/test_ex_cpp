#pragma once

#include <memory>
#include <random>

#include "curve.h"

// � ������ ������������ ����� ���������� ������� "�������"
class Fabric
{
protected:
	const double epsilon {0.001};
	std::random_device randomizer; // ������������� ��������� ��������� �����
	std::uniform_real_distribution <double> real_randomizer {-1, 1}; // ������������� '������������' ��� ����� � ��������� ������ ��� ������������
public:
	virtual std::shared_ptr<Curve> createCurve() = 0; // �������� ������
	virtual ~Fabric() {}
	virtual void setDiaposon(double min, double max) = 0; // ������ �������� �������� ��� ������������

};

class CircleFabric : Fabric
{
public:
	CircleFabric() : Fabric() { }
	virtual std::shared_ptr<Curve> createCurve()
	{
		double radii{ abs(real_randomizer(randomizer))}; // ����� �������� ��� �������
		while (radii < epsilon) // ���������� ��������� ����� �� ���������, ���� �� ����� ������ ����
		{
			radii += abs(real_randomizer(randomizer));
		}

		return std::make_shared<Circle>(Point3D{ real_randomizer(randomizer), real_randomizer(randomizer) }, radii);
	}
	virtual void setDiaposon(double min, double max) 
	{
		// ������� ��� ��������� �������� ������� � ����
		if (abs(max) + abs(min) < 2 * epsilon)
			return;
		real_randomizer = decltype(real_randomizer){min, max};
	}
};

class EllipseFabric : Fabric
{
public:
	EllipseFabric() : Fabric() { }
	virtual std::shared_ptr<Curve> createCurve()
	{
		double radii_x{ abs(real_randomizer(randomizer)) }, radii_y {abs(real_randomizer(randomizer))};
		while (radii_x < epsilon)
		{
			radii_x += abs(real_randomizer(randomizer));
		}
		while (radii_y < epsilon)
		{
			radii_y += abs(real_randomizer(randomizer));
		}

		return std::make_shared<Ellipse>(Point3D{ real_randomizer(randomizer), real_randomizer(randomizer) }, radii_x, radii_y);
	}
	virtual void setDiaposon(double min, double max)
	{
		if (abs(max) + abs(min) < 2 * epsilon)
			return;
		real_randomizer = decltype(real_randomizer){min, max};
	}
};

class HelixFabric : Fabric
{
public:
	HelixFabric() : Fabric() { }
	virtual std::shared_ptr<Curve> createCurve()
	{
		double radii_x{ abs(real_randomizer(randomizer)) }, step{ abs(real_randomizer(randomizer)) };
		while (radii_x < epsilon)
		{
			radii_x += abs(real_randomizer(randomizer));
		}
		while (step < epsilon)
		{
			step += abs(real_randomizer(randomizer));
		}

		return std::make_shared<Helix>(Point3D{ real_randomizer(randomizer), real_randomizer(randomizer), real_randomizer(randomizer) }, radii_x, step);
	}
	virtual void setDiaposon(double min, double max)
	{
		if (abs(max) + abs(min) < 2 * epsilon)
			return;
		real_randomizer = decltype(real_randomizer){min, max};
	}
};

