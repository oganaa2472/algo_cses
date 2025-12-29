#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    int a, b;
    cin >> a >> b;

    // Нөхцөл 1: Нийлбэр нь 3-т хуваагдах ёстой
    // Нөхцөл 2: Нэг нь нөгөөгөөсөө 2 дахин их байж болохгүй
    if ((a + b) % 3 == 0 && min(a, b) * 2 >= max(a, b)) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
}

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}