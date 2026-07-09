#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de I/O para maratona
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    long long min_r = 2e18, max_r = -2e18;
    long long min_c = 2e18, max_c = -2e18;

    for (int i = 0; i < n; ++i) {
        long long r, c;
        cin >> r >> c;
        min_r = min(min_r, r);
        max_r = max(max_r, r);
        min_c = min(min_c, c);
        max_c = max(max_c, c);
    }

    long long H = max_r - min_r + 1;
    long long W = max_c - min_c + 1;

    long long max_area = H * W;

    // Podemos distribuir o orçamento K entre aumentar a altura e/ou a largura.
    // Como os movimentos diagonais permitem aumentar a altura e a largura simultaneamente gastando 1 movimento
    // por passo (ex: mover o rei do canto superior direito para cima e para a direita),
    // o custo total para aumentar a altura em dh e a largura em dw é exatamente max(dh, dw).
    // Portanto, com K movimentos, podemos aumentar tanto a altura quanto a largura em até K unidades ao mesmo tempo!
    
    long long final_H = H + k;
    long long final_W = W + k;
    
    max_area = final_H * final_W;

    cout << max_area << "\n";

    return 0;
}
