/*
*	Copyright (C) 2019 Jin Won. All right reserved.
*
*	���ϸ�			: Camera.cpp
*	�ۼ���			: ����
*	���� ������		: 19.03.06
*
*	ī�޶� Ŭ����
*/

#include "Camera.h"

/* constructor */
Camera::Camera(
	const Point3D& eye,
	const Point3D& at,
	const Point3D& upVector) 
{
	set(eye, at, upVector);
}

/* member function */
void Camera::set(
	const Point3D& eye,
	const Point3D& at,
	const Vector3D& upVector) 
{
	__position = eye;
	__orthoBasis.u = (at - eye).getUnit();
	__orthoBasis.v = upVector.cross(__orthoBasis.u).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

const Point3D& Camera::getPosition() const
{
	return __position;
}

const OrthoBasis& Camera::getOrthoBasis() const
{
	return __orthoBasis;
}

void Camera::adjustForward(const float delta)
{
	__position += (__orthoBasis.u * delta);
}

void Camera::adjustHorizontal(const float delta)
{
	__position += (__orthoBasis.v * delta);
}

void Camera::adjustVertical(const float delta)
{
	__position += (__orthoBasis.w * delta);
}

void Camera::moveTo(const Point3D& position)
{
	__position = position;
}

void Camera::adjustPitch(const float angle)
{
	__orthoBasis.u = __orthoBasis.u.rotate(__orthoBasis.v, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

void Camera::adjustYaw(const float angle)
{
	__orthoBasis.u = __orthoBasis.u.rotate(__orthoBasis.w, angle).getUnit();
	__orthoBasis.v = __orthoBasis.v.rotate(__orthoBasis.w, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

void Camera::adjustRoll(const float angle)
{
	__orthoBasis.v = __orthoBasis.v.rotate(__orthoBasis.u, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

void Camera::orbitPitch(const Point3D& pivot, const float angle)
{
	__position -= pivot;
	__position = __position.rotate(__orthoBasis.v, angle);
	__position += pivot;

	__orthoBasis.u = __orthoBasis.u.rotate(__orthoBasis.v, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

void Camera::orbitYaw(const Point3D& pivot, const float angle)
{
	__position -= pivot;
	__position = __position.rotate(__orthoBasis.w, angle);
	__position += pivot;

	__orthoBasis.u = __orthoBasis.u.rotate(__orthoBasis.w, angle).getUnit();
	__orthoBasis.v = __orthoBasis.v.rotate(__orthoBasis.w, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}

void Camera::orbitRoll(const Point3D& pivot, const float angle)
{
	__position -= pivot;
	__position = __position.rotate(__orthoBasis.u, angle);
	__position += pivot;

	__orthoBasis.v = __orthoBasis.v.rotate(__orthoBasis.u, angle).getUnit();
	__orthoBasis.w = __orthoBasis.v.cross(__orthoBasis.u).getUnit();
}