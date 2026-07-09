#include <iostream>
#include <string>
#include <vector>

using namespace std;

string m_str, n_str;
vector<int> pos_m, pos_n;
bool solved = false;

void check() {
    long long n_val = 0;
    for (char c : n_str) {
        n_val = (n_val << 1) | (c - '0');
    }
    if (n_val == 0) return;

    long long rem_m = 0;
    for (char c : m_str) {
        rem_m = ((rem_m << 1) | (c - '0')) % n_val;
    }

    if (rem_m == 0) {
        cout << m_str << "\n";
        solved = true;
    }
}

void backtrack(size_t idx) {
    if (solved) return;
    if (idx == pos_m.size() + pos_n.size()) {
        check();
        return;
    }

    if (idx < pos_m.size()) {
        m_str[pos_m[idx]] = '0';
        backtrack(idx + 1);
        m_str[pos_m[idx]] = '1';
        backtrack(idx + 1);
    } else {
        size_t n_idx = idx - pos_m.size();
        n_str[pos_n[n_idx]] = '0';
        backtrack(idx + 1);
        n_str[pos_n[n_idx]] = '1';
        backtrack(idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> m_str >> n_str) {
        for (size_t i = 0; i < m_str.size(); i++) if (m_str[i] == '*') pos_m.push_back(i);
        for (size_t i = 0; i < n_str.size(); i++) if (n_str[i] == '*') pos_n.push_back(i);
        backtrack(0);
    }
    return 0;
}
