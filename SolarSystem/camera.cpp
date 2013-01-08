#include "StdAfx.h"
#include "camera.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h"

/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Возвращает перпендикулярный вектор от 2х переданных векторов.
/////   2 любых пересекающихся вектора образуют плоскость, от котороый мы
/////   и ищем перпендикуляр.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

coord cross(coord vVector1, coord vVector2)
{
	coord vNormal = coord();
 
	// Если у нас есть 2 вектора (вектор взгляда и вертикальный вектор), 
	// у нас есть плоскость, от которой мы можем вычислить угол в 90 градусов.
	// Рассчет cross'a прост, но его сложно запомнить с первого раза. 
	// Значение X для вектора - (V1.y * V2.z) - (V1.z * V2.y)
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
 
	// Значение Y - (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
 
	// Значение Z: (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z  = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
 
	// *ВАЖНО* Вы не можете менять этот порядок, иначе ничего не будет работать.
	// Должно быть именно так, как здесь. Просто запомните, если вы ищите Х, вы не
	// используете значение X двух векторов, и то же самое для Y и Z. Заметьте,
	// вы рассчитываете значение из двух других осей, и никогда из той же самой.
 
	// Итак, зачем всё это? Нам нужно найти ось, вокруг которой вращаться. Вращение камеры
	// влево и вправо простое - вертикальная ось всегда (0,1,0). 
	// Вращение камеры вверх и вниз отличается, так как оно происходит вне 
	// глобальных осей. Достаньте себе книгу по линейной алгебре, если у вас 
	// её ещё нет, она вам пригодится.
 
	// вернем результат.
	return vNormal;
}

/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////				Возвращает величину вектора
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
 
float getMagnitude(coord vNormal)
{
	// Это даст нам величину нашей нормали, 
	// т.е. длину вектора. Мы используем эту информацию для нормализации
	// вектора. Вот формула: magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)   где V - вектор.
 
	return (float)sqrt(
		  (vNormal.x * vNormal.x) 
		+ (vNormal.y * vNormal.y)
		+ (vNormal.z * vNormal.z) 
	);
}

/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Возвращает нормализированный вектор, длинна которого==1, 
/////	это делает все рассчеты проще.
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

coord normalize(coord vCoord)
{
	// Вы спросите, для чего эта ф-я? Мы должны убедиться, что наш вектор нормализирован.
	// Вектор нормализирован - значит, его длинна равна 1. Например,
	// вектор (2,0,0) после нормализации будет (1,0,0).
 
	// Вычислим величину нормали
	float magnitude = getMagnitude(vCoord);
 
	// Теперь у нас есть величина, и мы можем разделить наш вектор на его величину.
	// Это сделает длинну вектора равной единице, так с ним будет легче работать.
	vCoord = vCoord / magnitude;
 
	return vCoord;
}

