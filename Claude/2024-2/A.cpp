#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S; cin >> S;
    int n = S.size();

    for(int len = 1; len < n; len++){
        string t = S.substr(0, len);
        string suffix = S.substr(len);

        // Calcular sorted_unique(t)
        string su = t;
        sort(su.begin(), su.end());
        su.erase(unique(su.begin(), su.end()), su.end());

        if(su == suffix){
            cout << len << "\n";
            return 0;
        }
    }

    return 0;
}
