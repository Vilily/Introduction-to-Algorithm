/**
 * Description: ��ȡCUDA����
 * Author: Bao Wenjie
 * Date: 2021/3/4
 */

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

using namespace ::std;


int main()
{
	cudaError_t cudaStatus;
	int num = 0;
	cudaStatus = cudaGetDeviceCount(&num);
	cout << "���У�" << num << "�� GPU" << endl << endl;
	cudaDeviceProp prop;
	for (int i = 0; i < num; i++)
	{
		cudaGetDeviceProperties(&prop, i);
		cout << "��" << i << "�� GPU" << endl;
		cout << "GPU����: " << prop.name << endl;
		cout << "�Դ��СΪ: " << prop.totalGlobalMem << endl;
		cout << "�汾��: " << prop.major << "." << prop.minor << endl;
		cout << "GPU�����: " << prop.multiProcessorCount << endl;
	}
	
}