/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Math.h"

const float Jade::Math::Math::Pi		= 3.14159265359f;
const float Jade::Math::Math::TwoPi		= 6.28318530718f;
const float Jade::Math::Math::PiOverTwo = 1.57079632679f;
const float Jade::Math::Math::E			= 2.71828182845f;
const float Jade::Math::Math::Epsilon	= 0.00000000001f;
const float Jade::Math::Math::Deg2Rad	= Math::Pi / 180.0f;
const float Jade::Math::Math::Rad2Deg	= 180.0f / Math::Pi;

float Jade::Math::Math::Min(float x, float y)
{
	return std::min(x, y);
}

float Jade::Math::Math::Max(float x, float y)
{
	return std::max(x, y);
}

float Jade::Math::Math::Sqrt(float x)
{
	return std::sqrtf(x);
}

float Jade::Math::Math::InvSqrt(float x)
{
	return (1 / Sqrt(x));
}

float Jade::Math::Math::ASin(float a)
{
	return std::asinf(a);
}

float Jade::Math::Math::Sin(float a)
{
	return std::sinf(a);
}

float Jade::Math::Math::ACos(float a)
{
	return std::asinf(a);
}

float Jade::Math::Math::Cos(float a)
{
	return std::cosf(a);
}

float Jade::Math::Math::ATan(float a)
{
	return std::atanf(a);
}

float Jade::Math::Math::Tan(float a)
{
	return std::tanf(a);
}

float Jade::Math::Math::Pow(float x, float y)
{
	return std::powf(x, y);
}

float Jade::Math::Math::Exp(float x)
{
	return std::expf(x);
}

float Jade::Math::Math::Log(float x)
{
	return std::logf(x);;
}

float Jade::Math::Math::Log10(float x)
{
	return std::log10f(x);
}

float Jade::Math::Math::Abs(float x)
{
	return std::abs(x);
}

float Jade::Math::Math::Remainder(float x, float y)
{
	return std::remainderf(x, y);
}

float Jade::Math::Math::Round(float x)
{
	return std::roundf(x);
}

// Returns either 0 or 1.
int Jade::Math::Math::Random()
{
	return std::rand() % 2;
}

float Jade::Math::Math::Floor(float x)
{
	return std::floorf(x);
}

float Jade::Math::Math::Ceiling(float x)
{
	return std::ceilf(x);
}

bool Jade::Math::Math::IsNan(float x)
{
	return std::isnan(x);
}