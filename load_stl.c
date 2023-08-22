#include <stdint.h>
#include <stdlib.h>

#include "load_stl.h"

#define BINARY_STL_HEADER_SIZE 80

int load_stl(FILE *file, struct STLBinaryTriangle **triangles, uint32_t *num_triangles)
{
    uint8_t header[BINARY_STL_HEADER_SIZE];
    if (fread(header, BINARY_STL_HEADER_SIZE, 1, file) != 1)
    {
        return 1;
    }
    if (fread(num_triangles, sizeof(uint32_t), 1, file) != 1)
    {
        return 1;
    }
    *triangles = malloc(sizeof(struct STLBinaryTriangle) * *num_triangles);
    if (NULL == *triangles)
    {
        return 1;
    }
    // Not lenient, maybe we could make the reader more forgiving
    if (fread(*triangles, sizeof(struct STLBinaryTriangle), *num_triangles, file) != *num_triangles)
    {
        return 1;
    }
    return 0;
}
