#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void vec_map(float *a, const float *b, int n, float (*f)(float));
    void vec_map2(float *a, const float *b, const float *c, int n, float (*f)(float, float));
    float vec_reduce(const float *a, int n, float (*f)(float, float));
    float vec_map_reduce(const float *a, int n, float (*f)(float), float (*g)(float, float));
    float vec_map_reduce2(const float *a, const float *b, int n, float (*f)(float, float), float (*g)(float, float));
    void vec_add(float *a, const float *b, const float *c, int n);
    void vec_sub(float *a, const float *b, const float *c, int n);
    void vec_mul(float *a, const float *b, const float *c, int n);
    float vec_dot(const float *a, const float *b, int n);
    void vec3_cross(float *a, const float *b, const float *c);
    float vec2_cross(const float *b, const float *c);

#ifdef __cplusplus
}
#endif
