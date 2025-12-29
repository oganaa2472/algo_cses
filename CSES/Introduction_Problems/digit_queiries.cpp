#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef long long ll;

void solve() {
    ll k;
    cin >> k;

    ll length = 1;      // Оронгийн тоо (1-ээс эхэлнэ)
    ll count = 9;       // Тухайн оронтой тоонуудын нийт цифрийн тоо
    ll start = 1;       // Тухайн оронтой тоонуудын эхлэх тоо (1, 10, 100...)

    // 1. k-г агуулж буй тооны оронгийн тоог олох
    while (k > length * count) {
        k -= length * count;
        length++;
        count *= 10;
        start *= 10;
    }

    // 2. k цифр нь яг аль тоон дотор байгааг олох
    // k-1 ашиглах нь 0-ээс эхэлсэн индекслэлтэд тусална
    ll target_number = start + (k - 1) / length;

    // 3. Тухайн тооны аль цифр болохыг олох
    string s = to_string(target_number);
    cout << s[(k - 1) % length] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}