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

    // dp[i] = i мөнгийг бүрдүүлэх хамгийн цөөн зоосны тоо
    // Анх бүгдийг нь "хязгааргүй" (1e9) гэж үзнэ.
    // target + 1 хэмжээтэй үүсгэнэ (0-ээс target хүртэл)
    vector<int> dp(target + 1, 1e9);

    // Суурь нөхцөл
    dp[0] = 0;

    // 1-ээс target хүртэлх бүх мөнгөн дүнгийн хариуг олно
    for (int i = 1; i <= target; i++) {
        // Зоос бүрийг шалгах
        for (int c : coins) {
            // Хэрэв i мөнгөнөөс c зоосыг хасах боломжтой бол
            if (i - c >= 0) {
                dp[i] = min(dp[i], dp[i - c] + 1);
            }
        }
    }

    // Хэрэв dp[target] хэвээрээ 1e9 байвал боломжгүй гэсэн үг
    if (dp[target] == 1e9) {
        cout << -1 << "\n";
    } else {
        cout << dp[target] << "\n";
    }

    return 0;
}