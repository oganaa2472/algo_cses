#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct segtree {
    ll size;
    vector<ll> tree;

    ll merge(ll a, ll b) {
        return a + b;
    }

    ll single(int a) {
        return a;
    }

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0LL);
    }

    void build(vector<ll>& a, ll x, ll l, ll r) {
        if (r - l == 1) {
            // if (l < (ll)a.size()) 
            tree[x] = a[l];
            return;
        }
        ll m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<ll>& a) {
        build(a, 0, 0, size);
    }

    ll sum(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, m);
        ll s2 = sum(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    ll sum(ll l, ll r) {
        return sum(l, r, 0, 0, size);
    }

    void set(ll i, ll k, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            tree[x] = k;
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m) {
            set(i, k, 2 * x + 1, lx, m);
        } else {
            set(i, k, 2 * x + 2, m, rx);
        }
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(ll i, ll k) {
        set(i, k, 0, 0, size);
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
            ll left, right;
            cin >> left >> right;
            // Convert to 0-based index
            cout << seg.sum(left - 1, right) << endl;
        } else {
            ll i, k;
            cin >> i >> k;
            // Convert to 0-based index
            seg.set(i - 1, k);
        }
    }
    return 0;
}
