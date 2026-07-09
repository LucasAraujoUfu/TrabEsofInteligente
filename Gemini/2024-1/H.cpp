#include <iostream>
#include <string>
#include <vector>

using namespace std;

string m_str, n_str;
vector<int> pos_m, pos_n;
bool resolvido = false;

void checar() {
    long long n_val = 0;
    for (char c : n_str) {
        n_val = (n_val << 1) | (c - '0');
    }
    if (n_val == 0) return; // Divisão por zero inválida

    long long resto_m = 0;
    for (char c : m_str) {
        resto_m = ((resto_m << 1) | (c - '0')) % n_val;
    }

    if (resto_m == 0) {
        cout << m_str << "\n";
        resolvido = true;
    }
}

void solve(size_t idx) {
    if (resolvido) return;
    if (idx == pos_m.size() + pos_n.size()) {
        checar();
        return;
    }

    if (idx < pos_m.size()) {
        m_str[pos_m[idx]] = '0';
        solve(idx + 1);
        m_str[pos_m[idx]] = '1';
        solve(idx + 1);
    } else {
        size_t n_idx = idx - pos_m.size();
        n_str[pos_n[n_idx]] = '0';
        solve(idx + 1);
        n_str[pos_n[n_idx]] = '1';
        solve(idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> m_str >> n_str) {
        for (size_t i = 0; i < m_str.size(); i++) {
            if (m_str[i] == '*') pos_m.push_back(i);
        }
        for (size_t i = 0; i < n_str.size(); i++) {
            if (n_str[i] == '*') pos_n.push_back(i);
        }
        solve(0);
    }
    return 0;
}
