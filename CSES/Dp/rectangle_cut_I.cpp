#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    if (!(cin >> a >> b)) return 0;

    // dp[i][j] = i x j хэмжээтэй тэгш өнцөгтийг зүсэх хамгийн цөөн үйлдэл
    // a, b <= 500 тул санах ойд хангалттай багтана
    vector<vector<int>> dp(a + 1, vector<int>(b + 1));

    // Бүх боломжит хэмжээгээр давталт хийнэ
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (i == j) {
                // Квадрат бол 0 үйлдэл
                dp[i][j] = 0;
            } else {
                // Анхны утгыг хязгааргүй (маш том тоо) гэж үзнэ
                dp[i][j] = 1e9;

                // 1. Босоо зүсэлтүүдийг шалгах (Vertical cuts)
                // i-г k болон i-k гэж хуваана. 
                // Тэгш хэмтэй тул i/2 хүртэл шалгахад хангалттай.
                for (int k = 1; k <= i / 2; k++) {
                    dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
                }

                // 2. Хөндлөн зүсэлтүүдийг шалгах (Horizontal cuts)
                // j-г k болон j-k гэж хуваана.
                // j/2 хүртэл шалгахад хангалттай.
                for (int k = 1; k <= j / 2; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
                }
            }
        }
    }

    // Хариуг хэвлэх
    cout << dp[a][b] << "\n";

    return 0;
}