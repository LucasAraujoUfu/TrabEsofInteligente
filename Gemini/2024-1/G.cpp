#include <iostream>
#include <vector>

using namespace std;

struct No {
    long long volume;
    int nome;
    int esq, dir, pai;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int total_nos = 2 * n;
    vector<No> arvore(total_nos);

    for (int i = 1; i <= n; i++) {
        cin >> arvore[i].volume;
        arvore[i].nome = i;
        arvore[i].esq = arvore[i].dir = arvore[i].pai = 0;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int pai_id = n + i;
        arvore[pai_id].esq = a;
        arvore[pai_id].dir = b;
        arvore[a].pai = pai_id;
        arvore[b].pai = pai_id;
    }

    auto atualizar_no = [&](int id) {
        int e = arvore[id].esq;
        int d = arvore[id].dir;
        arvore[id].volume = arvore[e].volume + arvore[d].volume;
        if (arvore[e].volume > arvore[d].volume) {
            arvore[id].nome = arvore[e].nome;
        } else if (arvore[d].volume > arvore[e].volume) {
            arvore[id].nome = arvore[d].nome;
        } else {
            arvore[id].nome = min(arvore[e].nome, arvore[d].nome);
        }
    };

    // Inicializa a árvore de baixo para cima
    for (int i = n + 1; i < 2 * n; i++) {
        atualizar_no(i);
    }

    int raiz = 2 * n - 1;
    cout << arvore[raiz].nome << "\n";

    int q;
    if (cin >> q) {
        while (q--) {
            int no_id;
            long long qtd;
            cin >> no_id >> qtd;

            arvore[no_id].volume += qtd;
            int atual = arvore[no_id].pai;
            while (atual != 0) {
                atualizar_no(atual);
                atual = arvore[atual].pai;
            }
            cout << arvore[raiz].nome << "\n";
        }
    }

    return 0;
}
