#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total_sum += a[i];
    }

    if (total_sum % 2 != 0) {
        cout << "-1\n";
        return 0;
    }

    int target = total_sum / 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        int val = a[i - 1];
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= val && dp[i - 1][j - val]) {
                dp[i][j] = true;
            }
        }
    }

    if (!dp[n][target]) {
        cout << "-1\n";
        return 0;
    }

    vector<int> alice_items, bob_items;
    int curr_j = target;
    for (int i = n; i > 0; i--) {
        int val = a[i - 1];
        if (curr_j >= val && dp[i - 1][curr_j - val]) {
            alice_items.push_back(val);
            curr_j -= val;
        } else {
            bob_items.push_back(val);
        }
    }

    sort(alice_items.rbegin(), alice_items.rend());
    sort(bob_items.rbegin(), bob_items.rend());

    vector<int> order;
    int sum_a = 0, sum_b = 0;
    size_t idx_a = 0, idx_b = 0;

    while (idx_a < alice_items.size() || idx_b < bob_items.size()) {
        if (sum_a <= sum_b && idx_a < alice_items.size()) {
            order.push_back(alice_items[idx_a]);
            sum_a += alice_items[idx_a];
            idx_a++;
        } else if (idx_b < bob_items.size()) {
            order.push_back(bob_items[idx_b]);
            sum_b += bob_items[idx_b];
            idx_b++;
        } else {
            order.push_back(alice_items[idx_a]);
            sum_a += alice_items[idx_a];
            idx_a++;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << order[i] << (i + 1 == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
