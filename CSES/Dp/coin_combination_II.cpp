#include <iostream>
#include <vector>

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

    // Суурь нөхцөл: 0 мөнгийг 1 аргаар (юу ч сонгохгүй) гаргана
    dp[0] = 1;

    // Ялгаа нь энд байна:
    // 1. Гадна талд: ЗООСНУУДААР гүйнэ
    // Бид эхлээд зөвхөн эхний зоосыг ашиглаж болох бүх тоог олно.
    // Дараа нь хоёр дахь зоосыг нэмж ашиглах боломжуудыг нэмнэ, гэх мэт.
    for (int c : coins) {
        // 2. Дотор талд: НИЙЛБЭРЭЭР гүйнэ
        for (int i = 1; i <= target; i++) {
            if (i - c >= 0) {
                dp[i] = (dp[i] + dp[i - c]) % MOD;
            }
        }
    }

    cout << dp[target] << "\n";

    return 0;
}