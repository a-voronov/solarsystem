#pragma once

typedef struct coord 
{
public:
	double x;
	double y;
	double z;

	coord (double x, double y, double z) 
	{ 
		this->x = x; 
		this->y = y; 
		this->z = z; 
	}
	
	bool isZero()
	{
		return (this->x == 0.0) 
			&& (this->y == 0.0) 
			&& (this->z == 0.0);
	}
} coord;

typedef struct rotationCoord : public coord 
{
public:
	double angle;

	rotationCoord (double angle, double x, double y, double z) : coord (x, y, z)
	{
		this->angle = angle;
	}
} rotationCoord;
