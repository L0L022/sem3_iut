#include <iostream>
#include <pthread.h>
#include <cstring>

struct Array
{
  double * array;
  size_t size;
};

struct Thread
{
  pthread_t thread;
  Array array;
};

double sum(const Array &array)
{
  double res = 0;
  for (size_t i = 0; i < array.size; i++) {
    res += array.array[i];
  }
  return res;
}

void* sumThread(void* arg)
{
  return static_cast<void*>(new double(sum(*static_cast<Array*>(arg))));
}

int main()
{
  const size_t threadsSize = 2;
  Thread threads[threadsSize];

  const double array[] = {10, 8, 20, 2, 5, 11, 9.5, 18};
  const size_t arraySize = 8, step = arraySize/threadsSize;

  for (size_t i = 0; i < threadsSize; i++) {
    Thread &t = threads[i];
    t.array.size = arraySize/2;
    t.array.array = new double[t.array.size];
    std::memcpy(t.array.array, array + i * step, step * sizeof(double));

    pthread_create(&t.thread, NULL, sumThread, &t.array);
  }

  double totalSum = 0;
  for (size_t i = 0; i < threadsSize; i++) {
    Thread &t = threads[i];
    void *res = nullptr;
    pthread_join(t.thread, &res);
    totalSum += *static_cast<double*>(res);
    delete[] t.array.array;
    delete static_cast<double*>(res);
  }

  std::cout << "total: " << totalSum / arraySize << '\n';

  return 0;
}
