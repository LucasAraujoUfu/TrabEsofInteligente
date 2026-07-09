#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> bit_counts(30, 0);
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        for (int b = 0; b < 30; b++) {
            if ((val >> b) & 1) {
                bit_counts[b]++;
            }
        }
    }
    
    vector<int> resultado(n, 0);
    for (int b = 0; b < 30; b++) {
        int ativos = bit_counts[b];
        for (int i = 0; i < ativos; i++) {
            resultado[i] |= (1 << b);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << resultado[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}
