#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> C;

int solveForB(const int Bbits[8]) {
    int k = -1;
    for (int j = 0; j < 8; j++) if (Bbits[j]) { k = j; break; }
    if (k == -1) {
        for (int p = 0; p < N; p++) if (C[p]) return -1;
        return 0;
    }

    int numfree = 7 - k;
    int totalCombos = 1 << numfree;

    static vector<char> s;
    s.assign(N + 7, 0);

    int best = INT_MAX;
    vector<int> activeJ;
    for (int j = k + 1; j < 8; j++) if (Bbits[j]) activeJ.push_back(j);

    for (int combo = 0; combo < totalCombos; combo++) {
        for (int idx = 0; idx < numfree; idx++) {
            int i = -7 + idx;
            s[i + 7] = (combo >> idx) & 1;
        }
        int weight = __builtin_popcount(combo);

        for (int p = 0; p < N; p++) {
            int val = C[p];
            for (int j : activeJ) val ^= s[p - j + 7];
            int ip = p - k;
            s[ip + 7] = val;
            weight += val;
        }

        if (weight < best) best = weight;
    }
    return best;
}

int main() {
    scanf("%d", &N);
    char buf[4100];
    scanf("%s", buf);
    C.assign(N, 0);
    for (int i = 0; i < N; i++) C[i] = buf[i] - '0';

    int bestWeight = INT_MAX, bestBval = -1;
    for (int Bval = 0; Bval < 256; Bval++) {
        int Bbits[8];
        for (int j = 0; j < 8; j++) Bbits[j] = (Bval >> (7 - j)) & 1;
        int w = solveForB(Bbits);
        if (w < 0) continue;
        if (w < bestWeight || (w == bestWeight && Bval < bestBval)) {
            bestWeight = w; bestBval = Bval;
        }
    }

    char outb[9];
    for (int j = 0; j < 8; j++) outb[j] = ((bestBval >> (7 - j)) & 1) ? '1' : '0';
    outb[8] = 0;
    printf("%s %d\n", outb, bestWeight);
    return 0;
}
