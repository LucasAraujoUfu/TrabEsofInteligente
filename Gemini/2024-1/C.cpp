#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Implementação rápida de Suffix Array para inteiros via ordenação de prefixos
void construir_sa(const vector<int>& v, vector<int>& sa, vector<int>& lcp) {
    int n = v.size();
    vector<int> rank(n), eixos(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = v[i];
    }
    
    for (int k = 1; k < n; k <<= 1) {
        auto comp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int rA = (a + k < n) ? rank[a + k] : -1;
            int rB = (b + k < n) ? rank[b + k] : -1;
            return rA < rB;
        };
        sort(sa.begin(), sa.end(), comp);
        eixos[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            eixos[sa[i]] = eixos[sa[i - 1]] + (comp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = eixos;
    }
    
    // Algoritmo de Kasai para o LCP
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && v[i + k] == v[j + k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    vector<int> sa(n), lcp(n, 0);
    construir_sa(v, sa, lcp);

    long long soma_lcp = 0;
    vector<pair<int, int>> st; // {valor_lcp, peso/frequencia}
    long long soma_atual = 0;

    for (int i = 0; i < n - 1; i++) {
        int qtd = 1;
        while (!st.empty() && st.back().first >= lcp[i]) {
            soma_atual -= 1LL * st.back().first * st.back().second;
            qtd += st.back().second;
            st.pop_back();
        }
        st.push_back({lcp[i], qtd});
        soma_atual += 1LL * lcp[i] * qtd;
        soma_lcp += soma_atual;
    }

    long long total_pares = 1LL * n * n;
    // Cada elemento i pareia consigo mesmo dando comprimento (n - i)
    long long num = 2 * soma_lcp + (1LL * n * (n + 1)) / 2;
    long long den = total_pares;

    long long g = std::gcd(num, den);
    cout << num / g << "/" << den / g << "\n";

    return 0;
}
