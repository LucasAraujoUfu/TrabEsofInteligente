#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long vol;
    int name;
    int left, right, parent;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int total_nodes = 2 * n;
    vector<Node> tree(total_nodes);

    for (int i = 1; i <= n; i++) {
        cin >> tree[i].vol;
        tree[i].name = i;
        tree[i].left = tree[i].right = tree[i].parent = 0;
    }

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int p = n + i;
        tree[p].left = a;
        tree[p].right = b;
        tree[a].parent = p;
        tree[b].parent = p;
    }

    auto update_node = [&](int id) {
        int l = tree[id].left;
        int r = tree[id].right;
        tree[id].vol = tree[l].vol + tree[r].vol;
        if (tree[l].vol > tree[r].vol) {
            tree[id].name = tree[l].name;
        } else if (tree[r].vol > tree[l].vol) {
            tree[id].name = tree[r].name;
        } else {
            tree[id].name = min(tree[l].name, tree[r].name);
        }
    };

    for (int i = n + 1; i < 2 * n; i++) {
        update_node(i);
    }

    int root = 2 * n - 1;
    cout << tree[root].name << "\n";

    int q;
    if (cin >> q) {
        while (q--) {
            int node_id;
            long long delta;
            cin >> node_id >> delta;

            tree[node_id].vol += delta;
            int curr = tree[node_id].parent;
            while (curr != 0) {
                long long old_vol = tree[curr].vol;
                int old_name = tree[curr].name;
                update_node(curr);
                // Otimização: se o volume mudou mas o nome propagado continua igual,
                // e o nó pai não depende do volume bruto absoluto para desempate de nomes distantes,
                // precisamos continuar subindo pois o volume altera os níveis de cima.
                curr = tree[curr].parent;
            }
            cout << tree[root].name << "\n";
        }
    }
    return 0;
}
