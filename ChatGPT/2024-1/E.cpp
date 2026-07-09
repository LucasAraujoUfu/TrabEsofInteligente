#include <bits/stdc++.h>
using namespace std;

bool ok(const vector<vector<int>>& a) {
    int n = a.size();

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (a[i][j - 1] >= a[i][j])
                return false;
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 1; i < n; i++) {
            if (a[i - 1][j] >= a[i][j])
                return false;
        }
    }

    return true;
}

vector<vector<int>> rotateCCW(const vector<vector<int>>& a) {
    int n = a.size();
    vector<vector<int>> b(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[n - 1 - j][i] = a[i][j];
        }
    }

    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> mat(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
        }
    }

    for (int r = 0; r < 4; r++) {
        if (ok(mat)) {
            cout << r << '\n';
            return 0;
        }
        mat = rotateCCW(mat);
    }

    return 0;
}
