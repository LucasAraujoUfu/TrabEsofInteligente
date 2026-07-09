#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Estrutura para armazenar o intervalo de x em que a reta está dentro do playground
struct Intervalo {
    double l, r;
    int id;
    bool operator<(const Intervalo& outro) const {
        if (abs(l - outro.l) > 1e-9) return l < outro.l;
        return r < outro.r;
    }
};

// Estrutura para Árvore de Fenwick (Binary Indexed Tree) para contagem de inversões
struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    double A, B;
    if (!(cin >> n >> A >> B)) return 0; [cite: 194]

    vector<Intervalo> intervalos;

    for (int i = 0; i < n; ++i) {
        double M, C;
        cin >> M >> C; [cite: 194]

        // Resolver: A*x^2 - M*x + (B - C) = 0
        double a_coeff = A;
        double b_coeff = -M;
        double c_coeff = B - C;

        double delta = b_coeff * b_coeff - 4.0 * a_coeff * c_coeff;

        if (delta > 1e-9) { // Se há duas raízes reais distintas, a reta entra no playground
            double r1 = (-b_coeff - sqrt(delta)) / (2.0 * a_coeff);
            double r2 = (-b_coeff + sqrt(delta)) / (2.0 * a_coeff);
            intervalos.push_back({min(r1, r2), max(r1, r2), i});
        }
    }

    // Ordenar os intervalos pelo ponto esquerdo (L)
    sort(intervalos.begin(), intervalos.end());

    // Coordenadas para compressão dos valores de R para usar na BIT
    vector<double> rs;
    for (const auto& inv : intervalos) {
        rs.push_back(inv.r);
    }
    sort(rs.begin(), rs.end());
    rs.erase(unique(rs.begin(), rs.end(), [](double a, double b) {
        return abs(a - b) < 1e-9;
    }), rs.end());

    long long pares_validos = 0;
    BIT bit(rs.size());

    // Contar interseções usando a técnica de varredura
    for (const auto& inv : intervalos) {
        // Encontrar a posição comprimida de R
        int idx_r = lower_bound(rs.begin(), rs.end(), inv.r - 1e-9) - rs.begin() + 1;

        // Qualquer intervalo já processado (que tem L menor) e que possui o seu R 
        // maior do que o R atual irá cruzar com este intervalo.
        pares_validos += bit.query(idx_r, rs.size());

        // Inserir o R atual na árvore de Fenwick
        bit.update(idx_r, 1);
    }

    cout << pares_validos << "\n";

    return 0;
}
