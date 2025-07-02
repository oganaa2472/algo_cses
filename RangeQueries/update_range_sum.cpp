#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
struct segtree {
    ll size;
    vector<ll> tree;
 
    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0LL);
    }
 
    void build(vector<ll>& a, ll x, ll l, ll r) {
        if (r - l == 1) {
            if (l < (ll)a.size()) tree[x] = a[l];
            return;
        }
        ll m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        // tree[x] not needed for range-add + point-query
    }
 
    void build(vector<ll>& a) {
        build(a, 0, 0, size);
    }
 
    void add(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[x] += v;
            return;
        }
        ll m = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, m);
        add(l, r, v, 2 * x + 2, m, rx);
    }
 
    void add(ll l, ll r, ll v) {
        add(l, r, v, 0, 0, size);
    }
 
    ll get(ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1) return tree[x];
        ll m = (lx + rx) / 2;
        ll res;
        if (i < m) res = get(i, 2 * x + 1, lx, m);
        else res = get(i, 2 * x + 2, m, rx);
        return res + tree[x];
    }
 
    ll get(ll i) {
        return get(i, 0, 0, size);
    }
};
 
int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
 
    segtree seg;
    seg.init(n);
    seg.build(a);
 
    while (q--) {
        ll type;
        cin >> type;
        if (type == 2) {
            ll index;
            cin >> index;
            index--; // convert to 0-based
            cout << seg.get(index) << endl;
        } else if (type == 1) {
            ll left, right, val;
            cin >> left >> right >> val;
            left--; // convert to 0-based
            seg.add(left, right, val); // range is [left, right)
        }
    }
 
    return 0;

}
