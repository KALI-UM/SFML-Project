////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2023 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>::Vector2() :
	x(0),
	y(0)
{

}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>::Vector2(T X, T Y) :
	x(X),
	y(Y)
{

}


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector) :
	x(static_cast<T>(vector.x)),
	y(static_cast<T>(vector.y))
{
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator -(const Vector2<T>& right)
{
	return Vector2<T>(-right.x, -right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator *(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x * right, left.y * right);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator *(T left, const Vector2<T>& right)
{
	return Vector2<T>(right.x * left, right.y * left);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, T right)
{
	left.x *= right;
	left.y *= right;

	return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> operator /(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x / right, left.y / right);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& left, T right)
{
	left.x /= right;
	left.y /= right;

	return left;
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x != right.x) || (left.y != right.y);
}

////////////////////////////////////////////////////////////
//��ü ���� ����
// 
////////////////////////////////////////////////////////////
//ĳ����
//template <typename T, typename U>
//inline Vector2<T>(const Vector2<U>& v)
//{
//	return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
//}
////////////////////////////////////////////////////////////
//����
template <typename T>
inline T length(const Vector2<T>& v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}
////////////////////////////////////////////////////////////
//�Ÿ�
template <typename T>
inline T distance(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x-right.x, left.y-right.y).length();
}
////////////////////////////////////////////////////////////
//����ȭ
template <typename T>
inline Vector2<T> nomalize(const Vector2<T>& v)
{
	T len = length(v);
	return Vector2<T>(v.x / len, v.y / len);
}
////////////////////////////////////////////////////////////
//clamp
template <typename T>
inline Vector2<T> clamp(const Vector2<T>& v, const Vector2<T>& min, const Vector2<T>& max)
{
	return Vector2<T>(clamp(v.x, min.x, max.y), clamp(v.y, min.y,max.y));
}
////////////////////////////////////////////////////////////
//����
//template<typename T>
//inline Vector2<T> lerp(const Vector<T>& left, const Vector<T>& right, float ratio)
//{
//	float x = (float)left.x * (1.0f - ratio) + (float)right.x * ratio;
//	float y = (float)left.y * (1.0f - ratio) + (float)right.y * ratio);
//	return Vector2<T>((T)x, (T)y);
//}