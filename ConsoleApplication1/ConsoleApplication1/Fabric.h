#pragma once

#include <memory>
#include <random>

#include "curve.h"

// в данном заголовочном файле реализован паттерн "фабрика"
class Fabric
{
protected:
	const double epsilon {0.001};
	std::random_device randomizer; // инициализаци€ источника случайных чисел
	std::uniform_real_distribution <double> real_randomizer {-1, 1}; // инициализаци€ 'рандомайзера' дл€ чисел с плавающей точкой дл€ рандомайзера
public:
	virtual std::shared_ptr<Curve> createCurve() = 0; // создание кривой
	virtual ~Fabric() {}
	virtual void setDiaposon(double min, double max) = 0; // задать диапазон значений дл€ рандомайзера

};

class CircleFabric : Fabric
{
public:
	CircleFabric() : Fabric() { }
	virtual std::shared_ptr<Curve> createCurve()
	{
		double radii{ abs(real_randomizer(randomizer))}; // задаЄм значение дл€ радиуса
		while (radii < epsilon) // прибавл€ем случайное число из диапазона, пока не будет больше нул€
		{
			radii += abs(real_randomizer(randomizer));
		}

		return std::make_shared<Circle>(Point3D{ real_randomizer(randomizer), real_randomizer(randomizer) }, radii);
	}
	virtual void setDiaposon(double min, double max) 
	{
		// условие дл€ недопуска значений близким к нулю
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

