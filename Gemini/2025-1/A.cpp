#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Vetor para guardar o número máximo de alunos que gostam de alguma fruta em cada turma
    // Inicializado com 0
    vector<long long> max_na_turma(m, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            long long G_ij;
            cin >> G_ij;
            max_na_turma[j] = max(max_na_turma[j], G_ij);
        }
    }

    long long total_alunos = 0;
    for (int j = 0; j < m; ++j) {
        // Cada turma j precisa ter pelo menos max_na_turma[j] alunos, 
        // e no mínimo 1 aluno caso todo mundo tenha respondido 0.
        total_alunos += max(1LL, max_na_turma[j]);
    }

    cout << total_alunos << "\n";

    return 0;
}
