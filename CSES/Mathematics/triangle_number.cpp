#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int t;
    cin >> t;
    vector<ll> ns(t);
    ll max_n = 0;
    for(int i = 0; i < t; i++) {
        cin >> ns[i];
        max_n = max(max_n, ns[i]);
    }

    // Precompute triangle numbers
    vector<ll> tri;
    for(ll k = 1; ; k++) {
        ll tnum = k*(k+1)/2;
        if(tnum > max_n) break;
        tri.push_back(tnum);
    }
    
    set<ll> tri_set(tri.begin(), tri.end());

    for(int i = 0; i < t; i++) {
        ll n = ns[i];
        if(tri_set.count(n)) {
            cout << 1 << "\n";
            continue;
        }

        bool found = false;
        for(ll x : tri) {
            if(x >= n) break;
            if(tri_set.count(n - x)) {
                found = true;
                break;
            }
        }
        if(found) cout << 2 << "\n";
        else cout << 3 << "\n";  // max 3 needed
    }
    return 0;
}
