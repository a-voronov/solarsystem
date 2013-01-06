#pragma once

#include "coords.h"

class Camera 
{
public:
	coord m_vPosition;	// ������� ������.
	coord m_vView;		// ����������� ������.
	coord m_vUpVector;	// ������������ ������.
 
	//� ������ ���������� ����������� "m", �.�. ��� "member"-����������.
	//"v" ���������, �.�. ��� ����� ������ Vector (���������� �� V).
 
 
	// ����������� ������ Camera
	Camera();
 
	// ��� ���������� ���������, ����������� � ����. ������ ������.
	// � �������� ������������ ��� �������������.
	void positionCamera(
		float positionX, float positionY, float positionZ, 
		float viewX,	 float viewY,	  float viewZ, 
		float upVectorX, float upVectorY, float upVectorZ
	);
 
	// ��� �-� ����������� ������ ������/�����
	void moveCamera(float speed);

	// ��� �-� ������� ������ ������ ������� � ����������� �� ���������� ����������.
	// ������� ������� ��� �����-������� ��������. ��� ������, ��� �� ��������� 
	// �-�� ���� �������� � ���, ������ ������� ����� ��������.
	void rotateView(float angle, float x, float y, float z);

	// �������, ��������������� ������ �� ������� ����
	void setViewByMouse();

	// ������� ������� ������ ������ ����� (�������� ������ ���������).
	// vCenter - �����, ������ ������� ��� ���������.
	void rotateAroundPoint(coord vCenter, float angle, float x, float y, float z);
};