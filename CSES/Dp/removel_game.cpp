#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> x(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        sum += x[i];
    }

    // dp[i][j] нь i-ээс j хүртэлх завсарт
    // (Эхэлж нүүж буй тоглогчийн оноо - Хоёр дахь тоглогчийн оноо)
    vector<vector<long long>> dp(n, vector<long long>(n));

    // Суурь нөхцөл: Урт нь 1 байх үед
    for (int i = 0; i < n; i++) {
        dp[i][i] = x[i];
    }

    // Урт нь 2-оос n хүртэл тооцоолно
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            // Томьёоны дагуу хоёр захаас аль ашигтайг сонгоно
            dp[i][j] = max(x[i] - dp[i+1][j], x[j] - dp[i][j-1]);
        }
    }

    // Эцсийн хариу: (Нийт нийлбэр + Зөрүү) / 2
    cout << (sum + dp[0][n-1]) / 2 << "\n";

    return 0;
}