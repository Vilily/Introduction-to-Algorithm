/**
 * Description: ����GPUʵ�־���ӷ�
 * Author: Bao Wenjie
 * Date: 2021/3/3
 */

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

using namespace ::std;
const int max_x = 10;
const int max_y = 10;

__global__ void kernel_matrix_add(int* a, int* b, int* res, int maxn)
{
	res[maxn * blockIdx.x + blockIdx.y] = a[maxn * blockIdx.x + blockIdx.y] + b[maxn * blockIdx.x + blockIdx.y];
}

int main()
{
	int res[max_y * max_x], a[max_y * max_x], b[max_y * max_x];
	// �豸�ڴ��ַ
	int* dev_res, * dev_a, * dev_b;

	for (int i = 0; i < max_y * max_x; i++)
	{
		a[i] = b[i] = rand();
	}
	// ����GPU�ռ�
	cudaMalloc((void**)&dev_res, max_x * max_y * sizeof(int));
	cudaMalloc((void**)&dev_a, max_x * max_y * sizeof(int));
	cudaMalloc((void**)&dev_b, max_x * max_y * sizeof(int));

	// ���������ݸ��Ƶ��豸
	cudaMemcpy(dev_a, a, max_x * max_y * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, max_x * max_y * sizeof(int), cudaMemcpyHostToDevice);

	// ���ú˺���
	dim3 x = dim3(max_y, max_x, 1);
	kernel_matrix_add << <x, 1 >> > (dev_a, dev_b, dev_res, max_x);

	// ���豸���ݸ��Ƶ�����
	cudaMemcpy(res, dev_res, max_x * max_y * sizeof(int), cudaMemcpyDeviceToHost);

	// �ͷſռ�
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_res);

	for (int i = 0; i < max_x * max_y; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < max_x * max_y; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < max_x * max_y; i++)
	{
		cout << res[i] << " ";
	}
	return 0;
}