#include <stdio.h>
#include <stdlib.h>

#define CL_TARGET_OPENCL_VERSION 200
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;

    // Load the kernel source code from file
    FILE* fp;
    char* source_str;
    size_t source_size;

    fp = fopen("kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    // Get platform and device information
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    command_queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &ret);

    // Create a program from the kernel source code
    program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the kernel
    kernel = clCreateKernel(program, "hello_world", &ret);

    // Set the arguments of the kernel
    // Note: Modify this section based on your kernel requirements
    // For example, if you have a buffer object as the argument, create the buffer and set the argument accordingly
    cl_mem output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * N, NULL, &ret);
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&output_buffer);

    // Set the work sizes for the kernel execution
    size_t global_work_size[1] = {256};  // Define the global work size
    size_t local_work_size[1] = {64};    // Define the local work size

    // Execute the kernel
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);

    // Wait for the command queue to finish
    clFinish(command_queue);

    // Cleanup
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(source_str);

    return 0;
}
