#include <bits/stdc++.h>
using namespace std;

static const int NUMD = 21;
static const int FULL = 1 << NUMD;

int idxOf[7][7];

int main() {
    int cnt = 0;
    int da[NUMD], db[NUMD];
    for (int a = 1; a <= 6; a++)
        for (int b = a; b <= 6; b++) {
            idxOf[a][b] = cnt; da[cnt] = a; db[cnt] = b; cnt++;
        }

    vector<int> winnable(FULL);
    int deg[7], parent[7];
    for (int mask = 0; mask < FULL; mask++) {
        deg[0]=deg[1]=deg[2]=deg[3]=deg[4]=deg[5]=deg[6]=0;
        parent[0]=0;parent[1]=1;parent[2]=2;parent[3]=3;parent[4]=4;parent[5]=5;parent[6]=6;

        int pieces = 0, m = mask;
        while (m) {
            int i = __builtin_ctz(m);
            int a = da[i], b = db[i];
            deg[a]++; deg[b]++;
            int ra = a; while (parent[ra] != ra) ra = parent[ra] = parent[parent[ra]];
            int rb = b; while (parent[rb] != rb) rb = parent[rb] = parent[parent[rb]];
            if (ra != rb) parent[ra] = rb;
            pieces++;
            m &= (m - 1);
        }
        if (pieces == 0) { winnable[mask] = 0; continue; }
        if (pieces == 1) { winnable[mask] = 1; continue; }

        int root = -1; bool connected = true; int oddCount = 0;
        for (int v = 1; v <= 6; v++) {
            if (deg[v] > 0) {
                int rv = v; while (parent[rv] != rv) rv = parent[rv] = parent[parent[rv]];
                if (root == -1) root = rv;
                else if (rv != root) connected = false;
                if (deg[v] & 1) oddCount++;
            }
        }
        winnable[mask] = (connected && (oddCount == 0 || oddCount == 2)) ? 1 : 0;
    }

    vector<long long> ans(winnable.begin(), winnable.end());
    for (int bit = 0; bit < NUMD; bit++) {
        int b = 1 << bit;
        for (int S = 0; S < FULL; S++)
            if (S & b) ans[S] += ans[S ^ b];
    }

    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        int mask = 0;
        for (int i = 0; i < N; i++) {
            int a, b; scanf("%d %d", &a, &b);
            mask |= (1 << idxOf[a][b]);
        }
        printf("%lld\n", ans[mask]);
    }
    return 0;
}