///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Добавим ф-ю управления взглядом с пом. мышки
/////
///////////////////////////////// SET VIEW BY MOUSE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
void Camera::setViewByMouse()
{
	POINT mousePos;			// Это структура, хранящяя X и Y позиции мыши
 
	// Оператор " >> 1" - то же самое, что деление на 2, но намного быстрее
	int middleX = glutGet(GLUT_WINDOW_WIDTH) >> 1;	// Вычисляем половину ширины
	int middleY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;	// И половину высоты экрана
	float angleY = 0.0f;	// Направление взгляда вверх/вниз
	float angleZ = 0.0f;	// Значение, необходимое для вращения влево-вправо (по оси Y)
	static float currentRotX = 0.0f;
 
	// Получаем текущие коорд. мыши
	GetCursorPos(&mousePos);
 
	// Если курсор остался в том же положении, мы не вращаем камеру
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;
 
	// Теперь, получив координаты курсора, возвращаем его обратно в середину.
	SetCursorPos(middleX, middleY);
 
	// Теперь нам нужно направление (или вектор), куда сдвинулся курсор.
	// Его рассчет - простое вычитание. Просто возьмите среднюю точку и вычтите из неё
	// новую позицию мыши: VECTOR = P1 - P2; где P1 - средняя точка (400,300 при 800х600).
	// После получения дельты X и Y (или направления), я делю значение 
	// на 1000, иначе камера будет жутко быстрой.
	angleY = (float)((middleX - mousePos.x))/1000.0f;
	angleZ = (float)((middleY - mousePos.y)) / 1000.0f;
 
	static float lastRotX = 0.0f;
	lastRotX = currentRotX;		// Сохраняем последний угол вращения 
					// и используем заново currentRotX
 
	// Если текущее вращение больше 1 градуса, обрежем его, чтобы не вращать слишком быстро
	if(currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
 
		// врощаем на оставшийся угол
		if(lastRotX != 1.0f)
		{
			// Чтобы найти ось, вокруг которой вращаться вверх и вниз, нужно 
			// найти вектор, перпендикулярный вектору взгляда камеры и 
			// вертикальному вектору.
			// Это и будет наша ось. И прежде чем использовать эту ось, 
			// неплохо бы нормализовать её.
			coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = normalize(vAxis);
 
			// Вращаем камеру вокруг нашей оси на заданный угол
			this->rotateView(1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
 
	// Если угол меньше -1.0f, убедимся, что вращение не продолжится
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		if(lastRotX != -1.0f)
		{
			// Опять же вычисляем ось
			coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = normalize(vAxis);
 
			// Вращаем
			this->rotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	// Если укладываемся в пределы 1.0f -1.0f - просто вращаем
	else
	{
		coord vAxis = cross(m_vView - m_vPosition, m_vUpVector);
		vAxis = normalize(vAxis);
		this->rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}
 
	// Всегда вращаем камеру вокруг Y-оси
	this->rotateView(angleY, 0, 1, 0);
}

///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Конструктор класса CCamera
/////
///////////////////////////////// CCAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

Camera::Camera()
{
	coord vZero = coord();		//Инициализируем вектор нашей позиции в нулевые координаты
	coord vView = coord(0.0, 1.0, 0.5);		//Иниц. вектор взгляда
	coord vUp = coord(0.0, 0.0, 1.0);		//Вектор верт.
 
	m_vPosition = vZero;
	m_vView = vView;
	m_vUpVector = vUp;
}

///////////////////////////////// POSITION CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Устанавливает позицию, взгляд, верт. вектор камеры
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
 
	//Обширный код просто делает легче назначение переменных.
	//Можно просто сразу присвоить переменным класса переданные функции значения.
 
	m_vPosition = vPosition;
	m_vView = vView;
	m_vUpVector = vUpVector;
}

///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	                  Вращение камеры вокруг оси
/////
///////////////////////////////// ROTATE VIEW \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Camera::rotateView(float angle, float x, float y, float z)
{
	coord vNewView;
	coord vView;
 
	// Получим наш вектор взгляда (направление, куда мы смотрим)
	vView.x = m_vView.x - m_vPosition.x;	//направление по X
	vView.y = m_vView.y - m_vPosition.y;	//направление по Y
	vView.z = m_vView.z - m_vPosition.z;	//направление по Z
 
	// Теперь, имея вектор взгляда, хранящийся в CVector3 "vView", мы можем вращать его.
	// Эта ф-я будет вызыватся, когда нужно повернутся налево-направо.
	// Итак, нам нужно вращаться вокруг нашей позиции. Представьте это примерно так:
	// скажем, мы стоим на месте, смотря вперед. Мы смотрим в какую-то точку, верно?
	// Теперь, если мы повернем голову налево или направо, направление взгляда изменится.
	// Соответственно переместится точка, на которую мы смотрим (вектор взгляда).
	// Вот почему мы изменяем m_vView - потому что это и есть вектор 
	// взгляда. Мы будем вращать m_vView вокруг m_vPosition
	// по кругу, чтобы реализовать всё это.
	// Чтобы вращать что-то, используем синус и косинус. Для использования sin() & cos() мы
	// ранее подключили math.h.
	//
	// Чтобы реализовать вращение камеры, мы будем использовать axis-angle вращение.
	// Я должен предупредить, что формулы для рассчета вращения не очень просты, но
	// занимают не много кода. Axis-angle вращение позволяет нам вращать точку в пространстве
	// вокруг нужной оси. Это значит, что мы можем взять нашу точку взгляда (m_vView) и
	// вращать вокруг нашей позиции.
	// Чтобы лучше понять следующие рассчеты, советую вам посмотреть детальное
	// описание: http://astronomy.swin.edu.au/~pbourke/geometry/rotate/
 
	// Рассчитаем 1 раз синус и косинус переданного угла
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
 
	// Найдем новую позицию X для вращаемой точки
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)	* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;
 
	// Найдем позицию Y
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)	* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;
 
	// И позицию Z
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)	* vView.z;
 
	// Теперь просто добавим новый вектор вращения к нашей позиции, чтобы
	// установить новый взгляд камеры.
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
 
	// Чтобы вращать нашу позицию вокруг точки, всё, что нам надо - найти вектор
	// от нашей позиции к центральной точке вращения. Один раз получив вектор, 
	// мы вращаемся вокруг точки с заданной скоростью/углом. 
	// Новый вектор vCenter - точка, вокруг которой мы вращаемся.
 
	// Получим центр, вокруг которого нужно вращатся
	coord vPos = m_vPosition - vCenter;
 
	// Вычислим синус и косинус угла
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
 
	// Найдем значение X точки вращения
	vNewPosition.x  = (cosTheta + (1 - cosTheta) * x * x)		* vPos.x;
	vNewPosition.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vPos.y;
	vNewPosition.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vPos.z;
 
	// И значение Y
	vNewPosition.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vPos.x;
	vNewPosition.y += (cosTheta + (1 - cosTheta) * y * y)		* vPos.y;
	vNewPosition.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vPos.z;
 
	// И Z...
	vNewPosition.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vPos.x;
	vNewPosition.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vPos.y;
	vNewPosition.z += (cosTheta + (1 - cosTheta) * z * z)		* vPos.z;
 
	// Теперь просто прибавим новый вектор к нашей позиции,
	// чтобы установить новую позицию камеры.
	m_vPosition = vCenter + vNewPosition;
}

///////////////////////////////// MOVE CAMERA \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Движение камеры вперед-назад с заданной скоростью
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

// Это всё. Совсем не сложный класс, позволяющий нам хоть как-то двигаться в мире =)
