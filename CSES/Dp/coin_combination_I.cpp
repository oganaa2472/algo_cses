#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, target;
    if (!(cin >> n >> target)) return 0;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    int MOD = 1e9 + 7;

    // dp[i] = i нийлбэрийг гаргах аргын тоо
    vector<int> dp(target + 1, 0);

    // Суурь нөхцөл
    dp[0] = 1;

    // 1. Гадна талд: Нийлбэрээр гүйнэ
    for (int i = 1; i <= target; i++) {
        // 2. Дотор талд: Зооснуудаар гүйнэ
        for (int c : coins) {
            // Хэрэв i нийлбэрээс c зоосыг хасах боломжтой бол
            if (i - c >= 0) {
                dp[i] = (dp[i] + dp[i - c]) % MOD;
            }
        }
    }

    cout << dp[target] << "\n";

    return 0;
}