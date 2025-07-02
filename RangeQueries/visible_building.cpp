#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, q;
int h[MAXN];

// Segment Tree – барилга бүрийн хамгийн өндөр утгыг хадгалах
int seg[4 * MAXN];

// Сегмент мод бүтээх
void build(int x, int lx, int rx) {
    if (rx - lx == 1) {
        if (lx < n) seg[x] = h[lx];
        return;
    }
    int m = (lx + rx) / 2;
    build(2 * x + 1, lx, m);
    build(2 * x + 2, m, rx);
    seg[x] = max(seg[2 * x + 1], seg[2 * x + 2]);
}

// Максимум авах
int get_max(int l, int r, int x, int lx, int rx) {
    if (lx >= r || rx <= l) return 0;
    if (lx >= l && rx <= r) return seg[x];
    int m = (lx + rx) / 2;
    int left = get_max(l, r, 2 * x + 1, lx, m);
    int right = get_max(l, r, 2 * x + 2, m, rx);
    return max(left, right);
}

// Зүүнээс баруун руу харах үед харагдах барилга тоолох
int count_visible(int l, int r) {
    int cnt = 0;
    int current_max = 0;
    for (int i = l; i <= r; ++i) {
        int hi = h[i];
        if (hi > current_max) {
            cnt++;
            current_max = hi;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    // Segment tree бүтээх
    build(0, 0, n);

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--; // 0-based индекс
        cout << count_visible(a, b) << '\n';
    }

    return 0;
}
