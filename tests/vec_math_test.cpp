#include <gtest/gtest.h>

#include "../vec_math.h"

TEST(vec_math_test, vec_map)
{
    float a[2] = {1.0, 2.0};
    float b[2] = {0.0, 0.0};
    vec_map(b, a, 2, [](float x)
            { return x * x; });
    EXPECT_FLOAT_EQ(b[0], 1);
    EXPECT_FLOAT_EQ(b[1], 4);
}

TEST(vec_math_test, vec_map2)
{
    float a[2] = {0.0, 0.0};
    float b[2] = {1.0, 2.0};
    float c[2] = {3.0, 4.0};
    vec_map2(a, b, c, 2, [](float x, float y)
             { return 3 * x + 2 * y; });
    EXPECT_FLOAT_EQ(a[0], 9.0);
    EXPECT_FLOAT_EQ(a[1], 14.0);
}

TEST(vec_math_test, vec_reduce)
{
    float a[2] = {1.0, 2.0};
    float b = vec_reduce(a, 2, [](float x, float y)
                         { return x + y; });
    EXPECT_FLOAT_EQ(b, 3.0);
}

TEST(vec_math_test, vec_map_reduce)
{
    float a[2] = {1.0, 2.0};
    float b = vec_map_reduce(
        a, 2, [](float x)
        { return x * x; },
        [](float x, float y)
        { return x + y; });
    EXPECT_FLOAT_EQ(b, 5.0);
}

TEST(vec_math_test, vec_map_reduce2)
{
    float a[2] = {1.0, 2.0};
    float b[2] = {3.0, 4.0};
    float c = vec_map_reduce2(
        a, b, 2, [](float x, float y)
        { return x * y; },
        [](float x, float y)
        { return x + y; });
    EXPECT_FLOAT_EQ(c, 11.0);
}

TEST(vec_math_test, vec_add)
{
    float a[2] = {0.0, 0.0};
    float b[2] = {1.0, 2.0};
    float c[2] = {3.0, 4.0};
    vec_add(a, b, c, 2);
    EXPECT_FLOAT_EQ(a[0], 4.0);
    EXPECT_FLOAT_EQ(a[1], 6.0);
}

TEST(vec_math_test, vec_sub)
{
    float a[2] = {0.0, 0.0};
    float b[2] = {1.0, 2.0};
    float c[2] = {3.0, 4.0};
    vec_sub(a, b, c, 2);
    EXPECT_FLOAT_EQ(a[0], -2.0);
    EXPECT_FLOAT_EQ(a[1], -2.0);
}

TEST(vec_math_test, vec_mul)
{
    float a[2] = {0.0, 0.0};
    float b[2] = {1.0, 2.0};
    float c[2] = {3.0, 4.0};
    vec_mul(a, b, c, 2);
    EXPECT_FLOAT_EQ(a[0], 3.0);
    EXPECT_FLOAT_EQ(a[1], 8.0);
}

TEST(vec_math_test, vec_dot)
{
    float a[2] = {1.0, 2.0};
    float b[2] = {3.0, 4.0};
    float c = vec_dot(a, b, 2);
    EXPECT_FLOAT_EQ(c, 11.0);
}

TEST(vec_math_test, vec3_cross)
{
    float a[3] = {1.0, 2.0, 3.0};
    float b[3] = {4.0, 5.0, 6.0};
    float c[3] = {0.0, 0.0, 0.0};
    vec3_cross(c, a, b);
    EXPECT_FLOAT_EQ(c[0], -3.0);
    EXPECT_FLOAT_EQ(c[1], 6.0);
    EXPECT_FLOAT_EQ(c[2], -3.0);
}

TEST(vec_math_test, vec2_cross)
{
    float a[2] = {1.0, 2.0};
    float b[2] = {3.0, 4.0};
    float c = vec2_cross(a, b);
    EXPECT_FLOAT_EQ(c, -2.0);
}
