#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Grid-ийг унших
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int MOD = 1e9 + 7;

    // dp[i][j] = (i, j) нүдэнд хүрэх замын тоо
    // n x n хэмжээтэй 0-ээр дүүргэсэн хүснэгт
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Суурь нөхцөл: Эхлэх цэгт урхи байхгүй бол 1, байвал 0
    if (grid[0][0] == '.') {
        dp[0][0] = 1;
    } else {
        // Эхлэх цэг хаалттай бол шууд 0 хэвлээд дуусгаж болно
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Урхитай нүд рүү очиж болохгүй тул алгасна (dp нь 0 хэвээр үлдэнэ)
            if (grid[i][j] == '*') {
                dp[i][j] = 0;
                continue;
            }

            // Дээд талаас ирэх
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }
            
            // Зүүн талаас ирэх
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
            }
        }
    }

    // Төгсгөлийн цэг дэх утгыг хэвлэнэ
    cout << dp[n-1][n-1] << "\n";

    return 0;
}