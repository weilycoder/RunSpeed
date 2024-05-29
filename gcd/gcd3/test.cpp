// #include <cstdio>
#include <iostream>
#include <windows.h>

using namespace std;

unsigned sum;

const int M = 1000000;
const int T = 1000;

void work();
int gcd(int, int);

int pre[T + 2][T + 2];
int fac[M + 2][3];
bool isp[M + 2];
int pri[M / 10], tot;
int n;

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
  work();
  freopen("test.out", "w", stdout);
  for (int i = 2e2; i <= 1e4; i += 2e2) {
    printf("%d %.1f\n", i, get_runtime(i));
    fprintf(stderr, "%d\n", i);
  }
  return sum;
}

void work() {
  fac[1][0] = fac[1][1] = fac[1][2] = 1;
  for (int i = 2; i <= M; ++i) {
    if (!isp[i]) {
      fac[i][0] = fac[i][1] = 1;
      fac[i][2] = i;
      pri[++tot] = i;
    }
    for (int j = 1; pri[j] * i <= M; ++j) {
      int tmp = pri[j] * i;
      isp[tmp] = true;
      fac[tmp][0] = fac[i][0] * pri[j];
      fac[tmp][1] = fac[i][1];
      fac[tmp][2] = fac[i][2];
      if (fac[tmp][0] > fac[tmp][1]) {
        fac[tmp][0] ^= fac[tmp][1] ^= fac[tmp][0] ^= fac[tmp][1];
      }
      if (fac[tmp][1] > fac[tmp][2]) {
        fac[tmp][1] ^= fac[tmp][2] ^= fac[tmp][1] ^= fac[tmp][2];
      }
      if (i % pri[j] == 0) {
        break;
      }
    }
  }
  for (int i = 0; i <= T; ++i) {
    pre[0][i] = pre[i][0] = i;
  }
  for (int i = 1; i <= T; ++i) {
    for (int j = 1; j <= i; ++j) {
      pre[i][j] = pre[j][i] = pre[j][i % j];
    }
  }
}
int gcd(int a, int b) {
  int ans = 1;
  for (int i = 0; i < 3; ++i) {
    int tmp = (fac[a][i] > T) ? (b % fac[a][i] ? 1 : fac[a][i])
                              : pre[fac[a][i]][b % fac[a][i]];
    b /= tmp;
    ans *= tmp;
  }
  return ans;
}