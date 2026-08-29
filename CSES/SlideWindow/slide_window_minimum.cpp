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

    deque<pair<ll,ll>> dq;

    ll cur = x;
    ll ans = 0;

    for (ll i = 0; i < n; i++) {

        // current value
        if (i == 0)
            cur = x;
        else
            cur = (a * cur + b) % c;

        // window-оос гарсан element
        while (!dq.empty() && dq.front().second <= i-k)
            dq.pop_front();

        // monotonic queue
        while (!dq.empty() && dq.back().first >= cur)
            dq.pop_back();
 
        dq.push_back({cur, i});

        // window бүр complete болсон үед
        if (i >= k-1) {
            ans ^= dq.front().first;
        }
    }

    cout << ans << '\n';
}