#include "StdAfx.h"
#include "camera.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h"

/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ���������������� ������ �� 2� ���������� ��������.
/////   2 ����� �������������� ������� �������� ���������, �� �������� ��
/////   � ���� �������������.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

coord cross(coord vVector1, coord vVector2)
{
	coord vNormal = coord();
 
	// ���� � ��� ���� 2 ������� (������ ������� � ������������ ������), 
	// � ��� ���� ���������, �� ������� �� ����� ��������� ���� � 90 ��������.
	// ������� cross'a �����, �� ��� ������ ��������� � ������� ����. 
	// �������� X ��� ������� - (V1.y * V2.z) - (V1.z * V2.y)
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
 
	// �������� Y - (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
 
	// �������� Z: (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z  = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
 
	// *�����* �� �� ������ ������ ���� �������, ����� ������ �� ����� ��������.
	// ������ ���� ������ ���, ��� �����. ������ ���������, ���� �� ����� �, �� ��
	// ����������� �������� X ���� ��������, � �� �� ����� ��� Y � Z. ��������,
	// �� ������������� �������� �� ���� ������ ����, � ������� �� ��� �� �����.
 
	// ����, ����� �� ���? ��� ����� ����� ���, ������ ������� ���������. �������� ������
	// ����� � ������ ������� - ������������ ��� ������ (0,1,0). 
	// �������� ������ ����� � ���� ����������, ��� ��� ��� ���������� ��� 
	// ���������� ����. ��������� ���� ����� �� �������� �������, ���� � ��� 
	// � ��� ���, ��� ��� ����������.
 
	// ������ ���������.
	return vNormal;
}

/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////				���������� �������� �������
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
 
float getMagnitude(coord vNormal)
{
	// ��� ���� ��� �������� ����� �������, 
	// �.�. ����� �������. �� ���������� ��� ���������� ��� ������������
	// �������. ��� �������: magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)   ��� V - ������.
 
	return (float)sqrt(
		  (vNormal.x * vNormal.x) 
		+ (vNormal.y * vNormal.y)
		+ (vNormal.z * vNormal.z) 
	);
}

/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	���������� ����������������� ������, ������ ��������==1, 
/////	��� ������ ��� �������� �����.
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

coord normalize(coord vCoord)
{
	// �� ��������, ��� ���� ��� �-�? �� ������ ���������, ��� ��� ������ ��������������.
	// ������ �������������� - ������, ��� ������ ����� 1. ��������,
	// ������ (2,0,0) ����� ������������ ����� (1,0,0).
 
	// �������� �������� �������
	float magnitude = getMagnitude(vCoord);
 
	// ������ � ��� ���� ��������, � �� ����� ��������� ��� ������ �� ��� ��������.
	// ��� ������� ������ ������� ������ �������, ��� � ��� ����� ����� ��������.
	vCoord = vCoord / magnitude;
 
	return vCoord;
}

