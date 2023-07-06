__kernel void elementwise_add(__global const float* inputA, __global const float* inputB, __global float* output, const int size) {
    int i = get_global_id(0);
    if (i < size) {
        output[i] = inputA[i] + inputB[i];
    }
}
