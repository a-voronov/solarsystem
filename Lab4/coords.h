#pragma once

typedef struct coord 
{
public:
	double x;
	double y;
	double z;

	coord () 
	{ 
		this->x = 0.0; 
		this->y = 0.0; 
		this->z = 0.0; 
	}

	coord (double x, double y, double z) 
	{ 
		this->x = x; 
		this->y = y; 
		this->z = z; 
	}

	coord operator+ (coord vector)
	{
		return coord(vector.x + this->x, vector.y + this->y, vector.z + this->z);
	}

	coord operator- (coord vector)
	{
		return coord(this->x - vector.x, this->y - vector.y, this->z - vector.z);
	}

	coord operator* (float num)
	{
		return coord(this->x * num, this->y * num, this->z * num);
	}

	coord operator/ (float num)
	{
		return coord(this->x / num, this->y / num, this->z / num);
	}
	
	bool isZero ()
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
