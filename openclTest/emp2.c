/*
  Kompilacja:
  nvcc emp2.c -o emp2.exe -arch=sm_21 -lOpenCL
*/

#include <stdio.h>
#include <stdlib.h>

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>
#include <string.h>

#define PLATFORMIDS_MAX 10

const char *src_jadro_cl = "__kernel void nic() {}";

int main(int argc, char *argv[])
{
  int i;
  cl_int error;
  cl_platform_id platforms2[PLATFORMIDS_MAX];

  cl_device_id device_id;
  cl_uint num_platforms, devices;
  cl_context context;
  cl_command_queue cq;
  cl_program program;
  cl_kernel k_nic;
  cl_context_properties *properties = NULL;

  size_t param_value_size;
  size_t srcsize;
  size_t worksize = 1;
  char *bufor = NULL;

  error = clGetPlatformIDs(PLATFORMIDS_MAX, platforms2, &num_platforms);
  if (error == CL_SUCCESS){
    printf("Liczba platform :%d\n", num_platforms);
    for (i = 0; i < num_platforms; i++)
    {
      printf("Identyfikator platformy [%d]: %d\n", i + 1, platforms2[i]);
      error = clGetPlatformInfo(platforms2[i], CL_PLATFORM_NAME, 0, NULL, &param_value_size);
      bufor = (char *)malloc(param_value_size * sizeof(char));
      error = clGetPlatformInfo(platforms2[i], CL_PLATFORM_NAME, param_value_size, bufor, NULL);
      printf("\"CL_PLATFORM_NAME\":\"%s\"\n", bufor);
      free(bufor);
    }
  }
  else{
    return EXIT_FAILURE;
  }
  error = clGetDeviceIDs(platforms2[0], CL_DEVICE_TYPE_GPU, 1, &device_id, &devices);
  if (error == CL_SUCCESS)
  {
    printf("Liczba urzadzen CL_DEVICE_TYPE_GPU platformy nr 1: %d\n", devices);
  }
  else
    return EXIT_FAILURE;

  context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &error);
  if (error == CL_SUCCESS)
  {
    printf("Utworzono kontekst urzadzenia.\n");
  }
  else
    return EXIT_FAILURE;
  cq = clCreateCommandQueue(context, device_id, 0, &error);
  if (error == CL_SUCCESS)
  {
    printf("Utworzono kolejke.\n");
  }
  else
    return EXIT_FAILURE;

  srcsize = strlen(src_jadro_cl);
  program = clCreateProgramWithSource(context, 1, &src_jadro_cl, &srcsize, &error);
  if (error == CL_SUCCESS)
  {
    printf("Utworzono program.\n");
  }
  else
    return EXIT_FAILURE;

  error = clBuildProgram(program, 0, NULL, "", NULL, NULL);
  if (error == CL_SUCCESS)
  {
    printf("Zbudowano program.\n");
  }
  else
    return EXIT_FAILURE;

  k_nic = clCreateKernel(program, "nic", &error);
  if (error == CL_SUCCESS)
  {
    printf("Utworzono jadro \"nic()\".\n");
  }
  else
    return EXIT_FAILURE;

  error = clEnqueueNDRangeKernel(cq, k_nic, 1, NULL, &worksize, &worksize, 0, NULL, NULL);
  if (error == CL_SUCCESS)
  {
    printf("Uruchomiono przetwarzanie GPU\n");
  }
  else
    return EXIT_FAILURE;

  error = clFinish(cq);
  if (error == CL_SUCCESS)
  {
    printf("Zakonczono przetwarzanie GPU\n");
  }
  else
    return EXIT_FAILURE;

  clReleaseKernel(k_nic);
  clReleaseProgram(program);
  clReleaseCommandQueue(cq);
  clReleaseContext(context);
  return EXIT_SUCCESS;
}