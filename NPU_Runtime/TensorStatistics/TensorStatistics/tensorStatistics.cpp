#include <iostream>
#include <vector>

typedef std::vector<float> vec_f;

float getMin(const vec_f& tensor);
float getMax(const vec_f& tensor);
float getAverage(const vec_f& tensor);

void printTensor(const vec_f& tensor)
{
	for (float ele : tensor)
		std::cout << ele << " ";
	std::cout << std::endl;
}

float getMin(const vec_f& tensor)
{
	float min = tensor[0];

	for (int i = 1; i < tensor.size(); i++)
		if (min > tensor[i]) min = tensor[i];
	return min;
}

float getMax(const vec_f& tensor)
{
	float max = tensor[0];


	for (int i = 1; i < tensor.size(); i++)
	{
		if (max < tensor[i]) max = tensor[i];
	}
	return max;
}

float getAverage(const vec_f& tensor)
{
	float sum = 0.0;

	for (float ele : tensor)
		sum += ele;
		 
	return (sum / tensor.size());
}

int main(void)
{
	int uInput;

	std::cout << "Tensor 크기 입력 : " << std::endl;
	std::cin >> uInput;
	
	vec_f tensor(uInput);

	//입력
	for (int i = 0; i < uInput; i++)
		std::cin >> tensor[i];

	//출력
	printTensor(tensor);

	std::cout << "MIN " << getMin(tensor) << std::endl;
	std::cout << "MAX " << getMax(tensor) << std::endl;
	std::cout << "AVG " << getAverage(tensor) << std::endl;

	return 0;
}