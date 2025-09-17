#include <bits/stdc++.h>
using namespace std;

// Returns the k-th removed position (1-indexed) when eliminating every second child among n.
// This uses an O(log n) recursion based on splitting into evens first, then odds with a rotation for odd n.
static long long kth_removed(long long n, long long k) {
    if (n == 1) return 1;
    long long e = n / 2; // number of even positions removed in the first pass
    if (k <= e) return 2 * k; // first floor(n/2) removals are even positions: 2,4,6,...

    // process the remaining odds
    if ((n & 1LL) == 0) {
        // even n: remaining odds are 1,3,5,...,n-1; counting restarts from 1
        return 2 * kth_removed(e, k - e) - 1;
    } else {
        // odd n: remaining odds are 1,3,5,...,n; counting continues starting at last odd (rotation by 1)
        long long r = e + 1;           // number of remaining odds = ceil(n/2)
        long long t = k - e;           // which removal among the remaining odds (1..r)
        long long rotated_index = (t % r) + 1; // rotate-left by 1 relative to standard start-at-1 order
        return 2 * kth_removed(r, rotated_index) - 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << kth_removed(n, k) << '\n';
    }
    return 0;
}



