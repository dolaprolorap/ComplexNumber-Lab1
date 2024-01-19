#include <cassert>
#include "include/ComplexNumber.h"
#include "include/ComplexNumberPacker.h"

#include "src/ComplexNumber.cpp"
#include "src/ComplexNumberPacker.cpp"

void test_ConstructorDefault() {
    ComplexNumber c = ComplexNumber();
    assert(c.GetReal() == 0);
    assert(c.GetImaginary() == 0);
}

void test_Constructor() {
    ComplexNumber c(10, 5);
    assert(c.GetReal() == 10);
    assert(c.GetImaginary() == 5);
}

void test_ConstructorPolar() {
    ComplexNumber c(2, 3 * acos(-1)/4, true);
    assert(c.GetReal() + sqrt(2) < eps);
    assert(c.GetImaginary() - sqrt(2) < eps);
}

void test_FromFloat() {
    ComplexNumber c1(5.1f, 0);
    ComplexNumber c2(5.1f);

    assert(c1 == c2);
}

void test_GetReal() {
    ComplexNumber c(23.123f, 31.12f);
    float expected = 23.123f;

    float actual = c.GetReal();

    assert(expected == actual);
}

void test_SetReal() {
    ComplexNumber c(23.123f, 31.12f);
    float expected = 5.f;

    c.SetReal(5);

    assert(expected == c.GetReal());
}

void test_GetImaginary() {
    ComplexNumber c(23.123f, 31.12f);
    float expected = 31.12f;

    float actual = c.GetImaginary();

    assert(expected == actual);
}

void test_SetImaginary() {
    ComplexNumber c(23.123f, 31.12f);
    float expected = 5.f;

    c.SetReal(5);

    assert(expected == c.GetReal());
}

void test_Add() {
    ComplexNumber expected(7.5f, 12.7f);
    ComplexNumber c1(3, 8);
    ComplexNumber c2(4.5f, 4.7f);

    auto actual = c1 + c2;

    assert((expected - actual).Abs() < eps);
}

void test_Sub() {
    ComplexNumber expected(-1.5f, 3.3f);
    ComplexNumber c1(3, 8);
    ComplexNumber c2(4.5f, 4.7f);

    auto actual = c1 - c2;

    assert((expected - actual).Abs() < eps);
}

void test_Mult() {
    ComplexNumber expected(-24.1f, 50.1f);
    ComplexNumber c1(3, 8);
    ComplexNumber c2(4.5f, 4.7f);

    auto actual = c1 * c2;

    assert((expected - actual).Abs() < eps);
}

void test_Div() {
    ComplexNumber expected(1, -2);
    ComplexNumber c1(7, -4);
    ComplexNumber c2(3, 2);

    auto actual = c1 / c2;

    assert((expected - actual).Abs() < eps);
}

void test_Pow() {
    ComplexNumber expected(8, acos(-1), true);
    double arg1 = ((2.f / 3.f) * acos(-1));
    ComplexNumber c(4, arg1, true);
    float pow = 1.5f;

    auto actual = c ^ pow;
    
    assert((expected - actual).Abs() < eps);
}

void test_Abs() {
    ComplexNumber a(-4.0, 3.0);
    auto res = a.Abs();
    assert(res - 5 < eps);
}

void test_Arg() {
    ComplexNumber c(12, 4, true);
    assert(c.Arg() - 4 < eps);
}

void test_EqualComplex() {
    ComplexNumber a(5, 10);
    ComplexNumber b(5, 10);
    ComplexNumber c(-5, -10);
    assert(a == b);
    assert(a != c);
}

void test_EqualsInt() {
    ComplexNumber a(4, 0);
    int b = 4;
    assert(a == b);
    a.SetImaginary(2.f);
    assert(a != b);
}

void test_EqualsFloat() {
    ComplexNumber a = ComplexNumber(10, 0);
    float b = 10;
    assert(a == b);
    a.SetImaginary(1);
    assert(a != b);
}

void test_PacUnpackTest() {
    ComplexNumberPacker cmp;
    ComplexNumber a(1.33f, -14.421f);
    long long a_pack = cmp.Pack(a);
    ComplexNumber b = cmp.Unpack(a_pack);
    assert(a == b);
}