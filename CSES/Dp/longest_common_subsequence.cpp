#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    // DP хүснэгт үүсгэх (n+1 x m+1 хэмжээтэй)
    // dp[i][j] нь a-ийн эхний i, b-ийн эхний j элементийн LCS урт
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // 1. Уртыг тооцоолох
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // Векторын индекс 0-ээс эхэлдэг тул i-1, j-1 гэж хандана
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Уртыг хэвлэх
    cout << dp[n][m] << "\n";

    // 2. Дарааллыг сэргээх (Backtracking)
    vector<int> result;
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            // Тэнцүү бол энэ тоо LCS-ийн хэсэг мөн
            result.push_back(a[i - 1]);
            i--;
            j--;
        } else {
            // Тэнцүү биш бол аль ихийг нь дагаж явна
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--; // Дээшээ
            } else {
                j--; // Зүүн тийш
            }
        }
    }

    // Бид хойноос нь урагш олсон тул эргүүлэх хэрэгтэй
    reverse(result.begin(), result.end());

    // Дарааллыг хэвлэх
    for (int k = 0; k < result.size(); k++) {
        cout << result[k] << (k == result.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}