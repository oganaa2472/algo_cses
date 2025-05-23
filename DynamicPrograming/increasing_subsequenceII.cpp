#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }
    void update(int i, int val) {
        while (i <= n) {
            bit[i] = (bit[i] + val) % MOD;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while (i > 0) {
            res = (res + bit[i]) % MOD;
            i -= i & -i;
        }
        return res;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n), comp(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        comp[i] = a[i];
    }

    // Coordinate Compression
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
    }

    FenwickTree bit(comp.size());
    int result = 0;

    for (int i = 0; i < n; ++i) {
        int cnt = bit.query(a[i] - 1); // count of sequences ending in < a[i]
        int dp = (1 + cnt) % MOD;      // itself + previous counts
        bit.update(a[i], dp);          // update this value
        result = (result + dp) % MOD;
    }

    cout << result << "\n";
    return 0;
}
