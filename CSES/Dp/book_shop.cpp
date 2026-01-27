#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> price(n);
    vector<int> pages(n);

    // Үнүүдийг унших
    for (int i = 0; i < n; i++) cin >> price[i];
    
    // Хуудасны тоонуудыг унших
    for (int i = 0; i < n; i++) cin >> pages[i];

    // dp[j] = j үнэд багтах хамгийн их хуудасны тоо
    // Төсөв x хүртэл байж болох тул хэмжээ нь x + 1
    vector<int> dp(x + 1, 0);

    // Ном бүрээр гүйнэ
    for (int i = 0; i < n; i++) {
        // Төсвөөр гүйнэ (Хойноос урагшаа!)
        // Бидний байгаа мөнгө (j) тухайн номны үнээс (price[i]) их байх ёстой
        for (int j = x; j >= price[i]; j--) {
            dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
        }
    }

    // Хамгийн их төсөвт харгалзах хамгийн их хуудас
    cout << dp[x] << "\n";

    return 0;
}