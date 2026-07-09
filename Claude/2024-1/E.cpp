#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> Mat;

Mat rotACW(const Mat& m) {
    int n = m.size();
    Mat r(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            r[i][j] = m[j][n-1-i];
    return r;
}

bool isYoung(const Mat& m) {
    int n = m.size();
    // linhas crescentes (esquerda→direita)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n-1; j++)
            if (m[i][j] >= m[i][j+1]) return false;
    // colunas crescentes (cima→baixo)
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n; j++)
            if (m[i][j] >= m[i+1][j]) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    Mat m(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> m[i][j];

    for (int r = 0; r < 4; r++) {
        if (isYoung(m)) {
            cout << r << "\n";
            return 0;
        }
        m = rotACW(m);
    }

    return 0;
}
