#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    ll x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<ll> window(k);

    ll cur = x;
    ll xr = 0;

    // эхний window
    for (ll i = 0; i < k; i++) {

        if (i == 0)
            cur = x;
        else
            cur = (a * cur + b) % c;

        window[i] = cur;

        xr ^= cur;
    }

    ll ans = xr;

    ll idx = 0;

    // дараагийн window-ууд
    for (ll i = k; i < n; i++) {

        cur = (a * cur + b) % c;

        // хуучин element арилгах
        xr ^= window[idx];

        // шинэ element нэмэх
        xr ^= cur;

        window[idx] = cur;

        idx = (idx + 1) % k;

        ans ^= xr;
    }

    cout << ans << '\n';
}