/**
 * Description: ����GPUʵ�������ӷ�
 * Author: Bao Wenjie
 * Date: 2021/3/3
 * REF: https://blog.csdn.net/xierhacker/article/details/52473747?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control&dist_request_id=&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control
 */

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

using namespace ::std;
const int maxn = 10;

__global__ void kernel_add(int* a, int* b, int* res)
{
	res[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

int main()
{
	int res[maxn], a[maxn], b[maxn];
	// �豸�ڴ��ַ
	int* dev_res, * dev_a, * dev_b;

	for (int i = 0; i < maxn; i++)
		a[i] = b[i] = rand();
	// ����GPU�ռ�
	cudaMalloc((void**)&dev_res, maxn * sizeof(int));
	cudaMalloc((void**)&dev_a, maxn * sizeof(int));
	cudaMalloc((void**)&dev_b, maxn * sizeof(int));

	// ���������ݸ��Ƶ��豸
	cudaMemcpy(dev_a, a, maxn * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, maxn * sizeof(int), cudaMemcpyHostToDevice);

	// ���ú˺���
	kernel_add << <maxn, 1 >> > (dev_a, dev_b, dev_res);

	// ���豸���ݸ��Ƶ�����
	cudaMemcpy(res, dev_res, maxn * sizeof(int), cudaMemcpyDeviceToHost);

	// �ͷſռ�
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_res);

	for(int i = 0; i < maxn; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < maxn; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < maxn; i++)
	{
		cout << res[i] << " ";
	}
	return 0;
}