#pragma once

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
struct STLBinaryTriangle
{
    float normal[3];
    union
    {
        struct
        {
            float vertex1[3];
            float vertex2[3];
            float vertex3[3];
        };
        float vertices[3][3];
    };
    uint16_t attribute_byte_count;
};
#pragma pack(pop)

int load_stl(FILE *file, struct STLBinaryTriangle **triangles, uint32_t *num_triangles);
