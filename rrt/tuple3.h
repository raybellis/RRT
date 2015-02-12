/*
 *  core/tuple3.h
 *  RRT
 *
 *  Created by Ray Bellis on 18/08/2010.
 *  Copyright 2010 Ray Bellis. All rights reserved.
 *
 */

#ifndef __CORE_TUPLE3_H
#define __CORE_TUPLE3_H

#include <cassert>

template<typename T>
class tuple3 {

public:
	typedef tuple3<T>		self;
	typedef T				num;
	typedef num				array[3];

public:
	num						x, y, z;

public:
	tuple3();
	tuple3(const T x, const T y, const T z);
	tuple3(const array& a);
	tuple3(const self& rhs);
	tuple3(self&& rhs);

	self&					operator=(const self& rhs);

	void					set(const num x, const num y, const num z);
	void					set(const array& a);
	void					get(T& x, T& y, T& z) const;
	void					get(array& a) const;

public:
	self&					operator+=(const self& rhs);
	self&					operator-=(const self& rhs);
	self&					operator*=(const T val);
	self&					add_scaled(const self& rhs, const self& scale);
	self&					add_scaled(const self& rhs, const T scale);

	self					operator*(const T val) const;
	num&					operator[](const int n);
	num						operator[](const int n) const;
};

template<typename T>
tuple3<T>::tuple3()
{
	x = y = z = 0;
}

template<typename T>
tuple3<T>::tuple3(const num _x, const num _y, const num _z)
{
	x = _x;
	y = _y;
	z = _z;
}

template <typename T>
tuple3<T>::tuple3(const self& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

template <typename T>
tuple3<T>::tuple3(self&& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

template <typename T>
tuple3<T>::tuple3(const array& a)
{
	x = a[0];
	y = a[1];
	z = a[2];
}

template <typename T>
tuple3<T>& tuple3<T>::operator=(const self& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

template <typename T>
void tuple3<T>::set(const num _x, const num _y, const num _z)
{
	x = _x;
	y = _y;
	z = _z;
}

template <typename T>
void tuple3<T>::set(const array& a)
{
	x = a[0];
	y = a[1];
	z = a[2];
}

template <typename T>
void tuple3<T>::get(num& _x, num& _y, num& _z) const
{
	_x = x;
	_y = y;
	_z = z;
}

template <typename T>
void tuple3<T>::get(array& a) const
{
	a[0] = x;
	a[1] = y;
	a[2] = z;
}

template <typename T>
tuple3<T>& tuple3<T>::operator+=(const self& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <typename T>
tuple3<T>& tuple3<T>::operator-=(const self& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <typename T>
tuple3<T>& tuple3<T>::operator*=(const num val)
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

template <typename T>
tuple3<T> tuple3<T>::operator*(const num val) const
{
	return tuple3(x * val, y * val, z * val);
}

template <typename T>
tuple3<T>& tuple3<T>::add_scaled(const self& rhs, const self& scale)
{
	x += (rhs.x * scale.x);
	y += (rhs.y * scale.y);
	z += (rhs.z * scale.z);
	return *this;
}

template <typename T>
tuple3<T>& tuple3<T>::add_scaled(const self& rhs, const num scale)
{
	x += (rhs.x * scale);
	y += (rhs.y * scale);
	z += (rhs.z * scale);
	return *this;
}

template <typename T>
typename tuple3<T>::num& tuple3<T>::operator[](const int n)
{
	assert(n >= 0 && n < 3);
	return *(&x + n);
}

template <typename T>
typename tuple3<T>::num tuple3<T>::operator[](const int n) const
{
	assert(n >= 0 && n < 3);
	return *(&x + n);
}

#endif // __CORE_TUPLE3_H
