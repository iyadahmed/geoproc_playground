#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "load_stl.h"
#include "vec_math.h"

// http://web.archive.org/web/20230610012959/https://unix4lyfe.org/benchmarking/
uint64_t rdtscp(void)
{
    uint32_t lo, hi;
    __asm__ volatile("rdtscp"
                     : /* outputs */ "=a"(lo), "=d"(hi)
                     : /* no inputs */
                     : /* clobbers */ "%rcx");
    return (uint64_t)lo | (((uint64_t)hi) << 32);
}

int main()
{
    printf("Thread ID %d\n", omp_get_thread_num());
    int return_code = 0;
    FILE *file = NULL;
    struct timespec time_result;
    long start_ns = 0;
    long end_ns = 0;
    struct STLBinaryTriangle *triangles = NULL;
    uint32_t num_triangles = 0;
    float *x = NULL;
    float *y = NULL;
    float *z = NULL;
    uint64_t start_tsc = 0;
    uint64_t end_tsc = 0;

    file = fopen("../Stanford_Bunny.stl", "rb");
    if (NULL == file)
    {
        printf("Failed to open file\n");
        return_code = 1;
        goto cleanup;
    }

    if (load_stl(file, &triangles, &num_triangles))
    {
        printf("Failed to load STL file\n");
        return_code = 1;
        goto cleanup;
    }

    timespec_get(&time_result, TIME_UTC);
    start_ns = time_result.tv_nsec;
    start_tsc = rdtscp();

    float bb_min[3];
    float bb_max[3];
    for (int i = 0; i < 3; i++)
    {
        bb_min[i] = fminf(fminf(triangles[0].vertex1[i], triangles[0].vertex2[i]), triangles[0].vertex3[i]);
        bb_max[i] = fmaxf(fmaxf(triangles[0].vertex1[i], triangles[0].vertex2[i]), triangles[0].vertex3[i]);
    }
    for (uint32_t i = 1; i < num_triangles; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bb_min[j] = fminf(bb_min[j], fminf(fminf(triangles[i].vertex1[j], triangles[i].vertex2[j]), triangles[i].vertex3[j]));
            bb_max[j] = fmaxf(bb_max[j], fmaxf(fmaxf(triangles[i].vertex1[j], triangles[i].vertex2[j]), triangles[i].vertex3[j]));
        }
    }

    end_tsc = rdtscp();
    printf("Time: %lu cycles\n", end_tsc - start_tsc);
    timespec_get(&time_result, TIME_UTC);
    end_ns = time_result.tv_nsec;
    printf("Time: %ld ns\n", end_ns - start_ns);

    x = malloc(sizeof(float) * 3 * num_triangles);
    if (NULL == x)
    {
        printf("Failed to allocate memory\n");
        return_code = 1;
        goto cleanup;
    }
    y = malloc(sizeof(float) * 3 * num_triangles);
    if (NULL == y)
    {
        printf("Failed to allocate memory\n");
        return_code = 1;
        goto cleanup;
    }
    z = malloc(sizeof(float) * 3 * num_triangles);
    if (NULL == z)
    {
        printf("Failed to allocate memory\n");
        return_code = 1;
        goto cleanup;
    }

    for (uint32_t i = 0; i < num_triangles; i++)
    {
        for (int vi = 0; vi < 3; vi++)
        {
            x[i * 3 + vi] = triangles[i].vertices[vi][0];
            y[i * 3 + vi] = triangles[i].vertices[vi][1];
            z[i * 3 + vi] = triangles[i].vertices[vi][2];
        }
    }

    timespec_get(&time_result, TIME_UTC);
    start_ns = time_result.tv_nsec;
    start_tsc = rdtscp();

    float x_min = vec_reduce(x, num_triangles * 3, fminf);
    float y_min = vec_reduce(y, num_triangles * 3, fminf);
    float z_min = vec_reduce(z, num_triangles * 3, fminf);
    float x_max = vec_reduce(x, num_triangles * 3, fmaxf);
    float y_max = vec_reduce(y, num_triangles * 3, fmaxf);
    float z_max = vec_reduce(z, num_triangles * 3, fmaxf);

    end_tsc = rdtscp();
    printf("Time: %lu cycles\n", end_tsc - start_tsc);
    timespec_get(&time_result, TIME_UTC);
    end_ns = time_result.tv_nsec;
    printf("Time: %ld ns\n", end_ns - start_ns);
    printf("Bounding box min: (%f, %f, %f)\n", x_min, y_min, z_min);
    printf("Bounding box max: (%f, %f, %f)\n", x_max, y_max, z_max);

    printf("Bounding box min: (%f, %f, %f)\n", bb_min[0], bb_min[1], bb_min[2]);
    printf("Bounding box max: (%f, %f, %f)\n", bb_max[0], bb_max[1], bb_max[2]);

cleanup:
    if (NULL != x)
    {
        free(x);
    }
    if (NULL != y)
    {
        free(y);
    }
    if (NULL != z)
    {
        free(z);
    }
    if (NULL != triangles)
    {
        free(triangles);
    }
    if (NULL != file)
    {
        fclose(file);
    }
    return return_code;
}
