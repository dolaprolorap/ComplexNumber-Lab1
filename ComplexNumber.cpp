#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
#include <cmath>
#include <concepts>

#define eps 0.0001f

template<typename T>
	concept is_numeric = std::is_integral<T>::value || std::is_floating_point<T>::value;

template<is_numeric T>
class ComplexNumber {
private:
	T _real;
	T _imaginary;

public:
	ComplexNumber<T>(T a, T b, bool polar_form = false)
	{
		if (polar_form)
		{
			_real = a * cos(b);
			_imaginary = a * sin(b);
		}
		else
		{
			_real = a;
			_imaginary = b;
		}
	}

	ComplexNumber<T>() : ComplexNumber<T>(0, 0) {}

	ComplexNumber<T>(float a) : ComplexNumber<T>(a, 0) {}

	float GetReal() const { return _real; }

	float GetImaginary() const { return _imaginary; }

	void SetReal(float value) { _real = value; }

	void SetImaginary(float value) { _imaginary = value; }

	ComplexNumber<T> Add(const ComplexNumber<T>& l, const ComplexNumber<T>& r)
	{
		return ComplexNumber<T>(l._real + r._real, l._imaginary + r._imaginary);
	}

	ComplexNumber<T> Sub(const ComplexNumber<T>& l, const ComplexNumber<T>& r)
	{
		return ComplexNumber<T>(l._real - r._imaginary, l._real - r._imaginary);
	}

	ComplexNumber<T> Mult(const ComplexNumber<T>& l, const ComplexNumber<T>& r)
	{
		return ComplexNumber<T>(l.Abs() * r.Abs(), l.Arg() + r.Arg(), true);
	}

	ComplexNumber<T> Div(const ComplexNumber<T>& l, const ComplexNumber<T>& r)
	{
		T r_abs = r.Abs();
		if (r_abs == 0) throw "Zero Division";
		return ComplexNumber<T>(l.Abs()/r_abs, l.Arg() - r.Arg(), true);
	}

	ComplexNumber<T> Pow(const ComplexNumber<T>& num, float pow)
	{
		return ComplexNumber<T>(std::pow(num.Abs(), pow), num.Arg() * pow, true);
	}

	float Abs() const
	{
		return sqrt(_real * _real + _imaginary * _imaginary);
	}

	float Arg() const
	{
		if (!_real) return acos(-1);
		if (_real > 0) return atan(_imaginary / _real);
		return acos(-1) + atan(_imaginary / _real);
	}

	ComplexNumber<T> operator+(const ComplexNumber<T>& r) const
	{
		return Add(*this, r);
	}

	ComplexNumber<T> operator-(const ComplexNumber<T>& r) const
	{
		return Sub(*this, r);
	}

	ComplexNumber<T> operator*(const ComplexNumber<T>& r) const
	{
		return Mult(*this, r);
	}

	ComplexNumber<T> operator/(const ComplexNumber<T>& r) const
	{
		return Div(*this, r);
	}

	ComplexNumber<T> operator^(float r) const
	{
		return Pow(*this, r);
	}

	bool operator==(ComplexNumber<T>& r) const
	{
		return ((_real - r._real < eps) && (_imaginary - r._imaginary < eps));
	}

	bool operator==(float r) const
	{
		return ((_imaginary < eps) && (_imaginary - r < eps));
	}

	bool operator==(int r) const
	{
		return ((_imaginary < eps) && (_imaginary - r) < eps);
	}

	bool operator!=(ComplexNumber<T>& r) const
	{
		return !(*this == r);
	}

	bool operator!=(float r) const
	{
		return !(*this == r);
	}

	bool operator!=(int r) const
	{
		return !(*this == r);
	}
};

template<is_numeric T>
std::ostream& operator << (std::ostream& ofstr, const ComplexNumber<T>& comp)
{
	return ofstr << comp.GetReal() << " + i*" << comp.GetImaginary();
}

#endif