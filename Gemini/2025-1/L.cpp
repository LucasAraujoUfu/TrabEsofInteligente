#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Estrutura para armazenar as propriedades de uma palavra no dicionário
struct Palavra {
    string texto;
    long long x, y;
};

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Palavra> dicionario(n);
    map<string, pair<long long, long long>> coordenadas;

    for (int i = 0; i < n; ++i) {
        cin >> dicionario[i].texto >> dicionario[i].x >> dicionario[i].y;
        coordenadas[dicionario[i].texto] = {dicionario[i].x, dicionario[i].y};
    }

    int m;
    cin >> m;
    vector<string> texto_base(m);
    for (int i = 0; i < m; ++i) {
        cin >> texto_base[i];
    }

    int q, k_inicial;
    cin >> q >> k_inicial;

    while (q--) {
        int f;
        cin >> f;
        vector<string> consulta(f);
        for (int i = 0; i < f; ++i) {
            cin >> consulta[i];
        }

        int k_atual = k_inicial;
        vector<string> candidatas;

        // Tenta encontrar candidatas reduzindo K se necessário
        while (k_atual > 0) {
            // Pega as últimas k_atual palavras da consulta
            vector<string> alvo(k_atual);
            for (int i = 0; i < k_atual; ++i) {
                alvo[i] = consulta[f - k_atual + i];
            }

            // Busca no texto base
            for (int i = 0; i <= m - k_atual - 1; ++i) {
                bool casamento = true;
                for (int j = 0; j < k_atual; ++j) {
                    if (texto_base[i + j] != alvo[j]) {
                        casamento = false;
                        break;
                    }
                }
                // Se casou, a próxima palavra (no índice i + k_atual) é uma candidata
                if (casamento) {
                    candidatas.push_back(texto_base[i + k_atual]);
                }
            }

            // Se encontramos alguma candidata, podemos parar a busca
            if (!candidatas.empty()) {
                break;
            }
            k_atual--;
        }

        // Imprime a consulta original
        for (int i = 0; i < f; ++i) {
            cout << consulta[i] << " ";
        }

        // Se falhou em achar candidatas mesmo com K=1
        if (candidatas.empty()) {
            cout << "*\n";
            continue;
        }

        // Calcula S(d) para cada palavra d do dicionário para achar a melhor
        string melhor_palavra = "";
        long long maior_sim = -2e18; // Inicializa com valor muito baixo

        for (int i = 0; i < n; ++i) {
            long long sim_atual = 0;
            long long dx = dicionario[i].x;
            long long dy = dicionario[i].y;

            for (const string& cand : candidatas) {
                // Se a palavra candidata não estiver no dicionário, suas coordenadas são (0,0)
                long long cx = 0, cy = 0;
                if (coordenadas.count(cand)) {
                    cx = coordenadas[cand].first;
                    cy = coordenadas[cand].second;
                }
                sim_atual += (dx * cx + dy * cy);
            }

            // Como percorremos o dicionário na ordem de leitura (do mais comum ao menos comum),
            // a condição de maior estrito (>) garante o desempate correto para a primeira ocorrência.
            if (sim_atual > maior_sim) {
                maior_sim = sim_atual;
                melhor_palavra = dicionario[i].texto;
            }
        }

        cout << melhor_palavra << "\n";
    }

    return 0;
}
