#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        vector<int> b(k);
        for (int i = 0; i < k; ++i) cin >> b[i];

        sort(a.begin(), a.end(), greater<long long>()); // prices high -> low
        sort(b.begin(), b.end());                      // vouchers small -> large

        long long total = 0;
        for (long long v : a) total += v;

        // Use as many vouchers as possible (smallest sizes first)
        long long usedItems = 0;
        int m = 0;
        for (; m < k; ++m) {
            if (usedItems + b[m] <= n) usedItems += b[m];
            else break;
        }

        long long freebies = 0;
        int l = 0, r = n - 1;

        // Give away largest items for vouchers with b == 1
        int i = 0;
        while (i < m && b[i] == 1) {
            freebies += a[l];
            ++l;
            ++i;
        }

        // Remaining used vouchers have b > 1; process from largest b to smallest for safety
        for (int j = m - 1; j >= i; --j) {
            // take one from left as the paid item (advance l)
            ++l;
            // free item is current smallest
            freebies += a[r];
            r -= (b[j] - 1);
        }

        cout << (total - freebies) << '\n';
    }
    return 0;
}


