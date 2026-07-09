#include <bits/stdc++.h>
using namespace std;

struct Word {
    string s;
    long long x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Word> dict(N);
    unordered_map<string,int> id;

    for (int i = 0; i < N; i++) {
        cin >> dict[i].s >> dict[i].x >> dict[i].y;
        id[dict[i].s] = i;
    }

    int M;
    cin >> M;

    vector<int> text(M);

    for (int i = 0; i < M; i++) {
        string s;
        cin >> s;
        text[i] = id[s];
    }

    map<vector<int>, vector<int>> nxt;

    // cria todas as janelas de tamanho 1..5
    for (int k = 1; k <= 5; k++) {
        for (int i = 0; i + k < M; i++) {
            vector<int> key;

            for (int j = 0; j < k; j++)
                key.push_back(text[i+j]);

            nxt[key].push_back(text[i+k]);
        }
    }

    int Q, K;
    cin >> Q >> K;

    while (Q--) {
        int F;
        cin >> F;

        vector<int> query(F);
        for (int i = 0; i < F; i++) {
            string s;
            cin >> s;
            query[i] = id[s];
        }

        int bestK = -1;
        vector<int> cand;

        for (int k = K; k >= 1; k--) {
            vector<int> key;

            for (int i = F-k; i < F; i++)
                key.push_back(query[i]);

            auto it = nxt.find(key);

            if (it != nxt.end() && !it->second.empty()) {
                cand = it->second;
                bestK = k;
                break;
            }
        }

        cout.flush();

        for (int i = 0; i < F; i++)
            cout << dict[query[i]].s << ' ';

        if (bestK == -1) {
            cout << "*\n";
            continue;
        }

        long long bestScore = LLONG_MIN;
        int answer = 0;

        for (int d = 0; d < N; d++) {
            long long score = 0;

            for (int c : cand) {
                score += dict[d].x * dict[c].x +
                         dict[d].y * dict[c].y;
            }

            if (score > bestScore) {
                bestScore = score;
                answer = d;
            }
        }

        cout << dict[answer].s << '\n';
    }

    return 0;
}
