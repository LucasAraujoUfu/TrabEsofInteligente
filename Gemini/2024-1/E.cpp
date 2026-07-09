#include <iostream>
#include <vector>

using namespace std;

int n;

bool checar(const vector<vector<int>>& grid) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j + 1 < n && grid[i][j] >= grid[i][j+1]) return false;
            if (i + 1 < n && grid[i][j] >= grid[i+1][j]) return false;
        }
    }
    return true;
}

vector<vector<int>> rotacionar_anti_horario(const vector<vector<int>>& grid) {
    vector<vector<int>> nova(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nova[n - 1 - j][i] = grid[i][j];
        }
    }
    return nova;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> n)) return 0;
    
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    for (int r = 0; r < 4; r++) {
        if (checar(grid)) {
            cout << r << "\n";
            return 0;
        }
        grid = rotacionar_anti_horario(grid);
    }
    
    return 0;
}
