#include <bits/stdc++.h>
using namespace std;

static inline int readInt() {
    int c = getchar_unlocked();
    while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
    bool neg = false;
    if (c == '-') { neg = true; c = getchar_unlocked(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
    return neg ? -(int)x : (int)x;
}

int main() {
    int N = readInt();
    int M = readInt();

    vector<long long> colSum(M, 0);
    vector<long long> colMax(M, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            long long g = readInt();
            colSum[j] += g;
            if (g > colMax[j]) colMax[j] = g;
        }
    }

    long long total = 0;
    for (int j = 0; j < M; j++) {
        long long needByCapacity = (colSum[j] + N - 1) / N; // ceil(sum/N)
        long long Sj = max(colMax[j], needByCapacity);
        if (Sj < 1) Sj = 1; // turma sempre tem pelo menos 1 aluno
        total += Sj;
    }

    printf("%lld\n", total);
    return 0;
}
