#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 31;  // 2^30 > 1e9 тул k хүртэлх телепортод хангалттай
int up[MAXN][LOG];   // up[i][j] = i-с 2^j телепорт хийвэл хаана очих вэ

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // 1-р телепортын утгууд
    for (int i = 1; i <= n; i++) {
        cin >> up[i][0];
    }

    // Binary Lifting урьдчилгаа - up[i][j] үүсгэх
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    // Асуулт бүрийг боловсруулах
    while (q--) {
        int x;
        long long k;
        cin >> x >> k;

        // Binary Lifting-р k телепорт хийх
        for (int j = 0; j < LOG; j++) {
            if (k & (1LL << j)) {
                x = up[x][j];
            }
        }

        cout << x << '\n';
    }

    return 0;
}
