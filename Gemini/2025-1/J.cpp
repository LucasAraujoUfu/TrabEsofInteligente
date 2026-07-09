#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Otimização de I/O padrão da ICPC
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Vetor de booleanos para marcar quais dificuldades já possuímos (1 a 4)
    vector<bool> possui(5, false);

    // Lendo as 10 tarefas da entrada padrão
    for (int i = 0; i < 10; ++i) {
        int d;
        cin >> d;
        if (d >= 1 && d <= 4) {
            possui[d] = true;
        }
    }

    // Contando quantos níveis estão faltando
    int faltando = 0;
    for (int nivel = 1; nivel <= 4; ++nivel) {
        if (!possui[nivel]) {
            faltando++;
        }
    }

    // Imprime o resultado final seguido de quebra de linha (padrão ICPC)
    cout << faltando << "\n";

    return 0;
}
