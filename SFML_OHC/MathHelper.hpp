#include <cmath>

template <typename T>
static T clamp(const T& v, const T& min, const T& max)
{
	T value;
	value = v < min ? min : v;
	value = v > max ? max : v;
	return value;
}

template <typename T>
static T lerp(const T& left, const T& right, float ratio)
{
	ratio = clamp(ratio, 0.0f, 1.0f);
	float value = (float)left * (1.0f - ratio) + (float)right * ratio;
	return value;
}

template<>
static double lerp(const double& left, const double& right, float ratio)
{
	ratio = clamp(ratio, 0.0f, 1.0f);
	return left * (1.0 - (double)ratio) + right * (double)ratio;
}


