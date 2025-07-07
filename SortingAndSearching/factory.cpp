#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n, t;
    cin >> n >> t;
    vector<ll> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];

    ll left = 0, right = 1e18;
    while (left < right) {
        ll mid = left+(right-left) / 2;
        ll total = 0;
        for (int i = 0; i < n; i++) {
            total += mid / k[i];
            if (total >= t) break;
        }

        if (total >= t)
            right = mid;
        else
            left = mid + 1;
    }

    cout << left << endl;
    return 0;
}
