#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Модуль авах тоо
    int MOD = 1e9 + 7;

    // dp[i] нь i нийлбэрийг гаргах боломжийн тоог хадгална
    vector<int> dp(n + 1, 0);

    // Суурь нөхцөл
    dp[0] = 1;

    // 1-ээс n хүртэл тооцоолно
    for (int i = 1; i <= n; i++) {
        // Шоо 1-6 хүртэл буух боломжтой
        for (int j = 1; j <= 6; j++) {
            // Хэрэв i-j нь сөрөг биш бол (ө.х бид сөрөг тоо руу үсрэхгүй)
            if (i - j >= 0) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }

    cout << dp[n] << "\n";

    return 0;
}