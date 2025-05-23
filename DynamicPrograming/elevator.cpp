#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> weight(n);
    for (int i = 0; i < n; i++) cin >> weight[i];

    vector<pair<int, int>> dp(1 << n, {INF, 0});  
    dp[0] = {1, 0};  // 1 явалт, одоогийн жин 0

    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;  // Хэрэв зорчигч `i` аль хэдийн явсан бол алгасах
            
            int new_mask = mask | (1 << i);
            auto [rides, weight_sum] = dp[mask];

            if (weight_sum + weight[i] <= x) {
                dp[new_mask] = min(dp[new_mask], {rides, weight_sum + weight[i]});
            } else {
                dp[new_mask] = min(dp[new_mask], {rides + 1, weight[i]});
            }
        }
    }

    cout << dp[(1 << n) - 1].first << endl;  // Бүх зорчигч суусан төлөв
}
