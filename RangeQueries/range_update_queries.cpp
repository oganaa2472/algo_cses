#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int MAXN = 200005;

int n, q;
ll BIT[MAXN];
ll base[MAXN];

// Add value to one position in BIT
void add(int idx, ll val) {
    while (idx <= n) {
        BIT[idx] += val;
        idx += idx & -idx;
    }
}

// Query prefix sum up to index
ll query(int idx) {
    ll sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> base[i];
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b;
            ll u;
            cin >> a >> b >> u;
            add(a, u);
            add(b + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << base[k] + query(k) << "\n";
        }
    }
    return 0;
}
