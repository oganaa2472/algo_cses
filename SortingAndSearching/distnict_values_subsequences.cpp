#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1'000'000'007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;            cin >> n;
    unordered_map<long long,int> freq;
    for (int i = 0; i < n; ++i) {
        long long x;  cin >> x;
        ++freq[x];
    }

    long long ans = 1;
    for (auto [val, cnt] : freq) {
        ans = (ans * (cnt + 1)) % MOD;
    }
    ans = (ans - 1 + MOD) % MOD;   // remove empty subsequence
    cout << ans << '\n';
}
