#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

struct SegmentTree {
    int n;
    vector<ll> tree;
    
    SegmentTree(int size) {
        n = size;
        tree.assign(4*n, 0);
    }
    
    void update(int node, int l, int r, int pos, ll val) {
        if(l == r) {
            tree[node] = (tree[node] + val) % MOD;
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = (tree[2*node] + tree[2*node+1]) % MOD;
    }
    
    ll query(int node, int l, int r, int ql, int qr) {
        if(r < ql || l > qr) return 0;
        if(ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return (query(2*node, l, mid, ql, qr) + query(2*node+1, mid+1, r, ql, qr)) % MOD;
    }
    
    void update(int pos, ll val) {
        update(1, 1, n, pos, val);
    }
    
    ll query(int l, int r) {
        if(l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    
    // Coordinate compression
    vector<ll> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for(int i=0;i<n;i++)
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
    
    SegmentTree seg(vals.size());
    ll ans = 0;
    
    for(int i=0;i<n;i++) {
        ll dp = 1 + seg.query(1, a[i]-1); // sum of smaller numbers
        dp %= MOD;
        seg.update(a[i], dp);
        ans = (ans + dp) % MOD;
    }
    
    cout << ans << endl;
    return 0;
}
