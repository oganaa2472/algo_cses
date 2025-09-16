
#include <bits/stdc++.h>
using namespace std;

// Recursive function to find the k-th removed child
int kth_removed(int n, int k) {
    if (n == 1) return 1; // only one child left
    int removed_first_pass = n / 2; // number of children removed in the first round
    if (k <= removed_first_pass) {
        return 2 * k; // k-th removed is in the first pass (even positions)
    } else {
        // k-th removed is in the remaining odd-numbered children
        // recurse on smaller circle
        return 2 * kth_removed(n - removed_first_pass, k - removed_first_pass) - 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q; // number of queries
    while (q--) {
        int n, k;
        cin >> n >> k;
        cout << kth_removed(n, k) << "\n"; // output answer for each query
    }

    return 0;
}