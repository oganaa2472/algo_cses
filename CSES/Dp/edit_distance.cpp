#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // min функцэд хэрэгтэй

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n_str, m_str;
    cin >> n_str >> m_str;

    int n = n_str.length();
    int m = m_str.length();

    // dp[i][j] хүснэгт үүсгэх
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // Суурь нөхцөлүүд (Base Cases):
    // Хэрэв нэг мөр нь хоосон бол нөгөө мөрийн урттай тэнцүү хэмжээний
    // Insert эсвэл Remove үйлдэл хийнэ.
    for (int i = 0; i <= n; i++) dp[i][0] = i; // m_str хоосон үед i тэмдэгт хасна
    for (int j = 0; j <= m; j++) dp[0][j] = j; // n_str хоосон үед j тэмдэгт нэмнэ

    // Хүснэгтийг дүүргэх
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // Тэмдэгтүүд ижил бол (индекс 0-ээс эхлэх тул i-1, j-1)
            if (n_str[i - 1] == m_str[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Ялгаатай бол 3 үйлдлийн хамгийн багыг авч 1-ийг нэмнэ
                dp[i][j] = 1 + min({
                    dp[i - 1][j],    // Remove (Дээд тал)
                    dp[i][j - 1],    // Add (Зүүн тал)
                    dp[i - 1][j - 1] // Replace (Диагональ)
                });
            }
        }
    }

    // Хариу: Баруун доод булан дахь утга
    cout << dp[n][m] << "\n";

    return 0;
}