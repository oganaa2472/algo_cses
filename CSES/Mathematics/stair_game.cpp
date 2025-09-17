#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<long long> p(n);
        for(int i = 0; i < n; i++) cin >> p[i];

        long long xor_sum = 0;
        for(int i = 1; i < n; i++) // only p_2..p_n
            xor_sum ^= p[i];

        cout << (xor_sum ? "first" : "second") << "\n";
    }
}
