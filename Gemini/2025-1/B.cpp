#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Função para calcular o MDC estendido
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Combina duas condições de congruência: k = r1 mod m1 e k = r2 mod m2
bool merge_congruence(long long r1, long long m1, long long r2, long long m2, long long &r_out, long long &m_out) {
    long long x, y;
    long long g = extgcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return false;
    
    long long m = (m1 / g) * m2;
    // x corresponde ao m1 no gcd
    long long delta = (r2 - r1) / g;
    long long k1 = (x % (m2 / g)) * (delta % (m2 / g)) % (m2 / g);
    if (k1 < 0) k1 += m2 / g;
    
    r_out = (r1 + k1 * m1) % m;
    if (r_out < 0) r_out += m;
    m_out = m;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> A(n + 1), B(n + 1), P(n + 1);
    for (int i = 1; i <= n; ++i) cin >> A[i];
    for (int i = 1; i <= n; ++i) cin >> B[i];
    for (int i = 1; i <= n; ++i) cin >> P[i];

    vector<bool> vis(n + 1, false);
    long long ans_r = 0, ans_m = 1; // k = 0 mod 1 inicialmente
    bool possivel = true;

    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;

        // Extrai o ciclo
        vector<int> ciclo;
        int curr = i;
        while (!vis[curr]) {
            vis[curr] = true;
            ciclo.push_back(curr);
            curr = P[curr];
        }

        int L = ciclo.size();
        vector<int> valsA(L), valsB(L);
        for (int j = 0; j < L; ++j) {
            valsA[j] = A[ciclo[j]];
            valsB[j] = B[ciclo[j]];
        }

        // Encontra todos os shifts válidos s tal que após s passos, valsA vira valsB
        // Na transição da ICPC, após 1 passo, o elemento na posição pos vai para P[pos].
        // Isso significa que B[P[pos]] recebe A[pos], ou seja, B[ciclo[(j+1)%L]] = A[ciclo[j]] após 1 passo.
        // Portanto, após s passos, B[ciclo[(j+s)%L]] = A[ciclo[j]].
        vector<int> shifts_validos;
        for (int s = 0; s < L; ++s) {
            bool ok = true;
            for (int j = 0; j < L; ++j) {
                if (B[ciclo[(j + s) % L]] != A[ciclo[j]]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                shifts_validos.push_back(s);
            }
        }

        if (shifts_validos.empty()) {
            possivel = false;
            break;
        }

        // Combinar os shifts válidos deste ciclo com a resposta global acumulada
        // Como o ciclo pode ter múltiplos shifts válidos se houver repetições, 
        // testamos quais casam com o nosso ans_r mod ans_m atual.
        long long next_ans_r = -1, next_ans_m = -1;
        bool achou_combinacao = false;

        for (int s : shifts_validos) {
            long long temp_r, temp_m;
            if (merge_congruence(ans_r, ans_m, s, L, temp_r, temp_m)) {
                if (!achou_combinacao || temp_r < next_ans_r) {
                    next_ans_r = temp_r;
                    next_ans_m = temp_m;
                }
                achou_combinacao = true;
            }
        }

        if (!achou_combinacao) {
            possivel = false;
            break;
        }

        ans_r = next_ans_r;
        ans_m = next_ans_m;
    }

    if (!possivel) {
        cout << "IMPOSSIVEL\n";
    } else {
        if (ans_r > 1000000000LL) {
            cout << "DEMAIS\n";
        } else {
            cout << ans_r << "\n";
        }
    }

    return 0;
}
