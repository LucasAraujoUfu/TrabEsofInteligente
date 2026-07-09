#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> D(N);
    for (int i = 0; i < N; i++)
        cin >> D[i];

    int days = 0;
    int lastMax = 0;
    int currentMax = 0;

    for (int i = 0; i < N; i++) {
        currentMax = max(currentMax, D[i]);

        if (currentMax > lastMax) {
            days++;
            lastMax = currentMax;
            currentMax = 0;
        }
    }

    cout << days << '\n';

    return 0;
}
