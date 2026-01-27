#include <iostream>
#include <vector>
#include <numeric> // accumulate функцэд хэрэгтэй

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> coins(n);
    int max_possible_sum = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
        max_possible_sum += coins[i];
    }

    // dp[i] = i нийлбэрийг үүсгэх боломжтой эсэх
    // Бүх боломжит нийлбэрийн хэмжээгээр үүсгэнэ
    vector<bool> dp(max_possible_sum + 1, false);
    
    // Суурь нөхцөл: 0 нийлбэрийг үргэлж үүсгэж болно (зоос сонгохгүй байх)
    dp[0] = true;

    // Зоос бүрээр гүйнэ
    for (int c : coins) {
        // Одоо байгаа боломжит нийлбэрүүд дээр c-г нэмнэ.
        // Давхардаж ашиглахаас сэргийлж ХОЙНООС нь гүйнэ.
        for (int i = max_possible_sum; i >= c; i--) {
            // Хэрэв i-c нийлбэр боломжтой байсан бол
            // түүн дээр c-г нэмээд i нийлбэр бас боломжтой болно.
            if (dp[i - c]) {
                dp[i] = true;
            }
        }
    }

    // Хариуг цуглуулах
    vector<int> result;
    for (int i = 1; i <= max_possible_sum; i++) {
        if (dp[i]) {
            result.push_back(i);
        }
    }

    // 1. Нийт хэдэн ялгаатай нийлбэр байгааг хэвлэх
    cout << result.size() << "\n";

    // 2. Нийлбэрүүдийг хэвлэх
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << (i == result.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}