#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 200005;
ll tree[4 * MAXN];
ll lazy_a[4 * MAXN]; // Прогрессын тоо
ll lazy_b[4 * MAXN]; // Эхлэлийн тогтмол

// Арифметик прогрессын нийлбэрийг олох томьёо
ll ap_sum(ll a, ll b, ll n) {
    // Нийлбэр = n*a + n*(n-1)/2 * b
    return n * a + n * (n - 1) / 2 * b;
}

void push(int node, int start, int end) {
    if (lazy_a[node] == 0 && lazy_b[node] == 0) return;
    int mid = (start + end) / 2;
    int left_len = mid - start + 1;
    int right_len = end - mid;

    // Зүүн хүү рүү дамжуулах
    lazy_a[2 * node] += lazy_a[node];
    lazy_b[2 * node] += lazy_b[node];
    tree[2 * node] += ap_sum(lazy_b[node], lazy_a[node], left_len);

    // Баруун хүү рүү дамжуулах (Эхлэх утга нь өөрчлөгдөнө)
    ll right_start_b = lazy_b[node] + (ll)left_len * lazy_a[node];
    lazy_a[2 * node + 1] += lazy_a[node];
    lazy_b[2 * node + 1] += right_start_b;
    tree[2 * node + 1] += ap_sum(right_start_b, lazy_a[node], right_len);

    lazy_a[node] = lazy_b[node] = 0;
}

void build(const vector<int>& v, int node, int start, int end) {
    if (start == end) {
        tree[node] = v[start];
        return;
    }
    int mid = (start + end) / 2;
    build(v, 2 * node, start, mid);
    build(v, 2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return;
    if (start >= l && end <= r) {
        ll a = 1;
        ll b = start - l + 1;
        lazy_a[node] += a;
        lazy_b[node] += b;
        tree[node] += ap_sum(b, a, end - start + 1);
        return;
    }
    push(node, start, end);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

ll query(int node, int start, int end, int l, int r) {
    if (start > end || start > r || end < l) return 0;
    if (start >= l && end <= r) return tree[node];
    push(node, start, end);
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];
    build(v, 1, 1, n);
    while (q--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) update(1, 1, n, a, b);
        else cout << query(1, 1, n, a, b) << "\n";
    }
    return 0;
}