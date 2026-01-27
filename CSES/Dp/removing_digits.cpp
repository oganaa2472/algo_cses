#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // dp[i] = i тоог 0 болгох хамгийн цөөн алхам
    // Анх бүгдийг нь хязгааргүй (1e9) гэж үзнэ
    vector<int> dp(n + 1, 1e9);

    // Суурь нөхцөл
    dp[0] = 0;

    // 1-ээс n хүртэл тооцоолно
    for (int i = 1; i <= n; i++) {
        // i тооны цифр бүрийг шалгах
        int temp = i;
        while (temp > 0) {
            int digit = temp % 10; // Сүүлийн цифрийг авах
            temp /= 10;            // Сүүлийн цифрийг хасах

            // Хэрэв цифр 0-ээс ялгаатай бол хасаж үзнэ
            if (digit != 0) {
                dp[i] = min(dp[i], dp[i - digit] + 1);
            }
        }
    }

    cout << dp[n] << "\n";

    return 0;
}