#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // index i дээр +v нэмэх
    void update(int i, int v = 1) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    // 1..i хүртэлх нийлбэр
    int query(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // l..r
    int rangeQuery(int l, int r) const {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<array<int, 3>> ranges(n);
    vector<int> ys;

    for (int i = 0; i < n; i++) {
        cin >> ranges[i][0] >> ranges[i][1];
        ranges[i][2] = i;          // original index
        ys.push_back(ranges[i][1]);
    }

    // 1️⃣ Coordinate Compression on y
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getY = [&](int y) {
        return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1;
    };

    // 2️⃣ Sort by x asc, y desc
    sort(ranges.begin(), ranges.end(), [](auto &a, auto &b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });

    vector<int> contains(n, 0), containedBy(n, 0);

    int m = ys.size();

    // 3️⃣ Count how many ranges each range contains
    Fenwick bit1(m);
    for (int i = n - 1; i >= 0; i--) {
        int y = getY(ranges[i][1]);
        contains[ranges[i][2]] = bit1.query(y);
        bit1.update(y, 1);
    }

    // 4️⃣ Count how many ranges contain each range
    Fenwick bit2(m);
    for (int i = 0; i < n; i++) {
        int y = getY(ranges[i][1]);
        containedBy[ranges[i][2]] =
            bit2.query(m) - bit2.query(y - 1);
        bit2.update(y, 1);
    }

    // 5️⃣ Output
    for (int i = 0; i < n; i++)
        cout << contains[i] << " ";
    cout << "\n";

    for (int i = 0; i < n; i++)
        cout << containedBy[i] << " ";
    cout << "\n";

    return 0;
}
