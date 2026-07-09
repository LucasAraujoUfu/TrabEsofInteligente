#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de I/O para Maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    string C_str;
    cin >> C_str;

    // Vetor numérico para representar o conteúdo desejado C
    vector<int> C(n);
    for (int i = 0; i < n; ++i) {
        C[i] = C_str[i] - '0';
    }

    int melhor_Q = 1e9;
    int melhor_B_val = -1;

    // Testa todos os 256 padrões possíveis de 8 bits (0 a 255)
    for (int b_val = 0; b_val < 256; ++b_val) {
        // Extrai os bits do padrão B de b0 (MSB) até b7 (LSB)
        vector<int> B(8);
        for (int j = 0; j < 8; ++j) {
            B[j] = (b_val >> (7 - j)) & 1;
        }

        // Simulação com vetor de tamanho N para rastrear o estado atual
        vector<int> atual(n, 0);
        int operacoes = 0;
        bool possivel = true;

        // Passamos a janela i de -7 até N-1
        for (int i = -7; i < n; ++i) {
            // Verifica a posição mais à esquerda que está deixando de ser alcançada por qualquer janela futura.
            // Essa posição é exatamente (i + 0), que corresponde ao alinhamento com b0.
            int pos_critica = i;

            if (pos_critica >= 0 && pos_critica < n) {
                // Se o bit atual na memória simulada difere do alvo C, precisamos aplicar o XOR
                if (atual[pos_critica] != C[pos_critica]) {
                    operacoes++;
                    // Aplica o padrão B na janela [i, i+7]
                    for (int j = 0; j < 8; ++j) {
                        int idx = i + j;
                        if (idx >= 0 && idx < n) {
                            atual[idx] ^= B[j];
                        }
                    }
                }
            } else if (pos_critica < 0) {
                // Para i negativo, b0 está fora, mas outros bits de B podem interceptar o início de C.
                // Se o primeiro elemento visível de C (índice 0) já divergir da nossa simulação e a janela for a última 
                // oportunidade de afetá-lo de forma restrita, teríamos que aplicar.
                // Contudo, a varredura gulosa canônica funciona garantindo que corrigimos o primeiro bit incorreto de C.
                
                int primeiro_visivel = 0;
                // Descobre qual bit de B se alinha com o índice 0 de C
                int j_b = -i; 
                
                // Se o bit de B que toca o índice 0 for 1, e o índice 0 precisar ser invertido
                if (atual[primeiro_visivel] != C[primeiro_visivel] && B[j_b] == 1) {
                    operacoes++;
                    for (int j = 0; j < 8; ++j) {
                        int idx = i + j;
                        if (idx >= 0 && idx < n) {
                            atual[idx] ^= B[j];
                        }
                    }
                }
            }
        }

        // Verifica se a simulação obteve sucesso em igualar a string C por completo
        for (int i = 0; i < n; ++i) {
            if (atual[i] != C[i]) {
                possivel = false;
                break;
            }
        }

        // Se o padrão gerou a string com sucesso, avalia se minimiza Q
        if (possivel) {
            if (operacoes < melhor_Q) {
                melhor_Q = operacoes;
                melhor_B_val = b_val;
            }
            // O enunciado diz: "Se houver mais de um padrão B que minimize..., imprima o que corresponder
            // ao menor valor inteiro em base 2". Como nosso loop roda de 0 a 255, o primeiro a atingir
            // o mínimo estrito já será naturalmente o menor valor inteiro, dispensando tratamento de empate.
        }
    }

    // Imprime o resultado formatado em 8 bits binários seguido de Q
    for (int j = 0; j < 8; ++j) {
        cout << ((melhor_B_val >> (7 - j)) & 1);
    }
    cout << " " << melhor_Q << "\n";

    return 0;
}
