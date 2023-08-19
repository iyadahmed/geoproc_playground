#include "vec_math.h"

void vec_map(float *a, const float *b, int n, float (*f)(float))
{
    for (int i = 0; i < n; i++)
    {
        a[i] = f(b[i]);
    }
}

void vec_map2(float *a, const float *b, const float *c, int n, float (*f)(float, float))
{
    for (int i = 0; i < n; i++)
    {
        a[i] = f(b[i], c[i]);
    }
}

float vec_reduce(const float *a, int n, float (*f)(float, float))
{
    float result = a[0];
    for (int i = 1; i < n; i++)
    {
        result = f(result, a[i]);
    }
    return result;
}

float vec_map_reduce(const float *a, int n, float (*f)(float), float (*g)(float, float))
{
    float result = f(a[0]);
    for (int i = 1; i < n; i++)
    {
        result = g(result, f(a[i]));
    }
    return result;
}

float vec_map_reduce2(const float *a, const float *b, int n, float (*f)(float, float), float (*g)(float, float))
{
    float result = f(a[0], b[0]);
    for (int i = 1; i < n; i++)
    {
        result = g(result, f(a[i], b[i]));
    }
    return result;
}

static float add(float a, float b)
{
    return a + b;
}

void vec_add(float *a, const float *b, const float *c, int n)
{
    vec_map2(a, b, c, n, add);
}

static float sub(float a, float b)
{
    return a - b;
}

void vec_sub(float *a, const float *b, const float *c, int n)
{
    vec_map2(a, b, c, n, sub);
}

static float mul(float a, float b)
{
    return a * b;
}

void vec_mul(float *a, const float *b, const float *c, int n)
{
    vec_map2(a, b, c, n, mul);
}

float vec_dot(const float *a, const float *b, int n)
{
    return vec_map_reduce2(a, b, n, mul, add);
}

void vec3_cross(float *a, const float *b, const float *c)
{
    a[0] = b[1] * c[2] - b[2] * c[1];
    a[1] = b[2] * c[0] - b[0] * c[2];
    a[2] = b[0] * c[1] - b[1] * c[0];
}

float vec2_cross(const float *b, const float *c)
{
    return b[0] * c[1] - b[1] * c[0];
}
