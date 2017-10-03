#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  const double array[] = {10, 8, 20, 2, 5, 11, 9.5, 18};
  const size_t arraySize = sizeof(array)/sizeof(double);
  double totalSum = 0;

  #pragma omp for
  for (size_t i = 0; i < arraySize; i++) {
    totalSum += array[i];
  }

  std::cout << "total: " << totalSum / arraySize << '\n';

  return 0;
}
