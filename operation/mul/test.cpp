#include <cstdio>
#include <windows.h>
using namespace std;

unsigned sum;

inline unsigned mul(unsigned a, unsigned b) { return a * b; }

unsigned func(const int N) {
  unsigned r = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      r += mul(i, j);
  return r;
}

double get_runtime(const int N) {
  LARGE_INTEGER StartingTime, EndingTime;
  LARGE_INTEGER Frequency;
  QueryPerformanceFrequency(&Frequency);
  QueryPerformanceCounter(&StartingTime);
  sum += func(N);
  QueryPerformanceCounter(&EndingTime);
  return 1e6 * (EndingTime.QuadPart - StartingTime.QuadPart) /
         Frequency.QuadPart;
}

int main() {
  freopen("test.out", "w", stdout);
  for (int i = 1e3; i <= 5e4; i += 1e3) {
    printf("%d %.1f\n", i, get_runtime(i));
    fprintf(stderr, "%d\n", i);
  }
  return sum;
}