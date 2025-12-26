#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Fast I/O is essential
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    // We use a prefix array of size n+1
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        // Compute prefix XOR on the fly
        pref[i] = pref[i - 1] ^ x;
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        // The XOR sum of range [a, b] is pref[b] ^ pref[a-1]
        cout << (pref[b] ^ pref[a - 1]) << "\n";
    }

    return 0;
}