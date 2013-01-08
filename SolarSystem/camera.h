#pragma once

#include "coords.h"

class Camera 
{
public:
	coord m_vPosition;	// ѕозици€ камеры.
	coord m_vView;		// Ќаправление камеры.
	coord m_vUpVector;	// ¬ертикальный вектор.
 
	//¬ начале переменных подписываем "m", т.к. это "member"-переменные.
	//"v" добавл€ем, т.к. это члены класса Vector (начинаетс€ на V).
 
 
	//  онструктор класса Camera
	Camera();
 
	// “ут измен€етс€ положение, направление и верт. вектор камеры.
	// ¬ основном используетс€ при инициализации.
	void positionCamera(
		float positionX, float positionY, float positionZ, 
		float viewX,	 float viewY,	  float viewZ, 
		float upVectorX, float upVectorY, float upVectorZ
	);
 
	// Ёта ф-€ передвигает камеру вперед/назад
	void moveCamera(float speed);

	// Ёта ф-€ вращает камеру вокруг позиции в зависимости от переданных параметров.
	// –отаци€ сделана как осево-угловое вращение. Ёто значит, что вы передаете 
	// ф-ии угол вращени€ и ось, вокруг которой нужно вращатс€.
	void rotateView(float angle, float x, float y, float z);

	// ‘ункци€, устанавливающа€ взгл€д по позиции мыши
	void setViewByMouse();

	// ‘ункци€ вращает камеру вокруг точки (например вашего персонажа).
	// vCenter - “очка, вокруг которой она вращаетс€.
	void rotateAroundPoint(coord vCenter, float angle, float x, float y, float z);
};