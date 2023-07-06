#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "settings.h"
#include <time.h>
#include <omp.h>

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>
#define MAX_SOURCE_SIZE (0x100000)

char *kernelSource;
char folder[100];
char print = 0;
void checkError(cl_int status, const char *msg)
{
    if (status != CL_SUCCESS)
    {
        printf("%s: %d\n", msg, status);
        exit(1);
    }
}
void read_kernel()
{

    // Load the kernel source code from file
    FILE *fp;
    size_t source_size;

    fp = fopen("kernel.cl", "rb");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    kernelSource = (char *)malloc(MAX_SOURCE_SIZE);
    source_size = fread(kernelSource, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    // możliwe że kernel wychodzi po
}

void main_func()
{

    cl_int status;

    // Step 1: Set up the OpenCL environment
    cl_platform_id platform;
    status = clGetPlatformIDs(1, &platform, NULL);
    checkError(status, "clGetPlatformIDs");

    cl_device_id device;
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    checkError(status, "clGetDeviceIDs");

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &status);
    checkError(status, "clCreateContext");

    cl_command_queue commandQueue = clCreateCommandQueue(context, device, 0, &status);
    checkError(status, "clCreateCommandQueue");

    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&kernelSource, NULL, &status);
    // create from binary
    checkError(status, "clCreateProgramWithSource");

    // printf("Creating program with binary\n");
    // cl_program program = clCreateProgramWithBinary(context, 1, &device, &program_size, (const unsigned char **)&program_binaries, &binary_status, &status);

    status = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if (status != CL_SUCCESS)
    {
        size_t logSize;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
        char *log = (char *)malloc(logSize);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
        printf("Error in kernel: %s\n", log);
        free(log);
        exit(1);
    }
    // printf("Binary %d", CL_PROGRAM_BINARY_SIZES);
    //("Binary %d", CL_PROGRAM_BINARIES);

    cl_kernel kernel = clCreateKernel(program, "calculate_weight", &status);
    checkError(status, "clCreateKernel");

    const char *folders[] = {folder};
    int num_folders = sizeof(folders) / sizeof(pfolders[0]);

    char dna[MAX_DNA_LEN][MAX_WORD_LEN];

    char line[MAX_WORD_LEN];
    char filename[MAX_DNA_LEN];

    double begin;
    double end;
    double time_spent;

    for (int i = 0; i < num_folders; i++)
    {
        if (print)
            printf("%s\n", folders[i]);

        const char *ins_dir = folders[i];
        DIR *dir = opendir(ins_dir);
        if (dir == NULL)
        {
            printf("Failed to open directory: %s\n", ins_dir);
            continue;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            int dna_count = 0;
            if (entry->d_type == DT_REG)
            {

                if (print)
                {
                    printf("%s\n", entry->d_name);
                }

                begin = omp_get_wtime();

                snprintf(filename, sizeof(filename), "%s/%s", ins_dir, entry->d_name);
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    printf("Failed to open file: %s\n", filename);
                    return;
                }

                while (fgets(line, sizeof(line), file))
                {
                    line[strcspn(line, "\n")] = '\0';
                    strcpy(dna[dna_count], line);
                    dna_count++;
                }

                fclose(file);

                int *neighbours;
                neighbours = malloc((dna_count * dna_count) * sizeof(int));
                // int neighbours[dna_count * dna_count];

                // Step 2: Transfer data to the OpenCL device
                cl_mem dnaBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(dna), dna, &status);
                checkError(status, "clCreateBuffer");

                cl_mem neighboursBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, (dna_count * dna_count) * sizeof(int), NULL, &status);
                checkError(status, "clCreateBuffer");

                // Step 3: Execute the OpenCL kernel
                status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &dnaBuffer);
                checkError(status, "clSetKernelArg");

                status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &neighboursBuffer);
                checkError(status, "clSetKernelArg");

                int len = strlen(dna[0]);
                status = clSetKernelArg(kernel, 2, sizeof(int), &len);
                checkError(status, "clSetKernelArg");

                size_t globalSize[] = {(dna_count * dna_count)};
                // size_t localSize[] = {(2 + MAX_WORD_LEN * 2 + 2 + 6)};
                status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalSize, NULL, 0, NULL, NULL);
                checkError(status, "clEnqueueNDRangeKernel");

                // Step 4: Transfer the results back to the host
                status = clEnqueueReadBuffer(commandQueue, neighboursBuffer, CL_TRUE, 0, sizeof(int) * dna_count * dna_count, neighbours, 0, NULL, NULL);
                checkError(status, "clEnqueueReadBuffer");

                if (print)
                {
                    for (int i = 0; i < dna_count; i++)
                    {
                        for (int j = 0; j < dna_count; j++)
                        {
                            printf("%d ", neighbours[j * dna_count + i]);
                        }
                        printf("\n");
                    }
                }
                status = clReleaseMemObject(dnaBuffer);
                checkError(status, "clReleaseMemObject");
                status = clReleaseMemObject(neighboursBuffer);
                checkError(status, "clReleaseMemObject");


                end = omp_get_wtime();
                time_spent = end - begin;


                printf("%f|\n", time_spent * 1000);
            }
        }

        closedir(dir);
    }

    // ... Rest of the code

    // Step 5: Clean up and release resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    status = clReleaseCommandQueue(commandQueue);
    checkError(status, "clReleaseCommandQueue");
    status = clReleaseContext(context);
    checkError(status, "clReleaseContext");
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (i == 1)
        {
            strcpy(folder, argv[i]);
        }
        else if (i == 2)
        {
            print = atoi(argv[i]);
        }
    }

    read_kernel();
    // double begin = omp_get_wtime();
    main_func();
    // double end = omp_get_wtime();
    // double time_spent = end - begin;

    // printf("%f\n", time_spent * 1000);

    return 0;
}
