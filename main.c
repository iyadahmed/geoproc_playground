#include <stdio.h>

#include "vec_math.h"

int main()
{
    float a[3] = {0, 0, 0};
    float b[3] = {1, 0, 0};
    float c[3] = {0, 1, 0};
    float d = vec_dot(b, c, 3);
    printf("%f\n", d);
    vec3_cross(a, b, c);
    printf("%f %f %f\n", a[0], a[1], a[2]);
    float e = vec2_cross(b, c);
    printf("%f\n", e);
    return 0;
}
