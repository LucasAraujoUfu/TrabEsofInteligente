#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N != 2 && N % 2 == 0) {
        cout << "N\n";
        return 0;
    }

    vector<vector<int>> id(N + 1, vector<int>(N + 1, -1));

    int cnt = 0;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            id[i][j] = id[j][i] = cnt++;

    vector<char> used(cnt, 0);

    int P;
    cin >> P;
    vector<int> L(P);

    for (int i = 0; i < P; i++)
        cin >> L[i];

    for (int i = 1; i < P; i++) {
        if (L[i] == L[i - 1]) {
            cout << "N\n";
            return 0;
        }
        int e = id[L[i]][L[i - 1]];
        if (used[e]) {
            cout << "N\n";
            return 0;
        }
        used[e] = 1;
    }

    int Q;
    cin >> Q;
    vector<int> R(Q);

    for (int i = 0; i < Q; i++)
        cin >> R[i];

    for (int i = 1; i < Q; i++) {
        if (R[i] == R[i - 1]) {
            cout << "N\n";
            return 0;
        }
        int e = id[R[i]][R[i - 1]];
        if (used[e]) {
            cout << "N\n";
            return 0;
        }
        used[e] = 1;
    }

    long long E = 1LL * N * (N - 1) / 2;
    long long usedEdges = max(0, P - 1) + max(0, Q - 1);
    long long rem = E - usedEdges;

    if (rem < 0) {
        cout << "N\n";
        return 0;
    }

    if (P > 0 && Q > 0 && rem == 0) {
        cout << "N\n";
        return 0;
    }

    cout << "Y\n";
    return 0;
}