///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	������� �-� ���������� �������� � ���. �����
/////
///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
void Camera::setViewByMouse()
{
	POINT mousePos;			// ��� ���������, �������� X � Y ������� ����
 
	// �������� " >> 1" - �� �� �����, ��� ������� �� 2, �� ������� �������
	int middleX = glutGet(GLUT_WINDOW_WIDTH) >> 1;	// ��������� �������� ������
	int middleY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;	// � �������� ������ ������
	float angleY = 0.0f;	// ����������� ������� �����/����
	float angleZ = 0.0f;	// ��������, ����������� ��� �������� �����-������ (�� ��� Y)
	static float currentRotX = 0.0f;
 
	// �������� ������� �����. ����
	GetCursorPos(&mousePos);
 
	// ���� ������ ������� � ��� �� ���������, �� �� ������� ������
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;
 
	// ������, ������� ���������� �������, ���������� ��� ������� � ��������.
	SetCursorPos(middleX, middleY);
 
	// ������ ��� ����� ����������� (��� ������), ���� ��������� ������.
	// ��� ������� - ������� ���������. ������ �������� ������� ����� � ������� �� ��
	// ����� ������� ����: VECTOR = P1 - P2; ��� P1 - ������� ����� (400,300 ��� 800�600).
	// ����� ��������� ������ X � Y (��� �����������), � ���� �������� 
	// �� 1000, ����� ������ ����� ����� �������.
	angleY = (float)((middleX - mousePos.x))/1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;
 
	static float lastRotX = 0.0f;
	lastRotX = currentRotX;		// ��������� ��������� ���� �������� 
					// � ���������� ������ currentRotX
 
	// ���� ������� �������� ������ 1 �������, ������� ���, ����� �� ������� ������� ������
	if(currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
 
		// ������� �� ���������� ����
		if(lastRotX != 1.0f)
		{
			// ����� ����� ���, ������ ������� ��������� ����� � ����, ����� 
			// ����� ������, ���������������� ������� ������� ������ � 
			// ������������� �������.
			// ��� � ����� ���� ���. � ������ ��� ������������ ��� ���, 
			// ������� �� ������������� �.
			coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = normalize(vAxis);
 
			// ������� ������ ������ ����� ��� �� �������� ����
			this->rotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
 
	// ���� ���� ������ -1.0f, ��������, ��� �������� �� �����������
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		if(lastRotX != -1.0f)
		{
			// ����� �� ��������� ���
			coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = normalize(vAxis);
 
			// �������
			this->rotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	// ���� ������������ � ������� 1.0f -1.0f - ������ �������
	else
	{
		coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
		vAxis = normalize(vAxis);
		this->rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}
 
	// ������ ������� ������ ������ Y-���
	this->rotateView(angleY, 0, 1, 0);
}

///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	����������� ������ CCamera
/////
///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Camera::Camera()
{
	coord vZero = coord();		//�������������� ������ ����� ������� � ������� ����������
	coord vView = coord(0.0, 1.0, 0.5);		//����. ������ �������
	coord vUp = coord(0.0, 0.0, 1.0);		//������ ����.
 
	m_vPosition = vZero;
	m_vView = vView;
	m_vUpVector = vUp;
}

///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	������������� �������, ������, ����. ������ ������
/////
///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
 
void Camera::positionCamera(
	float positionX, float positionY, float positionZ,
	float viewX,	 float viewY,	  float viewZ, 
	float upVectorX, float upVectorY, float upVectorZ
)
{
	coord vPosition	= coord(positionX, positionY, positionZ);
	coord vView		= coord(viewX, viewY, viewZ);
	coord vUpVector	=  coord(upVectorX, upVectorY, upVectorZ);
 
	//�������� ��� ������ ������ ����� ���������� ����������.
	//����� ������ ����� ��������� ���������� ������ ���������� ������� ��������.
 
	m_vPosition = vPosition;
	m_vView = vView;
	m_vUpVector = vUpVector;
}

///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	                  �������� ������ ������ ���
/////
///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Camera::rotateView(float angle, float x, float y, float z)
{
	coord vNewView;
	coord vView;
 
	// ������� ��� ������ ������� (�����������, ���� �� �������)
	vView.x = m_vView.x - m_vPosition.x;	//����������� �� X
	vView.y = m_vView.y - m_vPosition.y;	//����������� �� Y
	vView.z = m_vView.z - m_vPosition.z;	//����������� �� Z
 
	// ������, ���� ������ �������, ���������� � CVector3 "vView", �� ����� ������� ���.
	// ��� �-� ����� ���������, ����� ����� ���������� ������-�������.
	// ����, ��� ����� ��������� ������ ����� �������. ����������� ��� �������� ���:
	// ������, �� ����� �� �����, ������ ������. �� ������� � �����-�� �����, �����?
	// ������, ���� �� �������� ������ ������ ��� �������, ����������� ������� ���������.
	// �������������� ������������ �����, �� ������� �� ������� (������ �������).
	// ��� ������ �� �������� m_vView - ������ ��� ��� � ���� ������ 
	// �������. �� ����� ������� m_vView ������ m_vPosition
	// �� �����, ����� ����������� �� ���.
	// ����� ������� ���-��, ���������� ����� � �������. ��� ������������� sin() & cos() ��
	// ����� ���������� math.h.
	//
	// ����� ����������� �������� ������, �� ����� ������������ axis-angle ��������.
	// � ������ ������������, ��� ������� ��� �������� �������� �� ����� ������, ��
	// �������� �� ����� ����. Axis-angle �������� ��������� ��� ������� ����� � ������������
	// ������ ������ ���. ��� ������, ��� �� ����� ����� ���� ����� ������� (m_vView) �
	// ������� ������ ����� �������.
	// ����� ����� ������ ��������� ��������, ������� ��� ���������� ���������
	// ��������: http://astronomy.swin.edu.au/~pbourke/geometry/rotate/
 
	// ���������� 1 ��� ����� � ������� ����������� ����
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
 
	// ������ ����� ������� X ��� ��������� �����
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)	* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;
 
	// ������ ������� Y
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)	* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;
 
	// � ������� Z
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)	* vView.z;
 
	// ������ ������ ������� ����� ������ �������� � ����� �������, �����
	// ���������� ����� ������ ������.
	m_vView.x = m_vPosition.x + vNewView.x;
	m_vView.y = m_vPosition.y + vNewView.y;
	m_vView.z = m_vPosition.z + vNewView.z;
}

///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This rotates the position around a given point
/////
///////////////////////////////// ROTATE AROUND POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Camera::rotateAroundPoint(coord vCenter, float angle, float x, float y, float z)
{
	coord vNewPosition;
 
	// ����� ������� ���� ������� ������ �����, ��, ��� ��� ���� - ����� ������
	// �� ����� ������� � ����������� ����� ��������. ���� ��� ������� ������, 
	// �� ��������� ������ ����� � �������� ���������/�����. 
	// ����� ������ vCenter - �����, ������ ������� �� ���������.
 
	// ������� �����, ������ �������� ����� ��������
	coord vPos = m_vPosition - vCenter;
 
	// �������� ����� � ������� ����
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
 
	// ������ �������� X ����� ��������
	vNewPosition.x  = (cosTheta + (1 - cosTheta) * x * x)		* vPos.x;
	vNewPosition.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vPos.y;
	vNewPosition.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vPos.z;
 
	// � �������� Y
	vNewPosition.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vPos.x;
	vNewPosition.y += (cosTheta + (1 - cosTheta) * y * y)		* vPos.y;
	vNewPosition.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vPos.z;
 
	// � Z...
	vNewPosition.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vPos.x;
	vNewPosition.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vPos.y;
	vNewPosition.z += (cosTheta + (1 - cosTheta) * z * z)		* vPos.z;
 
	// ������ ������ �������� ����� ������ � ����� �������,
	// ����� ���������� ����� ������� ������.
	m_vPosition = vCenter + vNewPosition;
}

///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	�������� ������ ������-����� � �������� ���������
/////
///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Camera::moveCamera(float speed)
{
	coord vVector = m_vView - m_vPosition;

	m_vPosition.x += vVector.x * speed;
	m_vPosition.y += vVector.y * speed;
	m_vPosition.z += vVector.z * speed;
	m_vView.x += vVector.x * speed;
	m_vView.y += vVector.y * speed;
	m_vView.z += vVector.z * speed;

}

// ��� ��. ������ �� ������� �����, ����������� ��� ���� ���-�� ��������� � ���� =)
