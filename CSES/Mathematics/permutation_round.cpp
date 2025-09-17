#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

long long lcm_mod(long long a, long long b) {
    return ((a / __gcd(a,b)) % MOD * (b % MOD)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--; // convert to 0-indexed
    }

    vector<bool> visited(n, false);
    long long ans = 1;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            int len = 0;
            int cur = i;
            while(!visited[cur]) {
                visited[cur] = true;
                cur = p[cur];
                len++;
            }
            ans = lcm_mod(ans, len);
        }
    }

    cout << ans << "\n";
    return 0;
}
