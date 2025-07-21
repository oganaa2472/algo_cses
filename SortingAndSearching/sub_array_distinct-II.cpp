#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int n, k;
    cin >> n >> k; // 🔧 Missing input for `k`

    vector<ll> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    map<ll, ll> occ;
    ll ans = 0;
    ll r = 0;

    for (ll l = 0; l < n; l++) {
        while (r < n && ((int)occ.size() < k || occ.count(val[r]) > 0)) {
            occ[val[r]]++;
            r++;
        }
        ans += r - l;
        occ[val[l]]--;
        if (occ[val[l]] == 0) {
            occ.erase(val[l]);
        }
    }

    cout << ans << endl;
}
