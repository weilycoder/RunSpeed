#include <iostream>
#include <windows.h>

using namespace std;

unsigned sum;

inline int gcd(int a, int b) {
  int i = __builtin_ctz(a);
  int j = __builtin_ctz(b);
  int k = min(i, j);
  int d;
  b >>= j;
  while (a) {
    a >>= i;
    d = b - a;
    i = __builtin_ctz(d);
    if (a < b)
      b = a;
    if (d < 0)
      a = -d;
    else
      a = d;
  }
  return b << k;
}

unsigned func(const int N) {
  unsigned r = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j)
      r += gcd(i, j);
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
  for (int i = 2e2; i <= 1e4; i += 2e2) {
    printf("%d %.1f\n", i, get_runtime(i));
    fprintf(stderr, "%d\n", i);
  }
  return sum;
}