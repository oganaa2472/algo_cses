#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // 1. Нийт нийлбэрийг олох
    long long total_sum = (long long)n * (n + 1) / 2;

    // Хэрэв нийлбэр сондгой бол тэнцүү хуваах боломжгүй
    if (total_sum % 2 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    long long target = total_sum / 2;
    long long MOD = 1e9 + 7;

    // dp[i] = i нийлбэрийг үүсгэх боломжийн тоо
    vector<int> dp(target + 1, 0);
    
    // Суурь нөхцөл: 0 нийлбэрийг 1 аргаар үүсгэнэ
    dp[0] = 1;

    // 2. DP тооцоолол
    // ЧУХАЛ: Бид давхардлыг арилгахын тулд 1-ээс n-1 хүртэл л гүйнэ.
    // n-р тоог нөгөө олонлогт фикс хийсэн гэж үздэг.
    for (int i = 1; i < n; i++) {
        // Хойноос нь урагш гүйнэ (0/1 Knapsack зарчим)
        for (int j = target; j >= i; j--) {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }

    cout << dp[target] << "\n";

    return 0;
}