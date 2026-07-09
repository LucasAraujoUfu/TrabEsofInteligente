#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, T;
    cin >> N >> T;

    vector<int> row(N+1), col(N+1);
    iota(row.begin(), row.end(), 0);
    iota(col.begin(), col.end(), 0);

    for (int t = 0; t < T; t++) {
        char c;
        int i, j;
        cin >> c >> i >> j;

        if (c == 'R') swap(row[i], row[j]);
        else swap(col[i], col[j]);
    }

    vector<int> invRow(N+1), invCol(N+1);

    for (int i = 1; i <= N; i++) {
        invRow[row[i]] = i;
        invCol[col[i]] = i;
    }

    vector<vector<int>> ans(N+1, vector<int>(N+1));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            ans[invRow[i]][invCol[j]] = (i + j) % N + 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
